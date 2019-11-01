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
		throw overflow_or_underflow_exception("Value is overflow or underflow: " + value);
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception("Input value is incorrect: " + value);
	}

	if (nb > CHAR_MAX)
	{
		throw overflow_exception("Value is overflow: (int8)" + value);
	}
	else if (nb < CHAR_MIN)
	{
		throw underflow_exception("Value is underflow: (int8)" + value);
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
		throw overflow_or_underflow_exception("Value is overflow or underflow: " + value);
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception("Input value is incorrect: " + value);
	}

	if (nb > SHRT_MAX)
	{
		throw overflow_exception("Value is overflow: (int16)" + value);
	}
	else if (nb < SHRT_MIN)
	{
		throw underflow_exception("Value is underflow: (int16)" + value);
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
		throw overflow_or_underflow_exception("Value is overflow or underflow: " + value);
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception("Input value is incorrect: " + value);
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
		throw overflow_or_underflow_exception("Value is overflow or underflow: " + value);
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception("Input value is incorrect: " + value);
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
		throw overflow_or_underflow_exception("Value is overflow or underflow: " + value);
	}
	catch(std::invalid_argument& e)
	{
		throw incorrect_input_exception("Input value is incorrect: " + value);
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

Factory::overflow_exception::overflow_exception(std::string const & str)
: std::overflow_error(str)
{}

Factory::underflow_exception::underflow_exception(std::string const & str)
: std::underflow_error(str)
{}

Factory::overflow_or_underflow_exception::overflow_or_underflow_exception(std::string const & str)
: std::range_error(str)
{}

Factory::incorrect_input_exception::incorrect_input_exception(std::string const & str)
: std::invalid_argument(str)
{}

//===End Exceptions=================================================================================