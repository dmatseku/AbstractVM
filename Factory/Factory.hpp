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



	class	overflow_or_underflow_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};



	class	overflow_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};



	class	underflow_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};



	class	incorrect_input_exception : public std::exception
	{
	public:
		const char* what() const noexcept override;
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