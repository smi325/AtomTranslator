#include "LexicalAnalyser.h"
#include <map>

std::map<char, int> digits{ { '0', 0 }, { '1', 1 }, { '2',  2}, { '3',  3}, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 }, { '8', 8 }, { '9', 9 }, };

std::map<char, LexemType> punctuation{ {'(', LexemType::lpar}, {')', LexemType::rpar}, {'{', LexemType::lbrace}, {'}', LexemType::rbrace}, {'[', LexemType::lbracket}, {']', LexemType::rbracket}, {';', LexemType::semicolon}, {',', LexemType::comma}, {':', LexemType::colon} };

std::map<std::string, LexemType> keywords{ {"int", LexemType::kwint}, {"char", LexemType::kwchar}, {"if", LexemType::kwif}, {"else", LexemType::kwelse}, {"switch", LexemType::kwswitch}, {"case", LexemType::kwcase}, {"while", LexemType::kwwhile}, {"for", LexemType::kwfor}, {"return", LexemType::kwreturn}, {"in", LexemType::kwin}, {"out", LexemType::kwout}, };

Token::Token(LexemType type)
{
	_type = type;
}

Token::Token(int value)
{
	_type = LexemType::num;
	_value = value;

}

Token::Token(LexemType type, const std::string& str)
{
	_type = type;
	_str = str;
}

Token::Token(char c)
{
	_type = LexemType::chr;
	_value = c;
}

void Token::print(std::ostream& stream)
{
	stream << '[' << type_to_str();
	switch (_type)
	{
	case LexemType::num:
		stream << ", " << _value;
		break;
	case LexemType::chr:
		stream << ", " << "'" << (char)_value << "'";
		break;
	case LexemType::id:
	case LexemType::str:
	case LexemType::error:
		stream << ", " << '"' << _str << '"';
		break;
	}
	stream << ']' << std::endl;
}

LexemType Token::type()
{
	return _type;
}

int Token::value()
{
	return _value;
}

std::string Token::str()
{
	return _str;
}

std::string Token::type_to_str()
{
	switch (_type)
	{
	case LexemType::num:
		return "num";
	case LexemType::chr:
		return "chr";
	case LexemType::str:
		return "str";
	case LexemType::id:
		return "id";
	case LexemType::lpar:
		return "lpar";
	case LexemType::rpar:
		return "rpar";
	case LexemType::lbrace:
		return "lbrace";
	case LexemType::rbrace:
		return "rbrace";
	case LexemType::lbracket:
		return "lbracket";
	case LexemType::rbracket:
		return "rbracket";
	case LexemType::semicolon:
		return "semicolon";
	case LexemType::comma:
		return "comma";
	case LexemType::colon:
		return "colon";
	case LexemType::opassign:
		return "opassign";
	case LexemType::opplus:
		return "opplus";
	case LexemType::opminus:
		return "opminus";
	case LexemType::opmult:
		return "opmult";
	case LexemType::opinc:
		return "opinc";
	case LexemType::opeq:
		return "opeq";
	case LexemType::opne:
		return "opne";
	case LexemType::oplt:
		return "oplt";
	case LexemType::opgt:
		return "opgt";
	case LexemType::ople:
		return "ople";
	case LexemType::opnot:
		return "opnot";
	case LexemType::opor:
		return "opor";
	case LexemType::opand:
		return "opand";
	case LexemType::kwint:
		return "kwint";
	case LexemType::kwchar:
		return "kwchar";
	case LexemType::kwif:
		return "kwif";
	case LexemType::kwelse:
		return "kwelse";
	case LexemType::kwswitch:
		return "kwswitch";
	case LexemType::kwcase:
		return "kwcase";
	case LexemType::kwwhile:
		return "kwwhile";
	case LexemType::kwfor:
		return "kwfor";
	case LexemType::kwreturn:
		return "kwreturn";
	case LexemType::kwin:
		return "kwin";
	case LexemType::kwout:
		return "kwout";
	case LexemType::eof:
		return "eof";
	case LexemType::error:
		return "error";
	}
}


//����� 2

Scanner::Scanner(std::istream& stream)
	: _stream(stream)
{
}

Token Scanner::getNextToken()