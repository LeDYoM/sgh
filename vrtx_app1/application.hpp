#ifndef APPLICATION_INCLUDE_HPP
#define APPLICATION_INCLUDE_HPP

#include <vortex/include/vapplication.hpp>

class Application : public vtx::VApplication
{
public:
	Application() noexcept;
	virtual ~Application();

	virtual void onStart() override;
	virtual void onFinish() override;

	virtual bool onUpdate() override;
};

#endif
