#pragma once
#include <vector>
#include <string>
#include <iostream>


class StringTable
{
public:
	const std::string& operator [](const int index) const;
	int add(const std::string name);
protected:
	std::vector<std::string> _strings;
	std::string error = "error";
};

std::ostream& operator << (std::ostream& os, const StringTable st);