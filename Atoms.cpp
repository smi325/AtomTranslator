#include "Atoms.h"
#include "StringTable.h"
#include "SymbolTable.h"

MemoryOperand::MemoryOperand(int index, const SymbolTable* SymbolTable)
{
	_index = index;
	_SymbolTable = SymbolTable;
}

NumberOperand::NumberOperand(int index)
{
	_index = index;
}

StringOperand::StringOperand(int index, const StringTable* StringTable)
{
	_index = index;
	_StringTable = StringTable;
}

LabelOperand::LabelOperand(int labelID)
{
	_labelID = labelID;
}


std::string MemoryOperand::toString() const
{
	std::string tmp = std::to_string(_index) + " " + _SymbolTable->operator[](_index)._name;
	return tmp;
}

std::string NumberOperand::toString() const
{
	std::string tmp = "'" + std::to_string(_index) + "'";
	return tmp;
}

std::string StringOperand::toString() const
{
	std::string tmp = std::to_string(_index) + " " + _StringTable->operator[](_index);
	return tmp;
}

std::string LabelOperand::toString() const
{
	std::string tmp = std::to_string(_labelID);
	return tmp;
}