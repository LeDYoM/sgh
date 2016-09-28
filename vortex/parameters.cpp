#include "parameters.hpp"
#include "include/logger.hpp"

namespace vtx
{
	Parameters::Parameters(int argc, char * argv[])
	{
		resetParameters(argc, argv);
	}

	void Parameters::resetParameters(const int argc, char * argv[])
	{
		std::vector<std::string> m_temp;
		LDEBUG("Parsing parameters...");
		LDEBUG("Number of parameters: "<<argc);
		for (int i(0); i < argc; ++i) {
			m_temp.emplace_back(argv[i]);
			LDEBUG("Parameter: " << argv[i]);
		}
		_resetParameters(std::move(m_temp));
	}

	void Parameters::resetParameters(const std::vector<std::string>& parameterVector)
	{
		_resetParameters(std::move(parameterVector));
	}

	void Parameters::resetParameters(std::vector<std::string>&& parameterVector)
	{
		_resetParameters(std::move(parameterVector));
	}

	void Parameters::_resetParameters(std::vector<std::string>&& parameterVector)
	{
		m_parameters = std::move(parameterVector);
	}

	void Parameters::_resetParameters(const std::vector<std::string> &parameterVector)
	{
		m_parameters = std::move(parameterVector);
	}
}
