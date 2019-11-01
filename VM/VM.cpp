#include "VM.hpp"
#include "../File/File.hpp"
#include <iostream>
#include <list>
#include <fstream>

namespace
{
	std::list<File>	files;
}

void
VM::add_file(std::string const &str)
{
	std::ifstream	file;

	file.open(str);
	if (!file)
		throw invalid_file_exception("File does not exist");

	files.emplace_back(File(file));
	file.close();
}

void
VM::add_file()
{
	files.emplace_back(File(std::cin));
}

void
VM::execute()
{
	std::string tmp;
	int			i = -1;

	if (files.empty())
		return;
	for (File& file : files)
	{
		std::cout << '\n'
			<< "~~~~~~  File: " << ++i << "  ~~~~~~"
			<< '\n' << std::endl;
		try
		{
			file.execute();
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

VM::invalid_file_exception::invalid_file_exception(std::string const & str)
: std::invalid_argument(str)
{}