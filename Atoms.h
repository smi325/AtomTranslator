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

class MemoryOperand : public RValue
{
public:
	MemoryOperand(int index, const SymbolTable* SymbolTable);
	std::string toString() const;

	int index() const; /*13.2*/
protected:
	int _index;
	const SymbolTable* _SymbolTable;
};

class NumberOperand : public RValue
{
public:
	NumberOperand(int index);
	std::string toString() const;
protected:
	int _index;
};

class StringOperand : public Operand
{
public:
	StringOperand(int index, const StringTable* StringTable);
	std::string toString() const;
private:
	int _index;
	const StringTable* _StringTable;
};

class LabelOperand : public Operand
{
public:
	LabelOperand(int labelID);
	std::string toString() const;
private:
	int _labelID;
};










class Atom
{
public:
	Atom() {};
	virtual std::string toString() const = 0;
};

class BinaryOpAtom : public Atom
{
public:
	BinaryOpAtom(const std::string& name, std::shared_ptr<RValue> left, std::shared_ptr<RValue> right, std::shared_ptr<MemoryOperand> result);
	std::string toString() const;
private:
	std::string _name;
	std::shared_ptr<RValue> _left;
	std::shared_ptr<RValue> _right;
	std::shared_ptr<MemoryOperand> _result;
};

class UnaryOpAtom : public Atom
{
public:
	UnaryOpAtom(const std::string& name, std::shared_ptr<RValue> operand, std::shared_ptr<MemoryOperand> result);
	std::string toString() const;
private:
	std::string _name;
	std::shared_ptr<RValue> _operand;
	std::shared_ptr<MemoryOperand> _result;
};

class ConditionalJumpAtom : public Atom
{
public:
	ConditionalJumpAtom(const std::string& condition, std::shared_ptr<RValue> left, std::shared_ptr<RValue> right, std::shared_ptr<LabelOperand> label);
	std::string toString() const;
private:
	std::string _condition;
	std::shared_ptr<RValue> _left;
	std::shared_ptr<RValue> _right;
	std::shared_ptr<LabelOperand> _label; /*!!!!!!!!!!!!!!!!*/
};

class JumpAtom : public Atom
{
public:
	JumpAtom(std::shared_ptr<LabelOperand> label);
	std::string toString() const;
private:
	std::shared_ptr<LabelOperand> _label;
};

class LabelAtom : public Atom
{
public:
	LabelAtom(std::shared_ptr<LabelOperand> label);
	std::string toString() const;
private:
	std::shared_ptr<LabelOperand> _label;
};

class InAtom : public Atom
{
public:
	InAtom(std::shared_ptr<MemoryOperand> result);
	std::string toString() const;
private:
	std::shared_ptr<MemoryOperand> _result;
};

class OutAtom : public Atom
{
public:
	OutAtom(std::shared_ptr<Operand> value);
	std::string toString() const;
private:
	std::shared_ptr<Operand> _value;
};

class CallAtom : public Atom
{
public:
	CallAtom(std::shared_ptr<MemoryOperand> func, std::shared_ptr<MemoryOperand> res);
	std::string toString() const;
private:
	std::shared_ptr<MemoryOperand> _func;
	std::shared_ptr<MemoryOperand> _res;
};

class RetAtom : public Atom
{
public:
	RetAtom(std::shared_ptr<RValue> ret);
	std::string toString() const;
private:
	std::shared_ptr<RValue> _ret;
};

class ParamAtom : public Atom
{
public:
	ParamAtom(std::shared_ptr<RValue> param);
	std::string toString() const;
private:
	std::shared_ptr<RValue> _param;
};