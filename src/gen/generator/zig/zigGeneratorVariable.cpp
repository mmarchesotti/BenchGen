#include "zigGeneratorVariable.h"

ZigGeneratorArray::ZigGeneratorArray(int size, int id) {
    this->typeString = "Array";
    this->totalSize = size;
    this->id = id;
    this->name = VarTypes::ARRAY + std::to_string(id);
}

ZigGeneratorArray::~ZigGeneratorArray() {}

std::vector<std::string> ZigGeneratorArray::new_(bool inFunction) {
    std::vector<std::string> temp = {"var " + this->name + ": *" + this->typeString + " = undefined;"};

    if (inFunction) {
        temp.push_back("if (pCounter > 0) {");
        temp.push_back("    pCounter -= 1;");
        temp.push_back("    " + this->name + " = vars.data[pCounter];");
        temp.push_back("    " + this->name + ".refC += 1;");
        temp.push_back("    // DEBUG_COPY(" + this->name + ".id);");
        temp.push_back("} else {");
        temp.push_back("    " + this->name + " = try allocator.create(" + this->typeString + ");");
        temp.push_back("    " + this->name + ".*.size = " + std::to_string(this->totalSize) + ";");
        temp.push_back("    " + this->name + ".*.refC = 1;");
        temp.push_back("    " + this->name + ".*.id = " + std::to_string(this->id) + ";");
        temp.push_back("    " + this->name + ".*.data = try allocator.allocZ(u32, " + this->name + ".*.size);");
        temp.push_back("    // DEBUG_COPY(" + this->name + ".id);");
        temp.push_back("}");
    } else {
        temp.push_back(this->name + " = try allocator.create(" + this->typeString + ");");
        temp.push_back(this->name + ".*.size = " + std::to_string(this->totalSize) + ";");
        temp.push_back(this->name + ".*.refC = 1;");
        temp.push_back(this->name + ".*.id = " + std::to_string(this->id) + ";");
        temp.push_back(this->name + ".*.data = try allocator.allocZ(u32, " + this->name + ".*.size);");
        temp.push_back("    // DEBUG_NEW(" + this->name + ".id);");
    }
    return temp;
}

std::vector<std::string> ZigGeneratorArray::insert() {
    std::vector<std::string> temp = {"for (0.." + this->name + ".size) |i| {"};
    temp.push_back("    " + this->name + ".data[i] += 1;");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> ZigGeneratorArray::remove() {
    std::vector<std::string> temp = {"for (0.." + this->name + ".size) |i| {"};
    temp.push_back("    " + this->name + ".data[i] -= 1;");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> ZigGeneratorArray::contains(bool shouldReturn) {
    int compare = rand() % 100;
    std::vector<std::string> temp = {};
    temp.push_back("for (0.." + this->name + ".size) |i| {");
    temp.push_back("    if (" + this->name + ".data[i] == " + std::to_string(compare) + ") {");
    if (shouldReturn) {
        temp.push_back("        return " + this->name + ";");
    } else {
        temp.push_back("        " + this->name + ".data[i] += " + std::to_string(compare) + ";");
    }
    temp.push_back("    }");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> ZigGeneratorArray::free() {
    std::vector<std::string> temp = {};
    temp.push_back(this->name + ".refC -= 1;");
    temp.push_back("if (" + this->name + ".refC == 0) {");
    temp.push_back("    allocator.free(" + this->name + ".data);");
    temp.push_back("    allocator.destroy(" + this->name + ");");
    temp.push_back("    // DEBUG_FREE(" + this->name + ".id);");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> ZigGeneratorArray::genIncludes() {
    return {};
}

std::vector<std::string> ZigGeneratorArray::genGlobalVars() {
    std::vector<std::string> temp = {};
    temp.push_back("// DEBUG_FREE(" + this->name + ".id);");
    temp.push_back("pub var gpa = std.heap.GeneralPurposeAllocator(.{}){};");
    temp.push_back("pub const allocator = gpa.allocator();");
    temp.push_back("");
    temp.push_back("const " + this->typeString + " = struct {");
    temp.push_back("    data: []u32,");
    temp.push_back("    size: usize,");
    temp.push_back("    refC: usize,");
    temp.push_back("    id: i32,");
    temp.push_back("};");
    temp.push_back("");
    temp.push_back("const " + this->typeString + "Param = struct {");
    temp.push_back("    data: []*" + this->typeString + ","); 
    temp.push_back("    size: usize,");
    temp.push_back("};");
    return temp;
}

std::vector<std::string> ZigGeneratorArray::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> temp = {};
    std::string dataSliceName = paramName + "_data";

    temp.push_back("const " + dataSliceName + " = try allocator.alloc(*" + this->typeString + ", " + std::to_string(varsParams.size()) + ");");
    
    for (int i = 0; i < (int)varsParams.size(); i++) {
        temp.push_back(dataSliceName + "[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }

    temp.push_back("const " + paramName + " = " + this->typeString + "Param{");
    temp.push_back("    .data = " + dataSliceName + ",");
    temp.push_back("    .size = " + std::to_string(varsParams.size()) + ",");
    temp.push_back("};");
    return temp;
}
