#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "StringTable.h"
#include "SymbolTable.h"
#include "Atoms.h"
#include "LexicalAnalyser.h"

class Translator
{
public:
	Translator(std::istream& stream);
	void printAtoms(std::ostream& stream);
	void generateAtom(std::shared_ptr<Atom> atom, Scope scope);
	std::shared_ptr<LabelOperand> newLabel();

	void syntaxError(const std::string& message);
	void lexicalError(const std::string& message);
/*
	E();
	E7();
	E7_();
	E6();
	E6_();
	E5();
	E5_();
	E4();
	E4_();
	E3();
	E3_();
	E2();
	E1();*/
	std::shared_ptr<RValue> Einit(Scope scope);
	std::shared_ptr<RValue> E(Scope scope);
	std::shared_ptr<RValue> E7(Scope scope);
	std::shared_ptr<RValue> E7_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E6(Scope scope);
	std::shared_ptr<RValue> E6_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E5(Scope scope);
	std::shared_ptr<RValue> E5_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E4(Scope scope);
	std::shared_ptr<RValue> E4_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E3(Scope scope);
	std::shared_ptr<RValue> E3_(Scope scope, std::shared_ptr<RValue> p);
	std::shared_ptr<RValue> E2(Scope scope);
	std::shared_ptr<RValue> E1(Scope scope);
	std::shared_ptr<MemoryOperand> E1_(Scope scope, std::string p);

	SymbolTable::TableRecord::RecordType Type(Scope scope);
	bool StmtList(Scope scope);
	int ParamList(Scope scope);
	int ParamList_(Scope scope);
	bool InitVar(Scope scope, SymbolTable::TableRecord::RecordType type, std::string name);
	bool DeclVarList_(Scope scope, SymbolTable::TableRecord::RecordType type);
	bool DeclareStmt(Scope scope);
	bool DeclareStmt_(Scope scope, SymbolTable::TableRecord::RecordType type, std::string name);

	bool Stmt(Scope scope);
protected:
	std::map<Scope, std::vector<std::shared_ptr<Atom>>> _atoms;
	StringTable _StringTable = StringTable();
	SymbolTable _SymbolTable = SymbolTable();
	Token _currentLexem = Token(LexemType::eof);/*!!!*/
	Scanner _scanner;/*!!!*/
	int _lbl_counter = -1;
};