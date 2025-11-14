#ifndef ODINAST_H
#define ODINAST_H

#include <cmath>

#include "../../generator/languageGenerator.h"
#include "../../shared/enums.h"
#include "../../shared/globalStructs.h"
#include "../languageAst.h"

void odinprintIndentationSpaces(int indent);

std::string odingenerateIfCondition(ProgrammingLanguageGenerator& generator);

class OdinStatementCode : public StatementCode {
   public:
    OdinStatementCode(std::shared_ptr<Node> stmt, std::shared_ptr<Node> code) : StatementCode(stmt, code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int) override;
    ~OdinStatementCode() = default;
};

class OdinLambdaCode : public LambdaCode {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinLambdaCode() = default;
};

class OdinId : public Id {
   public:
    OdinId(std::string id) : Id(id) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinId() = default;
};

class OdinInsert : public Insert {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinInsert() = default;
};

class OdinRemove : public Remove {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinRemove() = default;
};

class OdinNew : public New {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinNew() = default;
};

class OdinContains : public Contains {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinContains() = default;
};

class OdinLoop : public Loop {
   public:
    OdinLoop(std::shared_ptr<Node> code) : Loop(code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinLoop() = default;
};

class OdinCall : public Call {
   public:
    ~OdinCall(){};
    OdinCall(int id, std::shared_ptr<Node> code) : Call(id, code) {}
    OdinCall(){};
    void setId(int id) override { this->id = id; };
    void setCode(std::shared_ptr<Node> code) override { this->code = code; };
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
};

class OdinSeq : public Seq {
   public:
    OdinSeq(std::shared_ptr<Node> code) : Seq(code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinSeq() = default;
};

class OdinIf : public If {
   public:
    OdinIf(std::shared_ptr<Node> c1, std::shared_ptr<Node> c2) : If(c1, c2) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~OdinIf() = default;
};

#endif
