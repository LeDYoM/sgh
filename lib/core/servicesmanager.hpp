#ifndef LIB_SERVICESMANAGER_HPP
#define LIB_SERVICESMANAGER_HPP

#include <vector>
#include <lib/include/types.hpp>
#include "datamap.hpp"
#include <functional>
#include <typeindex>

namespace lib
{
	class AppService;

	namespace core
	{
		class AppController;
	}
	class Input;
	
	namespace draw
	{
		class RenderManager;
	}

	namespace core
	{
		namespace managers
		{
			class FileManager;
			class TextureManager;
			class FontManager;
			class ConfigurationManager;
		}
		class ServicesManager
		{
		public:
			ServicesManager(core::AppController *appController);
			virtual ~ServicesManager();

			void createServices();

			template <class T> void addService(sptr<T> newService)
			{
				addServiceInstance(std::type_index(typeid(T)), std::move(newService));
			}

			void setupAllServices();
			void initializeServices();
			void stopServices();
			void processSystemEvent(sptr<DataMap> data);

			template <class T> sptr<T> service() const
			{
				return std::dynamic_pointer_cast<T>(service(std::type_index(typeid(T))));
			}

			template<> sptr<Input> service() const { return m_input; }
			template<> sptr<draw::RenderManager> service() const { return m_renderManager; }
			template<> sptr<managers::TextureManager> service() const { return m_textureManager; }
			template<> sptr<managers::FontManager> service() const { return m_fontManager; }
			template<> sptr<managers::FileManager> service() const { return m_fileManager; }
			template<> sptr<managers::ConfigurationManager> service() const { return m_configurationManager; }

		private:
			void for_each_service(std::function<void(std::type_index, sptr<AppService>)> callback);
			void addServiceInstance(const std::type_index &typeName, sptr<AppService> newService);
			sptr<AppService> service(const std::type_index &serviceType) const;

			std::map<std::type_index, sptr<AppService>> m_services;
			core::AppController *m_appController;

			// Cached variables
			sptr<Input> m_input;
			sptr<draw::RenderManager> m_renderManager;
			sptr<managers::FileManager> m_fileManager;
			sptr<managers::TextureManager> m_textureManager;
			sptr<managers::FontManager> m_fontManager;
			sptr<managers::ConfigurationManager> m_configurationManager;
		};
	}
}
#endif
