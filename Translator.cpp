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
		exit(1);
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
		exit(1);
	}
}

std::shared_ptr<RValue> Translator::Einit()
{
	auto q = E();
	if (_scanner.getNextToken().type() != LexemType::eof)
		syntaxError("Закончилась трансляция, а лексемы еще имеются");
	return q;
}

std::shared_ptr<RValue> Translator::E()
{
	/*n1*/
	auto q = E7();
	return q;
}

std::shared_ptr<RValue> Translator::E7()
{
	/*n2*/
	auto r = E6();
	auto s = E7_(r);
	return s;
}

std::shared_ptr<RValue> Translator::E7_(std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n3*/
	if (_currentLexem.type() == LexemType::opor)
	{
		auto r = E6();
		auto s = _SymbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>("OR", p, r, s));
		auto t = E7_(s);
		return t;
	}
	/*n4*/
	_scanner.ungetG();
	return p;
}

std::shared_ptr<RValue> Translator::E6()
{
	/*n5*/
	auto r = E5();
	auto s = E6_(r);
	return s;
}

std::shared_ptr<RValue> Translator::E6_(std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n6*/
	if (_currentLexem.type() == LexemType::opand)
	{
		auto r = E5();
		auto s = _SymbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>("AND", p, r, s));
		auto t = E6_(s);
		return t;
	}
	/*n7*/
	_scanner.ungetG();
	return p;
}


std::shared_ptr<RValue> Translator::E5()
{
	/*n8*/
	auto r = E4();
	auto s = E5_(r);
	return s;
}

std::shared_ptr<RValue> Translator::E5_(std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n9*/
	if (_currentLexem.type() == LexemType::opeq)
	{
		auto r = E4();
		auto s = _SymbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s));
		generateAtom(std::make_shared<ConditionalJumpAtom>("EQ", p, r, l));
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	/*n10*/
	if (_currentLexem.type() == LexemType::opne)
	{
		auto r = E4();
		auto s = _SymbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s));
		generateAtom(std::make_shared<ConditionalJumpAtom>("NE", p, r, l));
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	/*n11*/
	if (_currentLexem.type() == LexemType::opgt)
	{
		auto r = E4();
		auto s = _SymbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s));
		generateAtom(std::make_shared<ConditionalJumpAtom>("GT", p, r, l));
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	/*n12*/
	if (_currentLexem.type() == LexemType::oplt)
	{
		auto r = E4();
		auto s = _SymbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s));
		generateAtom(std::make_shared<ConditionalJumpAtom>("LT", p, r, l));
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	/*n13*/
	if (_currentLexem.type() == LexemType::ople)
	{
		auto r = E4();
		auto s = _SymbolTable.alloc();
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s));
		generateAtom(std::make_shared<ConditionalJumpAtom>("LE", p, r, l));
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s));
		generateAtom(std::make_shared<LabelAtom>(l));
		return s;
	}
	/*n14*/
	_scanner.ungetG();
	return p;
}


std::shared_ptr<RValue> Translator::E4()
{
	/*n15*/
	auto r = E3();
	auto s = E4_(r);
	return s;
}

std::shared_ptr<RValue> Translator::E4_(std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n16*/
	if ((_currentLexem.type() == LexemType::opplus))
	{
		auto r = E3();
		auto s = _SymbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>("ADD", p, r, s));
		auto t = E4_(s);
		return t;
	}
	/*n17*/
	if (_currentLexem.type() == LexemType::opminus)
	{
		auto r = E3();
		auto s = _SymbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>("SUB", p, r, s));
		auto t = E4_(s);
		return t;
	}
	/*n18*/
	_scanner.ungetG();
	return p;
}

std::shared_ptr<RValue> Translator::E3()
{
	/*n19*/
	auto r = E2();
	auto s = E3_(r);
	return s;
}

std::shared_ptr<RValue> Translator::E3_(std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n20*/
	if ((_currentLexem.type() == LexemType::opmult))
	{
		auto r = E2();
		auto s = _SymbolTable.alloc();
		generateAtom(std::make_shared<BinaryOpAtom>("MUL", p, r, s));
		auto t = E3_(s);
		return t;
	}
	/*n21*/
	_scanner.ungetG();
	return p;
}

std::shared_ptr<RValue> Translator::E2()
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n22*/
	if ((_currentLexem.type() == LexemType::opnot))
	{
		auto q = E1();
		auto r = _SymbolTable.alloc();
		generateAtom(std::make_shared<UnaryOpAtom>("NOT", q, r));
		return r;
	}
	/*n23*/
	_scanner.ungetG();
	return E1();
}

std::shared_ptr<RValue> Translator::E1()
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n24*/
	if ((_currentLexem.type() == LexemType::lpar))
	{
		auto q = E();
		{
			_currentLexem = _scanner.getNextToken();
			if (_currentLexem.type() == LexemType::error)
			{
				lexicalError("Лексическая ошибка");
			}
			if ((_currentLexem.type() == LexemType::rpar))
			{
				return q;
			}
			syntaxError("Синтаксическая ошибка");
			return nullptr;
		}
	}
	/*n25*/
	if ((_currentLexem.type() == LexemType::num))
	{
		return std::make_shared<NumberOperand>(NumberOperand(_currentLexem.value()));
	}
	/*n26*/
	if ((_currentLexem.type() == LexemType::chr))
	{
		return std::make_shared<NumberOperand>(NumberOperand(_currentLexem.value()));
	}
	/*n27*/
	if ((_currentLexem.type() == LexemType::opinc))
	{
		_currentLexem = _scanner.getNextToken();
		if (_currentLexem.type() == LexemType::error)
		{
			lexicalError("Лексическая ошибка");
		}
		if ((_currentLexem.type() == LexemType::id))
		{
			auto q = _SymbolTable.add(_currentLexem.str());
			generateAtom(std::make_shared<BinaryOpAtom>("ADD", q, std::make_shared<NumberOperand>(1), q));
			return q;
		}
	}
	/*n28*/
	if ((_currentLexem.type() == LexemType::id))
	{
		auto r = _currentLexem.str();
		return E1_(r);
	}
	syntaxError("Синтаксическая ошибка");
	return nullptr;
}

std::shared_ptr<MemoryOperand> Translator::E1_(std::string p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n29*/
	if ((_currentLexem.type() == LexemType::opinc))
	{
		auto s = _SymbolTable.add(p);
		auto r = _SymbolTable.alloc();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", s, r));
		generateAtom(std::make_shared<BinaryOpAtom>("ADD", s, std::make_shared<NumberOperand>(1), s));
		return r;
	}
	/*n31*/
	_scanner.ungetG();
	auto q = _SymbolTable.add(p);
	return q;
}

