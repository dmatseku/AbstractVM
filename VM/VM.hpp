#ifndef ABSTRACTVM_VM_HPP
#define ABSTRACTVM_VM_HPP

#include <string>
#include <map>
#include <list>

namespace VM
{
	void	add_file(std::string const &);
	void	add_file();
	void	execute();

	class	invalid_file_exception : public std::invalid_argument
	{
	public:
		explicit invalid_file_exception(std::string const &);
	};
}

#endif
