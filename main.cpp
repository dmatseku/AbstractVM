#include <iostream>
#include "VM/VM.hpp"

int main(int ac, char** av)
{
	try
	{
		VM::read_file(av + 1, ac - 1);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}