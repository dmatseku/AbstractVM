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
	std::ifstream	file(str);
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
			std::cout << e.what() << std::endl;
		}
	}
}

const char*	VM::no_exit_exception::what() const noexcept
{
	return ("File has no end(");
}