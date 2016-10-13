#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
class Compiler
{
public:
	enum CompileType
	{
		WINDOWS,
		LINUX,
		MAC
	};
	Compiler();
	~Compiler();

	void compile(std::string filePath, CompileType type);

private:
	std::string m_mainFilePath;
	std::string m_cmd;
	
	bool fileExists(std::string filename);
};

