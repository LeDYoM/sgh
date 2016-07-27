#ifndef __LIB_IAPP_HPP__
#define __LIB_IAPP_HPP__

#include "compconfig.hpp"
#include "types.hpp"
#include "iappcontext.hpp"
#include <string>
#include <vector>

// TO Delete:
#include <lib/core/vecsptr.hpp>
#include <lib/draw/scene.hpp>

namespace lib
{
	struct IAppDescriptor
	{
		str Name;
		u32 Version;
		u32 SubVersion;
		u32 Patch;
		str configFile;
		str resourceFile;
		IAppDescriptor() = default;
	};

	class IApp
	{
	public:
		IApp() {}
		virtual ~IApp() {}

		virtual const IAppDescriptor getAppDescriptor() const = 0;
		virtual void onInit() = 0;
		virtual lib::VecSPtr<draw::Scene> scenesVector() = 0;
		virtual int loop() = 0;
		PIAppContext appContext() const { return m_iappContext; }
		void setAppContext(PIAppContext appContext) { m_iappContext = appContext; }
	private:
		PIAppContext m_iappContext;
	};
}

#endif
