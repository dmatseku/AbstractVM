/* Operands can be: int8, int16, int32, float and double.                       */
/*                                                                              */
/* Types have a hierarchy: int8 < int16 < int32 < float < double.               */
/*                                                                              */
/* If the operation is executed on operands of different types,                 */
/* the result should be of a larger type.                                       */
/*                                                                              */
/* Two types of operations are implemented: between two operands from the stack */
/* and between the operand from the stack and the input operand.                */
#include "File.hpp"
#include "../Factory/Factory.hpp"

void
File::check_operands_count(size_t need)
{
	if (this->_stack.size() < need)
	{
		throw not_enough_operands_exception("Not enough operands for command "
			"(need: " + std::to_string(need) +
			", exist: " + std::to_string(this->_stack.size()) + ")");
	}
}

void
File::add()
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(2);

	// get operands and pop they from the stack
	second_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand + *second_operand);
}

void
File::add(command_data const & info)
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(1);

	// get one operand and pop it from the stack
	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	// create the input operand
	second_operand.reset(Factory().createOperand(this->_types[info.type], info.parameter));

	this->_stack.push_front(*first_operand + *second_operand);
}

void
File::sub()
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(2);

	second_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand - *second_operand);
}

void
File::sub(command_data const & info)
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(1);

	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	second_operand.reset(Factory().createOperand(this->_types[info.type], info.parameter));

	this->_stack.push_front(*first_operand - *second_operand);
}

void
File::mul()
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(2);

	second_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand * *second_operand);
}

void
File::mul(command_data const & info)
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(1);

	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	second_operand.reset(Factory().createOperand(this->_types[info.type], info.parameter));

	this->_stack.push_front(*first_operand * *second_operand);
}

void
File::div()
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(2);

	second_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand / *second_operand);
}

void
File::div(command_data const & info)
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(1);

	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	second_operand.reset(Factory().createOperand(this->_types[info.type], info.parameter));

	this->_stack.push_front(*first_operand / *second_operand);
}

void
File::mod()
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(2);

	second_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();

	this->_stack.push_front(*first_operand % *second_operand);
}

void
File::mod(command_data const & info)
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	check_operands_count(1);

	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	second_operand.reset(Factory().createOperand(this->_types[info.type], info.parameter));

	this->_stack.push_front(*first_operand % *second_operand);
}