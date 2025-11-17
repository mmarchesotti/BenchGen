#include "odinGenerator.h"

#include <string>
#include <vector>

void OdinGenerator::generateIncludes() {
  libIncludes.push_back("package main");
  libIncludes.push_back("");
  libIncludes.push_back("import \"core:fmt\"");
  libIncludes.push_back("import \"core:os\"");
  libIncludes.push_back("import \"core:mem\"");
  libIncludes.push_back("import \"base:runtime\"");
  libIncludes.push_back("import \"core:strconv\"");
  libIncludes.push_back("import \"core:math/rand\"");

  std::vector<std::string> varIncludes = VariableFactory::genIncludes(varType);
  for (auto var : varIncludes) {
    libIncludes.push_back(var);
  }
}

void OdinGenerator::generateGlobalVars() {
  std::vector<std::string> varGlobalVars =
      VariableFactory::genGlobalVars(varType);
  for (auto gVar : varGlobalVars) {
    libGlobalVars.push_back(gVar);
  }
}

void OdinGenerator::generateRandomNumberGenerator() {
  GeneratorFunction rngFunction = GeneratorFunction(-1);
  rngFunction.addLine(
      {"get_path :: proc() -> u64 {",
       "    path := os.get_env(\"BENCH_PATH\");",
       "    if val, ok := strconv.parse_u64(path, 10); ok {",
       "        return val;", "        }",
       "    return rand.uint64();", "}"});
  functions.push_back(rngFunction);
}

void OdinGenerator::generateMainFunction() {
  mainFunction = GeneratorFunction(-1);
  mainFunction.addLine(
      {"main :: proc() {",
       "", "    path_seed: u64 = 0;", "",
       "    for arg, i in os.args {", "        if i == 0 { continue; }",
       "        if arg == \"-path-seed\" && i + 1 < len(os.args) {",
       "            if val, ok := strconv.parse_u64(os.args[i+1], 10); ok {",
       "                path_seed = val;", "            }", "        }", "    }",
       "    random_state := rand.create(path_seed)",
       "    context.random_generator = runtime.default_random_generator(&random_state)",
       "}"});
  mainFunction.insertBack = true;
  currentFunction.push(&mainFunction);
  startScope();
}

void OdinGenerator::addLine(std::string line, int d) {
  std::string indentedLine = currentScope.top().getIndentationTabs(d) + line;
  currentFunction.top()->addLine(indentedLine);
}

void OdinGenerator::addLine(std::vector<std::string> lines, int d) {
  for (auto line : lines) {
    addLine(line, d);
  }
}

void OdinGenerator::startScope() {
  GeneratorScope scope = GeneratorScope(currentScope.top().avaiableVarsID,
                                        currentScope.top().avaiableParamsID,
                                        currentScope.top().getIndentation());
  currentScope.push(scope);
}

void OdinGenerator::startFunc(int funcId, int nParameters) {
  GeneratorFunction func = GeneratorFunction(funcId);

  std::string typeString = VariableFactory::genTypeString(varType);
  std::string funcHeader = "func" + std::to_string(funcId) + " :: proc(vars: ^" +
                           typeString + "Param";

  if (nParameters > 0) {
    funcHeader += ", ";
    for (int i = 0; i < nParameters; i++) {
      funcHeader += "_path" + std::to_string(i) + ": u64, ";
    }
    funcHeader.pop_back();
    funcHeader.pop_back();
  }
  funcHeader += ") -> ^" + typeString + " {";

  func.addLine(funcHeader);

  functions.push_back(func);
  currentFunction.push(&(functions.back()));
  GeneratorScope scope = GeneratorScope();
  currentScope.push(scope);
  this->ifCounter.push(0);
  addLine("pCounter := vars.size;");

  for (int i = 0; i < nParameters; i++) {
    addLine("path" + std::to_string(i) + " := _path" + std::to_string(i) +
            ";");
  }
}

bool OdinGenerator::functionExists(int funcId) {
  for (auto& func : functions) {
    if (func.getId() == funcId) {
      return true;
    }
  }
  return false;
}

std::string OdinGenerator::createParams() {
  std::string name = "params" + std::to_string(currentScope.top().addParam());
  std::vector<GeneratorVariable*> varsParams;
  for (int i = 0; i < (int)currentScope.top().avaiableVarsID.size(); i++) {
    varsParams.push_back(variables[currentScope.top().avaiableVarsID[i]]);
  }
  std::vector<std::string> params =
      VariableFactory::genParams(varType, name, varsParams);
  addLine(params);
  return name;
}

void OdinGenerator::callFunc(int funcId, int nParameters) {
  std::string param = createParams();
  int id = addVar(varType);
  GeneratorVariable* var = variables[id];

  std::string line = var->name + " := func" +
                     std::to_string(funcId) + "(&" + param;
  if (nParameters > 0) {
    line += ", ";
    for (int i = 0; i < nParameters; i++) {
      line += "get_path(), ";
    }
    line.pop_back();
    line.pop_back();
  }
  line += ");";
  addLine(line);

  addLine("defer delete(" + param + ".data);");
}

int OdinGenerator::addVar(std::string type) {
  this->variables[varCounter] =
      VariableFactory::createVariable(type, varCounter);
  this->currentScope.top().addVar(varCounter);
  return varCounter++;
}

void OdinGenerator::freeVars(bool hasReturn, int returnVarPos) {
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

void OdinGenerator::returnFunc(int returnVarPos) {
  GeneratorVariable* var =
      variables[currentScope.top().avaiableVarsID[returnVarPos]];
  addLine("return " + var->name + ";");
}

void OdinGenerator::endScope() {
  std::string line = currentScope.top().getIndentationTabs(-1) + "}";
  currentFunction.top()->addLine(line);
  currentScope.pop();
}

void OdinGenerator::endIfScope() {
  std::string line = currentScope.top().getIndentationTabs(-1) + "";
  currentFunction.top()->addLine(line);
  currentScope.pop();
}

void OdinGenerator::endFunc() {
  endScope();
  currentFunction.pop();
  ifCounter.pop();
}

void OdinGenerator::genBuildScript(std::string dir, std::string target) {
  std::ofstream buildFile;
  buildFile.open(dir + "build.sh");
  buildFile << "#!/bin/bash\n";
  buildFile << "odin build ./src -out:" + target + " -o:speed\n";
  buildFile << "if [ $? -eq 0 ]; then\n";
  buildFile << "  echo \"Build successful!\"\n";
  buildFile << "else\n";
  buildFile << "  echo \"Build failed!\"\n";
  buildFile << "fi\n";
  buildFile.close();

  std::filesystem::permissions(dir + "build.sh",
                               std::filesystem::perms::owner_all |
                               std::filesystem::perms::group_read |
                               std::filesystem::perms::others_read,
                               std::filesystem::perm_options::add);

  std::ofstream runFile;
  runFile.open(dir + "run.sh");
  runFile << "#!/bin/bash\n";
  runFile << "./" + target + " $*\n";
  runFile.close();

  std::filesystem::permissions(dir + "run.sh",
                               std::filesystem::perms::owner_all |
                               std::filesystem::perms::group_read |
                               std::filesystem::perms::others_read,
                               std::filesystem::perm_options::add);
}

void OdinGenerator::genReadme(std::string dir, std::string target) {
  std::ofstream readme;
  readme.open(dir + "README.md");
  readme << "# " + target + " Program (Odin)\n\n";
  readme << "This program was generated by the **BenchGen** tool.\n\n";
  readme << "## Compilation\n\n";
  readme << "To compile the program, run the build script:\n\n";
  readme << "    ```bash\n";
  readme << "    ./build.sh\n";
  readme << "    ```\n\n";
  readme << "    The executable will be named `" + target + "`.\n\n";
  readme << "## Run\n\n";
  readme << "To run the program:\n\n";
  readme << "```bash\n";
  readme << "./run.sh\n";
  readme << "```\n\n";
  readme << "To run with arguments:\n\n";
  readme << "```bash\n";
  readme << "./run.sh -path-seed 123\n";
  readme << "```\n\n";
  readme << "### Optional Arguments\n\n";
  readme << "-   `-path-seed <seed>`: Sets the seed for the random number "
            "generator. Default is `0`.\n";
}

void OdinGenerator::generateFiles(std::string benchmarkName) {
  std::string benchDir = benchmarkName + "/";
  std::string sourceDir = benchDir + "src/";

  std::filesystem::create_directory(benchDir);
  std::filesystem::create_directory(sourceDir);

  this->genBuildScript(benchDir, benchmarkName);
  this->genReadme(benchDir, benchmarkName);

  // --- Generate lib.odin (core types, globals, utils) ---
  std::ofstream libFile;
  libFile.open(sourceDir + "lib.odin");

  for (auto include : libIncludes) {
    libFile << include << std::endl;
  }
  libFile << std::endl;

  for (auto var : libGlobalVars) {
    libFile << var << std::endl;
  }
  libFile << std::endl;

  for (auto& func : functions) {
    if (func.getId() == -1 && !func.insertBack) {
      auto lines = func.getLines();
      for (auto line : lines) {
        libFile << line << std::endl;
      }
      libFile << std::endl;
      break;
    }
  }
  libFile.close();

  // --- Generate func(index).odin files ---
  for (auto& func : functions) {
    if (func.getId() != -1) {
      std::string funcFileName =
          sourceDir + "func" + std::to_string(func.getId()) + ".odin";
      std::ofstream funcFile;
      funcFile.open(funcFileName);

      funcFile << "package main\n\n";

      auto lines = func.getLines();
      for (auto line : lines) {
        funcFile << line << std::endl;
      }
      funcFile << std::endl;
      funcFile.close();
    }
  }


  // --- Generate main.odin ---
  std::ofstream mainFile;
  mainFile.open(sourceDir + "main.odin");

  mainFile << "package main\n\n";
  mainFile << "import \"core:os\"\n";
  mainFile << "import \"core:mem\"\n";
  mainFile << "import \"base:runtime\"\n";
  mainFile << "import \"core:strconv\"\n";
  mainFile << "import \"core:math/rand\"\n\n";


  this->freeVars();

  auto mainLines = mainFunction.getLines();
  for (auto line : mainLines) {
    mainFile << line << std::endl;
  }
  mainFile.close();
}
