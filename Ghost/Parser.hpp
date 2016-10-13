#pragma once

#include "Compiler.hpp"

#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

class Parser
{
public:
	Parser(std::string fileName, bool compile);
	~Parser();

	std::vector<char> m_keys = { '{', '}' };
private:

	// Compiler
	Compiler m_compiler;

	// Used to begin the whole parsing on our queue
	void beginParse(std::string fileName, std::string Output);
	// Our input and output files
	std::ifstream m_inFile;
	std::ofstream m_outFile;

	std::string m_outputFileName;

	void Parser::saveFile(std::string output);

	// Converts our input line and returns it to our formatted line
	std::string convertLine(std::string line, int index); // Convert a specific line into the correct format (i = current iteration in the vector)
	std::string replaceAll(std::string line, const std::string &from,const std::string &to);
	std::size_t find(std::string line, std::string toFind);

	// Cleaners
	std::string handleBrackets(std::string line, int index);
	std::string handleStatementBrackets(std::string line, int index);

	// Formatter
	void formatIndents();
	std::string formatLine(std::string line, int indentCount);
	void deleteEmptyLine(std::string line);
	
	// Import (replace all import(x) with import x
	std::string handleImports(std::string line, int index);

	// Begin parsing the file
	bool begin();

	// Our input and output lines
	std::vector<std::string> m_inLines;
	std::vector<std::string> m_outLines;

	// Advanced getters
	std::string getStringBetween(std::string str, std::size_t posA, std::size_t posB); // Get a specific word between position A and B

	// Imports we need to convert
	void appendImport(std::string imports);
	std::vector<std::string> m_importCheckList; // Vector that contains all imports we've processed so far
	std::queue<std::string> m_imports;
};

