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










BinaryOpAtom::BinaryOpAtom(const std::string& name, std::shared_ptr<RValue> left, std::shared_ptr<RValue> right, std::shared_ptr<MemoryOperand> result)
{
	_name = name;
	_left = left;
	_right = right;
	_result = result;
}

UnaryOpAtom::UnaryOpAtom(const std::string& name, std::shared_ptr<RValue> operand, std::shared_ptr<MemoryOperand> result)
{
	_name = name;
	_operand = operand;
	_result = result;
}

ConditionalJumpAtom::ConditionalJumpAtom(const std::string& condition, std::shared_ptr<RValue> left, std::shared_ptr<RValue> right, std::shared_ptr<LabelOperand> label)
{
	_condition = condition;
	_left = left;
	_right = right;
	_label = label;
}

JumpAtom::JumpAtom(std::shared_ptr<LabelOperand> label)
{
	_label = label;
}

LabelAtom::LabelAtom(std::shared_ptr<LabelOperand> label)
{
	_label = label;
}

InAtom::InAtom(std::shared_ptr<MemoryOperand> result)
{
	_result = result;
}

OutAtom::OutAtom(std::shared_ptr<Operand> value)
{
	_value = value;
}


std::string BinaryOpAtom::toString() const
{
	std::string tmp = "(" + _name + ", " + _left->toString() + ", " + _right->toString() + ", " + _result->toString() + ")";
	return tmp;
}

std::string UnaryOpAtom::toString() const
{
	std::string tmp = "(" + _name + ", " + _operand->toString() + ", " + ", " + _result->toString() + ")";
	return tmp;
}

std::string ConditionalJumpAtom::toString() const
{
	std::string tmp = "(" + _condition + ", " + _left->toString() + ", " + _right->toString() + ", " + _label->toString() + ")";
	return tmp;
}

std::string JumpAtom::toString() const
{
	std::string tmp = "(JMP,,, " + _label->toString() + ")";
	return tmp;
}

std::string LabelAtom::toString() const
{
	std::string tmp = "(LBL,,, " + _label->toString() + ")";
	return tmp;
}

std::string InAtom::toString() const
{
	std::string tmp = "(IN,,, " + _result->toString() + ")";
	return tmp;
}

std::string OutAtom::toString() const
{
	std::string tmp = "(OUT,,, " + _value->toString() + ")";
	return tmp;
}