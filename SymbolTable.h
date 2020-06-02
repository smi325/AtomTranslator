#pragma once
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
	int add(const std::string& name);
	const TableRecord& operator [](const int index) const;
protected:
	std::vector<TableRecord> _records;
	TableRecord error = { "error" };
};