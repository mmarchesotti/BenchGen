#include "odinGeneratorVariable.h"
#include <vector>

OdinGeneratorArray::OdinGeneratorArray(int size, int id) {
  this->typeString = "Array";
  this->totalSize = size;
  this->id = id;
  this->name = VarTypes::ARRAY + std::to_string(id);
}

OdinGeneratorArray::~OdinGeneratorArray() {}

std::vector<std::string> OdinGeneratorArray::new_(bool inFunction) {
  // Odin pointers are nil-initialized by default
  std::vector<std::string> temp = {"var " + this->name + ": ^" +
                                   this->typeString + ";" };

  if (inFunction) {
    temp.push_back("if pCounter > 0 {");
    temp.push_back("    pCounter -= 1;");
    temp.push_back("    " + this->name + " = vars.data[pCounter];");
    temp.push_back("    " + this->name + ".refC += 1;");
    temp.push_back("} else {");
    // mem.new allocates and returns a pointer
    temp.push_back("    " + this->name + " = mem.new(" +
                   this->typeString + ");");
    temp.push_back("    " + this->name +
                   ".size = " + std::to_string(this->totalSize) + ";");
    temp.push_back("    " + this->name + ".refC = 1;");
    temp.push_back("    " + this->name + ".id = " + std::to_string(this->id) +
                   ";");
    // mem.make creates a slice
    temp.push_back("    " + this->name + ".data = mem.make([]u32, " +
                   this->name + ".size);");
    temp.push_back("}");
  } else {
    temp.push_back(this->name + " = mem.new(" + this->typeString +
                   ");");
    temp.push_back(this->name + ".size = " + std::to_string(this->totalSize) +
                   ";");
    temp.push_back(this->name + ".refC = 1;");
    temp.push_back(this->name + ".id = " + std::to_string(this->id) + ";");
    temp.push_back(this->name + ".data = mem.make([]u32, " +
                   this->name + ".size);");
  }
  return temp;
}

std::vector<std::string> OdinGeneratorArray::insert() {
    // Odin for loop `..<` is exclusive
  std::vector<std::string> temp = {"for i in 0.." + this->name + ".size { "};
  temp.push_back("    " + this->name + ".data[i] += 1;");
  temp.push_back("}");
  return temp;
}

std::vector<std::string> OdinGeneratorArray::remove() {
  std::vector<std::string> temp = {"for i in 0.." + this->name + ".size { "};
  temp.push_back("    " + this->name + ".data[i] -= 1;");
  temp.push_back("}");
  return temp;
}

std::vector<std::string> OdinGeneratorArray::contains(bool shouldReturn) {
  int compare = rand() % 100;
  std::vector<std::string> temp = {};
  temp.push_back("for i in 0.." + this->name + ".size {");
  temp.push_back("    if " + this->name +
                 ".data[i] == " + std::to_string(compare) + " {");
  if (shouldReturn) {
    temp.push_back("        return " + this->name + ";");
  } else {
    temp.push_back("        " + this->name +
                   ".data[i] += " + std::to_string(compare) + ";");
  }
  temp.push_back("    }");
  temp.push_back("}");
  return temp;
}

std::vector<std::string> OdinGeneratorArray::free() {
  std::vector<std::string> temp = {};
  temp.push_back(this->name + ".refC -= 1;");
  temp.push_back("if " + this->name + ".refC == 0 {");
  // mem.delete frees slices/maps, mem.free frees pointers from mem.new
  temp.push_back("    mem.delete(" + this->name + ".data);");
  temp.push_back("    mem.free(" + this->name + ");");
  temp.push_back("}");
  return temp;
}

std::vector<std::string> OdinGeneratorArray::genIncludes() { 
  // Imports are handled in OdinGenerator
  return {}; 
}

std::vector<std::string> OdinGeneratorArray::genGlobalVars() {
  std::vector<std::string> temp = {};
  // Odin doesn't need explicit allocator globals, it uses `context`
  temp.push_back(this->typeString + " :: struct {");
  temp.push_back("    data: []u32,");
  temp.push_back("    size: int,"); // Odin's `int` is pointer-sized
  temp.push_back("    refC: int,");
  temp.push_back("    id: i32,");
  temp.push_back("};");
  temp.push_back("");
  temp.push_back(this->typeString + "Param :: struct {");
  temp.push_back("    data: []^" + this->typeString + ","); // Slice of pointers
  temp.push_back("    size: int,");
  temp.push_back("};");
  return temp;
}

std::vector<std::string>
OdinGeneratorArray::genParams(std::string paramName,
                             std::vector<GeneratorVariable*> varsParams) {
  std::vector<std::string> temp = {};
  std::string dataSliceName = paramName + "_data";

  // Use mem.make to create a slice of pointers
  temp.push_back(dataSliceName + " := mem.make([]^" +
                 this->typeString + ", " + std::to_string(varsParams.size()) +
                 ");");

  for (int i = 0; i < (int)varsParams.size(); i++) {
    temp.push_back(dataSliceName + "[" + std::to_string(i) +
                   "] = " + varsParams[i]->name + ";");
  }

  // Odin struct literal syntax
  temp.push_back(paramName + " := " + this->typeString + "Param{");
  temp.push_back("    data = " + dataSliceName + ",");
  temp.push_back("    size = " + std::to_string(varsParams.size()) + ",");
  temp.push_back("};");
  return temp;
}
