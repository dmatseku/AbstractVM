#include "File.hpp"
#include "../Factory/Factory.hpp"
#include <iomanip>
#include <regex>

//===Operations=====================================================================================

void
File::execute(command_data const & line, int line_nb)
{
	try
	{
		if (line.parameter.empty())
		{
			non_p_operation operation = this->_non_parameter_funcs_map[line.command];
			(this->*operation)();
		}
		else
		{
			p_operation operation = this->_parameter_funcs_map[line.command];
			(this->*operation)(line);
		}
	}
	catch (std::exception& e)
	{
		std::cout << "(Line " + std::to_string(line_nb) + ") " + e.what() << std::endl;
	}
}

bool
File::validate_command(std::string const & str, command_data & data)
{
	std::regex non_parameter_commands("(\\s*)(pop|dump|add|sub|mul|div|mod|print|exit)(\\s*)");
	std::regex parameter_commands(
			"(\\s*)(push|assert|add|sub|mul|div|mod)(\\s+)(int8|int16|int32|float|double)"
							 "(\\()(-?\\d+\\.?\\d*f?)(\\))(\\s*)");
	std::cmatch info;
	bool res = false;

	if (str.empty())
		res = true;
	else if (std::regex_match(str.c_str(), info, non_parameter_commands))
	{
		data.command = info.str(COMMAND_POS);
		data.type = "";
		data.parameter = "";
		res = true;
	}
	else if (std::regex_match(str.c_str(), info, parameter_commands))
	{
		data.command = info.str(COMMAND_POS);
		data.type = info.str(TYPE_POS);
		data.parameter = info.str(ARG_POS);
		res = true;
	}
	return (res);
}

//===End Operations=================================================================================