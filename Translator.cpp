#include "Translator.h"

Translator::Translator(std::istream& stream) : _scanner(stream) {};

void Translator::printAtoms(std::ostream& stream)
{
	std::vector<std::shared_ptr<Atom>>::iterator iter = _atoms.begin();
	int n = 0;
	while (iter != _atoms.end())
	{
		stream << _atoms[n]->toString();
		n++;
		++iter;
	}
}

void Translator::generateAtom(std::shared_ptr<Atom> atom)
{
	_atoms.push_back(atom);
}

std::shared_ptr<LabelOperand> Translator::newLabel()
{
	_lbl_counter += 1;
	return std::make_shared<LabelOperand>(LabelOperand(_lbl_counter));
}

void Translator::syntaxError(const std::string& message)
{
	try
	{
		throw 1;
	}
	catch (int a)
	{
		std::cout << message;
	}
}

void Translator::lexicalError(const std::string& message)
{
	try
	{
		throw 1;
	}
	catch (int a)
	{
		std::cout << message;
	}
}

std::shared_ptr<RValue> Translator::E1()
{
	_currentLexem = _scanner.getNextToken();
	/*n25*/
	if (_currentLexem.type() == LexemType::num)
	{
		return std::make_shared<NumberOperand>(NumberOperand(_currentLexem.value()));
	}
	/*n26*/
	if (_currentLexem.type() == LexemType::chr)
	{
		char tmp1 = (char)(_currentLexem.value());
		std::string tmp2;
		tmp2 += tmp1;
		return _SymbolTable.add(tmp2);
	}
	syntaxError("Ошибка");
	return nullptr;
}