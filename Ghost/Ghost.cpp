// Ghost.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include "Parser.hpp"

int main(int argc, char** argv) 
{
	const float VERSION = 1.0;
	std::string mainFilePath = "Test";
	bool compileMode = false;

	if (argc > 1)
	{
		mainFilePath = argv[1];
		compileMode = argv[2];
	}
	else
	{
		std::cout << "Compile [y/n]: ";
		
		char answer;
		std::cin >> answer;

		switch (answer)
		{
		case 'y':
			compileMode = true;
			break;
		default:
			compileMode = false;
			break;
		}

	}

	std::cout << "Ghost Version: " << VERSION << std::endl;
	std::cout << "Joel Craig (CR)" << std::endl;
	std::cout << "Executing from path: " << argv[0] << std::endl;

	Parser parser(mainFilePath, compileMode);

	std::cin.get();

    return 0;
}

