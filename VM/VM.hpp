#ifndef ABSTRACTVM_VM_HPP
#define ABSTRACTVM_VM_HPP

#include <string>
#include <map>
#include <list>

namespace VM
{
	void	read_file(char**, int);

	class	invalid_file_exception : public std::invalid_argument
	{
	public:
		explicit invalid_file_exception(std::string const &);
	};
}

#endif
