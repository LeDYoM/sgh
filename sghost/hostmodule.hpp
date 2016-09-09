#ifndef HOSTMODULE_HPP
#define HOSTMODULE_HPP

#include <moduler/include/imoduleexport.hpp>

class HostModule : public virtual moduler::IModule
{
public:
	HostModule() {}
	virtual ~HostModule() {}

	virtual moduler::ModuleInformation *const moduleInformation() const override;
	virtual bool start() override;
	virtual bool stop() override;

};

DECLARE_MODULE_CREATION

#endif
