#ifndef ABSTRACTVM_OPERAND_HPP
#define ABSTRACTVM_OPERAND_HPP

#include "IOperand.hpp"

template <typename Type>
class Operand: public IOperand
{
public:
	Operand() = delete;
	Operand(eOperandType, Type);
	Operand(Operand const &) = default;

	int					getPrecision() const override;
	eOperandType		getType() const override;

	Operand&			operator =(Operand const &) = default;
	IOperand const *	operator +(IOperand const &) const override;
	IOperand const *	operator -(IOperand const &) const override;
	IOperand const *	operator *(IOperand const &) const override;
	IOperand const *	operator /(IOperand const &) const override;
	IOperand const *	operator %(IOperand const &) const override;

	std::string const &	toString() const override;



	class	invalid_operand_exception : public std::invalid_argument
	{
	public:
		explicit invalid_operand_exception(std::string const &);
	};



	~Operand() final = default;

private:
	eOperandType	_type;
	std::string		_str_data;
	Type const		_data;
};

#include "Operand.inl"

#endif