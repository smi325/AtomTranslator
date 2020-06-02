#pragma once
#include "Atoms.h"
#include <vector>
#include <string>
#include <iostream>


class StringTable
{
public:
	const std::string& operator [](const int index) const;
	std::shared_ptr<StringOperand> add(const std::string name);
protected:
	std::vector<std::string> _strings;
	std::string error = "error";
};

std::ostream& operator << (std::ostream& os, const StringTable st);