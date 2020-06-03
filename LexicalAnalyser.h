#pragma once
#include <string>
#include <iostream>


enum class LexemType
{
	num, chr, str, id, lpar, rpar, lbrace, rbrace, lbracket, rbracket,
	semicolon, comma, colon, opassign, opplus, opminus, opmult, opinc, opeq, opne, oplt,
	opgt, ople, opnot, opor, opand, kwint, kwchar, kwif, kwelse, kwswitch, kwcase, kwwhile,
	kwfor, kwreturn, kwin, kwout, eof, error
};


class Token
{
private:
	LexemType _type;
	int _value = 0;
	std::string _str;

public:
	Token(LexemType type);
	Token(int value);
	Token(LexemType type, const std::string& str);
	Token(char c);

	void print(std::ostream& stream);

	LexemType type();
	int value();
	std::string str();

	std::string type_to_str();
};


class Scanner
{
private:
	std::istream& _stream;
	int _state = 0;

public:
	Scanner(std::istream& stream);
	Token getNextToken();

};
