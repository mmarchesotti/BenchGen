#include "zigGenerator.h"

#include <string>
#include <vector>

void ZigGenerator::generateIncludes() {
  includes.push_back("pub const std = @import(\"std\");");

  std::vector<std::string> varIncludes = VariableFactory::genIncludes(varType);
  for (auto var : varIncludes) {
    includes.push_back(var);
  }
}

void ZigGenerator::generateGlobalVars() {
  std::vector<std::string> varGlobalVars =
      VariableFactory::genGlobalVars(varType);
  for (auto gVar : varGlobalVars) {
    globalVars.push_back(gVar);
  }

  globalVars.push_back("");
  globalVars.push_back("pub var prng = std.Random.DefaultPrng.init(0);");
  globalVars.push_back("pub const random = prng.random();");
}

void ZigGenerator::generateRandomNumberGenerator() {
  GeneratorFunction rngFunction = GeneratorFunction(-1);
  rngFunction.addLine(
      {"pub fn get_path() !u64 {",
       "    if (std.process.getEnvVarOwned(allocator, \"BENCH_PATH\")) ",
       "|path| {", "        defer allocator.free(path);",
       "        return std.fmt.parseUnsigned(u64, path, 10);",
       "    } else |err| {",
       "        if (err == error.EnvironmentVariableNotFound) {",
       "            return random.int(u64);", "        } else {",
       "            return err;", "        }", "    }", "}"});
  functions.push_back(rngFunction);
}

void ZigGenerator::generateMainFunction() {
  mainFunction = GeneratorFunction(-1);
  mainFunction.addLine(
      {"pub fn main() !void {", "    defer _ = lib.gpa.deinit();", "",
       "    var path_seed: u64 = 0;", "",
       "    const args = try std.process.argsAlloc(allocator);",
       "    defer std.process.argsFree(allocator, args);", "",
       "    var arg_idx: usize = 1;",
       "    while (arg_idx < args.len) : (arg_idx += 1) {",
       "        if (std.mem.eql(u8, args[arg_idx], \"-path-seed\")) {",
       "            arg_idx += 1;",
       "            if (arg_idx < args.len) { path_seed = ",
       "std.fmt.parseUnsigned(u64, args[arg_idx], 10) catch 0; }", "        }",
       "    }", "    lib.prng = std.Random.DefaultPrng.init(path_seed);", "}"});
  mainFunction.insertBack = true;
  currentFunction.push(&mainFunction);
  startScope();
}

void ZigGenerator::addLine(std::string line, int d) {
  std::string indentedLine = currentScope.top().getIndentationTabs(d) + line;
  currentFunction.top()->addLine(indentedLine);
}

void ZigGenerator::addLine(std::vector<std::string> lines, int d) {
  for (auto line : lines) {
    addLine(line, d);
  }
}

void ZigGenerator::startScope() {
  GeneratorScope scope = GeneratorScope(currentScope.top().avaiableVarsID,
                                        currentScope.top().avaiableParamsID,
                                        currentScope.top().getIndentation());
  currentScope.push(scope);
}

void ZigGenerator::startFunc(int funcId, int nParameters) {
  GeneratorFunction func = GeneratorFunction(funcId);

  std::string funcHeader = "pub fn func" + std::to_string(funcId) + "(vars: *" +
                           VariableFactory::genTypeString(varType) + "Param";
  if (nParameters > 0) {
    funcHeader += ", ";
    for (int i = 0; i < nParameters; i++) {
      funcHeader += "_path" + std::to_string(i) + ": u64, ";
    }
    funcHeader.pop_back();
    funcHeader.pop_back();
  }
  funcHeader += ") !*" + VariableFactory::genTypeString(varType) + " {";

  func.addLine(funcHeader);

  functions.push_back(func);
  currentFunction.push(&(functions.back()));
  GeneratorScope scope = GeneratorScope();
  currentScope.push(scope);
  this->ifCounter.push(0);
  
  addLine("var pCounter: usize = vars.size;");
  
  addLine("_ = &pCounter;"); 

  for (int i = 0; i < nParameters; i++) {
    addLine("const path" + std::to_string(i) + " = _path" + std::to_string(i) +
            ";");
            
    addLine("_ = &path" + std::to_string(i) + ";"); 
  }
}

bool ZigGenerator::functionExists(int funcId) {
  for (auto func : functions) {
    if (func.getId() == funcId) {
      return true;
    }
  }
  return false;
}

std::string ZigGenerator::createParams() {
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

void ZigGenerator::callFunc(int funcId, int nParameters) {
  std::string param = createParams();
  int id = addVar(varType);
  GeneratorVariable* var = variables[id];

  std::string line = "const " + var->name + " = try func" +
                     std::to_string(funcId) + "(&" + param;
  if (nParameters > 0) {
    line += ", ";
    for (int i = 0; i < nParameters; i++) {
      line += "try get_path(), ";
    }
    line.pop_back();
    line.pop_back();
  }
  line += ");";
  addLine(line);

  addLine("defer allocator.free(" + param + ".data);");
}

int ZigGenerator::addVar(std::string type) {
  this->variables[varCounter] =
      VariableFactory::createVariable(type, varCounter);
  this->currentScope.top().addVar(varCounter);
  return varCounter++;
}

void ZigGenerator::freeVars(bool hasReturn, int returnVarPos) {
  int numberOfAddedVars = currentScope.top().numberOfAddedVars;
  std::vector<int> availableVarsId = currentScope.top().avaiableVarsID;
  for (int i = 0; i < numberOfAddedVars; i++) {
    int varPos = availableVarsId.size() - i - 1;
    if (!hasReturn || varPos != returnVarPos) {
      GeneratorVariable* var = variables[availableVarsId[varPos]];
      addLine(var->free());
    }
  }

  currentScope.top().numberOfAddedVars = 0;
}

void ZigGenerator::returnFunc(int returnVarPos) {
  GeneratorVariable* var =
      variables[currentScope.top().avaiableVarsID[returnVarPos]];
  addLine("return " + var->name + ";");
}

void ZigGenerator::endScope() {
  std::string line = currentScope.top().getIndentationTabs(-1) + "}";
  currentFunction.top()->addLine(line);
  currentScope.pop();
}

void ZigGenerator::endIfScope() {
  std::string line = currentScope.top().getIndentationTabs(-1) + "";
  currentFunction.top()->addLine(line);
  currentScope.pop();
}

void ZigGenerator::endFunc() {
  endScope();
  currentFunction.pop();
  ifCounter.pop();
}

void ZigGenerator::genMakefile(std::string dir, std::string target) {
  std::ofstream buildFile;
  buildFile.open(dir + "build.zig");
  buildFile << "const std = @import(\"std\");\n\n";
  buildFile << "pub fn build(b: *std.Build) void {\n";
  buildFile << "    const target = b.standardTargetOptions(.{});\n";
  buildFile << "    const optimize = b.standardOptimizeOption(.{});\n\n";
  buildFile << "    const exe = b.addExecutable(.{\n";
  buildFile << "        .name = \"" + target + "\",\n";
  buildFile << "        .root_module = b.createModule(.{";
  buildFile << "            .root_source_file = b.path(\"src/main.zig\"),\n";
  buildFile << "            .target = target,\n";
  buildFile << "            .optimize = optimize,\n";
  buildFile << "        }),";
  buildFile << "    });\n\n";
  buildFile << "    b.installArtifact(exe);\n\n";
  buildFile << "    const run_step = b.step(\"run\", \"Run the app\");\n";
  buildFile << "    const run_exe = b.addRunArtifact(exe);\n";
  buildFile << "    run_exe.step.dependOn(&exe.step);\n";
  buildFile << "    run_step.dependOn(&run_exe.step);\n";
  buildFile << "}\n";
  buildFile.close();
}

void ZigGenerator::genReadme(std::string dir, std::string target) {
  std::ofstream readme;
  readme.open(dir + "README.md");
  readme << "# " + target + " Program (Zig)\n\n";
  readme << "This program was generated by the **BenchGen** tool.\n\n";
  readme << "## Compilation\n\n";
  readme << "To compile the program, use the Zig build system:\n\n";
  readme << "    ```bash\n";
  readme << "    zig build\n";
  readme << "    ```\n\n";
  readme << "    The executable will be located at `zig-out/bin/" + target + "`.\n\n";
  readme << "## Run\n\n";
  readme << "To compile and run the program at once:\n\n";
  readme << "```bash\n";
  readme << "zig build run\n";
  readme << "```\n\n";
  readme << "To run the compiled program with arguments:\n\n";
  readme << "```bash\n";
  readme << "./zig-out/bin/" + target + " -loops-factor 50 -path-seed 123\n";
  readme << "```\n\n";
  readme << "### Optional Arguments\n\n";
  readme << "-   `-path-seed <seed>`: Sets the seed for the random number "
            "generator. Default is `0`.\n\n";
  readme << "-   `-loops-factor <factor>`: Sets the factor for the number of "
            "loops. Default is `100`.\n\n";
}

void ZigGenerator::generateFiles(std::string benchmarkName) {
  std::string benchDir = benchmarkName + "/";
  std::string sourceDir = benchDir + "src/";

  std::filesystem::create_directory(benchDir);
  std::filesystem::create_directory(sourceDir);

  this->genMakefile(benchDir, benchmarkName);
  this->genReadme(benchDir, benchmarkName);

  // --- Generate lib.zig (core types, globals, utils) ---
  std::ofstream libFile;
  libFile.open(sourceDir + "lib.zig");

  for (auto include : includes) {
    libFile << include << std::endl;
  }
  libFile << std::endl;

  for (auto var : globalVars) {
    libFile << var << std::endl;
  }
  libFile << std::endl;

  for (auto func : functions) {
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

  // --- Generate func(index).zig files ---
  std::string arrayType = VariableFactory::genTypeString(varType);
  std::string paramType = arrayType + "Param";

  for (auto& func : functions) {
    if (func.getId() != -1) {
      std::string funcFileName =
          sourceDir + "func" + std::to_string(func.getId()) + ".zig";
      std::ofstream funcFile;
      funcFile.open(funcFileName);

      funcFile << "const lib = @import(\"lib.zig\");\n";
      funcFile << "const std = lib.std;\n";
      funcFile << "const allocator = std.heap.smp_allocator;\n";
      funcFile << "const " + arrayType + " = lib." + arrayType + ";\n";
      funcFile << "const " + paramType + " = lib." + paramType + ";\n";
      funcFile << "const get_path = lib.get_path;\n\n";

      for (auto& func_dep : functions) {
        if (func_dep.getId() != -1 && func_dep.getId() != func.getId()) {
          std::string depIdStr = std::to_string(func_dep.getId());
          funcFile << "const func" + depIdStr + " = @import(\"func" + depIdStr +
                          ".zig\").func" + depIdStr + ";\n";
        }
      }
      funcFile << "\n";

      auto lines = func.getLines();
      for (auto line : lines) {
        funcFile << line << std::endl;
      }
      funcFile << std::endl;
      funcFile.close();
    }
  }

  // --- Generate main.zig ---
  std::ofstream mainFile;
  mainFile.open(sourceDir + "main.zig");

  mainFile << "const lib = @import(\"lib.zig\");\n\n";

  mainFile << "const std = lib.std;\n";
  mainFile << "const allocator = std.heap.smp_allocator;\n";
  mainFile << "const " + arrayType + " = lib." + arrayType + ";\n";
  mainFile << "const " + paramType + " = lib." + paramType + ";\n";
  mainFile << "const get_path = lib.get_path;\n\n";

  for (auto func : functions) {
    if (func.getId() != -1) {
      std::string funcIdStr = std::to_string(func.getId());
      mainFile << "const func" + funcIdStr + " = @import(\"func" + funcIdStr +
                      ".zig\").func" + funcIdStr + ";\n";
    }
  }
  mainFile << std::endl;

  this->freeVars();

  auto mainLines = mainFunction.getLines();
  for (auto line : mainLines) {
    mainFile << line << std::endl;
  }
  mainFile.close();
}
