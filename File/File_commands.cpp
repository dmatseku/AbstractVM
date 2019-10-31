#include "File.hpp"
#include "../Factory/Factory.hpp"
#include <iomanip>

void
File::push(command_data const & info)
{
	IOperand const *	result;

	result = Factory().createOperand(this->_types[info.type], info.parameter);
	this->_stack.push_front(result);
}

void
File::assert(command_data const & info)
{
	eOperandType		operand_type = this->_types[info.type];
	std::string			str_value = info.parameter;

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
													+ std::to_string(this->_stack.size()));
	}
	if (operand_type != this->_stack.front()->getType()

		||	(operand_type < eOperandType::Float
			&& (std::stoi(str_value) != std::stoi(this->_stack.front()->toString())))

		|| (operand_type >= eOperandType::Float
			&& (std::stod(str_value) != std::stod(this->_stack.front()->toString()))))
	{
		throw assert_exception("Parameter is not equal to last operand");
	}
}

void
File::pop()
{
	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
													+ std::to_string(this->_stack.size()));
	}

	delete this->_stack.front();
	this->_stack.pop_front();
}

void
File::dump()
{
	for (IOperand const * operand : this->_stack)
		std::cout << operand->toString() << std::endl;
}

void
File::add()
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()));
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
File::sub()
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()));
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
File::mul()
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()));
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
File::div()
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()));
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
File::mod()
{
	IOperand const * first_operand;
	IOperand const * second_operand;

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()));
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
File::print()
{
	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
													+ std::to_string(this->_stack.size()));
	}

	int32_t value = std::stoi(this->_stack.front()->toString());
	if (this->_stack.front()->getType() != eOperandType::Int8
			|| value < 0 || value > 127)
	{
		throw not_ascii_exception("Last operand is not ASCII symbol");
	}

	std::cout << static_cast<char>(value) << std::endl;
}

void
File::exit()
{
	this->_exit = true;
}
