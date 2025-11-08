#include "languageAst.h"
#include "c/cAst.h"
#include "cpp/cppAst.h"
#include "go/goAst.h"
#include "julia/juliaAst.h"
#include "rust/rustAst.h"
#include "v/vAst.h"
#include "carbon/carbonAst.h"
#include "zig/zigAst.h"

Insert::~Insert() {};
Remove::~Remove() {};
New::~New() {};
Contains::~Contains() {};
StatementCode::~StatementCode() {};
Loop::~Loop() {};
Call::~Call() {};
Seq::~Seq() {};
If::~If() {};
Id::~Id(){};
LambdaCode::~LambdaCode(){};


void printIndentationSpaces(int ident)
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        cprintIndentationSpaces(ident);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        cppprintIndentationSpaces(ident);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        rustprintIndentationSpaces(ident);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        juliaprintIndentationSpaces(ident);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        goprintIndentationSpaces(ident);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        vprintIndentationSpaces(ident);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        zigprintIndentationSpaces(ident);
    }
}


std::string generateIfCondition(ProgrammingLanguageGenerator& generator)
{
   if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return cgenerateIfCondition(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return cppgenerateIfCondition(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return rustgenerateIfCondition(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return juliagenerateIfCondition(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return gogenerateIfCondition(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return vgenerateIfCondition(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return carbongenerateIfCondition(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ziggenerateIfCondition(generator);
    }
}

Insert get_insert()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CInsert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppInsert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustInsert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaInsert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoInsert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VInsert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonInsert();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigInsert();
    }
}

Remove get_remove()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CRemove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppRemove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustRemove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaRemove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoRemove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VRemove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonRemove();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigRemove();
    }
}

New get_new()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CNew();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppNew();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustNew();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaNew();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoNew();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VNew();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonNew();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigNew();
    }
}

Contains get_contains()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CContains();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppContains();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustContains();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaContains();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoContains();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VContains();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonContains();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigContains();
    }
}


StatementCode get_statementcode(std::shared_ptr<Node> stmt, std::shared_ptr<Node> code)
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CStatementCode(stmt, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppStatementCode(stmt, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustStatementCode(stmt, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaStatementCode(stmt, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoStatementCode(stmt, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VStatementCode(stmt, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonStatementCode(stmt, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigStatementCode(stmt, code);
    }
}


Loop get_loop(std::shared_ptr<Node> code)
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CLoop(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppLoop(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustLoop(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaLoop(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoLoop(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VLoop(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonLoop(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigLoop(code);
    }
}

Call get_call()
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CCall();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppCall();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustCall();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaCall();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoCall();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VCall();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonCall();
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigCall();
    }
}

Call get_call(int id, std::shared_ptr<Node> code)
{
    if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CCall(id, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppCall(id, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustCall(id, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaCall(id, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoCall(id, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VCall(id, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonCall(id, code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigCall(id, code);
    }
}


Seq get_seq(std::shared_ptr<Node> code)
{
      if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CSeq(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppSeq(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustSeq(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaSeq(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoSeq(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VSeq(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonSeq(code);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return VSeq(code);
    }
}

If get_if(std::shared_ptr<Node> c1, std::shared_ptr<Node> c2)
{
      if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CIf(c1, c2);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppIf(c1, c2);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustIf(c1, c2);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaIf(c1, c2);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoIf(c1, c2);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VIf(c1, c2);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonIf(c1, c2);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigIf(c1, c2);
    }
}

Id get_id(std::string id)
{
      if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        return CId(id);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        return CppId(id);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustId(id);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaId(id);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoId(id);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VId(id);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonId(id);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigId(id);
    }
}

void Loop::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CLoop(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppLoop(this->code).gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustLoop(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaLoop(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoLoop(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VLoop(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonLoop(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigLoop(this->code).gen(generator);
    }
};

void Loop::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CLoop(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppLoop(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        return RustLoop(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        return JuliaLoop(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        return GoLoop(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        return VLoop(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        return CarbonLoop(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        return ZigLoop(this->code).print(0);
    }
};

void Call::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CCall ccall = CCall(this->id, this->code);
        ccall.conditionalCounts = this->conditionalCounts;
        ccall.gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppCall cppcall = CppCall(this->id, this->code);
        cppcall.conditionalCounts = this->conditionalCounts;
        cppcall.gen(generator);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustCall rustcall = RustCall(this->id, this->code);
        rustcall.conditionalCounts = this->conditionalCounts;
        rustcall.gen(generator); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaCall juliacall = JuliaCall(this->id, this->code);
        juliacall.conditionalCounts = this->conditionalCounts;
        juliacall.gen(generator); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoCall gocall = GoCall(this->id, this->code);
        gocall.conditionalCounts = this->conditionalCounts;
        gocall.gen(generator); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VCall vcall = VCall(this->id, this->code);
        vcall.conditionalCounts = this->conditionalCounts;
        vcall.gen(generator); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonCall carboncall = CarbonCall(this->id, this->code);
        carboncall.conditionalCounts = this->conditionalCounts;
        carboncall.gen(generator); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigCall zigcall = ZigCall(this->id, this->code);
        zigcall.conditionalCounts = this->conditionalCounts;
        zigcall.gen(generator); 
    }
};

void Call::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CCall ccall = CCall(this->id, this->code);
        ccall.conditionalCounts = this->conditionalCounts;
        ccall.print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppCall cppcall = CppCall(this->id, this->code);
        cppcall.conditionalCounts = this->conditionalCounts;
        cppcall.print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustCall rustcall = RustCall(this->id, this->code);
        rustcall.conditionalCounts = this->conditionalCounts;
        rustcall.print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaCall juliacall = JuliaCall(this->id, this->code);
        juliacall.conditionalCounts = this->conditionalCounts;
        juliacall.print(0); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoCall gocall = GoCall(this->id, this->code);
        gocall.conditionalCounts = this->conditionalCounts;
        gocall.print(0); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VCall vcall = VCall(this->id, this->code);
        vcall.conditionalCounts = this->conditionalCounts;
        vcall.print(0); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonCall carboncall = CarbonCall(this->id, this->code);
        carboncall.conditionalCounts = this->conditionalCounts;
        carboncall.print(0); 
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigCall zigcall = ZigCall(this->id, this->code);
        zigcall.conditionalCounts = this->conditionalCounts;
        zigcall.print(0); 
    }
};

void Call::setId(int id){
    this->id = id;
};

void Call::setCode(std::shared_ptr<Node> code){
    this->code = code;
};

void Seq::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CSeq(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppSeq(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustSeq(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaSeq(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoSeq(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VSeq(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonSeq(this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigSeq(this->code).gen(generator);
    }
};

void Seq::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CSeq(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppSeq(this->code).print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustSeq(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaSeq(this->code).print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoSeq(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VSeq(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonSeq(this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigSeq(this->code).print(0);
    }
 };


void If::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CIf(this->c1, this->c2).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppIf(this->c1, this->c2).gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustIf(this->c1, this->c2).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaIf(this->c1, this->c2).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoIf(this->c1, this->c2).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VIf(this->c1, this->c2).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonIf(this->c1, this->c2).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigIf(this->c1, this->c2).gen(generator);
    }
};

void If::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CIf(this->c1, this->c2).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppIf(this->c1, this->c2).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustIf(this->c1, this->c2).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaIf(this->c1, this->c2).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoIf(this->c1, this->c2).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VIf(this->c1, this->c2).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonIf(this->c1, this->c2).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigIf(this->c1, this->c2).print(0);
    }
};

void Id::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CId(this->id).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppId(this->id).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustId(this->id).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaId(this->id).gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoId(this->id).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VId(this->id).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonId(this->id).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigId(this->id).gen(generator);
    }
};

void Id::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CId(this->id).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppId(this->id).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustId(this->id).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaId(this->id).print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoId(this->id).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VId(this->id).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonId(this->id).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigId(this->id).print(0);
    }
};

void Insert::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CInsert().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppInsert().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustInsert().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaInsert().gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoInsert().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VInsert().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonInsert().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigInsert().gen(generator);
    }
};


void Insert::print(int) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CInsert().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppInsert().print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustInsert().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaInsert().print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoInsert().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VInsert().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonInsert().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigInsert().print(0);
    }
};

void Remove::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CRemove().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppRemove().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustRemove().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaRemove().gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoRemove().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VRemove().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonRemove().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigRemove().gen(generator);
    }
};

void Remove::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CRemove().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppRemove().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustRemove().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaRemove().print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoRemove().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VRemove().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonRemove().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigRemove().print(0);
    }
};

void New::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CNew().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppNew().gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustNew().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaNew().gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoNew().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VNew().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonNew().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigNew().gen(generator);
    }
};

void New::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CNew().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppNew().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustNew().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaNew().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoNew().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VNew().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonNew().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigNew().print(0);
    }
 };

void Contains::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CContains().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppContains().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustContains().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaContains().gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoContains().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VContains().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonContains().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigContains().gen(generator);
    }
};

void Contains::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CContains().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppContains().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustContains().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaContains().print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoContains().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VContains().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonContains().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigContains().print(0);
    }
 };

void StatementCode::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CStatementCode(this->stmt, this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppStatementCode(this->stmt, this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustStatementCode(this->stmt, this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaStatementCode(this->stmt, this->code).gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoStatementCode(this->stmt, this->code).gen(generator);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VStatementCode(this->stmt, this->code).gen(generator);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonStatementCode(this->stmt, this->code).gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigStatementCode(this->stmt, this->code).gen(generator);  
    }
};


void StatementCode::print(int) { 

    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CStatementCode(this->stmt, this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppStatementCode(this->stmt, this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustStatementCode(this->stmt, this->code).print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaStatementCode(this->stmt, this->code).print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoStatementCode(this->stmt, this->code).print(0);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VStatementCode(this->stmt, this->code).print(0);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonStatementCode(this->stmt, this->code).print(0);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigStatementCode(this->stmt, this->code).print(0);  
    }
};

void LambdaCode::gen(ProgrammingLanguageGenerator& generator) {
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CLambdaCode().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppLambdaCode().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustLambdaCode().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaLambdaCode().gen(generator);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoLambdaCode().gen(generator);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VLambdaCode().gen(generator);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonLambdaCode().gen(generator);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigLambdaCode().gen(generator);  
    }
};

void LambdaCode::print(int) { 
    if (ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::C)
    {
        CLambdaCode().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CPP)
    {
        CppLambdaCode().print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::RUST)
    {
        RustLambdaCode().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::JULIA)
    {
        JuliaLambdaCode().print(0);   
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::GO)
    {
        GoLambdaCode().print(0);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::V)
    {
        VLambdaCode().print(0);  
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::CARBON)
    {
        CarbonLambdaCode().print(0);
    }else if(ProgrammingLanguage::LANGUAGE == ProgrammingLanguage::ZIG)
    {
        ZigLambdaCode().print(0);  
    }
};
