#include "rustGeneratorVariable.h"

// ARRAY

RustGeneratorArray::RustGeneratorArray(int size, int id) {
    this->typeString = "Array";
    this->totalSize = size;
    this->id = id;
    this->name = VarTypes::ARRAY + std::to_string(id);
}

std::vector<std::string> RustGeneratorArray::new_(bool inFunction) {
    std::vector<std::string> temp = {};
    if (inFunction) {
        temp.push_back("let " + this->name + " = Array::new_infunc(vars, &mut pCounter, " +
                       std::to_string(this->totalSize) + ", " + std::to_string(this->id) + ");");
    } else {
        temp.push_back("let " + this->name + " = Array::new_outfunc(" +
                       std::to_string(this->totalSize) + ", " + std::to_string(this->id) + ");");
    }
    return temp;
}

std::vector<std::string> RustGeneratorArray::insert() {
    return {"array_insert(&" + this->name + ");"};
}

std::vector<std::string> RustGeneratorArray::remove() {
    return {"array_remove(&" + this->name + ");"};
}

std::vector<std::string> RustGeneratorArray::contains(bool shouldReturn) {
    int compare = rand() % 100;  // Random value to compare against
    return {"let _ = array_contains(&" + this->name + ", " + std::to_string(compare) + ");"};
}

std::vector<std::string> RustGeneratorArray::free() {
    return {"array_free(&" + this->name + ");"};
}

std::vector<std::string> RustGeneratorArray::genIncludes() {
    return {};
}

std::vector<std::string> RustGeneratorArray::genGlobalVars() {
    return {
        "pub struct Array {",
        "    pub data: Vec<u32>,",
        "    pub size: usize,",
        "    pub refc: usize,",
        "    pub id: i32,",
        "}",
        "",
        "pub type ArrayRc = std::rc::Rc<std::cell::RefCell<Array>>;",
        "",
        "pub struct ArrayParam {",
        "    pub data: Vec<ArrayRc>,",
        "}",
        "",
        "impl Array {",
        "    pub fn new_infunc(vars: &mut ArrayParam, p_counter: &mut usize, size: usize, id: i32) -> ArrayRc {",
        "        if *p_counter > 0 {",
        "            *p_counter -= 1;",
        "            let obj = vars.data.swap_remove(*p_counter);",
        "            obj.borrow_mut().refc += 1;",
        "            obj",
        "        } else {",
        "            std::rc::Rc::new(std::cell::RefCell::new(Array { data: vec![0u32; size], size, refc: 1, id }))",
        "        }",
        "    }",
        "    pub fn new_outfunc(size: usize, id: i32) -> ArrayRc {",
        "        std::rc::Rc::new(std::cell::RefCell::new(Array { data: vec![0u32; size], size, refc: 1, id }))",
        "    }",
        "}",
        "",
        "pub fn array_insert(a: &ArrayRc) {",
        "    let mut x = a.borrow_mut();",
        "    for v in x.data.iter_mut() { *v = v.wrapping_add(1); }",
        "}",
        "pub fn array_remove(a: &ArrayRc) {",
        "    let mut x = a.borrow_mut();",
        "    for v in x.data.iter_mut() { *v = v.wrapping_sub(1); }",
        "}",
        "pub fn array_contains(a: &ArrayRc, compare: u32) -> bool {",
        "    let mut x = a.borrow_mut();",
        "    let mut found = false;",
        "    for v in x.data.iter_mut() {",
        "        if *v == compare { *v = v.wrapping_add(compare); found = true; }",
        "    }",
        "    found",
        "}",
        "pub fn array_free(a: &ArrayRc) {",
        "    let mut x = a.borrow_mut();",
        "    if x.refc > 0 { x.refc -= 1; }",
        "}",
        "",
    };
}

std::vector<std::string> RustGeneratorArray::genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) {
    std::vector<std::string> temp = {};
    temp.push_back("let mut " + paramName + " = ArrayParam { data: Vec::with_capacity(" +
                   std::to_string(varsParams.size()) + ") };");
    for (int i = 0; i < (int)varsParams.size(); i++) {
        temp.push_back(paramName + ".data.push(std::rc::Rc::clone(&" + varsParams[i]->name + "));");
    }
    return temp;
}

RustGeneratorArray::~RustGeneratorArray() {
}
