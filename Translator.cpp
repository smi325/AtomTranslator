#include "Translator.h"

Translator::Translator(std::istream& stream) : _scanner(stream) {};

void Translator::printAtoms(std::ostream& stream)
{
	std::map<Scope, std::vector<std::shared_ptr<Atom>>>::iterator it = _atoms.begin();
	while (it != _atoms.end())
	{
		std::vector<std::shared_ptr<Atom>>::iterator iter = it->second.begin();
		int n = 0;
		while (iter != it->second.end())
		{
			stream << it->second[n]->toString();
			n++;
			++iter;
		}
		++it;
	}
}

void Translator::generateAtom(std::shared_ptr<Atom> atom, Scope scope)
{
	_atoms[scope].push_back(atom);
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

std::shared_ptr<RValue> Translator::Einit(Scope scope)
{
	auto q = E(scope);
	if (_scanner.getNextToken().type() != LexemType::eof)
		syntaxError("Закончилась трансляция, а лексемы еще имеются");
	return q;
}

std::shared_ptr<RValue> Translator::E(Scope scope)
{
	/*n1*/
	auto q = E7(scope);
	return q;
}

std::shared_ptr<RValue> Translator::E7(Scope scope)
{
	/*n2*/
	auto r = E6(scope);
	auto s = E7_(scope, r);
	return s;
}

std::shared_ptr<RValue> Translator::E7_(Scope scope, std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n3*/
	if (_currentLexem.type() == LexemType::opor)
	{
		auto r = E6(scope);
		auto s = _SymbolTable.alloc(scope);
		generateAtom(std::make_shared<BinaryOpAtom>("OR", p, r, s), scope);
		auto t = E7_(scope, s);
		return t;
	}
	/*n4*/
	_scanner.ungetG();
	return p;
}

std::shared_ptr<RValue> Translator::E6(Scope scope)
{
	/*n5*/
	auto r = E5(scope);
	auto s = E6_(scope, r);
	return s;
}

std::shared_ptr<RValue> Translator::E6_(Scope scope, std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n6*/
	if (_currentLexem.type() == LexemType::opand)
	{
		auto r = E5(scope);
		auto s = _SymbolTable.alloc(scope);
		generateAtom(std::make_shared<BinaryOpAtom>("AND", p, r, s), scope);
		auto t = E6_(scope, s);
		return t;
	}
	/*n7*/
	_scanner.ungetG();
	return p;
}


std::shared_ptr<RValue> Translator::E5(Scope scope)
{
	/*n8*/
	auto r = E4(scope);
	auto s = E5_(scope, r);
	return s;
}

std::shared_ptr<RValue> Translator::E5_(Scope scope, std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n9*/
	if (_currentLexem.type() == LexemType::opeq)
	{
		auto r = E4(scope);
		auto s = _SymbolTable.alloc(scope);
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s), scope);
		generateAtom(std::make_shared<ConditionalJumpAtom>("EQ", p, r, l), scope);
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s), scope);
		generateAtom(std::make_shared<LabelAtom>(l), scope);
		return s;
	}
	/*n10*/
	if (_currentLexem.type() == LexemType::opne)
	{
		auto r = E4(scope);
		auto s = _SymbolTable.alloc(scope);
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s), scope);
		generateAtom(std::make_shared<ConditionalJumpAtom>("NE", p, r, l), scope);
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s), scope);
		generateAtom(std::make_shared<LabelAtom>(l), scope);
		return s;
	}
	/*n11*/
	if (_currentLexem.type() == LexemType::opgt)
	{
		auto r = E4(scope);
		auto s = _SymbolTable.alloc(scope);
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s), scope);
		generateAtom(std::make_shared<ConditionalJumpAtom>("GT", p, r, l), scope);
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s), scope);
		generateAtom(std::make_shared<LabelAtom>(l), scope);
		return s;
	}
	/*n12*/
	if (_currentLexem.type() == LexemType::oplt)
	{
		auto r = E4(scope);
		auto s = _SymbolTable.alloc(scope);
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s), scope);
		generateAtom(std::make_shared<ConditionalJumpAtom>("LT", p, r, l), scope);
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s), scope);
		generateAtom(std::make_shared<LabelAtom>(l), scope);
		return s;
	}
	/*n13*/
	if (_currentLexem.type() == LexemType::ople)
	{
		auto r = E4(scope);
		auto s = _SymbolTable.alloc(scope);
		auto l = newLabel();
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(1), s), scope);
		generateAtom(std::make_shared<ConditionalJumpAtom>("LE", p, r, l), scope);
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", std::make_shared<NumberOperand>(0), s), scope);
		generateAtom(std::make_shared<LabelAtom>(l), scope);
		return s;
	}
	/*n14*/
	_scanner.ungetG();
	return p;
}


std::shared_ptr<RValue> Translator::E4(Scope scope)
{
	/*n15*/
	auto r = E3(scope);
	auto s = E4_(scope, r);
	return s;
}

std::shared_ptr<RValue> Translator::E4_(Scope scope, std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n16*/
	if ((_currentLexem.type() == LexemType::opplus))
	{
		auto r = E3(scope);
		auto s = _SymbolTable.alloc(scope);
		generateAtom(std::make_shared<BinaryOpAtom>("ADD", p, r, s), scope);
		auto t = E4_(scope, s);
		return t;
	}
	/*n17*/
	if (_currentLexem.type() == LexemType::opminus)
	{
		auto r = E3(scope);
		auto s = _SymbolTable.alloc(scope);
		generateAtom(std::make_shared<BinaryOpAtom>("SUB", p, r, s), scope);
		auto t = E4_(scope, s);
		return t;
	}
	/*n18*/
	_scanner.ungetG();
	return p;
}

std::shared_ptr<RValue> Translator::E3(Scope scope)
{
	/*n19*/
	auto r = E2(scope);
	auto s = E3_(scope, r);
	return s;
}

std::shared_ptr<RValue> Translator::E3_(Scope scope, std::shared_ptr<RValue> p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n20*/
	if ((_currentLexem.type() == LexemType::opmult))
	{
		auto r = E2(scope);
		auto s = _SymbolTable.alloc(scope);
		generateAtom(std::make_shared<BinaryOpAtom>("MUL", p, r, s), scope);
		auto t = E3_(scope, s);
		return t;
	}
	/*n21*/
	_scanner.ungetG();
	return p;
}

std::shared_ptr<RValue> Translator::E2(Scope scope)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n22*/
	if ((_currentLexem.type() == LexemType::opnot))
	{
		auto q = E1(scope);
		auto r = _SymbolTable.alloc(scope);
		generateAtom(std::make_shared<UnaryOpAtom>("NOT", q, r), scope);
		return r;
	}
	/*n23*/
	_scanner.ungetG();
	return E1(scope);
}

std::shared_ptr<RValue> Translator::E1(Scope scope)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n24*/
	if ((_currentLexem.type() == LexemType::lpar))
	{
		auto q = E(scope);
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
			auto q = _SymbolTable.addVar(_currentLexem.str(), scope, SymbolTable::TableRecord::RecordType::integer);
			generateAtom(std::make_shared<BinaryOpAtom>("ADD", q, std::make_shared<NumberOperand>(1), q), scope);
			return q;
		}
	}
	/*n28*/
	if ((_currentLexem.type() == LexemType::id))
	{
		auto r = _currentLexem.str();
		return E1_(scope, r);
	}
	syntaxError("Синтаксическая ошибка");
	return nullptr;
}

std::shared_ptr<MemoryOperand> Translator::E1_(Scope scope, std::string p)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n29*/
	if ((_currentLexem.type() == LexemType::opinc))
	{
		auto s = _SymbolTable.addVar(p, scope, SymbolTable::TableRecord::RecordType::integer);
		auto r = _SymbolTable.alloc(scope);
		generateAtom(std::make_shared<UnaryOpAtom>("MOV", s, r), scope);
		generateAtom(std::make_shared<BinaryOpAtom>("ADD", s, std::make_shared<NumberOperand>(1), s), scope);
		return r;
	}
	/*n31*/
	_scanner.ungetG();
	auto q = _SymbolTable.addVar(p, scope, SymbolTable::TableRecord::RecordType::integer); /*ЗАМЕНИТЬ НА checkVar!!!!!!!!*/
	return q;
}

/*13.2*/

bool Translator::DeclareStmt(Scope scope)
{
	/*n1*/
	auto p = Type(scope);
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	if (_currentLexem.type() == LexemType::id)
	{
		DeclareStmt_(scope, p, _currentLexem.str());
		return true;
	}
	syntaxError("Синтаксическая ошибка");
	return false;
}

bool Translator::DeclareStmt_(Scope scope, SymbolTable::TableRecord::RecordType type, std::string name)
{
	/*n2*/
	if (scope > -1)
	{
		syntaxError("Function difinition inside function");
	}

	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	if (_currentLexem.type() == LexemType::lbracket)
	{
		auto scope_ = _SymbolTable.addFunc(name, type, 0)->index();
		auto n = ParamList(scope_);
		_SymbolTable[scope_]._len = n;
		return true;
	}
	syntaxError("Синтаксическая ошибка");
	return false;
}

bool Translator::DeclareStmt(Scope scope, SymbolTable::TableRecord::RecordType type, std::string name)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n3*/
	if (_currentLexem.type() == LexemType::opassign)
	{
		_currentLexem = _scanner.getNextToken();
		if (_currentLexem.type() == LexemType::error)
		{
			lexicalError("Лексическая ошибка");
		}
		if (_currentLexem.type() == LexemType::num)
		{
			_SymbolTable.addVar(name, scope, type, _currentLexem.value());
			DeclVarList_(scope, type);
			return true;
		}
		syntaxError("Синтаксическая ошибка");
	}
	/*n4*/
	_scanner.ungetG();
	_SymbolTable.addVar(name, scope, type);
	DeclVarList_(scope, type);
	return true;
}

SymbolTable::TableRecord::RecordType Translator::Type(Scope scope)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n5*/
	if (_currentLexem.type() == LexemType::kwchar)
	{
		return SymbolTable::TableRecord::RecordType::chr;
	}
	/*n6*/
	if (_currentLexem.type() == LexemType::kwint)
	{
		return SymbolTable::TableRecord::RecordType::integer;
	}
	syntaxError("Синтаксическая ошибка");
	return SymbolTable::TableRecord::RecordType::unknown;
}


bool Translator::DeclVarList_(Scope scope, SymbolTable::TableRecord::RecordType type)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n7*/
	if (_currentLexem.type() == LexemType::comma)
	{
		_currentLexem = _scanner.getNextToken();
		if (_currentLexem.type() == LexemType::error)
		{
			lexicalError("Лексическая ошибка");
		}
		if (_currentLexem.type() == LexemType::id)
		{
			auto name = _currentLexem.str();
			InitVar(scope, type, name);
			DeclVarList_(scope, type);
			return true;
		}
		syntaxError("Синтаксическая ошибка");
	}
	/*n8*/
	_scanner.ungetG();
	return true;
}

bool Translator::InitVar(Scope scope, SymbolTable::TableRecord::RecordType type, std::string name)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	if (_currentLexem.type() == LexemType::opassign)
	{
		_currentLexem = _scanner.getNextToken();
		if (_currentLexem.type() == LexemType::error)
		{
			lexicalError("Лексическая ошибка");
		}
		/*n9.1*/
		if (_currentLexem.type() == LexemType::num)
		{
			_SymbolTable.addVar(name, scope, type, _currentLexem.value());
			return true;
		}
		/*n9.2*/
		if (_currentLexem.type() == LexemType::chr)
		{
			_SymbolTable.addVar(name, scope, type, _currentLexem.value());
			return true;
		}
		syntaxError("Синтаксическая ошибка");
	}
	/*n10*/
	_scanner.ungetG();
	_SymbolTable.addVar(name, scope, type);
	return true;
}


int Translator::ParamList(Scope scope)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n11*/
	if (_currentLexem.type() == LexemType::kwchar || _currentLexem.type() == LexemType::kwint)
	{
		_scanner.ungetG();
		auto q = Type(scope);
		_currentLexem = _scanner.getNextToken();
		if (_currentLexem.type() == LexemType::error)
		{
			lexicalError("Лексическая ошибка");
		}
		if (_currentLexem.type() == LexemType::id)
		{
			auto name = _currentLexem.str();
			_SymbolTable.addVar(name, scope, q);
			auto s = ParamList_(scope);
			return (s + 1);
		}
		syntaxError("Синтаксическая ошибка");
	}
	/*n12*/
	_scanner.ungetG();
	return 0;
}

int Translator::ParamList_(Scope scope)
{
	_currentLexem = _scanner.getNextToken();
	if (_currentLexem.type() == LexemType::error)
	{
		lexicalError("Лексическая ошибка");
	}
	/*n13*/
	if (_currentLexem.type() == LexemType::comma)
	{
		_currentLexem = _scanner.getNextToken();
		if (_currentLexem.type() == LexemType::error)
		{
			lexicalError("Лексическая ошибка");
		}
		if (_currentLexem.type() == LexemType::kwchar || _currentLexem.type() == LexemType::kwint)
		{
			_scanner.ungetG();
			auto q = Type(scope);
			_currentLexem = _scanner.getNextToken();
			if (_currentLexem.type() == LexemType::error)
			{
				lexicalError("Лексическая ошибка");
			}
			if (_currentLexem.type() == LexemType::id)
			{
				auto name = _currentLexem.str();
				_SymbolTable.addVar(name, scope, q);
				auto s = ParamList_(scope);
				return (s + 1);
			}
			syntaxError("Синтаксическая ошибка");
		}
		syntaxError("Синтаксическая ошибка");
	}
	/*n14*/
	_scanner.ungetG();
	return 0;
}

bool Translator::StmtList(Scope scope)
{
	/*n16*/
	return true;
}
