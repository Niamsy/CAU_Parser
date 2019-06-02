// syntax_analyzer.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "SyntaxAnalyzer.h"

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Usage: symboltableFile" << std::endl;
		return 0;
	}

	try {
		SyntaxAnalyzer parser(av[1]);

		parser.Go();

	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}