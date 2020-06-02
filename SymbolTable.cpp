#include "SymbolTable.h"

std::shared_ptr<MemoryOperand> SymbolTable::add(const std::string& name)
{
	std::vector < SymbolTable::TableRecord > ::iterator iter = _records.begin();
	int n = 0;
	SymbolTable::TableRecord tmp = { name };
	while (iter != _records.end())
	{
		if (*iter == tmp)
		{
			MemoryOperand tmp_ret = MemoryOperand(n, this);
			return std::make_shared<MemoryOperand>(tmp_ret);
		}
		n++;
		++iter;
	}
	_records.push_back(SymbolTable::TableRecord{name});
	MemoryOperand tmp_ret = MemoryOperand(_records.size() - 1, this);
	return std::make_shared<MemoryOperand>(tmp_ret);
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