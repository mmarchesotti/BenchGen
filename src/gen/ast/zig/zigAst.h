#ifndef ZIGAST_H
#define ZIGAST_H

#include <cmath>

#include "../../generator/languageGenerator.h"
#include "../../shared/enums.h"
#include "../../shared/globalStructs.h"
#include "../languageAst.h"

void zigprintIndentationSpaces(int indent);

std::string ziggenerateIfCondition(ProgrammingLanguageGenerator& generator);

class ZigStatementCode : public StatementCode {
   public:
    ZigStatementCode(std::shared_ptr<Node> stmt, std::shared_ptr<Node> code) : StatementCode(stmt, code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int) override;
    ~ZigStatementCode() = default;
};

class ZigLambdaCode : public LambdaCode {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigLambdaCode() = default;
};

class ZigId : public Id {
   public:
    ZigId(std::string id) : Id(id) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigId() = default;
};

class ZigInsert : public Insert {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigInsert() = default;
};

class ZigRemove : public Remove {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigRemove() = default;
};

class ZigNew : public New {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigNew() = default;
};

class ZigContains : public Contains {
   public:
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigContains() = default;
};

class ZigLoop : public Loop {
   public:
    ZigLoop(std::shared_ptr<Node> code) : Loop(code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigLoop() = default;
};

class ZigCall : public Call {
   public:
    ~ZigCall(){};
    ZigCall(int id, std::shared_ptr<Node> code) : Call(id, code) {}
    ZigCall(){};
    void setId(int id) override { this->id = id; };
    void setCode(std::shared_ptr<Node> code) override { this->code = code; };
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
};

class ZigSeq : public Seq {
   public:
    ZigSeq(std::shared_ptr<Node> code) : Seq(code) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigSeq() = default;
};

class ZigIf : public If {
   public:
    ZigIf(std::shared_ptr<Node> c1, std::shared_ptr<Node> c2) : If(c1, c2) {}
    void gen(ProgrammingLanguageGenerator&) override;
    void print(int indent) override;
    ~ZigIf() = default;
};

#endif
