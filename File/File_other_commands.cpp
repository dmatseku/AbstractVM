#include "File.hpp"
#include "../Factory/Factory.hpp"

void
File::push(command_data const & info) // push the operand into the stack
{
	IOperand const *	result;

	result = Factory().createOperand(this->_types[info.type], info.parameter);
	this->_stack.push_front(result);
}

void
File::assert(command_data const & info) // compare the input operand and last operand in the stack
{
	eOperandType		operand_type = this->_types[info.type];
	std::string			str_value = info.parameter;

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()) + ")");
	}


	if (operand_type != this->_stack.front()->getType() //if the types are different

		// else if the type is integer and operands are different
		||	(operand_type < eOperandType::Float
			&& (std::stoi(str_value) != std::stoi(this->_stack.front()->toString())))
		// else if the type is floating point and operands are different
		|| (operand_type >= eOperandType::Float
			&& (std::stod(str_value) != std::stod(this->_stack.front()->toString()))))
	{
		throw assert_exception("Parameter is not equal to last operand");
	}
}

void
File::pop() // pop the last operand from the stack
{
	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()) + ")");
	}

	delete this->_stack.front();
	this->_stack.pop_front();
}

void
File::dump() // print all operands
{
	for (IOperand const * operand : this->_stack)
		std::cout << operand->toString() << std::endl;
}

void
File::print() // print the last operand as ASCII symbol if it is possible
{
	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
													+ std::to_string(this->_stack.size()) + ")");
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
File::exit() // accept the "exit" command
{
	this->_exit = true;
}
