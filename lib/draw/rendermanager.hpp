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
		class RenderStates;

		class RenderManager : public AppService
		{
		public:
			RenderManager();
			virtual ~RenderManager();

			static const str staticTypeName() { return "RenderManager"; }

			NotifableProperty<sptr<core::RenderTarget>> renderTarget;

			virtual void Init() override;

			void startFrame();
			void finishFrame();
			void preRenderNode(const sptr<RenderNode> &, const RenderStates&);
			void preRenderNode(const sptr<RenderNode> &);
			void renderAll();
			void renderOne(const RenderNode *);

		private:
			std::vector<const RenderNode*> m_renderList;
		};
	}
}

#endif
