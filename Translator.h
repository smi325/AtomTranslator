#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "StringTable.h"
#include "SymbolTable.h"
#include "Atoms.h"
#include "LexicalAnalyser.h"

class Translator
{
public:
	Translator(std::istream& stream);
	void printAtoms(std::ostream& stream);
	void generateAtom(std::shared_ptr<Atom> atom);
	std::shared_ptr<LabelOperand> newLabel();

	void syntaxError(const std::string& message);
	void lexicalError(const std::string& message);

	std::shared_ptr<RValue> E1();
protected:
	std::vector<std::shared_ptr<Atom>> _atoms;
	StringTable _StringTable = StringTable();
	SymbolTable _SymbolTable = SymbolTable();
	Token _currentLexem = Token(LexemType::eof);/*!!!*/
	Scanner _scanner;/*!!!*/
	int _lbl_counter = -1;
};