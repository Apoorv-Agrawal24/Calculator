#ifndef SOLVE_H
#define SOLVE_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>


enum class Type
{
	ADD,
	SUB,
	MUL,
	DIV,
	NUM,
	LPAREN,
	RPAREN,
};

struct Token
{
	Type type;
	long long value;

	Token operator+(const Token &token)
	{
		Token returnTok;
		returnTok.type = Type::NUM;
		returnTok.value = this->value + token.value;
		return returnTok;
	}

	Token operator-(const Token &token)
	{
		Token returnTok;
		returnTok.type = Type::NUM;
		returnTok.value = this->value - token.value;
		return returnTok;
	}

	Token operator/(const Token &token)
	{
		Token returnTok;
		returnTok.type = Type::NUM;
		returnTok.value = this->value / token.value;
		return returnTok;
	}

	Token operator*(const Token &token)
	{
		Token returnTok;
		returnTok.type = Type::NUM;
		returnTok.value = this->value * token.value;
		return returnTok;
	}
};

class Solve
{
private:
	std::vector<Token> lexer(const std::string expression);
	bool isNum(const char testNum);
	std::vector<Token> infix(const std::vector<Token> tokens);
	int precedence(const Type symbol);
	std::stack<Token> eval(const std::vector<Token> tokens);
public:
	long long run(const std::string expression)
	{
		std::stack<Token> tokens = eval(infix(lexer(expression)));
		return tokens.top().value;
	}
	void show(const std::vector<Token> tokens);
};

#endif