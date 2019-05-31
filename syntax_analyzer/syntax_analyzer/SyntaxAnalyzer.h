#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "FileManager.h"

class SyntaxAnalyzer
{
	enum Terminal : int
	{
		VTYPE = 0,
		NUM,
		LITERAL,
		ID,
		IF,
		ELSE,
		WHILE,
		RETURN,
		ADDSUB,
		MULTDIV,
		ASSIGN,
		COMP,
		SEMI,
		COMMA,
		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,
		ENDMARKER
	};

	enum NonTerminal : int
	{
		CODE = 0,
		DECL,
		ARG,
		MOREARGS,
		BLOCK,
		STMT,
		RHS,
		RHSORFCALL,
		EXPR,
		EXPR2,
		TERM,
		TERM2,
		FACTOR,
		COND,
		NRETURN
	};

	std::vector<std::string> _symbolTable;
	std::vector<std::vector<std::string>> _llTable;

private:
	void ComputeSymbolTable(std::string const &);
	void FillLLTable();

	int StringToTerminal(std::string const &) const;
	int StringToNonTerminal(std::string const &) const;
	std::string const &TokenToTerminal(std::string const &) const;

public:
	SyntaxAnalyzer(std::string const &);
	~SyntaxAnalyzer() = default;

	void Go();
};
