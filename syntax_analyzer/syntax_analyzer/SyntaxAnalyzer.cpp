#include "pch.h"
#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer(std::string const &filePath) :
	_llTable(NRETURN + 1, std::vector<std::string>(ENDMARKER + 1))
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

	std::cout << "Symbol table just with tokens : " << std::endl;
	for (auto &token : _symbolTable) {
		std::cout << token << std::endl;
	}
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
	_llTable[STMT][ID] = "if RHSORFCALL semi";
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
	_llTable[FACTOR][NUM] = "num";
	_llTable[FACTOR][ID] = "id";
	_llTable[FACTOR][LPAREN] = "lparen EXPR rparen";
	_llTable[COND][NUM] = "FACTOR comp FACTOR";
	_llTable[COND][ID] = "FACTOR comp FACTOR";
	_llTable[COND][LPAREN] = "FACTOR comp FACTOR";
	_llTable[NRETURN][RETURN] = "return FACTOR semi";
}

int SyntaxAnalyzer::StringToTerminal(std::string const &) const
{
	// TODO: insérer une instruction return ici

}

int SyntaxAnalyzer::StringToNonTerminal(std::string const &) const
{
	// TODO: insérer une instruction return ici
}


std::string const & SyntaxAnalyzer::TokenToTerminal(std::string const &line) const
{
	// TODO: insérer une instruction return ici
	std::string value;
	std::string token;

	token = line.substr(0, line.find('\t'));
	value = line.substr(line.find('\t'));
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);

	if (token == "ID")
		return "id";
	else if (token == "INT")
		return "vtype";
	else if (token == "CHAR")
		return "vtype";
	else if (token == "NUMBER")
		return "num";
	else if (token == "STRING")
		return "literal";
	else if (token == "KEYWORD" && value == "while")
		return "while";
	else if (token == "KEYWORD" && value == "if")
		return "if";
	else if (token == "KEYWORD" && value == "else")
		return "else";
	else if (token == "KEYWORD" && value == "return")
		return "return";
	else if (token == "ARITHMETIC_OPERATOR" && (value == "+" || value == "-"))
		return "addsub";
	else if (token == "ARITHMETIC_OPERATOR" && (value == "/" || value == "*"))
		return "multdiv";
	else if (token == "ASSIGNMENT_OPERATOR")
		return "assign";
	else if (token == "COMPARISION_OPERATOR")
		return "comp";
	else if (token == "SEMI_COL")
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
}

void SyntaxAnalyzer::Go()
{

}
