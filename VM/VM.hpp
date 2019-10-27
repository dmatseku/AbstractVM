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

	class	no_exit_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};
}

#endif
