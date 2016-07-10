#ifndef LIB_RENDERMANAGER_HPP__
#define LIB_RENDERMANAGER_HPP__

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include "renderstates.hpp"
#include <lib/include/properties.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class RenderTarget;
		}
	}
	namespace draw
	{
		class RenderNode;
		class Camera;
		class RenderStates;

		class RenderManager : public AppService
		{
		public:
			RenderManager();
			virtual ~RenderManager();

			static const str staticTypeName() { return "RenderManager"; }

			virtual void Init() override;

			void startFrame(sptr<drivers::render::RenderTarget> renderTarget, sptr<Camera> camera);
			void finishFrame();
			void preRenderNode(const sptr<RenderNode> &, const RenderStates&) const;
			void preRenderNode(const sptr<RenderNode> &);
		private:
			std::vector<const RenderNode*> m_renderList;
			sptr<Camera> m_camera;
			sptr<drivers::render::RenderTarget> m_renderTarget;
		};
	}
}

#endif
