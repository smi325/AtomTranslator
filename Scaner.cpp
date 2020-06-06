#include "LexicalAnalyser.h"
#include <map>

std::map<char, int> digits{ { '0', 0 }, { '1', 1 }, { '2',  2}, { '3',  3}, { '4', 4 }, { '5', 5 }, { '6', 6 }, { '7', 7 }, { '8', 8 }, { '9', 9 }, };

std::map<char, LexemType> punctuation{ {'(', LexemType::lpar}, {')', LexemType::rpar}, {'{', LexemType::lbrace}, {'}', LexemType::rbrace}, {'[', LexemType::lbracket}, {']', LexemType::rbracket}, {';', LexemType::semicolon}, {',', LexemType::comma}, {':', LexemType::colon} };

std::map<std::string, LexemType> keywords{ {"int", LexemType::kwint}, {"char", LexemType::kwchar}, {"if", LexemType::kwif}, {"else", LexemType::kwelse}, {"switch", LexemType::kwswitch}, {"case", LexemType::kwcase}, {"while", LexemType::kwwhile}, {"for", LexemType::kwfor}, {"return", LexemType::kwreturn}, {"in", LexemType::kwin}, {"out", LexemType::kwout}, };

Token::Token() {};

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


//ЧАСТЬ 2

Scanner::Scanner(std::istream& stream)
	: _stream(stream)
{
}

void Scanner::ungetG()
{
	_unget_check = true;
}

Token Scanner::getNextToken(){	if (_unget_check == true)	{		_unget_check = false;		return _last_token;	}	char chr;	int value_int = 0;	char value_char;	std::string value_str = "";	while (true)	{		_stream >> chr;		if (_state == 0)		{			if (_stream.eof()) /* Проверка на конец потока*/			{				_last_token = Token(LexemType::eof);				return Token(LexemType::eof);			}			if (chr == ' ' || chr == '	' || chr == '\n') /* Пропуск пробелов*/			{				continue;			}			if (chr == '*')			{				_last_token = Token(LexemType::opmult);				return Token(LexemType::opmult);			}			if (chr == '>')			{				_last_token = Token(LexemType::opgt);				return Token(LexemType::opgt);			}			if (punctuation.count(chr) > 0)			{				_last_token = Token(punctuation[chr]);				return Token(punctuation[chr]);			}			if (digits.count(chr) > 0) /* Числа*/			{				value_int = (int)chr - 48;				_state = 1;				continue;			}			if (chr == '\'')			{				_state = 2;				continue;			}			if (chr == '"')			{				_state = 4;				continue;			}			if (((chr >= 'A') && (chr <= 'Z')) || ((chr >= 'a') && (chr <= 'z')) || (chr == '_'))			{				value_str += chr;				_state = 5;				continue;			}			if (chr == '-')			{				_state = 6;				continue;			}			if (chr == '!')			{				_state = 7;				continue;			}			if (chr == '<')			{				_state = 8;				continue;			}			if (chr == '=')			{				_state = 9;				continue;			}			if (chr == '+')			{				_state = 10;				continue;			}			if (chr == '|')			{				_state = 11;				continue;			}			if (chr == '&')			{				_state = 12;				continue;			}			_last_token = Token(LexemType::error, "неподдерживаемый языком символ");			return Token(LexemType::error, "неподдерживаемый языком символ");		}		/* Считывание чисел*/		if (_state == 1)		{			if (_stream.eof())			{				_state = 0;				_last_token = Token(value_int);				return Token(value_int);			}			if (digits.count(chr) == 0)			{				_stream.unget();				_state = 0;				_last_token = Token(value_int);				return Token(value_int);			}			if (digits.count(chr) > 0)			{				if (value_int >= 0)					value_int = value_int * 10 + (int)chr - 48;				if (value_int < 0)					value_int = value_int * 10 - (int)chr + 48;			}		} 		/* Считывание символьной константы*/		if (_state == 2)		{			if (_stream.eof())			{				_last_token = Token(LexemType::error, "неожиданный конец файла при чтении символьной константы");				return Token(LexemType::error, "неожиданный конец файла при чтении символьной константы");			}			if (chr != '\'')			{				value_char = chr;				_state = 3;				continue;			}			if (chr == '\'')			{				_last_token = Token(LexemType::error, "пустая символьная константа");				return Token(LexemType::error, "пустая символьная константа");			}		}		if (_state == 3)		{			if (chr == '\'')			{				_state = 0;				_last_token = Token(value_char);				return Token(value_char);			}			if (chr != '\'')			{				_last_token = Token(LexemType::error, "символьная константа содержит более одного символа");				return Token(LexemType::error, "символьная константа содержит более одного символа");			}		}		/* Считывание строки*/		if (_state == 4)		{			if (_stream.eof())			{				_last_token = Token(LexemType::error, "неожиданный конец файла при чтении строки");				return Token(LexemType::error, "неожиданный конец файла при чтении строки");			}			if (chr != '"')			{				value_str += chr;			}			if (chr == '"')			{				_state = 0;				_last_token = Token(LexemType::str, value_str);				return Token(LexemType::str, value_str);			}		}		/* Считывание id или keyword*/		if (_state == 5)		{			if (_stream.eof())			{				if (keywords.count(value_str) > 0)				{					_state = 0;					_last_token = Token(keywords[value_str]);					return Token(keywords[value_str]);				}				if (keywords.count(value_str) == 0)				{					_state = 0;					_last_token = Token(LexemType::id, value_str);					return Token(LexemType::id, value_str);				}			}			if ((((chr >= 'A') && (chr <= 'Z')) || ((chr >= 'a') && (chr <= 'z')) || (chr == '_')) || digits.count(chr) > 0)			{				value_str += chr;			}			else			{				_stream.unget();				_state = 0;				if (keywords.count(value_str) > 0)				{					_state = 0;					_last_token = Token(keywords[value_str]);					return Token(keywords[value_str]);				}				if (keywords.count(value_str) == 0)				{					_state = 0;					_last_token = Token(LexemType::id, value_str);					return Token(LexemType::id, value_str);				}			}		}		/* Считывание операции "-" или отрицательного числа*/		if (_state == 6)		{			if (_stream.eof())			{				_state = 0;				_last_token = Token(LexemType::opminus);				return Token(LexemType::opminus);			}			if (digits.count(chr) > 0)			{				value_int = -1 * ((int)chr - 48);				_state = 1;				continue;			}			if (digits.count(chr) == 0)			{				_stream.unget();				_state = 0;				_last_token = Token(LexemType::opminus);				return Token(LexemType::opminus);			}		}		/* Считывание "!=" или "!"*/		if (_state == 7)		{			if (_stream.eof())			{				_state = 0;				_last_token = Token(LexemType::opnot);				return Token(LexemType::opnot);			}			if (chr == '=')			{				_state = 0;				_last_token = Token(LexemType::opne);				return Token(LexemType::opne);			}			if (chr != '=')			{				_state = 0;				_stream.unget();				_last_token = Token(LexemType::opnot);				return Token(LexemType::opnot);			}		}		/* Считывание "<" или "<="*/		if (_state == 8)		{			if (_stream.eof())			{				_state = 0;				_last_token = Token(LexemType::oplt);				return Token(LexemType::oplt);			}			if (chr == '=')			{				_state = 0;				_last_token = Token(LexemType::ople);				return Token(LexemType::ople);			}			if (chr != '=')			{				_state = 0;				_stream.unget();				_last_token = Token(LexemType::oplt);				return Token(LexemType::oplt);			}		}		/* Считывание "=" или "=="*/		if (_state == 9)		{			if (_stream.eof())			{				_state = 0;				_last_token = Token(LexemType::opassign);				return Token(LexemType::opassign);			}			if (chr == '=')			{				_state = 0;				_last_token = Token(LexemType::opeq);				return Token(LexemType::opeq);			}			if (chr != '=')			{				_state = 0;				_stream.unget();				_last_token = Token(LexemType::opassign);				return Token(LexemType::opassign);			}		}		/* Считывание "+" или "+="*/		if (_state == 10)		{			if (_stream.eof())			{				_state = 0;				_last_token = Token(LexemType::opplus);				return Token(LexemType::opplus);			}			if (chr == '+')			{				_state = 0;				_last_token = Token(LexemType::opinc);				return Token(LexemType::opinc);			}			if (chr != '+')			{				_state = 0;				_stream.unget();				_last_token = Token(LexemType::opplus);				return Token(LexemType::opplus);			}		}		/* Считывание "||"*/		if (_state == 11)		{			if (_stream.eof())			{				_last_token = Token(LexemType::error, "неожиданный конец файла при чтении ||");				return Token(LexemType::error, "неожиданный конец файла при чтении ||");			}			if (chr == '|')			{				_state = 0;				_last_token = Token(LexemType::opor);				return Token(LexemType::opor);			}			if (chr != '|')			{				_last_token = Token(LexemType::error, "одиночный символ |");				return Token(LexemType::error, "одиночный символ |");			}		}		/* Считывание "&&"*/		if (_state == 12)		{			if (_stream.eof())			{				_last_token = Token(LexemType::error, "неожиданный конец файла при чтении &&");				return Token(LexemType::error, "неожиданный конец файла при чтении &&");			}			if (chr == '&')			{				_state = 0;				_last_token = Token(LexemType::opand);				return Token(LexemType::opand);			}			if (chr != '&')			{				_last_token = Token(LexemType::error, "одиночный символ &");				return Token(LexemType::error, "одиночный символ &");			}		}	}}