#include "StringTable.h"

int StringTable::add(const std::string name)
{
	std::vector<std::string>::iterator iter = _strings.begin();
	int n = 0;
	while (iter != _strings.end())
	{
		if (*iter == name)
		{
			return n;
		}
		n++;
		++iter;
	}
	_strings.push_back(name);
	return (_strings.size() - 1);
}

const std::string& StringTable::operator [](const int index) const
{
	if (index < _strings.size())
		return _strings[index];
	return error;
}

std::ostream& operator << (std::ostream& os, const StringTable st)
{
	int n = 0;
	while (st[n] != "error")
	{
		os << st[n];
		n++;
	}
	return os;
}