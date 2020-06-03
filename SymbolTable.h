#pragma once
#include "Atoms.h"
#include <vector>
#include <string>
#include <iostream>


class SymbolTable
{
public:
	struct TableRecord
	{
		std::string _name;
		bool operator == (const TableRecord& other) const;
	};
	std::shared_ptr<MemoryOperand> add(const std::string& name);
	const TableRecord& operator [](const int index) const;
	std::shared_ptr<MemoryOperand> alloc();
protected:
	std::vector<TableRecord> _records;
	TableRecord error = { "error" };
};