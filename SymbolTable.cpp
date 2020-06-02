#include "SymbolTable.h"

int SymbolTable::add(const std::string& name)
{
	std::vector < SymbolTable::TableRecord > ::iterator iter = _records.begin();
	int n = 0;
	SymbolTable::TableRecord tmp = { name };
	while (iter != _records.end())
	{
		if (*iter == tmp)
		{
			return n;
		}
		n++;
		++iter;
	}
	_records.push_back(SymbolTable::TableRecord{name});
	return (_records.size() - 1);
}

bool SymbolTable::TableRecord::operator == (const TableRecord& other) const
{
	if (this->_name == other._name)
		return true;
	else
		return false;
}

const SymbolTable::TableRecord& SymbolTable::operator [](const int index) const
{
	if (index < _records.size())
		return _records[index];
	return error;
}