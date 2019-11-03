#include "VM.hpp"
#include "../File/File.hpp"
#include <iostream>
#include <list>
#include <fstream>

namespace
{
	void read_from_file(std::string const & file_name)
	{
		std::ifstream stream;

		stream.open(file_name);
		if (!stream)
			throw VM::invalid_file_exception("File does not exist");

		File file(stream);

		stream.close();
	}

	void read_from_stdin()
	{
		File file(std::cin);
	}
}

void
VM::read_file(char** files, int count)
{
	if (!count)
	{
		read_from_stdin();
		return;
	}

	for (int i = 0; i < count; i++)
	{
		std::cout << "~~~~~~~~ File: " + std::to_string(i) + " ~~~~~~~~\n" << std::endl;

		if (!strcmp(files[i], "-in"))
			read_from_stdin();
		else
			read_from_file(files[i]);

		std::cout << std::endl;
	}
}

VM::invalid_file_exception::invalid_file_exception(std::string const & str)
: std::invalid_argument(str)
{}