#ifndef APPLICATION_INCLUDE_HPP
#define APPLICATION_INCLUDE_HPP

#include <vortex/include/iapplication.hpp>

class Application : public vtx::IApplication
{
public:
	constexpr Application() noexcept {}
	virtual ~Application() {}

	virtual void onStart() {}
	virtual void onFinish() {}

	virtual void onUpdate() {}
};

#endif
