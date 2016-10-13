#include "Compiler.hpp"



Compiler::Compiler()
{
}


Compiler::~Compiler()
{
}

void Compiler::compile(std::string filePath, CompileType type)
{
	if (type == WINDOWS)
	{


		std::cout << "**************************" << std::endl;
		std::cout << "Compiling..." << std::endl;

		m_cmd = "ghost-compile.bat";

		m_mainFilePath = filePath += ".exe";
		remove("test.exe");
		
		system(m_cmd.c_str());

		while (!fileExists(m_mainFilePath))
		{
			// Wait
		}

		rename("test.exe", m_mainFilePath.c_str());

		std::cout << "Compilation finished, press any key to continue" << std::endl;
	}
}


bool Compiler::fileExists(std::string fileName)
{
	std::ifstream file(fileName);

	if (file.good())
	{
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}