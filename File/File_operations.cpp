#include "File.hpp"
#include "../Factory/Factory.hpp"
#include <iomanip>
#include <regex>

//===Operations=====================================================================================

void
File::execute()
{
	for (command_data const & line : this->_lines_list)
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

		if (this->_exit)
			break;
	}

	if (!this->_exit)
		throw no_exit_exception("File has no exit(");
}

bool
File::validate_command(std::string const & str, command_data & data)
{
	std::regex non_parameter_commands("(pop|dump|add|sub|mul|div|mod|print|exit)(\\s*)");
	std::regex parameter_commands("(push|assert)(\\s+)(int8|int16|int32|float|double)"
							 "(\\()(-?\\d+\\.?\\d*f?)(\\))(\\s*)");
	std::cmatch info;
	bool res = false;

	if (str.empty())
		res = true;
	else if (std::regex_match(str.c_str(), info, non_parameter_commands))
	{
		data.command = info.str(1);
		data.type = "";
		data.parameter = "";
		res = true;
	}
	else if (std::regex_match(str.c_str(), info, parameter_commands))
	{
		data.command = info.str(1);
		data.type = info.str(3);
		data.parameter = info.str(5);
		res = true;
	}
	return (res);
}

//===End Operations=================================================================================