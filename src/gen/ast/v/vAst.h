#ifndef VAST_H
#define VAST_H

#include <cmath>

#include "../../generator/languageGenerator.h"
#include "../../shared/enums.h"
#include "../../shared/globalStructs.h"
#include "../languageAst.h"

void vprintIndentationSpaces(int indent);
std::string vgenerateIfCondition(ProgrammingLanguageGenerator& generator);

class VStatementCode : public StatementCode {
public:
    VStatementCode(std::shared_ptr<Node> stmt, std::shared_ptr<Node> code) : StatementCode(stmt, code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int) override;
    ~VStatementCode() = default;
};

class VLambdaCode : public LambdaCode {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VLambdaCode() = default;
};

class VId : public Id {
public:
    VId(std::string id) : Id(id) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VId() = default;
};

class VInsert : public Insert {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VInsert() = default;
};

class VRemove : public Remove {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VRemove() = default;
};

class VNew : public New {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VNew() = default;
};

class VContains : public Contains {
public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VContains() = default;
};

class VLoop : public Loop {
public:
    VLoop(std::shared_ptr<Node> code) : Loop(code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VLoop() = default;
};

class VCall : public Call {
public:
    ~VCall() {};
    VCall(int id, std::shared_ptr<Node> code) : Call(id, code) {}
    VCall() {};
    void setId(int id) override { this->id = id; };
    void setCode(std::shared_ptr<Node> code) override { this->code = code; };
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
};

class VSeq : public Seq {
public:
    VSeq(std::shared_ptr<Node> code) : Seq(code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VSeq() = default;
};

class VIf : public If {
public:
    VIf(std::shared_ptr<Node> c1, std::shared_ptr<Node> c2) : If(c1, c2) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~VIf() = default;
};

#endif