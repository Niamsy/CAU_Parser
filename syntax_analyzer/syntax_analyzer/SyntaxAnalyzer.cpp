#include "pch.h"
#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer(std::string const &filePath) :
	_llTable(NRETURN + 1, std::vector<std::string>(ENDMARKER + 1, ""))
{
	auto fileManager = new FileManager();
	fileManager->Open(filePath);
	auto symbolTableSource = fileManager->Read();
	fileManager->Close();
	ComputeSymbolTable(symbolTableSource);
	FillLLTable();
}

void SyntaxAnalyzer::ComputeSymbolTable(std::string const &symbolTableSource)
{
	std::istringstream iss(symbolTableSource);

	std::string line;
	while (std::getline(iss, line)) {
		_symbolTable.push_back(line);
	}
	_symbolTable.push_back("e");
}

void SyntaxAnalyzer::FillLLTable()
{
	_llTable[CODE][VTYPE] = "vtype id DECL CODE";
	_llTable[CODE][ENDMARKER] = "e";
	_llTable[DECL][SEMI] = "semi";
	_llTable[DECL][LPAREN] = "lparen ARG rparen lbrace BLOCK RETURN rbrace";
	_llTable[ARG][VTYPE] = "vtype id MOREARGS";
	_llTable[ARG][RPAREN] = "e";
	_llTable[MOREARGS][COMMA] = "comma vtype id MOREARGS";
	_llTable[MOREARGS][RPAREN] = "e";
	_llTable[BLOCK][VTYPE] = "STMT BLOCK";
	_llTable[BLOCK][ID] = "STMT BLOCK";
	_llTable[BLOCK][ID] = "STMT BLOCK";
	_llTable[BLOCK][IF] = "STMT BLOCK";
	_llTable[BLOCK][WHILE] = "STMT BLOCK";
	_llTable[BLOCK][RETURN] = "e";
	_llTable[BLOCK][RBRACE] = "e";
	_llTable[STMT][VTYPE] = "vtype id semi";
	_llTable[STMT][ID] = "id RHSORFCALL semi";
	_llTable[STMT][IF] = "if lparen COND rparen lbrace BLOCK rbrace else lbrace BLOCK rbrace";
	_llTable[STMT][WHILE] = "while lparen COND rparen lbrace BLOCK rbrace";
	_llTable[RHS][NUM] = "EXPR";
	_llTable[RHS][LITERAL] = "literal";
	_llTable[RHS][ID] = "EXPR";
	_llTable[RHS][LPAREN] = "EXPR";
	_llTable[RHSORFCALL][ASSIGN] = "assign RHS";
	_llTable[EXPR][NUM] = "TERM EXPR2";
	_llTable[EXPR][ID] = "TERM EXPR2";
	_llTable[EXPR][LPAREN] = "TERM EXPR2";
	_llTable[EXPR2][ADDSUB] = "addsub EXPR";
	_llTable[EXPR2][SEMI] = "e";
	_llTable[EXPR2][RPAREN] = "e";
	_llTable[TERM][NUM] = "FACTOR TERM2";
	_llTable[TERM][ID] = "FACTOR TERM2";
	_llTable[TERM][LPAREN] = "FACTOR TERM2";
	_llTable[TERM2][ADDSUB] = "e";
	_llTable[TERM2][MULTDIV] = "multdiv TERM";
	_llTable[TERM2][SEMI] = "e";
	_llTable[FACTOR][NUM] = "num";
	_llTable[FACTOR][ID] = "id";
	_llTable[FACTOR][LPAREN] = "lparen EXPR rparen";
	_llTable[COND][NUM] = "FACTOR comp FACTOR";
	_llTable[COND][ID] = "FACTOR comp FACTOR";
	_llTable[COND][LPAREN] = "FACTOR comp FACTOR";
	_llTable[NRETURN][RETURN] = "return FACTOR semi";
}


int SyntaxAnalyzer::StringToTerminal(std::string const &str) const
{
	if (str == "vtype")
		return VTYPE;
	else if (str == "num")
		return NUM;
	else if (str == "literal")
		return LITERAL;
	else if (str == "id")
		return ID;
	else if (str == "if")
		return IF;
	else if (str == "else")
		return ELSE;
	else if (str == "while")
		return WHILE;
	else if (str == "return")
		return RETURN;
	else if (str == "addsub")
		return ADDSUB;
	else if (str == "multdiv")
		return MULTDIV;
	else if (str == "assign")
		return ASSIGN;
	else if (str == "comp")
		return COMP;
	else if (str == "semi")
		return SEMI;
	else if (str == "comma")
		return COMMA;
	else if (str == "lparen")
		return LPAREN;
	else if (str == "rparen")
		return RPAREN;
	else if (str == "lbrace")
		return LBRACE;
	else if (str == "rbrace")
		return RBRACE;
	else if (str == "e")
		return ENDMARKER;
	else
		throw std::exception("Error: Invalid terminal.");
}

int SyntaxAnalyzer::StringToNonTerminal(std::string const &str) const
{
	if (str == "CODE")
		return CODE;
	else if (str == "DECL")
		return DECL;
	else if (str == "ARG")
		return ARG;
	else if (str == "MOREARGS")
		return MOREARGS;
	else if (str == "BLOCK")
		return BLOCK;
	else if (str == "STMT")
		return STMT;
	else if (str == "RHS")
		return RHS;
	else if (str == "RHSORFCALL")
		return RHSORFCALL;
	else if (str == "EXPR")
		return EXPR;
	else if (str == "EXPR2")
		return EXPR2;
	else if (str == "TERM")
		return TERM;
	else if (str == "TERM2")
		return TERM2;
	else if (str == "FACTOR")
		return FACTOR;
	else if (str == "COND")
		return COND;
	else if (str == "RETURN")
		return NRETURN;
	else
		throw std::exception("Error: Invalid non terminal.");
}


std::string SyntaxAnalyzer::TokenToTerminal(std::string const &line) const
{
	std::string value;
	std::string token;

	token = line.substr(0, line.find('\t'));
	value = line.substr(line.find('\t') + 1, line.size() - 1);
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);

	if (token == "ID")
		return "id";
	else if (token == "INT")
		return "vtype";
	else if (token == "CHAR")
		return "vtype";
	else if (token == "INTEGER")
		return "num";
	else if (token == "STRING")
		return "literal";
	else if (token == "KEYWORD" && value.find("while") == 0)
		return "while";
	else if (token == "KEYWORD" && value.find("if") == 0)
		return "if";
	else if (token == "KEYWORD" && value.find("else") == 0)
		return "else";
	else if (token == "KEYWORD" && value.find("return") == 0)
		return "return";
	else if (token == "ARITHMETIC_OPERATOR" && (value == "+" || value == "-"))
		return "addsub";
	else if (token == "ARITHMETIC_OPERATOR" && (value == "/" || value == "*"))
		return "multdiv";
	else if (token == "ASSIGNMENT_OPERATOR")
		return "assign";
	else if (token == "COMPARISON_OPERATOR")
		return "comp";
	else if (token == "SEMICOL")
		return "semi";
	else if (token == "LBRACE")
		return "lbrace";
	else if (token == "RBRACE")
		return "rbrace";
	else if (token == "LPAREN")
		return "lparen";
	else if (token == "RPAREN")
		return "rparen";
	else if (token == "COMMA")
		return "comma";
	else if (token == "e")
		return "e";
	else
		throw std::exception("Error: Invalid token.");
}

void SyntaxAnalyzer::FillStack(std::string const &str)
{
	std::vector<std::string> splitString;
	std::string word;
	std::stringstream ss(str);

	_stack.pop();
	while (std::getline(ss, word, ' ')) {
		splitString.push_back(word);
	}
	std::reverse(splitString.begin(), splitString.end());
	for (auto &elem : splitString) {
		_stack.push(elem);

	}
}


void SyntaxAnalyzer::Go()
{
	std::string inputPointer;
	std::string tableElem;
	int lineCounter = 0;
	int terminal;
	int nonTerminal;

	_stack.push("e");
	_stack.push("CODE");

	for (auto &elem : _symbolTable)
	{
		inputPointer = TokenToTerminal(elem);
		terminal = StringToTerminal(inputPointer);
		
		while (_stack.top() != inputPointer)
		{
			try {
				nonTerminal = StringToNonTerminal(_stack.top());
			}
			catch (...) {
				std::cout << "Error line: " << lineCounter << ". Token \"" << elem << "\" should match a " << _stack.top() << "." << std::endl;
				return;
			}
			tableElem = _llTable[nonTerminal][terminal];
			if (tableElem == "e") {
				_stack.pop();
				continue;
			}
			if (tableElem.size() > 0) {
				try {
					FillStack(tableElem);
				}
				catch (...) {
					std::cout << "Error line: " << lineCounter << ". Token \"" << elem << "\" should match a " << _stack.top() << "." << std::endl;
					return;
				}
			}
			else
			{
				std::cout << "Error line: " << lineCounter << ". Token \"" << elem << "\" should match a " << _stack.top() << "." << std::endl;
				return;
			}
		}
		
		_stack.pop();
		lineCounter += 1;
	}

	if (!_stack.empty())
	{
		std::cout << "Stack not empty, grammar error" << std::endl;
	}
	else {
		std::cout << "Success !" << std::endl;
	}
}
