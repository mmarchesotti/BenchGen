#ifndef MLIRAST_H
#define MLIRAST_H

#include <cmath>

#include "../../generator/languageGenerator.h"
#include "../../shared/enums.h"
#include "../../shared/globalStructs.h"
#include "../languageAst.h"

void mlirprintIndentationSpaces(int indent);
std::string mlirgenerateIfCondition(ProgrammingLanguageGenerator& generator);

class MlirNew : public New {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~MlirNew() = default;
};

class MlirArithOp : public ArithOp {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirArithOp() = default;
};

class MlirCondOp : public CondOp {
public:
    public:
    MlirCondOp(std::shared_ptr<Node> c1, std::shared_ptr<Node> c2) : CondOp(c1, c2) {
    
    }

    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirCondOp() = default;
};

class MlirLogicOp : public LogicOp {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirLogicOp() = default;
};

class MlirFreeOp : public FreeOp {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirFreeOp() = default;
};

class MlirUnaryOp : public UnaryOp {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirUnaryOp() = default;
};

class MlirSelectOp : public SelectOp {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirSelectOp() = default;
};

class MlirLogicSCOp : public LogicSCOp {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirLogicSCOp() = default;
};

class MlirIncDecOp : public IncDecOp {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirIncDecOp() = default;
};

class MlirReductionOp : public ReductionOp {
public:

    void gen(ProgrammingLanguageGenerator&) override;
    void print(int ident) override;

    ~MlirReductionOp() = default;
};

class MlirStatementCode : public StatementCode {
   public:
    MlirStatementCode(std::shared_ptr<Node> stmt, std::shared_ptr<Node> code) : StatementCode(stmt, code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int) override;
    ~MlirStatementCode() = default;
};

class MlirId : public Id {
   public:
    MlirId(std::string id) : Id(id) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~MlirId() = default;
};

#endif