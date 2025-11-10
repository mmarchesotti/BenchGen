#include "carbonGeneratorVariable.h"


CarbonGeneratorArray::CarbonGeneratorArray(int size, int id) {
    this->typeString = "MArray";
    this->totalSize = size;
    this->id = id;
    this->name = VarTypes::ARRAY + std::to_string(id);
}

std::vector<std::string> CarbonGeneratorArray::new_(bool inFunction) {
    std::vector<std::string> temp = {"var " + this->name + ": " + this->typeString +";"};
    if (inFunction) {
        temp.push_back("if (pCounter > 0) {");
        temp.push_back("   " + this->name + " = vars.data[pCounter-1];");
        temp.push_back("     pCounter -= 1;");
        temp.push_back("   " + this->name + ".refC++;");
       // temp.push_back("   DEBUG_COPY(" + this->name + "->id);");
        temp.push_back("} else {");
        temp.push_back("   " + this->name + " = (alloc<"+this->typeString+">)(1);");
        temp.push_back("   " + this->name + ".size = " + std::to_string(this->totalSize) + ";");
        temp.push_back("   " + this->name + ".refC = 1;");
        temp.push_back("   " + this->name + ".id = " + std::to_string(this->id) + ";");
        temp.push_back("   " + this->name + ".data = (alloc<u32>)(" + this->name + ".size);");
        temp.push_back("   for (var i: i32 in 0..."+this->name+".size) {");
        temp.push_back("        "+this->name+".data[i] = 0;");
        temp.push_back("   }");
      //  temp.push_back("   DEBUG_NEW(" + this->name + "->id);");
        temp.push_back("}");
    } else {
        temp.push_back(this->name + " = (alloc<"+this->typeString+">)(1);");
        temp.push_back(this->name + ".size = " + std::to_string(this->totalSize) + ";");
        temp.push_back(this->name + ".refC = 1;");
        temp.push_back(this->name + ".id = " + std::to_string(this->id) + ";");
        temp.push_back(this->name + ".data = (alloc<u32>)(" + this->name + ".size);");
        temp.push_back("for (var i: i32 in 0..."+this->name+".size) {");
        temp.push_back("     "+this->name+".data[i] = 0;");
        temp.push_back("}");
       // temp.push_back("DEBUG_NEW(" + this->name + "->id);");
    }
    return temp;
}

std::vector<std::string> CarbonGeneratorArray::insert() {
    std::vector<std::string> temp = {"for (var i: i32 in 0..." + this->name + ".size) {"};
    temp.push_back("   " + this->name + "->data[i] += 1;");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> CarbonGeneratorArray::remove() {
    std::vector<std::string> temp = {"for (var i: i32 in 0..." + this->name + ".size) {"};
    temp.push_back("   " + this->name + "->data[i] -= 1;");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> CarbonGeneratorArray::contains(bool shouldReturn) {
    int compare = rand() % 100;  // Random value to compare against
    std::vector<std::string> temp = {};
    temp.push_back("for (var i: i32 = 0; i < " + this->name + ".size; i += 1) {");
    temp.push_back("   if (" + this->name + ".data[i] == " + std::to_string(compare) + ") { ");
    if (shouldReturn) {
        temp.push_back("      return " + this->name + ";");
    } else {
        temp.push_back("      " + this->name + ".data[i] += " + std::to_string(compare) + ";");
    }
    temp.push_back("   }");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> CarbonGeneratorArray::free() {
    std::vector<std::string> temp = {};
    temp.push_back(this->name + ".refC -= 1;");
    temp.push_back("if(" + this->name + ".refC == 0) {");
    temp.push_back("   free(" + this->name + ".data);");
    temp.push_back("   free(" + this->name + ");");
    //temp.push_back("   DEBUG_FREE(" + this->name + "->id);");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> CarbonGeneratorArray::genIncludes() {
    return {};
}

std::vector<std::string> CarbonGeneratorArray::genGlobalVars() {
    std::vector<std::string> temp = {};
    temp.push_back("class MArray {");
    temp.push_back("   var data: u32*;");
    temp.push_back("   var size: u64;");
    temp.push_back("   var refC: u64;");
    temp.push_back("   var id: i32;");
    temp.push_back("}");

    temp.push_back("class MArray_param {");
    temp.push_back("   var data: MyArray**;");
    temp.push_back("   var size: u64;");
    temp.push_back("}");
    return temp;
}

std::vector<std::string> CarbonGeneratorArray::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> temp = {};
    temp.push_back("var " + paramName + ": " + this->typeString + "_param;");
    temp.push_back(paramName + ".size = " + std::to_string(varsParams.size()) + ";");
    temp.push_back(paramName + ".data = (alloc<"+this->typeString+">)(" + paramName + ".size);");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        temp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }
    return temp;
}

CarbonGeneratorArray::~CarbonGeneratorArray() {
}
