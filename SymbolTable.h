#pragma once
#include "Atoms.h"
#include <vector>
#include <string>
#include <iostream>

typedef int Scope;
const Scope GlobalScope = -1;

class SymbolTable
{
public:
	struct TableRecord
	{
		std::string _name;

		enum class RecordKind { unknown, var, func };
		enum class RecordType { unknown, integer, chr };

		RecordKind _kind = RecordKind::unknown;
		RecordType _type = RecordType::unknown;

		mutable int _len = -1;
		int _init = 0;
		Scope _scope = GlobalScope;
		int _offset = -1;

		bool operator == (const TableRecord& other) const;
	};
	std::shared_ptr<MemoryOperand> add(const std::string& name, Scope scope);
	const TableRecord& operator [](const int index) const;
	std::shared_ptr<MemoryOperand> alloc(Scope scope);
	/*13.2*/
	std::shared_ptr<MemoryOperand> addVar(const std::string& name,
		const Scope scope,
		const TableRecord::RecordType type,
		const int init = 0);	std::shared_ptr<MemoryOperand> addFunc(const std::string& name,
		const TableRecord::RecordType type,
		const int len);	std::shared_ptr<MemoryOperand> checkVar(const Scope scope,
		const std::string& name);	std::shared_ptr<MemoryOperand> checkFunc(const std::string& name,
		int len);
protected:
	std::vector<TableRecord> _records;
	TableRecord error = { "error" };
};