#ifndef VTX_PARAMETERS_PARSER_INCLUDE_HPP
#define VTX_PARAMETERS_PARSER_INCLUDE_HPP

#include <vector>
#include <string>

namespace vtx
{
	class Parameters
	{
	public:
		Parameters() = default;
		Parameters(const int argc, char *argv[]);
		~Parameters() = default;

		void resetParameters(const int argc, char *argv[]);
		void resetParameters(const std::vector<std::string> &parameterVector);
		void resetParameters(std::vector<std::string> &&parameterVector);
	private:
		void _resetParameters(std::vector<std::string> &&parameterVector);
		void _resetParameters(const std::vector<std::string> &parameterVector);
		std::vector<std::string> m_parameters;
	};
}

#endif
