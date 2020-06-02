#pragma once
#include <vector>
#include <string>
#include <iostream>


class StringTable;
class SymbolTable;

class Operand
{
public:
	Operand() {};
	virtual std::string toString() const = 0;
};

class RValue : public Operand
{
public:
	RValue() {};
};

class MemoryOperand : RValue
{
public:
	MemoryOperand(int index, const SymbolTable* SymbolTable);
	std::string toString() const;
protected:
	int _index;
	const SymbolTable* _SymbolTable;
};

class NumberOperand : RValue
{
public:
	NumberOperand(int index);
	std::string toString() const;
protected:
	int _index;
};

class StringOperand : Operand
{
public:
	StringOperand(int index, const StringTable* StringTable);
	std::string toString() const;
private:
	int _index;
	const StringTable* _StringTable;
};

class LabelOperand : Operand
{
public:
	LabelOperand(int labelID);
	std::string toString() const;
private:
	int _labelID;
};