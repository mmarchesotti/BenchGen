#include "vGenerator.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

void VGenerator::generateModules() {
    modules.push_back("import os");
    modules.push_back("import rand");
    
    std::vector<std::string> varIncludes = VariableFactory::genIncludes(varType);
    for (auto var : varIncludes) {
        modules.push_back(var);
    }
}

void VGenerator::generateGlobalVars() {
    std::vector<std::string> varGlobalVars = VariableFactory::genGlobalVars(varType);
    bool in_struct = false;

    for (const auto& line : varGlobalVars) {
        size_t first_char_pos = line.find_first_not_of(" \t");
        std::string content = (first_char_pos == std::string::npos) ? "" : line.substr(first_char_pos);
        std::string indentation = (first_char_pos == std::string::npos) ? "" : line.substr(0, first_char_pos);

        if (content.rfind("struct ", 0) == 0) {
            globalVars.push_back(indentation + "pub " + content);
            globalVars.push_back(indentation + "\tpub mut:");
            in_struct = true;
        } else if (in_struct) {
            if (content.rfind("}", 0) == 0) {
                globalVars.push_back(line);
                in_struct = false;
            } else if (content != "mut:") {
                globalVars.push_back(line);
            }
        } else {
            globalVars.push_back(line);
        }
    }
}

void VGenerator::generateRandomNumberGenerator() {
    GeneratorFunction rngFunction = GeneratorFunction(-1);
    rngFunction.addLine({
        "pub fn get_path() u64 {",
        "    path := os.getenv('BENCH_PATH')",
        "    if path != '' {",
        "        val := strconv.parse_uint(path, 10, 64) or { return 0 }",
        "        return val",
        "    }",
        "    n := u64(rand.u32())",
        "    return (n << 32) | u64(rand.u32())",
        "}",
    });
    functions.push_back(rngFunction);
}

void VGenerator::generateMainFunction() {
    mainFunction = GeneratorFunction(-1);
    mainFunction.addLine({
        "fn main() {",
        "    mut loops_factor := 100",
        "    mut path_seed := u64(0)",
        "",
        "    args := os.args",
        "    for i := 1; i < args.len; i++ {",
        "        match args[i] {",
        "            '-path-seed' {",
        "                i++",
        "                if i < args.len {",
        "                    path_seed = args[i].u64()",
        "                }",
        "            }",
        "            '-loops-factor' {",
        "                i++",
        "                if i < args.len {",
        "                    loops_factor = args[i].int()",
        "                }",
        "            }",
        "            else {}",
        "        }",
        "    }",
        "    rand.seed([u32(path_seed), u32(path_seed >> 32)])",
        "}"
    });
    mainFunction.insertBack = true;
    currentFunction.push(&mainFunction);
    startScope();
}

void VGenerator::addLine(std::string line, int d) {
    std::string indentedLine = currentScope.top().getIndentationTabs(d) + line;

    // WORKAROUND for V compiler's strictness with type aliases in slice literals.
    std::string find_str = "[]" + VariableFactory::genTypeString(varType) + "{";
    std::string replace_str = "[]functions." + VariableFactory::genTypeString(varType) + "{";
    size_t pos = indentedLine.find(find_str);
    if (pos != std::string::npos) {
        indentedLine.replace(pos, find_str.length(), replace_str);
    }
    
    currentFunction.top()->addLine(indentedLine);
}

void VGenerator::addLine(std::vector<std::string> lines, int d) {
    for (auto line : lines) {
        addLine(line, d);
    }
}

void VGenerator::startScope() {
    GeneratorScope scope = GeneratorScope(currentScope.top().avaiableVarsID, currentScope.top().avaiableParamsID, currentScope.top().getIndentation());
    currentScope.push(scope);
}

void VGenerator::startFunc(int funcId, int nParameters) {
    GeneratorFunction func = GeneratorFunction(funcId);
    // Functions must be public (`pub`) to be visible from other modules.
    std::string funcHeader = "pub fn func" + std::to_string(funcId) + "(vars " + VariableFactory::genTypeString(varType) + "Param, ";
    
    for (int i = 0; i < nParameters; i++) {
        funcHeader += "path" + std::to_string(i) + " u64, ";
    }
    funcHeader += "loops_factor int) " + VariableFactory::genTypeString(varType) + " {";
    func.addLine(funcHeader);
    functions.push_back(func);
    currentFunction.push(&(functions.back()));
    GeneratorScope scope = GeneratorScope();
    currentScope.push(scope);
    this->ifCounter.push(0);
    addLine("mut p_counter := vars.size");
}

bool VGenerator::functionExists(int funcId) {
    for (auto func : functions) {
        if (func.getId() == funcId) {
            return true;
        }
    }
    return false;
}

std::string VGenerator::createParams() {
    std::string name = "params" + std::to_string(currentScope.top().addParam());
    std::vector<GeneratorVariable*> varsParams;
    for (int i = 0; i < (int)currentScope.top().avaiableVarsID.size(); i++) {
        varsParams.push_back(variables[currentScope.top().avaiableVarsID[i]]);
    }
    std::vector<std::string> params = VariableFactory::genParams(varType, name, varsParams);
    addLine(params);
    return name;
}

void VGenerator::callFunc(int funcId, int nParameters) {
    std::string param = createParams();
    int id = addVar(varType);
    GeneratorVariable* var = variables[id];
    
    std::string func_call = "func" + std::to_string(funcId);
    // If the call is being made from `main` (id -1), prefix with the module name.
    if (currentFunction.top()->getId() == -1) {
        func_call = "functions." + func_call;
    }

    std::string line = "mut " + var->name + " := " + func_call + "(" + param + ", ";

    for (int i = 0; i < nParameters; i++)
        line += "get_path(), ";
    line += "loops_factor";
    line += ")";
    addLine(line);
}

int VGenerator::addVar(std::string type) {
    this->variables[varCounter] = VariableFactory::createVariable(type, varCounter);
    this->currentScope.top().addVar(varCounter);
    return varCounter++;
}

void VGenerator::freeVars(bool hasReturn, int returnVarPos) {
    int numberOfAddedVars = currentScope.top().numberOfAddedVars;
    std::vector<int> availableVarsId = currentScope.top().avaiableVarsID;
    for (int i = 0; i < numberOfAddedVars; i++) {
        int varPos = availableVarsId.size() - i - 1;
        if (!hasReturn || varPos != returnVarPos) {
            GeneratorVariable* var = variables[availableVarsId[varPos]];
            addLine(var->free());
        }
    }
}

void VGenerator::returnFunc(int returnVarPos) {
    GeneratorVariable* var = variables[currentScope.top().avaiableVarsID[returnVarPos]];
    addLine("return " + var->name);
}

void VGenerator::endScope() {
    std::string line = currentScope.top().getIndentationTabs(-1) + "}";
    currentFunction.top()->addLine(line);
    currentScope.pop();
}

void VGenerator::endIfScope() {
    currentScope.pop();
}

void VGenerator::endFunc() {
    endScope();
    currentFunction.pop();
    ifCounter.pop();
}

void VGenerator::genMakefile(std::string dir, std::string target) {
    std::string correct_target = std::filesystem::path(target).filename().string();
    std::ofstream makefile;
    makefile.open(dir + "/Makefile");
    makefile << "TARGET = " << correct_target << "\n";
    makefile << "MAIN_MODULE = src/main\n\n";
    makefile << "all: $(TARGET)\n\n";
    makefile << "$(TARGET):\n";
    makefile << "\tv $(MAIN_MODULE) -o $(TARGET)\n\n";
    makefile << "run:\n";
    makefile << "\tv run $(MAIN_MODULE)\n\n";
    makefile << "clean:\n";
    makefile << "\trm -f $(TARGET)\n";
    makefile.close();
}

void VGenerator::genReadme(std::string dir, std::string target) {
    std::string correct_target = std::filesystem::path(target).filename().string();
    std::ofstream readmeFile;
    readmeFile.open(dir + "/README.md");
    readmeFile << "# Benchmark: " << correct_target << "\n\n";
    readmeFile << "This benchmark was auto-generated.\n\n";
    readmeFile << "To compile and run:\n";
    readmeFile << "```sh\n";
    readmeFile << "make\n";
    readmeFile << "./" << correct_target << "\n";
    readmeFile << "```\n";
    readmeFile.close();
}

void VGenerator::generateFiles(std::string benchmarkName) {
	std::string benchDir = benchmarkName + "/";
    std::string mainDir = benchDir + "src/main/";
    std::string functionsDir = benchDir + "src/functions/";

    std::filesystem::create_directories(mainDir);
    std::filesystem::create_directories(functionsDir);

    std::ofstream mainFile;
    mainFile.open(mainDir + "main.v");
    mainFile << "module main\n\n";
    mainFile << "import functions\n";

    for (auto mod : modules) {
        mainFile << mod << std::endl;
    }
    mainFile << std::endl;

    mainFile << "type " << VariableFactory::genTypeString(varType)
             << " = functions." << VariableFactory::genTypeString(varType) << "\n";
    mainFile << "type " << VariableFactory::genTypeString(varType) + "Param"
             << " = functions." << VariableFactory::genTypeString(varType) + "Param" << "\n\n";
    
    mainFile << "fn get_path() u64 { return functions.get_path() }\n\n";

    auto mainLines = mainFunction.getLines();
    for (auto line : mainLines) {
        mainFile << line << std::endl;
    }
    mainFile.close();

    if (!globalVars.empty()) {
        std::ofstream typesFile;
        typesFile.open(functionsDir + "types.v");
        typesFile << "module functions\n\n";
        for (auto var : globalVars) {
            typesFile << var << std::endl;
        }
        typesFile.close();
    }

    for (auto func : functions) {
        std::string funcFileName;
        bool is_path_func = (func.getId() == -1);

        if (is_path_func) {
            funcFileName = "path.v";
        } else {
            funcFileName = "func" + std::to_string(func.getId()) + ".v";
        }

        std::ofstream funcFile;
        funcFile.open(functionsDir + funcFileName);
        funcFile << "module functions\n\n";
        funcFile << "import os\n";
        funcFile << "import rand\n";
        // Only add 'strconv' to the file that actually uses it.
        if (is_path_func) {
            funcFile << "import strconv\n";
        }
        funcFile << "\n";

        auto funcLines = func.getLines();
        for (auto line : funcLines) {
            funcFile << line << std::endl;
        }
        funcFile.close();
    }

    this->genMakefile(benchDir, benchmarkName);
    this->genReadme(benchDir, benchmarkName);
}


