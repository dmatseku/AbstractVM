#ifndef ABSTRACTVM_FILE_HPP
#define ABSTRACTVM_FILE_HPP

#include <list>
#include <map>
#include "../Operand/IOperand.hpp"
#include <istream>
#include <iostream>

class File
{
public:
	explicit File(std::istream&);
	File(File const &);

	typedef void	(File::* operation)(std::string const &);
	File&			operator =(File const &);
	operation		operator[](std::string&);

	bool			should_exit() const;

	using			iterator = std::list<std::string>::iterator;
	using			const_iterator = std::list<std::string>::const_iterator;
	iterator		begin();
	iterator		end();
	const_iterator	begin() const;
	const_iterator	end() const;
	const_iterator	cbegin() const;
	const_iterator	cend() const;

	~File() = default;



	class	invalid_command_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};

	class	invalid_parameter_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};

	class	not_enough_operands_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};

	class	assert_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};

	class	not_ascii_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};



private:
	File();
	std::map<std::string, void (File::*)(std::string const &)>	_funcs_map;
	std::list<std::string>										_lines_list;
	std::list<IOperand const *>									_stack;
	bool														_exit;

	void			push(std::string const &);
	void			pop(std::string const &);
	void			dump(std::string const &);
	void			assert(std::string const &);
	void			add(std::string const &);
	void			sub(std::string const &);
	void			mul(std::string const &);
	void			div(std::string const &);
	void			mod(std::string const &);
	void			print(std::string const &);
	void			exit(std::string const &);
};

#endif