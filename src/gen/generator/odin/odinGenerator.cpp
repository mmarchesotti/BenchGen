#include "odinGenerator.h"

#include <string>
#include <vector>

void OdinGenerator::generateIncludes() {
  // All files will be in 'main' package
  includes.push_back("package main");
  includes.push_back("");
  includes.push_back("import \"core:fmt\"");
  includes.push_back("import \"core:os\"");
  includes.push_back("import \"core:mem\"");
  includes.push_back("import \"base:runtime\"");
  includes.push_back("import \"core:strconv\"");
  includes.push_back("import \"core:math/rand\"");

  std::vector<std::string> varIncludes = VariableFactory::genIncludes(varType);
  for (auto var : varIncludes) {
    includes.push_back(var);
  }
}

void OdinGenerator::generateGlobalVars() {
  std::vector<std::string> varGlobalVars =
      VariableFactory::genGlobalVars(varType);
  for (auto gVar : varGlobalVars) {
    globalVars.push_back(gVar);
  }

  globalVars.push_back("");
  globalVars.push_back("prng: rand.Rand");
}

void OdinGenerator::generateRandomNumberGenerator() {
  GeneratorFunction rngFunction = GeneratorFunction(-1);
  rngFunction.addLine(
      {"get_path :: proc() -> u64 {",
       "    if path, ok := os.get_env(\"BENCH_PATH\"); ok {",
       "        if val, err := strconv.parse_u64(path, 10); err == nil {",
       "            return val;", "        }", "    }",
       "    return rand.uint64(&prng);", "}"});
  functions.push_back(rngFunction);
}

void OdinGenerator::generateMainFunction() {
  mainFunction = GeneratorFunction(-1);
  mainFunction.addLine(
      {"main :: proc() {",
       // Set up default allocators in the context
       "    context.allocator = mem.heap_allocator()",
       "    context.temp_allocator = mem.arena_allocator(mem.heap_allocator())",
       "    defer mem.arena_allocator_delete(context.temp_allocator)",
       "", "    path_seed: u64 = 0;", "",
       "    for arg, i in os.args {", "        if i == 0 { continue; }",
       "        if arg == \"-path-seed\" && i + 1 < len(os.args) {",
       "            if val, err := strconv.parse_u64(os.args[i+1], 10); err == nil {",
       "                path_seed = val;", "            }", "        }", "    }",
       "    rand.init(&prng, path_seed);", "}"});
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
  // Odin uses '.' to access pointer struct fields
  addLine("pCounter := vars.size;"); 

  for (int i = 0; i < nParameters; i++) {
    addLine("path" + std::to_string(i) + " :: _path" + std::to_string(i) +
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

  // genParams uses mem.make, so we use mem.delete
  addLine("defer mem.delete(" + param + ".data);");
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
  buildFile << "odin build ./src -out:" + target + "\n";
  buildFile << "if [ $? -eq 0 ]; then\n";
  buildFile << "  echo \"Build successful!\"\n";
  buildFile << "  # ./run.sh\n";
  buildFile << "else\n";
  buildFile << "  echo \"Build failed!\"\n";
  buildFile << "fi\n";
  buildFile.close();

  // Make it executable
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

  // Make it executable
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

  // --- Generate lib.odin (core types, globals, utils, and all funcs) ---
  std::ofstream libFile;
  libFile.open(sourceDir + "lib.odin");

  for (auto include : includes) {
    libFile << include << std::endl;
  }
  libFile << std::endl;

  for (auto var : globalVars) {
    libFile << var << std::endl;
  }
  libFile << std::endl;

  // Find and write all functions (utils and generated)
  for (auto& func : functions) {
    if (func.getId() == -1 && func.insertBack) {
      continue;  // Skip main function stub
    }
    auto lines = func.getLines();
    for (auto line : lines) {
      libFile << line << std::endl;
    }
    libFile << std::endl;
  }
  libFile.close();

  // --- Generate main.odin ---
  std::ofstream mainFile;
  mainFile.open(sourceDir + "main.odin");

  // main.odin is in the same package, but needs its own imports
  mainFile << "package main\n\n";
  mainFile << "import \"core:fmt\"\n";
  mainFile << "import \"core:os\"\n";
  mainFile << "import \"core:mem\"\n";
  mainFile << "import \"base:runtime\"\n";
  mainFile << "import \"core:strconv\"\n";
  mainFile << "import \"core:math/rand\"\n\n";

  // Call freeVars for the main scope before writing the function
  // This is the segfault fix
  this->freeVars();

  auto mainLines = mainFunction.getLines();
  for (auto line : mainLines) {
    mainFile << line << std::endl;
  }
  mainFile.close();
}
