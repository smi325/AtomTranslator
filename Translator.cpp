#include "Translator.h"

Translator::Translator(std::istream& stream)
{
	Scanner _scanner = Scanner(stream);
	Token _currentLexem = _scanner.getNextToken();
}

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