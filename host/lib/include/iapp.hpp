#ifndef __LIB_IAPP_HPP__
#define __LIB_IAPP_HPP__

#include "compconfig.hpp"
#include "types.hpp"
#include "wcp.hpp"
#include <string>
#include <vector>

// TO Delete:
#include <lib/core/vecsptr.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	struct IAppDescriptor
	{
		std::string Name;
		u32 Version;
		u32 SubVersion;
		u32 Patch;
		std::string configFile;
		std::string resourceFile;
		WindowCreationParams wcp;
		inline IAppDescriptor(const std::string &n, const u32 v, const u32 s, const u32 p, const std::string &cf, const std::string &rf, const WindowCreationParams &wcp_)
			: Name(n), Version{ v }, SubVersion{ s }, Patch{ p }, configFile(cf), resourceFile(rf), wcp(wcp_) {	}

		/*
		inline IAppDescriptor(const IAppDescriptor &rh) : Name(rh.Name), Version{ rh.Version }, SubVersion{ rh.SubVersion }, Patch{ rh.Patch }, configFile{ rh.configFile },
			resourceFile{ rh.resourceFile }, wcp{ rh.wcp } {}
			*/
	};

	struct ServicesRequest
	{
		std::vector<std::string> requestedServices;
		ServicesRequest(ServicesRequest &&rh) : requestedServices( std::move(rh.requestedServices) ) {}
		ServicesRequest() {}
	};

	class IApp
	{
	public:
		IApp() {}
		virtual ~IApp() {}

		virtual const IAppDescriptor getAppDescriptor() const = 0;
		virtual ServicesRequest getServicesRequest() const = 0;
		virtual void onInit() = 0;
		virtual lib::VecSPtr<draw::Scene> scenesVector() = 0;
		virtual int loop() = 0;


	};
}

#endif
