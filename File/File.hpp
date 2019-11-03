#ifndef ABSTRACTVM_FILE_HPP
#define ABSTRACTVM_FILE_HPP

#include <list>
#include <map>
#include "../Operand/IOperand.hpp"
#include <istream>
#include <iostream>
#include <regex>

class File
{
private:

//===Structures=====================================================================================

	struct	command_data
	{
		std::string		command;
		std::string		type;
		std::string		parameter;
	};

//===End Structures=================================================================================

public:
//===Constructors and Destructor====================================================================

	explicit File(std::istream&);
	File(File const &) = delete;

	~File();

//===End Constructors and Destructor================================================================

//===Typedefs and Usings============================================================================

	typedef void	(File::* p_operation)(command_data const &);
	typedef void	(File::* non_p_operation)();

//===End Typedefs and Usings========================================================================

//===Operators======================================================================================

	File&			operator =(File const &) = delete;

//===End Operators==================================================================================

//===Exceptions=====================================================================================

	class	not_enough_operands_exception : public std::length_error
	{
	public:
		explicit not_enough_operands_exception(std::string const &);
	};

	class	not_ascii_exception : public std::invalid_argument
	{
	public:
		explicit not_ascii_exception(std::string const &);
	};

	class	assert_exception : public std::invalid_argument
	{
	public:
		explicit assert_exception(std::string const &);
	};

	class	no_exit_exception : public std::runtime_error
	{
	public:
		explicit no_exit_exception(std::string const &);

	};

//===End Exceptions=================================================================================


private:

//===Constructors===================================================================================

	File();

//===End Constructors===============================================================================

//===Properties=====================================================================================

	std::map<std::string, void (File::*)(command_data const &)>	_parameter_funcs_map;
	std::map<std::string, void (File::*)()>						_non_parameter_funcs_map;
	std::map<std::string, eOperandType>							_types;
	std::list<IOperand const *>									_stack;
	bool														_exit;

//===End Properties=================================================================================

//===Operations=====================================================================================

	static bool		validate_command(std::string const &, command_data &);
	void			execute(command_data const & line, int line_nb);

	void			push(command_data const &);
	void			assert(command_data const &);

	void			pop();
	void			dump();
	void			add();
	void			sub();
	void			mul();
	void			div();
	void			mod();
	void			print();
	void			exit();

//===End Operations=================================================================================

};

#endif