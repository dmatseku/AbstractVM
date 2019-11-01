#include <iostream>
#include "VM/VM.hpp"

int main(int ac, char** av)
{
	int file_nb = 1;
	try
	{
		if (ac == 1)
			VM::add_file();
		else
		{
			for (file_nb = 1; file_nb < ac; file_nb++)
			{
				VM::add_file(av[file_nb]);
				std::cout << av[file_nb] << ": OK" << std::endl;
			}
		}
		try
		{
			VM::execute();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	catch (std::exception& e)
	{
		if (ac > 1)
			std::cout << av[file_nb] << ": " << e.what() << std::endl;
		else
			std::cout << "stdin: " << e.what() << std::endl;
	}
	return (0);
}