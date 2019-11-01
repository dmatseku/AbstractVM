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
//===Constructors===================================================================================

	explicit File(std::istream&);
	File(File const &);

//===End Constructors===============================================================================

//===Typedefs and Usings============================================================================

	typedef void	(File::* p_operation)(command_data const &);
	typedef void	(File::* non_p_operation)();
	using			iterator = std::list<std::string>::iterator;
	using			const_iterator = std::list<std::string>::const_iterator;

//===End Typedefs and Usings========================================================================

//===Operators======================================================================================

	File&			operator =(File const &);

//===End Operators==================================================================================

//===Operations=====================================================================================

	void			execute();

//===End Operations=================================================================================

//===Destructor=====================================================================================

	~File();

//===End Destructor=================================================================================



//===Exceptions=====================================================================================

	class	invalid_command_or_parameter_exception : public std::invalid_argument
	{
	public:
		explicit invalid_command_or_parameter_exception(std::string const &);
	};

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

//===Base properties================================================================================

	std::map<std::string, void (File::*)(command_data const &)>	_parameter_funcs_map;
	std::map<std::string, void (File::*)()>						_non_parameter_funcs_map;
	std::map<std::string, eOperandType>							_types;
	std::list<command_data>										_lines_list;
	std::list<IOperand const *>									_stack;
	bool														_exit;

//===End Base properties============================================================================

//===Operations=====================================================================================

	static bool		validate_command(std::string const &, command_data &);

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