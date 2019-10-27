#include "File.hpp"
#include "../Factory/Factory.hpp"
#include <iomanip>

void
File::push(std::string const & str)
{
	std::string			tmp;
	eOperandType		operand_type = eOperandType::Int8;
	IOperand const *	result;

	if (str.find(' ') == std::string::npos
	|| str.find('(') == std::string::npos
	|| str.find(')') == std::string::npos
	|| str.find(')') < str.length() - 1)
	{
		throw invalid_parameter_exception();
	}

	tmp = str;
	tmp.erase(0, tmp.find(' ') + 1);
	tmp.erase(tmp.find('('));
	if (tmp == "int16")
		operand_type = eOperandType::Int16;
	else if (tmp == "int32")
		operand_type = eOperandType::Int32;
	else if (tmp == "float")
		operand_type = eOperandType::Float;
	else if (tmp == "double")
		operand_type = eOperandType::Double;
	else if (tmp != "int8")
	{
		throw invalid_parameter_exception();
	}

	tmp = str;
	tmp.erase(0, tmp.find('(') + 1);
	tmp.erase(tmp.find(')'));
	result = Factory().createOperand(operand_type, tmp);
	this->_stack.push_front(result);
}

void
File::assert(std::string const & str)
{
	std::string			tmp;
	eOperandType		operand_type = eOperandType::Int8;

	if (str.find(' ') == std::string::npos
		|| str.find('(') == std::string::npos
		|| str.find(')') == std::string::npos
		|| str.find(')') < str.length() - 1)
	{
		throw invalid_parameter_exception();
	}

	tmp = str;
	tmp.erase(0, tmp.find(' ') + 1);
	tmp.erase(tmp.find('('));
	if (tmp == "int16")
		operand_type = eOperandType::Int16;
	else if (tmp == "int32")
		operand_type = eOperandType::Int32;
	else if (tmp == "float")
		operand_type = eOperandType::Float;
	else if (tmp == "double")
		operand_type = eOperandType::Double;
	else if (tmp != "int8")
	{
		throw invalid_parameter_exception();
	}

	tmp = str;
	tmp.erase(0, tmp.find('(') + 1);
	tmp.erase(tmp.find(')'));

	if (operand_type != this->_stack.front()->getType()

	|| (operand_type < eOperandType::Float
		&& (std::to_string(std::stoi(tmp)) != this->_stack.front()->toString()))

	|| (operand_type >= eOperandType::Float
		&& (std::to_string(std::stod(tmp)) != this->_stack.front()->toString())))
	{
		throw assert_exception();
	}
}

void
File::pop(std::string const & str)
{
	if (str != "pop")
	{
		throw invalid_parameter_exception();
	}

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception();
	}

	delete this->_stack.front();
	this->_stack.pop_front();
}

void
File::dump(std::string const & str)
{
	if (str != "dump")
	{
		throw invalid_parameter_exception();
	}

	for (IOperand const * operand : this->_stack)
		std::cout << operand->toString() << std::endl;
}

void
File::add(std::string const & str)
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (str != "add")
	{
		throw invalid_parameter_exception();
	}
	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception();
	}

	first_operand = this->_stack.front();
	this->_stack.pop_front();
	second_operand = this->_stack.front();
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand + *second_operand);

	delete first_operand;
	delete second_operand;
}

void
File::sub(std::string const & str)
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (str != "sub")
	{
		throw invalid_parameter_exception();
	}
	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception();
	}

	first_operand = this->_stack.front();
	this->_stack.pop_front();
	second_operand = this->_stack.front();
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand - *second_operand);

	delete first_operand;
	delete second_operand;
}

void
File::mul(std::string const & str)
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (str != "mul")
	{
		throw invalid_parameter_exception();
	}
	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception();
	}

	first_operand = this->_stack.front();
	this->_stack.pop_front();
	second_operand = this->_stack.front();
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand * *second_operand);

	delete first_operand;
	delete second_operand;
}

void
File::div(std::string const & str)
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (str != "div")
	{
		throw invalid_parameter_exception();
	}
	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception();
	}

	first_operand = this->_stack.front();
	this->_stack.pop_front();
	second_operand = this->_stack.front();
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand / *second_operand);

	delete first_operand;
	delete second_operand;
}

void
File::mod(std::string const & str)
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (str != "mod")
	{
		throw invalid_parameter_exception();
	}
	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception();
	}

	first_operand = this->_stack.front();
	this->_stack.pop_front();
	second_operand = this->_stack.front();
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand % *second_operand);

	delete first_operand;
	delete second_operand;
}

void
File::print(std::string const & str)
{
	if (str != "print")
	{
		throw invalid_parameter_exception();
	}

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception();
	}

	if (this->_stack.front()->getType() != eOperandType::Int8)
	{
		throw not_ascii_exception();
	}

	int32_t value = std::stoi(this->_stack.front()->toString());
	if (value < 0 || value > 127)
	{
		throw not_ascii_exception();
	}

	std::cout << static_cast<char>(value) << std::endl;
}

void
File::exit(std::string const & str)
{
	if (str != "exit")
	{
		throw invalid_parameter_exception();
	}

	this->_exit = true;
}
