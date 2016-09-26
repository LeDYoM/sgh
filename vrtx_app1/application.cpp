#include "application.hpp"

Application::Application() noexcept
{
}

Application::~Application()
{

}

void Application::onStart()
{
//	VApplication::onStart();
}

void Application::onFinish()
{
	VApplication::onFinish();
}

bool Application::onUpdate()
{
	return VApplication::onUpdate() && false;
}
