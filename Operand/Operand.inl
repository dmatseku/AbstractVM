#ifndef ABSTRACTVM_OPERAND_INL
#define ABSTRACTVM_OPERAND_INL

#include "Operand.hpp"
#include "../Factory/Factory.hpp"
#include <climits>

//===Constructors and Destructor====================================================================
template <typename Type>
inline Operand<Type>::Operand(eOperandType type, Type value):
_type(type), _data(value)
{
	this->_str_data = std::to_string(value);
}

//===End Constructors and Destructor================================================================

//===Getters========================================================================================


template <typename Type>
inline int
Operand<Type>::getPrecision() const
{
	if (this->_type < eOperandType::Float)
		return (0);

	int precision = 0;
	std::string str_value = this->_str_data;

	if (str_value.find('.') != std::string::npos)
	{
		str_value.erase(0, str_value.find('.') + 1);
		precision = str_value.length();
	}
	return (precision);
}

template <typename Type>
inline eOperandType
Operand<Type>::getType() const
{
	return (this->_type);
}

template <typename Type>
inline std::string const &
Operand<Type>::toString() const
{
	return (this->_str_data);
}

//===End Getters====================================================================================

//===Operators======================================================================================

template <typename Type>
inline IOperand const *
Operand<Type>::operator	+(IOperand const & src) const
{
	double		src_data = 0;
	std::string	res;

	if (src.getType() < eOperandType::Float)
		src_data = static_cast<double>(std::stoi(src.toString()));
	else
		src_data = std::stod(src.toString());

	res = std::to_string(this->_data + src_data);

	if (this->_type > src.getType())
		return (Factory().createOperand(this->_type, res));
	return (Factory().createOperand(src.getType(), res));
}

template <typename Type>
inline IOperand const *
Operand<Type>::operator	-(IOperand const & src) const
{
	double		src_data = 0;
	std::string	res;

	if (src.getType() < eOperandType::Float)
		src_data = static_cast<double>(std::stoi(src.toString()));
	else
		src_data = std::stod(src.toString());

	res = std::to_string(this->_data - src_data);

	if (this->_type > src.getType())
		return (Factory().createOperand(this->_type, res));
	return (Factory().createOperand(src.getType(), res));
}

template <typename Type>
inline IOperand const *
Operand<Type>::operator	*(IOperand const & src) const
{
	double		src_data = 0;
	std::string	res;

	if (src.getType() < eOperandType::Float)
		src_data = static_cast<double>(std::stoi(src.toString()));
	else
		src_data = std::stod(src.toString());

	res = std::to_string(this->_data * src_data);

	if (this->_type > src.getType())
		return (Factory().createOperand(this->_type, res));
	return (Factory().createOperand(src.getType(), res));
}

template <typename Type>
inline IOperand const *
Operand<Type>::operator	/(IOperand const & src) const
{
	double		src_data = 0;
	std::string	res;

	if (src.getType() < eOperandType::Float)
		src_data = static_cast<double>(std::stoi(src.toString()));
	else
		src_data = std::stod(src.toString());

	if (src_data == 0)
	{
		throw division_or_modulo_by_null_exception();
	}

	res = std::to_string(this->_data / src_data);

	if (this->_type > src.getType())
		return (Factory().createOperand(this->_type, res));
	return (Factory().createOperand(src.getType(), res));
}

template <typename Type>
inline IOperand const *
Operand<Type>::operator	%(IOperand const & src) const
{
	int32_t		src_data = 0;
	std::string	res;


	if (src.getType() >= eOperandType::Float)
	{
		throw invalid_operand_exception();
	}

	src_data = static_cast<int32_t>(std::stoi(src.toString()));

	if (src_data == 0)
	{
		throw division_or_modulo_by_null_exception();
	}

	res = std::to_string(static_cast<int32_t>(this->_data) % src_data);

	if (this->_type > src.getType())
		return (Factory().createOperand(this->_type, res));
	return (Factory().createOperand(src.getType(), res));
}
//===End Operators==================================================================================

//===Exceptions=====================================================================================

template <typename Type>
const char*	Operand<Type>::invalid_operand_exception::what() const noexcept
{
	return ("Invalid operand for modulo");
}

template <typename Type>
const char*	Operand<Type>::division_or_modulo_by_null_exception::what() const noexcept
{
	return ("Division or modulo by null");
}

//===End Exceptions=================================================================================

#endif