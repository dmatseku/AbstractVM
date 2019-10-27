#include "VM.hpp"
#include "File.hpp"
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
	size_t		char_pos;
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
			for (std::string &line : file)
			{
				if (line.find(';') != std::string::npos)
					line.erase(line.find(';'));

				if (line.empty())
					continue;

				if ((char_pos = line.find(' ')) == std::string::npos)
					tmp = line;
				else
					tmp = line.substr(0, char_pos);
				File::operation op = file[tmp];
				(file.*op)(line);
				if (file.should_exit())
					break;
			}
			if (!file.should_exit())
			{
				throw no_exit_exception();
			}
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