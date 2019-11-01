#ifndef ABSTRACTVM_FACTORY_HPP
#define ABSTRACTVM_FACTORY_HPP

#include "../Operand/IOperand.hpp"
#include <map>
#include <string>

class Factory
{
public:
	Factory();

	Factory&			operator =(Factory const &);

	IOperand const *	createOperand(eOperandType, std::string const &) const;



	class	overflow_or_underflow_exception : public std::range_error
	{
	public:
		explicit overflow_or_underflow_exception(std::string const &);
	};



	class	overflow_exception : public std::overflow_error
	{
	public:
		explicit overflow_exception(std::string const &);
	};



	class	underflow_exception : public std::underflow_error
	{
	public:
		explicit underflow_exception(std::string const &);
	};



	class	incorrect_input_exception : public std::invalid_argument
	{
	public:
		explicit incorrect_input_exception(std::string const &);
	};



	~Factory() = default;
private:
	std::map<eOperandType, IOperand const * (Factory::*)(std::string const &) const> _funcs_map;

	IOperand const *	createInt8(std::string const &) const;
	IOperand const *	createInt16(std::string const &) const;
	IOperand const *	createInt32(std::string const &) const;
	IOperand const *	createFloat(std::string const &) const;
	IOperand const *	createDouble(std::string const &) const;

	Factory(Factory const &);
};

#endif