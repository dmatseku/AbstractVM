#include <iostream>
#include "VM/VM.hpp"

int main(int ac, char** av)
{
	try
	{
		if (ac == 1)
			VM::add_file();
		else
		{
			for (int nb = 1; nb < ac; nb++)
				VM::add_file(av[nb]);
		}
		VM::execute();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}