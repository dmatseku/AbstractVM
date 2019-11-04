#include "File.hpp"
#include "../Factory/Factory.hpp"

void
File::add()
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	second_operand.reset(Factory().createOperand(this->_types[info.type], info.parameter));

	this->_stack.push_front(*first_operand + *second_operand);
}

void
File::sub()
{
	std::unique_ptr<IOperand const> first_operand(nullptr);
	std::unique_ptr<IOperand const> second_operand(nullptr);

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.size() < 2)
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 2, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

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

	if (this->_stack.empty())
	{
		throw not_enough_operands_exception("Not enough operands for command (need: 1, exist: "
											+ std::to_string(this->_stack.size()) + ")");
	}

	first_operand.reset(this->_stack.front());
	this->_stack.pop_front();
	second_operand.reset(Factory().createOperand(this->_types[info.type], info.parameter));

	this->_stack.push_front(*first_operand % *second_operand);
}