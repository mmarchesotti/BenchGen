#include "generatorVariable.h"

#include "c/cGeneratorVariable.h"
#include "cpp/cppGeneratorVariable.h"
#include "go/goGeneratorVariable.h"
#include "julia/juliaGeneratorVariable.h"
#include "rust/rustGeneratorVariable.h"
#include "v/vGeneratorVariable.h"
#include "carbon/carbonGeneratorVariable.h"
#include "zig/zigGeneratorVariable.h"
#include "odin/odinGeneratorVariable.h"
#include "d/dGeneratorVariable.h"
#include "mlir/mlirGeneratorVariable.h"

unsigned int VariableFactory::var_counter = 0;


GeneratorSortedList::GeneratorSortedList() {};
GeneratorSortedList::GeneratorSortedList(int id){};
GeneratorSortedList::~GeneratorSortedList(){};
GeneratorArray::GeneratorArray() {};
GeneratorArray::GeneratorArray(int totalSize, int id) {};
GeneratorArray::~GeneratorArray() {};

GeneratorScalar::GeneratorScalar() {};
GeneratorScalar::~GeneratorScalar() {};


std::vector<std::string> GeneratorSortedList::new_(bool inFunction)
{
    return CGeneratorSortedList().new_(inFunction);
}

std::vector<std::string>  GeneratorSortedList::insert()
{
    return CGeneratorSortedList().insert();
}

std::vector<std::string>  GeneratorSortedList::remove()
{
    return CGeneratorSortedList().remove();  
}

std::vector<std::string>  GeneratorSortedList::contains(bool shouldReturn)
{
    return CGeneratorSortedList().contains(shouldReturn);
}

std::vector<std::string>  GeneratorSortedList::free()
{
    return CGeneratorSortedList().free();
}

std::vector<std::string>  GeneratorSortedList::genIncludes()
{
    return CGeneratorSortedList().genIncludes();
}

std::vector<std::string>  GeneratorSortedList::genGlobalVars()
{
    return CGeneratorSortedList().genGlobalVars();
}

std::vector<std::string>  GeneratorSortedList::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams)
{
    return CGeneratorSortedList().genParams(paramName, varsParams);
}

std::vector<std::string> GeneratorArray::new_(bool inFunction)
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().new_(inFunction);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().new_(inFunction);
    }
}


std::vector<std::string>  GeneratorArray::insert()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().insert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().insert();
    }
}

std::vector<std::string>  GeneratorArray::remove()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().remove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().remove();
    }
}

std::vector<std::string>  GeneratorArray::contains(bool shouldReturn)
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return CppGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().contains(shouldReturn);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().contains(shouldReturn);
    }
}

std::vector<std::string>  GeneratorArray::free()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().free();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().free();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return CppGeneratorArray().free(); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().free();   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().free();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().free();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().free();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().free();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().free();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().free();
    }
}

std::vector<std::string>  GeneratorArray::genIncludes()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().genIncludes();   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().genIncludes();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().genIncludes();
    }
}

std::vector<std::string>  GeneratorArray::genGlobalVars()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().genGlobalVars();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().genGlobalVars();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustGeneratorArray().genGlobalVars();   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().genGlobalVars();   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().genGlobalVars();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().genGlobalVars();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().genGlobalVars();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().genGlobalVars();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().genGlobalVars();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().genGlobalVars();
    }
}

std::vector<std::string>  GeneratorArray::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams)
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaGeneratorArray().genParams(paramName, varsParams);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ODIN)
    {
        return OdinGeneratorArray().genParams(paramName, varsParams);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::D)
    {
        return DGeneratorArray().genParams(paramName, varsParams);
    }
}


std::vector<std::string> GeneratorScalar::new_(bool inFunction) {;
    return MlirGeneratorScalar().new_(inFunction);
}

std::vector<std::string> GeneratorScalar::arithmetic(std::string opt) {
    return MlirGeneratorScalar().arithmetic(opt);
}

std::vector<std::string> GeneratorScalar::conditional() {
    return MlirGeneratorScalar().conditional();
}

std::vector<std::string> GeneratorScalar::logical(bool shouldReturn) {
    return MlirGeneratorScalar().logical(shouldReturn);
}

std::vector<std::string> GeneratorScalar::free() {
    return MlirGeneratorScalar().free();
}

std::vector<std::string> GeneratorScalar::unary(std::string op) {
    return MlirGeneratorScalar().unary(op);
}

std::vector<std::string> GeneratorScalar::select(bool shouldReturn) {
    return MlirGeneratorScalar().select(shouldReturn);
}

std::vector<std::string> GeneratorScalar::logical_sc(bool shouldReturn) {
    return MlirGeneratorScalar().logical_sc(shouldReturn);
}


std::vector<std::string> GeneratorScalar::incdec(bool isInc) {
    return MlirGeneratorScalar().incdec(isInc);
}

std::vector<std::string> GeneratorScalar::reduction() {
    return MlirGeneratorScalar().reduction();
}

std::vector<std::string> GeneratorScalar::call(std::string funcName) {
    return MlirGeneratorScalar().call(funcName);
}

std::vector<std::string> GeneratorScalar::insert() {
    return {};
}
std::vector<std::string> GeneratorScalar::remove() {
    return {};
}
std::vector<std::string> GeneratorScalar::contains(bool shouldReturn) {
    return {};
}
std::vector<std::string> GeneratorScalar::genIncludes() {
    return {};
}
std::vector<std::string> GeneratorScalar::genGlobalVars() {
    return {};
}
std::vector<std::string> GeneratorScalar::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {}

std::string VariableFactory::genTypeString(std::string type) {
    GeneratorVariable* var = createVariable(type, 0);
    std::string typeString = var->typeString;
    delete var;
    return typeString;
}

std::vector<std::string> VariableFactory::genIncludes(std::string type) {
    GeneratorVariable* var = createVariable(type, 0);
    std::vector<std::string> includes = var->genIncludes();
    delete var;
    return includes;
}

std::vector<std::string> VariableFactory::genGlobalVars(std::string type) {
    GeneratorVariable* var = createVariable(type, 0);
    std::vector<std::string> globalVars = var->genGlobalVars();
    delete var;
    return globalVars;
}

std::vector<std::string> VariableFactory::genParams(std::string type, std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    GeneratorVariable* var = createVariable(type, 0);
    std::vector<std::string> params = var->genParams(paramName, varsParams);
    delete var;
    return params;
}
GeneratorGHashTable::GeneratorGHashTable(int id) {
    this->typeString = "ghash_t";
    this->id = id;
    this->name = VarTypes::GHASH_TABLE + std::to_string(id);
}

GeneratorGHashTable::~GeneratorGHashTable() {
}

std::vector<std::string> GeneratorGHashTable::genIncludes() {
    std::vector<std::string> temp = {};
    temp.push_back("#include <stdbool.h>");
    temp.push_back("#include <glib.h>");
    return temp;
}

std::vector<std::string> GeneratorGHashTable::new_(bool inFunction) {
    std::vector<std::string> tmp = {};

    if (inFunction) {
        tmp.push_back("ghash_t* " + this->name + ";");
        tmp.push_back("if (pCounter > 0) {");
        tmp.push_back("   " + this->name + " = vars->data[--pCounter];");
        tmp.push_back("   " + this->name + "->refC++;");
        tmp.push_back("   DEBUG_COPY(" + this->name + "->id);");
        tmp.push_back("} else {");
        tmp.push_back("   " + this->name + " = (ghash_t*)malloc(sizeof(ghash_t));");
        tmp.push_back("   " + this->name + "->refC = 1;");
        tmp.push_back("   " + this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back("   " + this->name + "->n = 0;");
        tmp.push_back("   " + this->name + "->hash = g_hash_table_new(g_str_hash, g_str_equal);");
        tmp.push_back("   DEBUG_NEW(" + this->name + "->id);");
        tmp.push_back("}");
    } else {
        tmp.push_back("ghash_t* " + this->name + " = (ghash_t*)malloc(sizeof(ghash_t));");
        tmp.push_back(this->name + "->refC = 1;");
        tmp.push_back(this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back(this->name + "->n = 0;");
        tmp.push_back(this->name + "->hash = g_hash_table_new(g_str_hash, g_str_equal);");
        tmp.push_back("DEBUG_NEW(" + this->name + "->id);");
    }
    return tmp;
}

std::vector<std::string> GeneratorGHashTable::insert() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("g_hash_table_insert("+this->name+"->hash,\""+ str_value +"\",\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_hash_table_size("+this->name + "->hash);");
    tmp.push_back("COUNT_INSERT();");
    
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGHashTable::remove() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("g_hash_table_remove("+this->name+"->hash,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_hash_table_size("+this->name + "->hash);");
    tmp.push_back("COUNT_REMOVE();");
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGHashTable::contains(bool shouldReturn) {
    std::vector<std::string> tmp = {};
    int value = rand() % 100;

    std::string str_value = std::to_string(value);
     
    tmp.push_back("g_hash_table_contains("+this->name+"->hash,\""+ str_value +"\");");
    tmp.push_back("COUNT_CONTAINS();");
    
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGHashTable::free() {
    std::vector<std::string> tmp = {};

    tmp.push_back(this->name + "->refC--;");
    tmp.push_back("if(" + this->name + "->refC == 0){");
    tmp.push_back("	g_hash_table_remove_all("+this->name + "->hash);");
    tmp.push_back("	" + this->name + "->n = 0;");
    tmp.push_back("  DEBUG_FREE(" + this->name + "->id);");
    tmp.push_back("	free("+this->name+");");
    tmp.push_back("}");
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGHashTable::genGlobalVars() {
    std::vector<std::string> tmp = {};

    tmp.push_back("typedef struct ghash_t {");
    tmp.push_back("     GHashTable* hash;");
    tmp.push_back("     size_t refC;");
    tmp.push_back("     int id;");
    tmp.push_back("     unsigned int n;");
    tmp.push_back("} ghash_t;");

    tmp.push_back("typedef struct {");
    tmp.push_back("   ghash_t** data;");
    tmp.push_back("   size_t size;");
    tmp.push_back("} " + this->typeString + "_param;");
    return tmp;
}

std::vector<std::string> GeneratorGHashTable::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> tmp = {};
    tmp.push_back(this->typeString + "_param " + paramName + ";");
    tmp.push_back(paramName + ".size = " + std::to_string(varsParams.size()) + ";");
    tmp.push_back(paramName + ".data = (" + this->typeString + "**)malloc(" + paramName + ".size*sizeof(" + this->typeString + "*));");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        tmp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }

    return tmp;
}

GeneratorGList::GeneratorGList(int id) {
    this->typeString = "glist_t";
    this->id = id;
    this->name = VarTypes::GLIST + std::to_string(id);
}

GeneratorGList::~GeneratorGList() {
}

std::vector<std::string> GeneratorGList::genIncludes() {
    std::vector<std::string> temp = {};
    temp.push_back("#include <stdbool.h>");
    temp.push_back("#include <glib.h>");
    return temp;
}

std::vector<std::string> GeneratorGList::new_(bool inFunction) {
    std::vector<std::string> tmp = {};

    if (inFunction) {
        tmp.push_back("glist_t* " + this->name + ";");
        tmp.push_back("if (pCounter > 0) {");
        tmp.push_back("   " + this->name + " = vars->data[--pCounter];");
        tmp.push_back("   " + this->name + "->refC++;");
        tmp.push_back("   DEBUG_COPY(" + this->name + "->id);");
        tmp.push_back("} else {");
        tmp.push_back("   " + this->name + " = (glist_t*)malloc(sizeof(glist_t));");
        tmp.push_back("   " + this->name + "->refC = 1;");
        tmp.push_back("   " + this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back("   " + this->name + "->n = 0;");
        tmp.push_back("   " + this->name + "->list = NULL;");
        tmp.push_back("   DEBUG_NEW(" + this->name + "->id);");
        tmp.push_back("}");
    } else {
        tmp.push_back("glist_t* " + this->name + " = (glist_t*)malloc(sizeof(glist_t));");
        tmp.push_back(this->name + "->refC = 1;");
        tmp.push_back(this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back(this->name + "->n = 0;");
        tmp.push_back(this->name + "->list = NULL;");
        tmp.push_back("DEBUG_NEW(" + this->name + "->id);");
    }
    return tmp;
}

std::vector<std::string> GeneratorGList::insert() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back(this->name+"->list = g_list_append("+this->name+"->list,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_list_length("+this->name + "->list);");
    tmp.push_back("COUNT_INSERT();");
    
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGList::remove() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back(this->name+"->list = g_list_remove("+this->name+"->list,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_list_length("+this->name + "->list);");
    tmp.push_back("COUNT_REMOVE();");
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGList::contains(bool shouldReturn) {
    std::vector<std::string> tmp = {};
    int value = rand() % 100;

    std::string str_value = std::to_string(value);

    tmp.push_back("g_list_find("+this->name+"->list,\""+ str_value +"\");");
    tmp.push_back("COUNT_CONTAINS();");
    
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGList::free() {
    std::vector<std::string> tmp = {};

    tmp.push_back(this->name + "->refC--;");
    tmp.push_back("if(" + this->name + "->refC == 0){");
    tmp.push_back("	g_list_free("+this->name + "->list);");
    tmp.push_back("	" + this->name + "->n = 0;");
    tmp.push_back("  DEBUG_FREE(" + this->name + "->id);");
    tmp.push_back("	free("+this->name+");");
    tmp.push_back("}");
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGList::genGlobalVars() {
    std::vector<std::string> tmp = {};

    tmp.push_back("typedef struct glist_t {");
    tmp.push_back("     GList* list;");
    tmp.push_back("     size_t refC;");
    tmp.push_back("     int id;");
    tmp.push_back("     unsigned int n;");
    tmp.push_back("} glist_t;");

    tmp.push_back("typedef struct {");
    tmp.push_back("   glist_t** data;");
    tmp.push_back("   size_t size;");
    tmp.push_back("} " + this->typeString + "_param;");
    return tmp;
}

std::vector<std::string> GeneratorGList::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> tmp = {};
    tmp.push_back(this->typeString + "_param " + paramName + ";");
    tmp.push_back(paramName + ".size = " + std::to_string(varsParams.size()) + ";");
    tmp.push_back(paramName + ".data = (" + this->typeString + "**)malloc(" + paramName + ".size*sizeof(" + this->typeString + "*));");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        tmp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }

    return tmp;
}

GeneratorGArray::GeneratorGArray(int id) {
    this->typeString = "garray_t";
    this->id = id;
    this->name = VarTypes::GARRAY + std::to_string(id);
}

GeneratorGArray::~GeneratorGArray() {
}

std::vector<std::string> GeneratorGArray::genIncludes() {
    std::vector<std::string> temp = {};
    temp.push_back("#include <stdbool.h>");
    temp.push_back("#include <glib.h>");
    return temp;
}

std::vector<std::string> GeneratorGArray::new_(bool inFunction) {
    std::vector<std::string> tmp = {};

    if (inFunction) {
        tmp.push_back("garray_t* " + this->name + ";");
        tmp.push_back("if (pCounter > 0) {");
        tmp.push_back("   " + this->name + " = vars->data[--pCounter];");
        tmp.push_back("   " + this->name + "->refC++;");
        tmp.push_back("   DEBUG_COPY(" + this->name + "->id);");
        tmp.push_back("} else {");
        tmp.push_back("   " + this->name + " = (garray_t*)malloc(sizeof(garray_t));");
        tmp.push_back("   " + this->name + "->refC = 1;");
        tmp.push_back("   " + this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back("   " + this->name + "->n = 0;");
        tmp.push_back("   " + this->name + "->garray = g_array_new(FALSE, FALSE, sizeof(gint));;");
        tmp.push_back("   DEBUG_NEW(" + this->name + "->id);");
        tmp.push_back("}");
    } else {
        tmp.push_back("garray_t* " + this->name + " = (garray_t*)malloc(sizeof(garray_t));");
        tmp.push_back(this->name + "->refC = 1;");
        tmp.push_back(this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back(this->name + "->n = 0;");
        tmp.push_back(this->name + "->garray = g_array_new(FALSE, FALSE, sizeof(gint));");
        tmp.push_back("DEBUG_NEW(" + this->name + "->id);");
    }
    return tmp;
}

std::vector<std::string> GeneratorGArray::insert() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("gint var"+std::to_string(VariableFactory::var_counter)+" = "+str_value+";");
    tmp.push_back("g_array_append_val("+this->name+"->garray, var"+std::to_string(VariableFactory::var_counter)+");");
    tmp.push_back(this->name + "->n = " + this->name+"->garray->len;");
    tmp.push_back("COUNT_INSERT();");
    
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGArray::remove() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("for (guint i = 0; i < "+this->name+"->garray->len; i++) {");
    tmp.push_back("	if (g_array_index("+this->name+"->garray, gint, i) == "+str_value+") {");
    tmp.push_back("		g_array_remove_index("+this->name+"->garray, i);");
    tmp.push_back("	}");
    tmp.push_back("}");
    tmp.push_back("COUNT_REMOVE();");
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGArray::contains(bool shouldReturn) {
    std::vector<std::string> tmp = {};
    int value = rand() % 100;

    std::string str_value = std::to_string(value);
    
    tmp.push_back("bool find"+std::to_string(VariableFactory::var_counter)+" = FALSE;");
    
    tmp.push_back("for (guint i = 0; i < "+this->name+"->garray->len; i++) {");
    tmp.push_back("	if(g_array_index("+this->name+"->garray, gint, i) == "+str_value+"){");
    tmp.push_back("		find"+std::to_string(VariableFactory::var_counter)+" = TRUE;");
    tmp.push_back("		i = "+this->name+"->garray->len;");
    tmp.push_back("	}");
    tmp.push_back("}");
    tmp.push_back("COUNT_CONTAINS();");
    
    
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGArray::free() {
    std::vector<std::string> tmp = {};

    tmp.push_back(this->name + "->refC--;");
    tmp.push_back("if(" + this->name + "->refC == 0){");
    tmp.push_back("	g_array_free("+this->name + "->garray,TRUE);");
    tmp.push_back("	" + this->name + "->n = 0;");
    tmp.push_back("  DEBUG_FREE(" + this->name + "->id);");
    tmp.push_back("	free("+this->name+");");
    tmp.push_back("}");
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGArray::genGlobalVars() {
    std::vector<std::string> tmp = {};

    tmp.push_back("typedef struct garray_t {");
    tmp.push_back("     GArray* garray;");
    tmp.push_back("     size_t refC;");
    tmp.push_back("     int id;");
    tmp.push_back("     unsigned int n;");
    tmp.push_back("} garray_t;");

    tmp.push_back("typedef struct {");
    tmp.push_back("   garray_t** data;");
    tmp.push_back("   size_t size;");
    tmp.push_back("} " + this->typeString + "_param;");
    return tmp;
}

std::vector<std::string> GeneratorGArray::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> tmp = {};
    tmp.push_back(this->typeString + "_param " + paramName + ";");
    tmp.push_back(paramName + ".size = " + std::to_string(varsParams.size()) + ";");
    tmp.push_back(paramName + ".data = (" + this->typeString + "**)malloc(" + paramName + ".size*sizeof(" + this->typeString + "*));");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        tmp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }

    return tmp;
}

GeneratorGTree::GeneratorGTree(int id) {
    this->typeString = "gtree_t";
    this->id = id;
    this->name = VarTypes::GTREE + std::to_string(id);
}

GeneratorGTree::~GeneratorGTree() {
}

std::vector<std::string> GeneratorGTree::genIncludes() {
    std::vector<std::string> temp = {};
    temp.push_back("#include <stdbool.h>");
    temp.push_back("#include <glib.h>");
    return temp;
}

std::vector<std::string> GeneratorGTree::new_(bool inFunction) {
    std::vector<std::string> tmp = {};

    if (inFunction) {
        tmp.push_back("gtree_t* " + this->name + ";");
        tmp.push_back("if (pCounter > 0) {");
        tmp.push_back("   " + this->name + " = vars->data[--pCounter];");
        tmp.push_back("   " + this->name + "->refC++;");
        tmp.push_back("   DEBUG_COPY(" + this->name + "->id);");
        tmp.push_back("} else {");
        tmp.push_back("   " + this->name + " = (gtree_t*)malloc(sizeof(gtree_t));");
        tmp.push_back("   " + this->name + "->refC = 1;");
        tmp.push_back("   " + this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back("   " + this->name + "->n = 0;");
        tmp.push_back("   " + this->name + "->tree = g_tree_new((GCompareFunc)g_strcmp0);");
        tmp.push_back("   DEBUG_NEW(" + this->name + "->id);");
        tmp.push_back("}");
    } else {
        tmp.push_back("gtree_t* " + this->name + " = (gtree_t*)malloc(sizeof(gtree_t));");
        tmp.push_back(this->name + "->refC = 1;");
        tmp.push_back(this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back(this->name + "->n = 0;");
        tmp.push_back(this->name + "->tree = g_tree_new((GCompareFunc)g_strcmp0);");
        tmp.push_back("DEBUG_NEW(" + this->name + "->id);");
    }
    return tmp;
}

std::vector<std::string> GeneratorGTree::insert() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("g_tree_insert("+this->name+"->tree,\""+ str_value +"\",\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_tree_height("+this->name + "->tree);");
    tmp.push_back("COUNT_INSERT();");
    
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGTree::remove() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("g_tree_remove("+this->name+"->tree,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_tree_height("+this->name + "->tree);");
    tmp.push_back("COUNT_REMOVE();");
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGTree::contains(bool shouldReturn) {
    std::vector<std::string> tmp = {};
    int value = rand() % 100;

    std::string str_value = std::to_string(value);
     
    tmp.push_back("g_tree_lookup("+this->name+"->tree,\""+ str_value +"\");");
    tmp.push_back("COUNT_CONTAINS();");
    
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGTree::free() {
    std::vector<std::string> tmp = {};

    tmp.push_back(this->name + "->refC--;");
    tmp.push_back("if(" + this->name + "->refC == 0){");
    tmp.push_back("	g_tree_destroy("+this->name + "->tree);");
    tmp.push_back("	" + this->name + "->n = 0;");
    tmp.push_back(" DEBUG_FREE(" + this->name + "->id);");
    tmp.push_back("	free("+this->name+");");
    tmp.push_back("}");
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGTree::genGlobalVars() {
    std::vector<std::string> tmp = {};

    tmp.push_back("typedef struct gtree_t {");
    tmp.push_back("     GTree* tree;");
    tmp.push_back("     size_t refC;");
    tmp.push_back("     int id;");
    tmp.push_back("     unsigned int n;");
    tmp.push_back("} gtree_t;");

    tmp.push_back("typedef struct {");
    tmp.push_back("   gtree_t** data;");
    tmp.push_back("   size_t size;");
    tmp.push_back("} " + this->typeString + "_param;");
    return tmp;
}

std::vector<std::string> GeneratorGTree::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> tmp = {};
    tmp.push_back(this->typeString + "_param " + paramName + ";");
    tmp.push_back(paramName + ".size = " + std::to_string(varsParams.size()) + ";");
    tmp.push_back(paramName + ".data = (" + this->typeString + "**)malloc(" + paramName + ".size*sizeof(" + this->typeString + "*));");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        tmp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }

    return tmp;
}

GeneratorGQueue::GeneratorGQueue(int id) {
    this->typeString = "gqueue_t";
    this->id = id;
    this->name = VarTypes::GTREE + std::to_string(id);
}

GeneratorGQueue::~GeneratorGQueue() {
}

std::vector<std::string> GeneratorGQueue::genIncludes() {
    std::vector<std::string> temp = {};
    temp.push_back("#include <stdbool.h>");
    temp.push_back("#include <glib.h>");
    return temp;
}

std::vector<std::string> GeneratorGQueue::new_(bool inFunction) {
    std::vector<std::string> tmp = {};

    if (inFunction) {
        tmp.push_back("gqueue_t* " + this->name + ";");
        tmp.push_back("if (pCounter > 0) {");
        tmp.push_back("   " + this->name + " = vars->data[--pCounter];");
        tmp.push_back("   " + this->name + "->refC++;");
        tmp.push_back("   DEBUG_COPY(" + this->name + "->id);");
        tmp.push_back("} else {");
        tmp.push_back("   " + this->name + " = (gqueue_t*)malloc(sizeof(gqueue_t));");
        tmp.push_back("   " + this->name + "->refC = 1;");
        tmp.push_back("   " + this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back("   " + this->name + "->n = 0;");
        tmp.push_back("   " + this->name + "->queue = g_queue_new();");
        tmp.push_back("   DEBUG_NEW(" + this->name + "->id);");
        tmp.push_back("}");
    } else {
        tmp.push_back("gqueue_t* " + this->name + " = (gqueue_t*)malloc(sizeof(gqueue_t));");
        tmp.push_back(this->name + "->refC = 1;");
        tmp.push_back(this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back(this->name + "->n = 0;");
        tmp.push_back(this->name + "->queue = g_queue_new();");
        tmp.push_back("DEBUG_NEW(" + this->name + "->id);");
    }
    return tmp;
}

std::vector<std::string> GeneratorGQueue::insert() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("g_queue_push_tail("+this->name+"->queue,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_queue_get_length("+this->name + "->queue);");
    tmp.push_back("COUNT_INSERT();");
    
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGQueue::remove() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("g_queue_remove("+this->name+"->queue,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = g_queue_get_length("+this->name + "->queue);");
    tmp.push_back("COUNT_REMOVE();");
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGQueue::contains(bool shouldReturn) {
    std::vector<std::string> tmp = {};
    int value = rand() % 100;

    std::string str_value = std::to_string(value);
     
    tmp.push_back("g_queue_find("+this->name+"->queue,\""+ str_value +"\");");
    tmp.push_back("COUNT_CONTAINS();");
    
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGQueue::free() {
    std::vector<std::string> tmp = {};

    tmp.push_back(this->name + "->refC--;");
    tmp.push_back("if(" + this->name + "->refC == 0){");
    tmp.push_back("	g_queue_free("+this->name + "->queue);");
    tmp.push_back("	" + this->name + "->n = 0;");
    tmp.push_back(" DEBUG_FREE(" + this->name + "->id);");
    tmp.push_back("	free("+this->name+");");
    tmp.push_back("}");
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGQueue::genGlobalVars() {
    std::vector<std::string> tmp = {};

    tmp.push_back("typedef struct gqueue_t {");
    tmp.push_back("     GQueue* queue;");
    tmp.push_back("     size_t refC;");
    tmp.push_back("     int id;");
    tmp.push_back("     unsigned int n;");
    tmp.push_back("} gqueue_t;");

    tmp.push_back("typedef struct {");
    tmp.push_back("   gqueue_t** data;");
    tmp.push_back("   size_t size;");
    tmp.push_back("} " + this->typeString + "_param;");
    return tmp;
}

std::vector<std::string> GeneratorGQueue::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> tmp = {};
    tmp.push_back(this->typeString + "_param " + paramName + ";");
    tmp.push_back(paramName + ".size = " + std::to_string(varsParams.size()) + ";");
    tmp.push_back(paramName + ".data = (" + this->typeString + "**)malloc(" + paramName + ".size*sizeof(" + this->typeString + "*));");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        tmp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }

    return tmp;
}


GeneratorGString::GeneratorGString(int id) {
    this->typeString = "gstring_t";
    this->id = id;
    this->name = VarTypes::GSTRING + std::to_string(id);
}

GeneratorGString::~GeneratorGString() {
}

std::vector<std::string> GeneratorGString::genIncludes() {
    std::vector<std::string> temp = {};
    temp.push_back("#include <stdbool.h>");
    temp.push_back("#include <glib.h>");
    return temp;
}

std::vector<std::string> GeneratorGString::new_(bool inFunction) {
    std::vector<std::string> tmp = {};

    if (inFunction) {
        tmp.push_back("gstring_t* " + this->name + ";");
        tmp.push_back("if (pCounter > 0) {");
        tmp.push_back("   " + this->name + " = vars->data[--pCounter];");
        tmp.push_back("   " + this->name + "->refC++;");
        tmp.push_back("   DEBUG_COPY(" + this->name + "->id);");
        tmp.push_back("} else {");
        tmp.push_back("   " + this->name + " = (gstring_t*)malloc(sizeof(gstring_t));");
        tmp.push_back("   " + this->name + "->refC = 1;");
        tmp.push_back("   " + this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back("   " + this->name + "->n = 0;");
        tmp.push_back("   " + this->name + "->gstring = g_string_new();");
        tmp.push_back("   DEBUG_NEW(" + this->name + "->id);");
        tmp.push_back("}");
    } else {
        tmp.push_back("gstring_t* " + this->name + " = (gstring_t*)malloc(sizeof(gstring_t));");
        tmp.push_back(this->name + "->refC = 1;");
        tmp.push_back(this->name + "->id = " + std::to_string(this->id) + ";");
        tmp.push_back(this->name + "->n = 0;");
        tmp.push_back(this->name + "->gstring = g_string_new();");
        tmp.push_back("DEBUG_NEW(" + this->name + "->id);");
    }
    return tmp;
}

std::vector<std::string> GeneratorGString::insert() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("g_string_append("+this->name+"->gstring->str,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = "+this->name + "->gstring->len);");
    tmp.push_back("COUNT_INSERT();");
    
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGString::remove() {
    std::vector<std::string> tmp = {};

    int value = rand() % 100;
    std::string str_value = std::to_string(value);

    tmp.push_back("strstr("+this->name+"->gstring->str,\""+ str_value +"\");");
    tmp.push_back(this->name + "->n = "+this->name + "->gstring->len);");
    tmp.push_back("COUNT_REMOVE();");
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGString::contains(bool shouldReturn) {
    std::vector<std::string> tmp = {};
    int value = rand() % 100;

    std::string str_value = std::to_string(value);
     
    tmp.push_back("strstr("+this->name+"->gstring->str,\""+ str_value +"\");");
    tmp.push_back("COUNT_CONTAINS();");
    
    VariableFactory::var_counter++;

    return tmp;
}

std::vector<std::string> GeneratorGString::free() {
    std::vector<std::string> tmp = {};

    tmp.push_back(this->name + "->refC--;");
    tmp.push_back("if(" + this->name + "->refC == 0){");
    tmp.push_back("	g_string_free("+this->name + "->gstring, 1);");
    tmp.push_back("	" + this->name + "->n = 0;");
    tmp.push_back(" DEBUG_FREE(" + this->name + "->id);");
    tmp.push_back("	free("+this->name+");");
    tmp.push_back("}");
    VariableFactory::var_counter++;
    return tmp;
}

std::vector<std::string> GeneratorGString::genGlobalVars() {
    std::vector<std::string> tmp = {};

    tmp.push_back("typedef struct gstring_t {");
    tmp.push_back("     GString* gstring;");
    tmp.push_back("     size_t refC;");
    tmp.push_back("     int id;");
    tmp.push_back("     unsigned int n;");
    tmp.push_back("} gstring_t;");

    tmp.push_back("typedef struct {");
    tmp.push_back("   gstring_t** data;");
    tmp.push_back("   size_t size;");
    tmp.push_back("} " + this->typeString + "_param;");
    return tmp;
}

std::vector<std::string> GeneratorGString::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> tmp = {};
    tmp.push_back(this->typeString + "_param " + paramName + ";");
    tmp.push_back(paramName + ".size = " + std::to_string(varsParams.size()) + ";");
    tmp.push_back(paramName + ".data = (" + this->typeString + "**)malloc(" + paramName + ".size*sizeof(" + this->typeString + "*));");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        tmp.push_back(paramName + ".data[" + std::to_string(i) + "] = " + varsParams[i]->name + ";");
    }

    return tmp;
}
