#include "rustGenerator.h"

RustGenerator::RustGenerator(std::string variableType) {
    this->ifCounter.push(0);
    this->varCounter = 0;
    this->loopLevel = 0;
    this->loopCounter = 0;
    this->varType = variableType;
    currentScope.push(GeneratorScope(0));
    generateIncludes();
    generateGlobalVars();
    generateRandomNumberGenerator();
    generateMainFunction();
}

void RustGenerator::generateIncludes() {
    includes.push_back("#![allow(unused_mut, unused_variables, unused_parens, dead_code, non_snake_case, non_camel_case_types)]");
    includes.push_back("use std::env;");
    includes.push_back("");
    std::vector<std::string> varIncludes = VariableFactory::genIncludes(varType);
    for (auto var : varIncludes) {
        includes.push_back(var);
    }
}

void RustGenerator::generateGlobalVars() {
    std::vector<std::string> varGlobalVars = VariableFactory::genGlobalVars(varType);
    for (auto gVar : varGlobalVars) {
        globalVars.push_back(gVar);
    }
}

void RustGenerator::generateRandomNumberGenerator() {
    GeneratorFunction rngFunction = GeneratorFunction(-1);
    rngFunction.addLine({
        "fn get_path() -> u64 {",
        "    if let Ok(path) = env::var(\"BENCH_PATH\") {",
        "        if let Ok(num) = path.parse::<u64>() {",
        "            return num;",
        "        }",
        "    }",
        "    ((benchgen_rand() as u64) << 32) | (benchgen_rand() as u64)",
        "}",
    });
    functions.push_back(rngFunction);
}

void RustGenerator::generateMainFunction() {
    mainFunction = GeneratorFunction(-1);
    mainFunction.addLine({
        "fn main() {",
        "    let mut loopsFactor: i32 = 100;",
        "    benchgen_srand(0);",
        "    let args: Vec<String> = env::args().collect();",
        "    let mut i = 1usize;",
        "    while i < args.len() {",
        "        match args[i].as_str() {",
        "            \"-path-seed\" => {",
        "                i += 1;",
        "                if i < args.len() {",
        "                    if let Ok(seed) = args[i].parse::<u64>() {",
        "                        benchgen_srand(seed);",
        "                    }",
        "                }",
        "            }",
        "            \"-loops-factor\" => {",
        "                i += 1;",
        "                if i < args.len() {",
        "                    if let Ok(val) = args[i].parse::<i32>() {",
        "                        loopsFactor = val;",
        "                    }",
        "                }",
        "            }",
        "            _ => {}",
        "        }",
        "        i += 1;",
        "    }",
        "    let _ = loopsFactor;",
        "}",
    });
    mainFunction.insertBack = true;
    currentFunction.push(&mainFunction);
    startScope();
}

void RustGenerator::addLine(std::string line, int d) {
    std::string indentedLine = currentScope.top().getIndentationTabs(d) + line;
    currentFunction.top()->addLine(indentedLine);
}

void RustGenerator::addLine(std::vector<std::string> lines, int d) {
    for (auto line : lines) {
        addLine(line, d);
    }
}

void RustGenerator::startScope() {
    GeneratorScope scope = GeneratorScope(currentScope.top().avaiableVarsID, currentScope.top().avaiableParamsID, currentScope.top().getIndentation());
    currentScope.push(scope);
}

void RustGenerator::startFunc(int funcId, int nParameters) {
    GeneratorFunction func = GeneratorFunction(funcId);
    std::string funcHeader = "fn func" + std::to_string(funcId) + "(vars: &mut " +
                             VariableFactory::genTypeString(varType) + "Param, ";

    for (int i = 0; i < nParameters; i++) {
        funcHeader += "PATH" + std::to_string(i) + ": u64, ";
    }
    funcHeader += "loopsFactor: i32";
    funcHeader += ") -> " + VariableFactory::genTypeString(varType) + "Rc {";
    func.addLine(funcHeader);
    functions.push_back(func);
    currentFunction.push(&(functions.back()));
    GeneratorScope scope = GeneratorScope();
    currentScope.push(scope);
    this->ifCounter.push(0);
    addLine("let mut pCounter: usize = vars.data.len();");
    addLine("let _ = pCounter;");
    addLine("let _ = loopsFactor;");
}

bool RustGenerator::functionExists(int funcId) {
    for (auto func : functions) {
        if (func.getId() == funcId) {
            return true;
        }
    }
    return false;
}

std::string RustGenerator::createParams() {
    std::string name = "params" + std::to_string(currentScope.top().addParam());
    std::vector<GeneratorVariable*> varsParams;
    for (int i = 0; i < (int)currentScope.top().avaiableVarsID.size(); i++) {
        varsParams.push_back(variables[currentScope.top().avaiableVarsID[i]]);
    }
    std::vector<std::string> params = VariableFactory::genParams(varType, name, varsParams);
    addLine(params);
    return name;
}

void RustGenerator::callFunc(int funcId, int nParameters) {
    std::string param = createParams();

    int id = addVar(varType);
    GeneratorVariable* var = variables[id];
    std::string line = "let " + var->name + " = func" + std::to_string(funcId) + "(&mut " + param + ", ";

    for (int i = 0; i < nParameters; i++)
        line += "get_path(), ";
    line += "loopsFactor";
    line += ");";
    addLine(line);
}

int RustGenerator::addVar(std::string type) {
    this->variables[varCounter] = VariableFactory::createVariable(type, varCounter);
    this->currentScope.top().addVar(varCounter);
    return varCounter++;
}

void RustGenerator::freeVars(bool hasReturn, int returnVarPos) {
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

void RustGenerator::returnFunc(int returnVarPos) {
    GeneratorVariable* var = variables[currentScope.top().avaiableVarsID[returnVarPos]];
    addLine("return " + var->name + ";");
}

void RustGenerator::endScope() {
    std::string line = currentScope.top().getIndentationTabs(-1) + "}";
    currentFunction.top()->addLine(line);
    currentScope.pop();
}

void RustGenerator::endFunc() {
    endScope();
    currentFunction.pop();
    ifCounter.pop();
}

void RustGenerator::genMakefile(std::string dir, std::string target) {
    std::ofstream makefile;

    makefile.open(dir + "Makefile");
    makefile << "RUSTC = rustc\n";
    makefile << "RUSTFLAGS = -O\n";
    makefile << "TARGET = " + target + "\n";
    makefile << "SRC_DIR = src\n";
    makefile << "SRC = $(SRC_DIR)/$(TARGET).rs\n\n";

    makefile << "all: $(TARGET)\n\n";

    makefile << "$(TARGET): $(SRC)\n";
    makefile << "\t$(RUSTC) $(RUSTFLAGS) $(SRC) -o $(TARGET)\n\n";

    makefile << "clean:\n";
    makefile << "\trm -f $(TARGET)\n";
}

void RustGenerator::genReadme(std::string dir, std::string target) {
    std::ofstream readme;
    readme.open(dir + "README.md");
    readme << "# " + target + " Program (Rust)\n\n";
    readme << "Generated by the **BenchGen** tool.\n\n";
    readme << "## Compilation\n\n";
    readme << "```bash\nmake\n```\n\n";
    readme << "Produces executable `" + target + "`.\n\n";
    readme << "## Run\n\n";
    readme << "```bash\n./" + target + "\n```\n\n";
    readme << "### Optional Arguments\n\n";
    readme << "- `-path-seed <seed>`: seed for the RNG (default 0)\n";
    readme << "- `-loops-factor <factor>`: loops factor (default 100)\n";
}

void RustGenerator::generateFiles(std::string benchmarkName) {
    std::string benchDir = benchmarkName + "/";
    std::string baseName = std::filesystem::path(benchmarkName).filename().string();
    std::string sourceFile = baseName + ".rs";
    std::string sourceDir = benchDir + "src/";

    std::filesystem::create_directory(benchDir);
    std::filesystem::create_directory(sourceDir);

    std::ofstream file;
    file.open(sourceDir + sourceFile);

    for (auto& inc : includes) {
        file << inc << "\n";
    }
    file << "\n";

    for (auto& gvar : globalVars) {
        file << gvar << "\n";
    }
    file << "\n";

    file << "thread_local! { pub static BENCHGEN_STATE: std::cell::Cell<u64> = std::cell::Cell::new(1); }\n";
    file << "pub fn benchgen_srand(seed: u64) { BENCHGEN_STATE.with(|s| s.set(seed)); }\n";
    file << "pub fn benchgen_rand() -> u32 {\n";
    file << "    BENCHGEN_STATE.with(|s| {\n";
    file << "        let new_state = s.get().wrapping_mul(6364136223846793005u64).wrapping_add(1);\n";
    file << "        s.set(new_state);\n";
    file << "        (new_state >> 32) as u32\n";
    file << "    })\n";
    file << "}\n\n";

    for (auto& func : functions) {
        for (auto& line : func.getLines()) {
            file << line << "\n";
        }
        file << "\n";
    }

    for (auto& line : mainFunction.getLines()) {
        file << line << "\n";
    }

    genMakefile(benchDir, baseName);
    genReadme(benchDir, baseName);
    file.close();
}
