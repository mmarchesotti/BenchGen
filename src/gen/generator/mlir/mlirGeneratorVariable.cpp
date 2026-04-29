#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include "mlirGeneratorVariable.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "../../shared/consts.h"

RegisterControl* regcontrol = new RegisterControl();

MlirGeneratorScalar::~MlirGeneratorScalar() {}

MlirGeneratorScalar::MlirGeneratorScalar(int totalSize, int id) {
    this->totalSize = totalSize;
    this->id = id;
}

std::string MlirGeneratorScalar::randomIntType() {
    static std::vector<std::string> types = {"i8", "i16", "i32", "i64"};
    return types[(int)rand() % types.size()];
}

int MlirGeneratorScalar::bitWidth(const std::string &type) {
    return std::stoi(type.substr(1));
}

void MlirGeneratorScalar::beginScope() {
    regcontrol->scopeStack.push_back(regcontrol->registers.size());
}

void MlirGeneratorScalar::removeVars() {
    if (!regcontrol->scopeStack.empty()) {
        regcontrol->registers.resize(regcontrol->scopeStack.back());
    }
}

void MlirGeneratorScalar::finalScope() {
    this->removeVars();
    regcontrol->scopeStack.pop_back();
}

std::string MlirGeneratorScalar::maxType(const std::string &a, const std::string &b) {
    return bitWidth(a) >= bitWidth(b) ? a : b;
}

std::string RegisterControl::newRegister(const std::string &type) {
    std::string reg = "%r" + std::to_string(regcontrol->regCounter++);
    this->registers.push_back({reg, type});
    return reg;
}

RegInfo RegisterControl::randomRegister() {
    int idx = (int)rand() % regcontrol->registers.size();
    return this->registers[idx];
}

std::string RegisterControl::castIfNeeded(
    RegInfo &reg,
    const std::string &targetType,
    std::vector<std::string> &lines)
{
    if (reg.type == targetType)
        return reg.name;

    std::string newReg = this->newRegister(targetType);

    lines.push_back(
        "    " + newReg + " = arith.extsi " +
        reg.name + " : " + reg.type +
        " to " + targetType
    );

    return newReg;
}


std::vector<std::string> MlirGeneratorScalar::new_(bool) {
    std::vector<std::string> lines;

    int n = (int)rand() % 5 + 1;
    
    lines.push_back("    %c0 = arith.constant 0 : index");
    lines.push_back("    %c2 = arith.constant 0 : i1");
    lines.push_back("    %c10 = arith.constant " + std::to_string((int)rand() % 100) + " : index");
    lines.push_back("    %c1 = arith.constant 1 : index");

    for (int i = 0; i < n; i++) {
        std::string type = randomIntType();
        std::string r = regcontrol->newRegister(type);

        lines.push_back(
            "    " + r +
            " = arith.constant 0 : " + type
        );
    }

    return lines;
}

std::vector<std::string> MlirGeneratorScalar::arithmetic(std::string opt) {
    std::vector<std::string> lines;

    if (regcontrol->registers.size() < 2)
        return lines;

    RegInfo A = regcontrol->randomRegister();
    RegInfo B = regcontrol->randomRegister();

    std::string targetType = maxType(A.type, B.type);

    std::string a = regcontrol->castIfNeeded(A, targetType, lines);
    std::string b = regcontrol->castIfNeeded(B, targetType, lines);

    std::string c = regcontrol->newRegister(targetType);

    if (opt == "+")
        lines.push_back("    " + c + " = arith.addi " + a + ", " + b + " : " + targetType);
    else if (opt == "-")
        lines.push_back("    " + c + " = arith.subi " + a + ", " + b + " : " + targetType);
    else if (opt == "*")
        lines.push_back("    " + c + " = arith.muli " + a + ", " + b + " : " + targetType);

    return lines;
}

std::vector<std::string> MlirGeneratorScalar::conditional() {
    
}


std::vector<std::string> MlirGeneratorScalar::logical(bool) {
    std::vector<std::string> lines;

    RegInfo A = regcontrol->randomRegister();
    RegInfo B = regcontrol->randomRegister();

    std::string targetType = maxType(A.type, B.type);

    std::string a = regcontrol->castIfNeeded(A, targetType, lines);
    std::string b = regcontrol->castIfNeeded(B, targetType, lines);
    

    if (A.type != "i1") {
        std::string tmp = regcontrol->newRegister("i1");
        std::string newReg = regcontrol->newRegister(A.type);
        lines.push_back(newReg+" = arith.extsi %c2 : i1 to " + a);    
        lines.push_back("    " + tmp + " = arith.cmpi ne, " +
                        a + ", "+newReg+" : " + a);
        A = {tmp, "i1"};
    }

    if (B.type != "i1") {
        std::string tmp = regcontrol->newRegister("i1");
        std::string newReg = regcontrol->newRegister(B.type);
        lines.push_back(newReg+" = arith.extsi %c2 : i1 to " + b);
        lines.push_back("    " + tmp + " = arith.cmpi ne, " +
                        b + ", "+newReg+" : " + b);
        B = {tmp, "i1"};
    }

    std::string res = regcontrol->newRegister("i1");

    lines.push_back("    " + res + " = arith.andi " +
                    a + ", " + b + " : i1");

    return lines;
}

std::vector<std::string> MlirGeneratorScalar::incdec(bool isInc) {
    std::vector<std::string> lines;

    RegInfo A = regcontrol->randomRegister();
    
    std::string one = regcontrol->newRegister(A.type);
    lines.push_back("    " + one + " = arith.constant 1 : " + A.type);

    std::string res = regcontrol->newRegister(A.type);

    std::string op = isInc ? "addi" : "subi";

    lines.push_back("    " + res + " = arith." + op + " " +
                    A.name + ", " + one + " : " + A.type);

    return lines;
}

std::vector<std::string> MlirGeneratorScalar::call(std::string funcName) {
    std::vector<std::string> lines;

    RegInfo arg = regcontrol->randomRegister();

    std::string res = regcontrol->newRegister(arg.type);

    lines.push_back("    " + res +
                    " = func.call @" + funcName +
                    "(" + arg.name + ") : (" +
                    arg.type + ") -> " + arg.type);

    return lines;
}

std::vector<std::string> MlirGeneratorScalar::unary(std::string op) {
    std::vector<std::string> lines;

    if (regcontrol->registers.empty())
        return lines;

    RegInfo src = regcontrol->randomRegister();
    std::string dst = regcontrol->newRegister(src.type);

    if (op == "-") {
        lines.push_back(
            "    " + dst +
            " = arith.negsi " +
            src.name + " : " + src.type
        );
    }
    else {
        lines.push_back(
            "    " + dst +
            " = arith.addi " +
            src.name + ", 0 : " + src.type
        );
    }

    return lines;
}

std::vector<std::string> MlirGeneratorScalar::select(bool) {
    std::vector<std::string> lines;

    RegInfo cond = regcontrol->randomRegister();
    RegInfo A = regcontrol->randomRegister();
    RegInfo B = regcontrol->randomRegister();

    if (cond.type != "i1") {
        std::string tmp = regcontrol->newRegister("i1");

        std::string newReg = regcontrol->newRegister(cond.type);
        lines.push_back(newReg+" = arith.extsi %c2 : i1 to " + cond.type);
        lines.push_back("    " + tmp +
                        " = arith.cmpi ne, " +
                        cond.name + ", "+newReg+" : " + cond.type);
        cond = {tmp, "i1"};
    }

    std::string targetType = maxType(A.type, B.type);

    std::string a = regcontrol->castIfNeeded(A, targetType, lines);
    std::string b = regcontrol->castIfNeeded(B, targetType, lines);

    std::string res = regcontrol->newRegister(targetType);

    lines.push_back("    " + res +
                    " = arith.select " +
                    cond.name + ", " +
                    a + ", " + b +
                    " : " + targetType);

    return lines;
}


std::vector<std::string> MlirGeneratorScalar::logical_sc(bool) {
    std::vector<std::string> lines;

    RegInfo A = regcontrol->randomRegister();
    RegInfo B = regcontrol->randomRegister();

    if (A.type != "i1") {
        std::string tmp = regcontrol->newRegister("i1");

        std::string targetType_a = maxType(A.type, "i16");
        std::string newReg = regcontrol->newRegister(targetType_a);
        lines.push_back(newReg+" = arith.extsi %c2 : i1 to " + targetType_a);
        lines.push_back("    " + tmp +
                        " = arith.cmpi ne, " +
                        A.name + ", "+newReg+" : " + A.type);
        A = {tmp, "i1"};
    }

    if (B.type != "i1") {
        std::string tmp = regcontrol->newRegister("i1");
        std::string newReg = regcontrol->newRegister(B.type);
        lines.push_back(newReg+" = arith.extsi %c2 : i1 to " + B.type);
        lines.push_back("    " + tmp +
                        " = arith.cmpi ne, " +
                        B.name + ", "+newReg+" : " + B.type);
        B = {tmp, "i1"};
    }

    std::string res = regcontrol->newRegister("i1");

    lines.push_back("    " + res +
                    " = arith.ori " +
                    A.name + ", " + B.name +
                    " : i1");

    return lines;
}


std::vector<std::string> MlirGeneratorScalar::reduction() {
    std::vector<std::string> lines;

    std::string type = randomIntType();

    std::string acc = regcontrol->newRegister(type);
    lines.push_back("    " + acc +
                    " = arith.constant 0 : " + type);

    std::string i = regcontrol->newRegister(type);
    
    lines.push_back("    scf.for " + i +
                    " = %c0 to %c10 step %c1 {");
        
    std::string sum = regcontrol->newRegister(type);
    lines.push_back(i+"_"+type+" = arith.index_cast " + i + " : index to "+type);
    lines.push_back("        " + sum +
                    " = arith.addi " +
                    acc + ", " + i +
                    "_"+type+" : " + type);

    lines.push_back("    }");

    return lines;
}

std::vector<std::string> MlirGeneratorScalar::free() {
    return {};
}