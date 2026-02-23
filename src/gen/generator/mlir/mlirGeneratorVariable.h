#ifndef MLIRVARIABLEGENERATOR_H
#define MLIRVARIABLEGENERATOR_H

#include <cstdlib>
#include <memory>
#include <string>

#include "../generatorVariable.h"

struct RegInfo {
    std::string name;
    std::string type;
};

class RegisterControl {
    public:
        int regCounter = 0; 
        std::vector<RegInfo> registers;
        std::vector<size_t> scopeStack;

        RegisterControl(){};
    
        std::string newRegister(const std::string &type);
        RegInfo randomRegister();
    
        std::string castIfNeeded(
            RegInfo &reg,
            const std::string &targetType,
            std::vector<std::string> &lines);
  
};

class MlirGeneratorScalar : public GeneratorScalar {
   public:
    int totalSize;

    MlirGeneratorScalar(){};
    MlirGeneratorScalar(int totalSize, int id);
    ~MlirGeneratorScalar();


    virtual std::vector<std::string> new_(bool inFunction = false) override;
    virtual std::vector<std::string> arithmetic(std::string opt) override;
    virtual std::vector<std::string> conditional() override;
    virtual std::vector<std::string> logical(bool shouldReturn = false) override;
    virtual std::vector<std::string> free() override;
    virtual std::vector<std::string> unary(std::string op) override;
    virtual std::vector<std::string> select(bool shouldReturn) override;
    virtual std::vector<std::string> logical_sc(bool shouldReturn) override;
    virtual std::vector<std::string> incdec(bool isInc) override;
    virtual std::vector<std::string> reduction() override;
    virtual std::vector<std::string> call(std::string funcName) override;

    void beginScope();
    void finalScope();
    void removeVars();

   private:

    std::string randomIntType();
    int bitWidth(const std::string &type);
    std::string maxType(const std::string &a, const std::string &b);
};

extern RegisterControl* regcontrol;

#endif
