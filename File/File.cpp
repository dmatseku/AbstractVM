#include "File.hpp"
#include <iostream>
#include <string>

//===Constructors and Destructor====================================================================

File::File()
{
	this->_parameter_funcs_map["push"] = &File::push;
	this->_parameter_funcs_map["assert"] = &File::assert;

	this->_non_parameter_funcs_map["pop"] = &File::pop;
	this->_non_parameter_funcs_map["dump"] = &File::dump;
	this->_non_parameter_funcs_map["add"] = &File::add;
	this->_non_parameter_funcs_map["sub"] = &File::sub;
	this->_non_parameter_funcs_map["mul"] = &File::mul;
	this->_non_parameter_funcs_map["div"] = &File::div;
	this->_non_parameter_funcs_map["mod"] = &File::mod;
	this->_non_parameter_funcs_map["print"] = &File::print;
	this->_non_parameter_funcs_map["exit"] = &File::exit;

	this->_types["int8"] = eOperandType::Int8;
	this->_types["int16"] = eOperandType::Int16;
	this->_types["int32"] = eOperandType::Int32;
	this->_types["float"] = eOperandType::Float;
	this->_types["double"] = eOperandType::Double;

	this->_exit = false;
}

File::File(std::istream& stream): File()
{
	std::string		str;
	bool			standard_input = (&stream == &std::cin);
	command_data	data;
	int				line = 1;

	while (std::getline(stream, str) && (!standard_input || str != ";;"))
	{
		if (str.find(';') != std::string::npos)
			str.erase(str.find(';'));

		if (!File::validate_command(str, data))
			throw invalid_command_or_parameter_exception("(Line " + std::to_string(line) + ") "
					"Command or parameter is invalid: \"" + str + "\"");

		if (!str.empty())
			this->_lines_list.push_back(data);

		if (!stream.good())
			stream.clear();
		line++;
	}
}

File::~File()
{
	for (auto operand : this->_stack)
		delete operand;
}

File::File(File const & src): File()
{
	for (command_data const & line : src._lines_list)
		this->_lines_list.push_back(line);
}

//===End Constructors and Destructor================================================================

//===Operators======================================================================================

File&
File::operator =(File const & src)
{
	if (&src != this)
	{
		this->_lines_list.clear();
		for (command_data const & line : src._lines_list)
			this->_lines_list.push_back(line);
	}
	return (*this);
}

//===End Operators==================================================================================


//===Exceptions=====================================================================================


File::invalid_command_or_parameter_exception::invalid_command_or_parameter_exception
(std::string const & str): std::invalid_argument(str)
{}

File::not_enough_operands_exception::not_enough_operands_exception(std::string const & str)
: std::length_error(str)
{}

File::assert_exception::assert_exception(std::string const & str)
: std::invalid_argument(str)
{}

File::not_ascii_exception::not_ascii_exception(std::string const & str)
: std::invalid_argument(str)
{}

File::no_exit_exception::no_exit_exception(std::string const & str)
: std::runtime_error(str)
{}

//===End Exceptions=================================================================================