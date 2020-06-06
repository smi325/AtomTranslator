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

		int _len = -1;
		int _init = 0;
		Scope _scope = GlobalScope;
		int _offset = -1;

		bool operator == (const TableRecord& other) const;
	};
	std::shared_ptr<MemoryOperand> add(const std::string& name, Scope scope);
	const TableRecord& operator [](const int index) const;
	std::shared_ptr<MemoryOperand> alloc(Scope scope);
protected:
	std::vector<TableRecord> _records;
	TableRecord error = { "error" };
};