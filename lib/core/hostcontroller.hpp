#ifndef __LIB_HOSTCONTROLLER_HPP__
#define __LIB_HOSTCONTROLLER_HPP__

#include <lib/core/vecsptr.hpp>
#include <lib/include/iapp.hpp>
#include <unordered_map>
#include <queue>
#include <string>

namespace lib
{
	namespace core
	{
		struct LoadedAppDescriptor 
		{
			str id;
			LoadedAppDescriptor(const str&_id) :id( id ) {}
			LoadedAppDescriptor(const LoadedAppDescriptor&) = default;
			LoadedAppDescriptor(LoadedAppDescriptor&&rh) :id{ std::move(rh.id) }{}
			LoadedAppDescriptor& operator=(const LoadedAppDescriptor&) = default;
			LoadedAppDescriptor& operator=(LoadedAppDescriptor&&rh) { std::swap(id, rh.id); }
		};

		struct LoadedAppDescriptorHasher
		{
			std::size_t operator()(lib::core::LoadedAppDescriptor const& s) const
			{
				return std::hash<std::string>()(s.id);
			}
		};

		class Window;
		class Driver;
		class HostTask;
		class AppController;

		class HostController
		{
		public:
			HostController(const std::vector<std::string> &params);
			virtual ~HostController();

			int initialize();
			int run();
			int finalize();

			const LoadedAppDescriptor *const loadAppFromFileName(const str&fileName);
			void removeAppFromId(const LoadedAppDescriptor*);
		private:
			void addApp(uptr<IApp> iapp);
			void addTask(sptr<HostTask> newTask);
			void removeApp(sptr<AppController> iapp);

			void processTask();
			sptr<Window> m_window{ nullptr };
			bool exit{ false };
			std::queue<sptr<HostTask>> m_pendingTasks;
			std::unordered_map<LoadedAppDescriptor, sptr<AppController>, LoadedAppDescriptorHasher> m_apps;
			sptr<Driver> m_driver{ nullptr };
		};
	}
}

#endif
