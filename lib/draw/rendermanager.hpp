#ifndef LIB_RENDERMANAGER_HPP__
#define LIB_RENDERMANAGER_HPP__

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include "renderstates.hpp"
#include <lib/include/properties.hpp>

namespace lib
{
	namespace core
	{
		class RenderTarget;
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

			void startFrame(sptr<core::RenderTarget> renderTarget, sptr<Camera> camera);
			void finishFrame();
			void preRenderNode(const sptr<RenderNode> &, const RenderStates&);
			void preRenderNode(const sptr<RenderNode> &);
			void renderAll();
			void renderOne(const RenderNode *);

		private:
			std::vector<const RenderNode*> m_renderList;
			sptr<Camera> m_camera;
			sptr<core::RenderTarget> m_renderTarget;
		};
	}
}

#endif
