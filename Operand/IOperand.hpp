#ifndef ABSTRACTVM_IOPERAND_HPP
#define ABSTRACTVM_IOPERAND_HPP

#include <string>
#include "eOperandType.hpp"

class IOperand
{
public:
	virtual int					getPrecision() const = 0;
	virtual eOperandType		getType() const = 0;

	virtual IOperand const *	operator +(IOperand const &) const = 0;
	virtual IOperand const *	operator -(IOperand const &) const = 0;
	virtual IOperand const *	operator *(IOperand const &) const = 0;
	virtual IOperand const *	operator /(IOperand const &) const = 0;
	virtual IOperand const *	operator %(IOperand const &) const = 0;

	virtual std::string const &	toString() const = 0;

	virtual ~IOperand() = default;
};

#endif
