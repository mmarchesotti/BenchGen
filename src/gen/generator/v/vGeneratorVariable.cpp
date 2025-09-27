#include "vGeneratorVariable.h"

VGeneratorArray::VGeneratorArray(int size, int id) {
    this->typeString = "Array";
    this->totalSize = size;
    this->id = id;
    this->name = VarTypes::ARRAY + std::to_string(id);
}

VGeneratorArray::~VGeneratorArray() {}

std::vector<std::string> VGeneratorArray::new_(bool inFunction) {
    std::vector<std::string> temp = {"mut " + this->name + " := " + this->typeString + "{}"};
    if (inFunction) {
        temp.push_back("if p_counter > 0 {");
        temp.push_back("    " + this->name + " = vars.data[p_counter-1]");
        temp.push_back("    p_counter--");
        temp.push_back("    " + this->name + ".ref_c++");
        temp.push_back("} else {");
        temp.push_back("    " + this->name + " = " + this->typeString + "{");
        temp.push_back("        size: " + std::to_string(this->totalSize) + ",");
        temp.push_back("        ref_c: 1,");
        temp.push_back("        id: " + std::to_string(this->id) + ",");
        temp.push_back("        data: []u32{len: " + std::to_string(this->totalSize) + "}");
        temp.push_back("    }");
        temp.push_back("}");
    } else {
        temp.push_back(this->name + " = " + this->typeString + "{");
        temp.push_back("    size: " + std::to_string(this->totalSize) + ",");
        temp.push_back("    ref_c: 1,");
        temp.push_back("    id: " + std::to_string(this->id) + ",");
        temp.push_back("    data: []u32{len: " + std::to_string(this->totalSize) + "}");
        temp.push_back("}");
    }
    return temp;
}

std::vector<std::string> VGeneratorArray::insert() {
    std::vector<std::string> temp;
    temp.push_back("for i := 0; i < " + this->name + ".size; i++ {");
    temp.push_back("    " + this->name + ".data[i] = u32(i)");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> VGeneratorArray::remove() {
    std::vector<std::string> temp;
    temp.push_back("for i := 0; i < " + this->name + ".size; i++ {");
    temp.push_back("    " + this->name + ".data[i]--");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> VGeneratorArray::contains(bool shouldReturn) {
    int compare = rand() % 100;
    std::vector<std::string> temp;
    temp.push_back("for i := 0; i < " + this->name + ".size; i++ {");
    temp.push_back("    if " + this->name + ".data[i] == " + std::to_string(compare) + " {");
    if (shouldReturn) {
        temp.push_back("        return " + this->name);
    } else {
        temp.push_back("        " + this->name + ".data[i] += " + std::to_string(compare));
    }
    temp.push_back("    }");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> VGeneratorArray::free() {
    std::vector<std::string> temp;
    temp.push_back(this->name + ".ref_c--");
    temp.push_back("if " + this->name + ".ref_c == 0 {");
    // V has automatic memory management for arrays, so we don't need to free manually.
    // This block can be left empty or used for debugging.
    temp.push_back("}");
    return temp;
}

std::vector<std::string> VGeneratorArray::genIncludes() {
    return {};
}

std::vector<std::string> VGeneratorArray::genGlobalVars() {
    std::vector<std::string> temp;
    temp.push_back("struct Array {");
    temp.push_back("mut:");
    temp.push_back("    data []u32");
    temp.push_back("    size int");
    temp.push_back("    ref_c int");
    temp.push_back("    id   int");
    temp.push_back("}");
    temp.push_back("struct ArrayParam {");
    temp.push_back("    data []Array");
    temp.push_back("    size int");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> VGeneratorArray::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> temp;
    temp.push_back("mut " + paramName + " := " + this->typeString + "Param{");
    temp.push_back("    size: " + std::to_string(varsParams.size()) + ",");
    temp.push_back("    data: []" + this->typeString + "{len: " + std::to_string(varsParams.size()) + "}");
    temp.push_back("}");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        temp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name);
    }
    return temp;
}