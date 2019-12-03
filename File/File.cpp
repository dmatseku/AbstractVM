#include "File.hpp"
#include <iostream>
#include <string>

//===Constructors and Destructor====================================================================

File::File()
{
	// initialization of a map that contains functions that take parameters
	this->_parameter_funcs_map["push"] = &File::push;
	this->_parameter_funcs_map["assert"] = &File::assert;
	this->_parameter_funcs_map["add"] = &File::add;
	this->_parameter_funcs_map["sub"] = &File::sub;
	this->_parameter_funcs_map["mul"] = &File::mul;
	this->_parameter_funcs_map["div"] = &File::div;
	this->_parameter_funcs_map["mod"] = &File::mod;


	// initialization of a map that contains functions that don't take parameters
	this->_non_parameter_funcs_map["pop"] = &File::pop;
	this->_non_parameter_funcs_map["dump"] = &File::dump;
	this->_non_parameter_funcs_map["add"] = &File::add;
	this->_non_parameter_funcs_map["sub"] = &File::sub;
	this->_non_parameter_funcs_map["mul"] = &File::mul;
	this->_non_parameter_funcs_map["div"] = &File::div;
	this->_non_parameter_funcs_map["mod"] = &File::mod;
	this->_non_parameter_funcs_map["print"] = &File::print;
	this->_non_parameter_funcs_map["exit"] = &File::exit;

	// initialization of a map that contains operand types
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
	int				line_nb = 1;

	//reading from stream
	while (std::getline(stream, str) && (!standard_input || str != ";;"))
	{
		if (!this->_exit) //after the "exit" command, next commands are ignored
		{
			//erase comments
			if (str.find(';') != std::string::npos)
				str.erase(str.find(';'));

			//validate and execute command
			// it's a maybe correct command, empty line or incorrect command.
			// if a command is correct and it's not empty, then execute it.
			// else if a line is empty, then, ignore it.
			// else it is incorrect command.
			if (File::validate_command(str, data) && !str.empty())
				execute(data, line_nb);
			else if (!str.empty())
				std::cout << "(Line " + std::to_string(line_nb) + ") "
					  "Invalid command or parameter: \"" + str + "\"" << std::endl;
		}

		if (!stream.good())
			stream.clear();
		line_nb++;
	}

	//if the file did not receive the "end" command, then it's error
	if (!this->_exit)
		throw no_exit_exception("File has no exit(");
}

File::~File()
{
	for (auto operand : this->_stack)
		delete operand;
}

//===End Constructors and Destructor================================================================

//===Exceptions=====================================================================================

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