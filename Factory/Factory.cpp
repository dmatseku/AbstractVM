#include "Factory.hpp"
#include <cstdint>
#include <climits>
#include "../Operand/Operand.hpp"

//===Constructors and Destructor====================================================================

Factory::Factory()
{
	this->_funcs_map[eOperandType::Int8] = &Factory::createInt8;
	this->_funcs_map[eOperandType::Int16] = &Factory::createInt16;
	this->_funcs_map[eOperandType::Int32] = &Factory::createInt32;
	this->_funcs_map[eOperandType::Float] = &Factory::createFloat;
	this->_funcs_map[eOperandType::Double] = &Factory::createDouble;
}

//===End Constructors and Destructor================================================================

//===Functions======================================================================================

IOperand const *
Factory::createInt8(std::string const & value) const
{
	int_fast32_t nb = 0;

	try
	{
		nb = std::stoi(value);
	}
	catch (std::out_of_range& e)
	{
		throw overflow_or_underflow_exception();
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception();
	}

	if (nb > CHAR_MAX)
	{
		throw overflow_exception();
	}
	else if (nb < CHAR_MIN)
	{
		throw underflow_exception();
	}

	return (new Operand<int_fast8_t>(eOperandType::Int8, static_cast<int8_t>(nb)));
}

IOperand const *
Factory::createInt16(std::string const & value) const
{
	int_fast32_t nb = 0;

	try
	{
		nb = std::stoi(value);
	}
	catch (std::out_of_range& e)
	{
		throw overflow_or_underflow_exception();
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception();
	}

	if (nb > SHRT_MAX)
	{
		throw overflow_exception();
	}
	else if (nb < SHRT_MIN)
	{
		throw underflow_exception();
	}

	return (new Operand<int_fast16_t>(eOperandType::Int16, static_cast<int_fast16_t>(nb)));
}

IOperand const *
Factory::createInt32(std::string const & value) const
{
	int_fast32_t nb = 0;

	try
	{
		nb = std::stoi(value);
	}
	catch (std::out_of_range& e)
	{
		throw overflow_or_underflow_exception();
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception();
	}

	return (new Operand<int_fast32_t>(eOperandType::Int32, nb));
}

IOperand const *
Factory::createFloat(std::string const & value) const
{
	float nb = 0;

	try
	{
		nb = std::stof(value);
	}
	catch (std::out_of_range& e)
	{
		throw overflow_or_underflow_exception();
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception();
	}

	return (new Operand<float>(eOperandType::Float, nb));
}

IOperand const *
Factory::createDouble(std::string const & value) const
{
	double nb = 0;

	try
	{
		nb = std::stod(value);
	}
	catch (std::out_of_range& e)
	{
		throw overflow_or_underflow_exception();
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception();
	}

	return (new Operand<double>(eOperandType::Double, nb));
}


IOperand const *
Factory::createOperand(eOperandType type, std::string const & value) const
{
	IOperand const * res = nullptr;
	IOperand const *(Factory::*func)(std::string const &) const;

	func = this->_funcs_map.at(type);
	res = (this->*func)(value);
	return (res);
}

//===End Functions==================================================================================

//===Operators======================================================================================

Factory&
Factory::operator =(Factory const &src)
{
	static_cast<void>(src);
	return (*this);
}

//===End Operators==================================================================================

//===Exceptions=====================================================================================

const char*	Factory::overflow_exception::what() const noexcept
{
	return ("Value is overflow");
}

const char*	Factory::underflow_exception::what() const noexcept
{
	return ("Value is underflow");
}

const char*	Factory::overflow_or_underflow_exception::what() const noexcept
{
	return ("Value is overflow or underflow");
}

const char*	Factory::incorrect_input_exception::what() const noexcept
{
	return ("Input value is incorrect");
}

//===End Exceptions=================================================================================