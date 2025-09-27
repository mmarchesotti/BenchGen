#include "vGenerator.h"

void VGenerator::generateModules() {
    modules.push_back("import os");
    modules.push_back("import rand");
    modules.push_back("import strconv");
    
    std::vector<std::string> varIncludes = VariableFactory::genIncludes(varType);
    for (auto var : varIncludes) {
        modules.push_back(var);
    }
}

void VGenerator::generateGlobalVars() {
    std::vector<std::string> varGlobalVars = VariableFactory::genGlobalVars(varType);
    for (auto gVar : varGlobalVars) {
        globalVars.push_back(gVar);
    }
}

void VGenerator::generateRandomNumberGenerator() {
    GeneratorFunction rngFunction = GeneratorFunction(-1);
    rngFunction.addLine({
        "fn get_path() u64 {",
        "    path := os.getenv('BENCH_PATH')",
        "    if path != '' {",
        "        val := strconv.parse_u64(path, 10) or { return 0 }",
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
        "    mut path_seed := 0",
        "",
        "    args := os.args",
        "    for i := 1; i < args.len; i++ {",
        "        match args[i] {",
        "            '-path-seed' {",
        "                i++",
        "                if i < args.len {",
        "                    path_seed = args[i].int()",
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
        "    rand.seed(path_seed.bytes())",
        "}"
    });
    mainFunction.insertBack = true;
    currentFunction.push(&mainFunction);
    startScope();
}

void VGenerator::addLine(std::string line, int d) {
    std::string indentedLine = currentScope.top().getIndentationTabs(d) + line;
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
    std::string funcHeader = "fn func" + std::to_string(funcId) + "(vars " + VariableFactory::genTypeString(varType) + "Param, ";
    
    for (int i = 0; i < nParameters; i++) {
        funcHeader += "PATH" + std::to_string(i) + " u64, ";
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
    std::string line = "mut " + var->name + " := func" + std::to_string(funcId) + "(" + param + ", ";

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
    std::ofstream makefile;
    makefile.open(dir + "Makefile");
    makefile << "TARGET = " + target + "\n";
    makefile << "SRC_DIR = src\n\n";
    makefile << "all: $(TARGET)\n\n";
    makefile << "$(TARGET):\n";
    makefile << "\tv $(SRC_DIR) -o $(TARGET)\n\n";
    makefile << "run:\n";
    makefile << "\tv run $(SRC_DIR)\n\n";
    makefile << "clean:\n";
    makefile << "\trm -f $(TARGET)\n";
}

void VGenerator::genReadme(std::string dir, std::string target) {
    std::ofstream readme;
    readme.open(dir + "README.md");
    readme << "# " + target + " Program\n\n";
    readme << "This program was generated by the **BenchGen** tool.\n\n";
    readme << "## Compilation\n\n";
    readme << "To compile the program:\n\n";
    readme << "    ```bash\n";
    readme << "    make\n";
    readme << "    ```\n\n";
    readme << "## Run\n\n";
    readme << "To run the program, execute the following command:\n\n";
    readme << "```bash\n";
    readme << "./" + target + "\n";
    readme << "```\n\n";
    readme << "### Optional Arguments\n\n";
    readme << "-   `-path-seed <seed>`: Sets the seed for the random number generator. Default is `0`.\n\n";
    readme << "-   `-loops-factor <factor>`: Sets the factor for the number of loops. Default is `100`.\n\n";
    readme << "#### Example:\n\n";
    readme << "```bash\n";
    readme << "./" + target + " -loops-factor 50 -path-seed 123\n";
    readme << "```";
}

void VGenerator::generateFiles(std::string benchmarkName) {
    std::string benchDir = benchmarkName + "/";
    std::string mainFile = benchmarkName + ".v";
    std::string sourceDir = benchDir + "src/";

    std::filesystem::create_directory(benchDir);
    std::filesystem::create_directory(sourceDir);

    std::ofstream file;
    file.open(sourceDir + mainFile);
    file << "module main\n\n";

    for (auto mod : modules) {
        file << mod << std::endl;
    }
    file << std::endl;

    for (auto var : globalVars) {
        file << var << std::endl;
    }
    file << std::endl;

    for (auto func : functions) {
        auto lines = func.getLines();
        for (auto line : lines) {
            file << line << std::endl;
        }
        file << std::endl;
    }
    
    auto mainLines = mainFunction.getLines();
    for (auto line : mainLines) {
        file << line << std::endl;
    }
    
    this->genMakefile(benchDir, benchmarkName);
    this->genReadme(benchDir, benchmarkName);
    file.close();
}