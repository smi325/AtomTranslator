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
	std::string kind = "unknown";
	if (_SymbolTable->operator[](_index)._kind == SymbolTable::TableRecord::RecordKind::var)
		kind = "var";
	if (_SymbolTable->operator[](_index)._kind == SymbolTable::TableRecord::RecordKind::func)
		kind = "func";

	std::string type = "unknown";
	if (_SymbolTable->operator[](_index)._type == SymbolTable::TableRecord::RecordType::integer)
		kind = "integer";
	if (_SymbolTable->operator[](_index)._type == SymbolTable::TableRecord::RecordType::chr)
		kind = "chr";
	std::string name = _SymbolTable->operator[](_index)._name;
	std::string len = std::to_string(_SymbolTable->operator[](_index)._len);
	std::string init = std::to_string(_SymbolTable->operator[](_index)._init);
	std::string scope = std::to_string(_SymbolTable->operator[](_index)._scope);
	std::string offset = std::to_string(_SymbolTable->operator[](_index)._offset);
	std::string tmp = std::to_string(_index) + " " + name + " " + kind + " " + type + " " + len + " " + init + " " + scope + " " + offset;
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

/*13.2*/

CallAtom::CallAtom(std::shared_ptr<MemoryOperand> func, std::shared_ptr<MemoryOperand> res)
{
	_func = func;
	_res = res;
}

RetAtom::RetAtom(std::shared_ptr<RValue> ret)
{
	_ret = ret;
}

ParamAtom::ParamAtom(std::shared_ptr<RValue> param)
{
	_param = param;
}


std::string CallAtom::toString() const
{
	std::string tmp = "(CALL, " + _func->toString() + ",," + _res->toString() + ")";
	return tmp;
}

std::string RetAtom::toString() const
{
	std::string tmp = "(RET,,, " + _ret->toString() + ")";
	return tmp;
}

std::string ParamAtom::toString() const
{
	std::string tmp = "(PARAM,,, " + _param->toString() + ")";
	return tmp;
}