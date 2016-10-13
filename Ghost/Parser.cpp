#include "Parser.hpp"





Parser::Parser(std::string fileName, bool compile)
{
	// Add our first file to our queue to be parsed
	m_imports.push(fileName);


	// Parse the rest of our imports
	while (!m_imports.empty())
	{
		// Parse all of our imports
		m_inLines.clear();
		m_outLines.clear();
		beginParse(m_imports.front() + ".ghost", m_imports.front());
		m_imports.pop();
	}

	// Run the compiler
	if (compile)
	{
		m_compiler.compile(fileName + ".py", Compiler::WINDOWS);
	}

}

void Parser::beginParse(std::string fileName, std::string Output)
{
	if (m_inFile.is_open())
	{
		m_inFile.close();
	}

	if (m_outFile.is_open())
	{
		m_outFile.close();
	}


	m_inFile.open(fileName.c_str());
	m_outputFileName = Output + ".py";

	if (m_inFile.is_open())
	{
		std::cout << "Parsing: " << fileName << ".. ";
		if (begin())
		{
			saveFile(m_outputFileName);
		}
		std::cout << "Done " << std::endl;
	}
	else
	{
		std::cout << "Failed to open: " + fileName << std::endl;
	}
}

void Parser::saveFile(std::string output)
{
	m_outFile.open(output.c_str());

	if (m_outFile.is_open())
	{
		std::cout << "Writing file file: " << output << std::endl;

		// Format the outlines
		//formatIndents();

		// Write each line to the file
		for (int i = 0; i < m_outLines.size(); i++)
		{
			m_outFile << m_outLines.at(i) << "\n";
		}

		// Close the file once it's finished being written to.
		m_outFile.close();
	}
	else
	{
		std::cout << "Unable to write to file: " << output << std::endl;
	}


}

bool Parser::begin()
{
	std::string temp_line;

	// Load all of our lines into memory
	while (std::getline(m_inFile, temp_line))
	{
		m_inLines.push_back(temp_line);
	}

	m_inFile.close();

	// Begin parisng the lines
	for (auto i = 0; i < m_inLines.size(); i++)
	{
		std::string convertedStr = convertLine(m_inLines[i], i);
		//convertedStr = formatLine(convertedStr, -1);
		m_outLines.push_back(convertedStr);
	}

	formatIndents();

	// Remove all close brackets
	for (auto i = 0; i < m_outLines.size(); i++)
	{
		m_outLines[i] = replaceAll(m_outLines[i], "}", "");
	}

	return true;
}

std::string Parser::getStringBetween(std::string str, std::size_t posA, std::size_t posB)
{
	std::string strFinal = "";

	for (int i = posA; i < posB; i++)
	{
		// If this occurs then there are no brackets after the if statement
		if (!isspace(str.at(i)))
		{
			// There are no brackets here
			strFinal += str.at(i);
		}
	}

	return strFinal;
}

void Parser::appendImport(std::string imports)
{
	bool unique = true;

	for (std::size_t i = 0; i < m_importCheckList.size(); i++)
	{
		if (m_importCheckList[i] == imports)
		{
			unique = false;
			break;
		}
	}

	if (unique)
	{
		std::cout << "Added ghost import: " << imports << std::endl;
		m_imports.push(imports);
		m_importCheckList.push_back(imports);
	}
}

std::string Parser::convertLine(std::string line, int index)
{
	std::string str;
	
	str = handleImports(line , index);
	str = handleBrackets(str, index);
	str = handleStatementBrackets(str, index);
	return str;
}

std::string Parser::replaceAll(std::string line, const std::string &from, const std::string &to)
{
	size_t start_pos = 0;
	while ((start_pos = line.find(from, start_pos)) != std::string::npos) 
	{
		line.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return line;
}

std::size_t Parser::find(std::string line, std::string toFind)
{
	std::size_t found = line.find(toFind);

	return found;
}

std::string Parser::handleBrackets(std::string line, int index)
{

	if (find(line, "{") != std::string::npos)
	{
		// Get our start and finish block
		std::size_t startBlock = index;
		std::size_t closedBlock = 0;

		for (int i = index; i < m_outLines.size(); i++)
		{
			if (find(m_outLines[i], "}") != std::string::npos)
			{
				closedBlock = 0;
			}
		}

		// Python likes to have a ":" after any if, while, for or do statement, so lets add one
		m_outLines[startBlock - 1].append(":");

		// Add tabs to the inside of our block of code
		for (int i = startBlock; i < closedBlock; i++)
		{
			m_outLines[i] = "\t" + m_outLines[i];
		}

		// Could possibly put an error throw here, we didn't find an end block
	}

	// Clean up all of our brackets
	std::string finalStr = replaceAll(line, "{", "\n");
	finalStr += "\t";

	return finalStr;
}

std::string Parser::handleStatementBrackets(std::string line, int index)
{
	bool brackets = true;
	std::string finalStr = line;
	// If we find a bracket ( or ) in an if statement, delete the first and last occureance of it
	std::size_t found = find(line, "if");

	// Check for while's
	if (found != std::string::npos)
	{
		found = find(line, "while");
	}


	if (found != std::string::npos)
	{

		// Do a manual position find here incase we are calling a function
		// and it could trigger our event
		for (int i = found + 1; i < line.size(); i++)
		{
			// If this occurs then there are no brackets after the if statement
			if (line.at(i) == '(' || isspace(line.at(i)))
			{
				// There are no brackets here
				brackets = false;
				break;
			}
			else
			{

				// There are brackets
				brackets = true;
				break;
			}
		}

		if (brackets)
		{
			// Get the first occurance of the bracket
			std::size_t firstOccurance = find(finalStr, "(");

			// Remove the first occurance first, as it will offset our last occurance if we do it at the same time

			finalStr = finalStr.replace(firstOccurance , 1 , " ");
			// Get the last occurance of the bracket
			std::size_t lastOccurance = 0;
			for (int i = 0; i < finalStr.size(); i++)
			{
				if (finalStr.at(i) == ')')
				{
					lastOccurance = i;
				}
			}

			// Replace the occurances with an empty gap
			finalStr = finalStr.replace(lastOccurance, 1, " ");
		}
	}
	return finalStr;
}


void Parser::formatIndents()
{
	int indentCount = 0;
	std::string currentLine = "";
	bool skipIndent;

	for (int i = 0; i < m_outLines.size(); i++)
	{
		currentLine = m_outLines[i];
		skipIndent = false;

		// Find items to indent
		if (find(currentLine, ":") != std::string::npos || find(currentLine, "{") != std::string::npos)
		{
			indentCount++;
			skipIndent = true;
		}

		if (find(currentLine, "}") != std::string::npos)
		{
			indentCount--;
			skipIndent = false;
		}

		// Apply indent to line
		if (!skipIndent)
		{
			for (int i = 0; i < indentCount; i++)
			{
				currentLine += "\t";
			}
		}

		m_outLines[i] = currentLine;

	}
}

std::string Parser::formatLine(std::string line, int indentCount)
{
	return std::string();
}

void Parser::deleteEmptyLine(std::string line)
{

	for (std::vector<std::string>::iterator it = m_outLines.begin(); it != m_outLines.end(); it++)
	{
		if (line == (*it))
		{
			m_outLines.erase(it);

			break;
		}
	}

}

std::string Parser::handleImports(std::string line, int index)
{
	// Replace the import
	std::string finalStr = line;
	std::size_t found = find(finalStr, "import(");


	if (found != std::string::npos)
	{
		// We first want to add the import to the queue for parsing
		std::size_t posA = find(finalStr, "(") + 1;
		std::size_t posB = find(finalStr, (")"));

		if (posA > 1)
		{
			std::string import = getStringBetween(finalStr, posA, posB);
			appendImport(import);
		}


		// Replace our imports with standard imports
		finalStr = replaceAll(finalStr, "(", " ");
		finalStr = replaceAll(finalStr, ")", " ");
	}

	return finalStr;
}

Parser::~Parser()
{
}




