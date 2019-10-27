#include "File.hpp"
#include <iostream>
#include <string>

//===Constructors and Destructor====================================================================

File::File()
{
	this->_funcs_map["push"] = &File::push;
	this->_funcs_map["pop"] = &File::pop;
	this->_funcs_map["dump"] = &File::dump;
	this->_funcs_map["assert"] = &File::assert;
	this->_funcs_map["add"] = &File::add;
	this->_funcs_map["sub"] = &File::sub;
	this->_funcs_map["mul"] = &File::mul;
	this->_funcs_map["div"] = &File::div;
	this->_funcs_map["mod"] = &File::mod;
	this->_funcs_map["print"] = &File::print;
	this->_funcs_map["exit"] = &File::exit;
	this->_exit = false;
}

File::File(std::istream& stream): File()
{
	std::string	str;
	bool		standard_input = (&stream == &std::cin);

	while (std::getline(stream, str) && (!standard_input || str != ";;"))
	{
		this->_lines_list.push_back(str);
		if (!stream.good())
			stream.clear();
	}
}

File::File(File const & src): File()
{
	for (std::string const & line : src)
		this->_lines_list.push_back(line);
}

//===End Constructors and Destructor================================================================

//===Getters========================================================================================

bool
File::should_exit() const
{
	return (this->_exit);
}

//===End Getters====================================================================================

//===Operators======================================================================================

File&
File::operator =(File const & src)
{
	if (&src != this)
	{
		this->_lines_list.clear();
		for (std::string const & line : src)
			this->_lines_list.push_back(line);
	}
	return (*this);
}

File::operation
File::operator[](std::string& func_name)
{
	if (this->_funcs_map.find(func_name) == this->_funcs_map.end())
	{
		throw invalid_command_exception();
	}
	return (this->_funcs_map.at(func_name));
}

//===End Operators==================================================================================

//===Iterators======================================================================================

File::iterator
File::begin()
{
	return (this->_lines_list.begin());
}

File::iterator
File::end()
{
	return (this->_lines_list.end());
}

File::const_iterator
File::begin() const
{
	return (this->_lines_list.begin());
}

File::const_iterator
File::end() const
{
	return (this->_lines_list.end());
}

File::const_iterator
File::cbegin() const
{
	return (this->_lines_list.begin());
}

File::const_iterator
File::cend() const
{
	return (this->_lines_list.end());
}

//===End Iterators==================================================================================

//===Exceptions=====================================================================================

const char*	File::invalid_command_exception::what() const noexcept
{
	return ("Invalid command");
}

const char*	File::invalid_parameter_exception::what() const noexcept
{
	return ("Invalid parameter for command");
}

const char*	File::not_enough_operands_exception::what() const noexcept
{
	return ("Not enough operands for command");
}

const char*	File::assert_exception::what() const noexcept
{
	return ("Assert command is not true");
}

const char*	File::not_ascii_exception::what() const noexcept
{
	return ("Last operand is not ascii");
}

//===End Exceptions=================================================================================