#include "cGenerator.h"
#include "../../ast/c/cAst.h"

void CGenerator::generateIncludes() {
    includes.push_back("#include <stdio.h>");
    includes.push_back("#include <stdlib.h>");
    includes.push_back("#include <string.h>");
    includes.push_back("#ifdef DEBUG");
    includes.push_back("    #define DEBUG_NEW(id) printf(\"[NEW]\\t\\tId \%d created\\n\", id)");
    includes.push_back("    #define DEBUG_COPY(id) printf(\"[COPY]\\t\\tId \%d copied\\n\", id)");
    includes.push_back("    #define DEBUG_RETURN(id) printf(\"[RETURN]\\tId \%d returned\\n\", id)");
    includes.push_back("    #define DEBUG_FREE(id) printf(\"[FREE]\\t\\tId \%d freed\\n\", id)");
    includes.push_back("#else");
    includes.push_back("    #define DEBUG_NEW(id)");
    includes.push_back("    #define DEBUG_COPY(id)");
    includes.push_back("    #define DEBUG_RETURN(id)");
    includes.push_back("    #define DEBUG_FREE(id)");
    includes.push_back("#endif");
    includes.push_back("#ifdef COUNT");
    includes.push_back("    #define COUNT_INSERT() printf(\"insert\\n\")");
    includes.push_back("    #define COUNT_REMOVE() printf(\"remove\\n\")");
    includes.push_back("    #define COUNT_CONTAINS() printf(\"contains\\n\")");
    includes.push_back("#else");
    includes.push_back("    #define COUNT_INSERT()");
    includes.push_back("    #define COUNT_REMOVE()");
    includes.push_back("    #define COUNT_CONTAINS()");
    includes.push_back("#endif");
    std::vector<std::string> varIncludes = VariableFactory::genIncludes(varType);
    for (auto var : varIncludes) {
        globalVars.push_back(var);
    }
}

void CGenerator::generateGlobalVars() {
    std::vector<std::string> varGlobalVars = VariableFactory::genGlobalVars(varType);
    for (auto gVar : varGlobalVars) {
        globalVars.push_back(gVar);
    }
}

void CGenerator::generateRandomNumberGenerator() {
    GeneratorFunction rngFunction = GeneratorFunction(-1);
        rngFunction.addLine({
    "unsigned long get_path() {",
    "    const char* path = getenv(\"BENCH_PATH\");",
    "    if (path != NULL) {",
    "        return (unsigned long)atoi(path);",
    "    } else {",
    "        unsigned long hi = benchgen_rand();",
    "        unsigned long lo = benchgen_rand();",
    "        return (hi << 32) | lo;",
    "    }",
    "}"
    });

    
    functions.push_back(rngFunction);
}

void CGenerator::generateMainFunction() {
    mainFunction = GeneratorFunction(-1);
    mainFunction.addLine({
    "static unsigned long benchgen_state = 1;",
    "",
    "void benchgen_srand(unsigned long seed) {",
    "    benchgen_state = seed;",
    "}",
    "",
    "unsigned long benchgen_rand(void) {",
    "    benchgen_state = 6364136223846793005ULL * benchgen_state + 1ULL;",
    "    return benchgen_state >> 32;",
    "}",
    ""
    });
    mainFunction.addLine({"int main(int argc, char** argv) {",
                          "   int loopsFactor = 100;",
                          "   benchgen_srand(0);",
                          "   for (int i = 1; i < argc; i++) {",
                          "      if (strcmp(argv[i], \"-path-seed\") == 0) {",
                          "         i++;",
                          "         if (i < argc) {",
                          "            benchgen_srand(atoi(argv[i]));",
                          "         }",
                          "      }",
                          "      else if (strcmp(argv[i], \"-loops-factor\") == 0) {",
                          "         i++;",
                          "         if (i < argc) {",
                          "            loopsFactor = atoi(argv[i]);",
                          "         }",
                          "      }",
                          "   }",
                          "   return 0;",
                          "}"});
    mainFunction.insertBack = true;
    currentFunction.push(&mainFunction);
    startScope();
}

void CGenerator::addLine(std::string line, int d) {
    std::string indentedLine = currentScope.top().getIndentationTabs(d) + line;
    currentFunction.top()->addLine(indentedLine);
}

void CGenerator::addLine(std::vector<std::string> lines, int d) {
    for (auto line : lines) {
        addLine(line, d);
    }
}

void CGenerator::startScope() {
    GeneratorScope scope = GeneratorScope(currentScope.top().avaiableVarsID, currentScope.top().avaiableParamsID, currentScope.top().getIndentation());
    currentScope.push(scope);
}

void CGenerator::startFunc(int funcId, int nParameters) {

    path_stack_init();
    GeneratorFunction func = GeneratorFunction(funcId);
    std::string funcHeader = VariableFactory::genTypeString(varType) + "* func" + std::to_string(funcId) + "(" + VariableFactory::genTypeString(varType) + "_param* vars, ";
    
    for (int i = 0; i < nParameters; i++) {
        funcHeader += "const unsigned long PATH" + std::to_string(i) + ", ";
    }
    funcHeader += "int loopsFactor";
    funcHeader += ") {";
    func.addLine(funcHeader);
    functions.push_back(func);
    currentFunction.push(&(functions.back()));
    GeneratorScope scope = GeneratorScope();
    currentScope.push(scope);
    this->ifCounter.push(0);
    addLine("size_t pCounter = vars->size;");
}

bool CGenerator::functionExists(int funcId) {
    for (auto func : functions) {
        if (func.getId() == funcId) {
            return true;
        }
    }
    return false;
}

std::string CGenerator::createParams() {
    std::string name = "params" + std::to_string(currentScope.top().addParam());
    std::vector<GeneratorVariable*> varsParams;
    for (int i = 0; i < (int)currentScope.top().avaiableVarsID.size(); i++) {
        varsParams.push_back(variables[currentScope.top().avaiableVarsID[i]]);
    }
    std::vector<std::string> params = VariableFactory::genParams(varType, name, varsParams);
    addLine(params);
    return name;
}

void CGenerator::callFunc(int funcId, int nParameters) {
    std::string param = "";
    param = createParams();

    int id = addVar(varType);
    GeneratorVariable* var = variables[id];
    std::string line = var->typeString + "* " + var->name + " = func" + std::to_string(funcId) + "(&" + param + ", ";

    for (int i = 0; i < nParameters; i++)
        line += "get_path(), ";
    line += "loopsFactor";
    line += ");";
    addLine(line);

    line = "DEBUG_RETURN(" + var->name + "->id);";
    addLine(line);

    line = "free(" + param + ".data);";
    addLine(line);
}

int CGenerator::addVar(std::string type) {
    this->variables[varCounter] = VariableFactory::createVariable(type, varCounter);
    this->currentScope.top().addVar(varCounter);
    return varCounter++;
}

void CGenerator::freeVars(bool hasReturn, int returnVarPos) {

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

void CGenerator::returnFunc(int returnVarPos) {
    GeneratorVariable* var = variables[currentScope.top().avaiableVarsID[returnVarPos]];
    addLine("return " + var->name + ";");
}

void CGenerator::endScope() {
    std::string line = currentScope.top().getIndentationTabs(-1) + "}";
    currentFunction.top()->addLine(line);
    currentScope.pop();
}

void CGenerator::endFunc() {
    endScope();
    currentFunction.pop();
    ifCounter.pop();
}

void CGenerator::genMakefile(std::filesystem::path dir, std::string target) {
    std::ofstream makefile;

    makefile.open(dir/"Makefile");
    makefile << "CC = clang\n";
    makefile << "LLVMFLAGS = -DDEBUG -S -emit-llvm\n";
    makefile << "TARGET = " + target + "\n";
    makefile << "SRC_DIR = src\n";
    makefile << "OBJ_DIR = obj\n";
    makefile << "LL_DIR = ll\n";
    makefile << "GLIB_CFLAGS = $(shell pkg-config --cflags glib-2.0)\n";
    makefile << "GLIB_LIBS = $(shell pkg-config --libs glib-2.0)\n\n";

    makefile << "SRC = $(wildcard $(SRC_DIR)/*.c)\n";
    makefile << "OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))\n";
    makefile << "LL = $(patsubst $(SRC_DIR)/%.c, $(LL_DIR)/%.ll, $(SRC))\n\n";

    makefile << "all: $(TARGET)\n\n";

    makefile << "$(TARGET): $(OBJ)\n";
  
    makefile << "\t$(CC) ${CFLAGS} $(OBJ) -o $(TARGET) $(GLIB_LIBS)\n\n";

    makefile << "$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)\n";
    makefile << "\t$(CC) ${CFLAGS} $(GLIB_CFLAGS) -c $< -o $@\n\n";

    makefile << "$(LL_DIR)/%.ll: $(SRC_DIR)/%.c | $(LL_DIR)\n";
    makefile << "\t$(CC) ${LLVMFLAGS} $< -o $@\n\n";

    makefile << "$(OBJ_DIR) $(LL_DIR):\n";
    makefile << "\tmkdir -p $@\n\n";

    makefile << "llvm: $(LL)\n";
    makefile << "\t$(CC) ./ll/*.ll -o llvm_${TARGET}\n\n";

    makefile << "clean:\n";
    makefile << "\trm -f $(OBJ) $(LL) $(TARGET) llvm_${TARGET}\n";
    makefile << "\trm -rf $(OBJ_DIR) $(LL_DIR)\n\n";
}

void CGenerator::genReadme(std::filesystem::path dir, std::string target) {
    std::ofstream readme;
    readme.open(dir/"README.md");
    readme << "# " + target + " Program\n\n";
    readme << "This program was generated by the **BenchGen** tool.\n\n";

    readme << "## Compilation\n\n";
    readme << "There are two ways to compile the program:\n\n";
    readme << "1. Standard Compilation:\n\n";
    readme << "    ```bash\n";
    readme << "    make\n";
    readme << "    ```\n\n";
    readme << "    This will create:\n\n";
    readme << "    - The executable file `" + target + "`\n\n";
    readme << "    - The object files in the `obj` directory\n\n";
    readme << "2. LLVM Compilation:\n\n";
    readme << "    ```bash\n";
    readme << "    make llvm\n";
    readme << "    ```\n\n";
    readme << "    This will create and `ll` folder containing `.ll` files, which are LLVM IR (Intermediate Representation).\n\n";

    readme << "### Compiling with debug mode:\n\n";
    readme << "If you want to include debug prints in the output, compile the program with the `-DDEBUG` flag by modifying the `CFLAGS` during the `make` command:\n\n";
    readme << "```bash\n";
    readme << "make CFLAGS=\"-DDEBUG\"\n";
    readme << "```\n\n";
    readme << "This will create an executable with debug mode enabled, which prints additional debugging information to the terminal during execution.\n\n";

    readme << "## Run\n\n";
    readme << "To run the program, execute the following command:\n\n";
    readme << "```bash\n";
    readme << "./" + target + "\n";
    readme << "```\n\n";

    readme << "### Optional Arguments\n\n";
    readme << "This program accepts the following optional arguments:\n\n";
    readme << "-   `-path-seed <seed>`: Sets the seed for the random number generator. Default is `0`.\n\n";
    readme << "-   `-loops-factor <factor>`: Sets the factor for the number of loops. Default is `100`.\n\n";

    readme << "#### Example:\n\n";
    readme << "```bash\n";
    readme << "./" + target + " -loops-factor 50 -path-seed 123\n";
    readme << "```";
}

void CGenerator::generateFiles(std::string benchmarkName) {
    std::filesystem::path benchDir = benchmarkName;
    std::filesystem::path sourceDir = benchDir / "src";

    std::string benchName = benchDir.filename().string();
    if (!benchDir.has_filename())
        benchName = benchDir.parent_path().filename().string();

    std::string sourceFile = benchName + ".c";
    std::string includeName = benchName + ".h";

    std::filesystem::create_directories(benchDir);
    std::filesystem::create_directories(sourceDir);

    std::ofstream file;
    file.open(sourceDir/sourceFile);

    std::ofstream includeFile;
    includeFile.open(sourceDir/includeName);

    // Includes
    includeFile << "#ifndef " + benchName + "\n";
    includeFile << "#define " + benchName + "\n";

    for (auto include : includes) {
        includeFile << include << std::endl;
    }
    file << "#include \"" << includeName << "\"";
    file << std::endl;

    // Global variables
    for (auto var : globalVars) {
        includeFile << var << std::endl;
    }
    includeFile << std::endl;

    // Headers
    includeFile << "void benchgen_srand(unsigned long seed);\n";
    includeFile << "unsigned long benchgen_rand(void);\n";

    
    for (auto func : functions) {
        std::string header = func.getLines()[0];
        header.pop_back();
        header.pop_back();
        header += ";";
        includeFile << header << std::endl;
    }
    file << std::endl;

    // Main function
    auto lines = mainFunction.getLines();
    for (auto line : lines) {
        file << line << std::endl;
    }
    file << std::endl;

    // Functions
    for (auto func : functions) {
        std::string funcSource;
        if (func.getId() == -1) {
            funcSource = "path.c";
        } else {
            funcSource = "func" + std::to_string(func.getId()) + ".c";
        }
        std::ofstream funcFile;
        funcFile.open(sourceDir/funcSource);
        funcFile << "#include \"" << includeName << "\" \n";

        lines = func.getLines();
        for (auto line : lines) {
            funcFile << line << std::endl;
        }
        funcFile << std::endl;
        funcFile.close();
    }
    includeFile << "#endif";
    this->genMakefile(benchDir, benchName);
    this->genReadme(benchDir, benchName);
    includeFile.close();
    file.close();
}
