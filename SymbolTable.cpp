#include "SymbolTable.h"

std::shared_ptr<MemoryOperand> SymbolTable::add(const std::string& name, Scope scope)
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
	auto push_tmp = SymbolTable::TableRecord{ name };
	push_tmp._scope = scope;
	_records.push_back(push_tmp);
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


std::shared_ptr<MemoryOperand> SymbolTable::alloc(Scope scope)/*!!!!!!!!!!!!!!!*/
{
	/*return this->add("temp" + std::to_string(_records.size()), scope);*/
	return this->addVar("[temp]" + std::to_string(_records.size()), scope, SymbolTable::TableRecord::RecordType::integer);
}


/*13.2*/

std::shared_ptr<MemoryOperand> SymbolTable::addVar(const std::string& name,
	const Scope scope,
	const TableRecord::RecordType type,
	const int init)
{
	std::vector < SymbolTable::TableRecord > ::iterator iter = _records.begin();
	int n = 0;
	while (iter != _records.end())
	{
		if (iter->_name == name && iter->_scope == scope)
		{
			return nullptr;
		}
		n++;
		++iter;
	}
	auto push_tmp = SymbolTable::TableRecord{ name };
	push_tmp._scope = scope;
	push_tmp._type = type;
	push_tmp._kind = TableRecord::RecordKind::var;
	_records.push_back(push_tmp);
	MemoryOperand tmp_ret = MemoryOperand(_records.size() - 1, this);
	return std::make_shared<MemoryOperand>(tmp_ret);
}

std::shared_ptr<MemoryOperand> SymbolTable::addFunc(const std::string& name,
	const TableRecord::RecordType type,
	const int len)
{
	std::vector < SymbolTable::TableRecord > ::iterator iter = _records.begin();
	int n = 0;
	while (iter != _records.end())
	{
		if (iter->_name == name)
		{
			return nullptr;
		}
		n++;
		++iter;
	}
	auto push_tmp = SymbolTable::TableRecord{ name };
	push_tmp._len = len;
	push_tmp._type = type;
	push_tmp._kind = TableRecord::RecordKind::func;
	_records.push_back(push_tmp);
	MemoryOperand tmp_ret = MemoryOperand(_records.size() - 1, this);
	return std::make_shared<MemoryOperand>(tmp_ret);
}

std::shared_ptr<MemoryOperand> SymbolTable::checkVar(const Scope scope,
	const std::string& name){
	std::vector < SymbolTable::TableRecord > ::iterator iter = _records.begin();
	int n = 0;
	while (iter != _records.end())
	{
		if (iter->_name == name && iter->_scope == scope)
		{
			if (iter->_kind != TableRecord::RecordKind::var)
				return nullptr;
			MemoryOperand ret_tmp = MemoryOperand(n, this);
			return std::make_shared<MemoryOperand>(ret_tmp);
		}
		n++;
		++iter;
	}
	if (scope != GlobalScope)
	{
		iter = _records.begin();
		n = 0;
		while (iter != _records.end())
		{
			if (iter->_name == name && iter->_scope == GlobalScope)
			{
				if (iter->_kind != TableRecord::RecordKind::var)
					return nullptr;
				MemoryOperand ret_tmp = MemoryOperand(n, this);
				return std::make_shared<MemoryOperand>(ret_tmp);
			}
			n++;
			++iter;
		}
	}
	return nullptr;
}

std::shared_ptr<MemoryOperand> SymbolTable::checkFunc(const std::string& name,
	int len)
{
	std::vector < SymbolTable::TableRecord > ::iterator iter = _records.begin();
	int n = 0;
	while (iter != _records.end())
	{
		if (iter->_name == name && iter->_scope == GlobalScope)
		{
			if (iter->_kind != TableRecord::RecordKind::func)
				return nullptr;
			if (iter->_len != len)
				return nullptr;
			MemoryOperand ret_tmp = MemoryOperand(n, this);
			return std::make_shared<MemoryOperand>(ret_tmp);
		}
		n++;
		++iter;
	}
	return nullptr;
}