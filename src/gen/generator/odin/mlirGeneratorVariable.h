#ifndef MLIRVARIABLEGENERATOR_H
#define MLIRVARIABLEGENERATOR_H

#include <cstdlib>
#include <memory>
#include <string>

#include "../generatorVariable.h"

class MlirGeneratorScalar : public GeneratorScalar {
   public:
    int totalSize;

    MlirGeneratorScalar(){};

    MlirGeneratorScalar(int totalSize, std::vector<int> ids);

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

    virtual std::vector<std::string> insert() override;
    virtual std::vector<std::string> remove() override;
    virtual std::vector<std::string> contains(bool shouldReturn = false) override;
    virtual std::vector<std::string> genIncludes() override;
    virtual std::vector<std::string> genGlobalVars() override;
    virtual std::vector<std::string> genParams(std::string paramName, std::vector<GeneratorVariable*> varsParams) override;
};

#endif
