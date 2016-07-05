#include "rendermanager.hpp"
#include "transformation.hpp"
#include <lib/core/log.hpp>
#include "renderstates.hpp"
#include "rendernode.hpp"
#include "camera.hpp"
#include <lib/core/rendertarget.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/driver.hpp>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
//#include <SFML/Graphics/GLCheck.hpp>
#include <SFML/System/Err.hpp>
#include <cassert>
#include <iostream>

//#define glCheck(x) x
#define glCheck(x)

inline bool activate(const bool p) { return p; }

namespace lib
{
	namespace draw
	{

		namespace
		{
			// Convert a BlendMode constant to the corresponding OpenGL constant.
			inline const u32 factorToGlConstant(const BlendType blendFactor)
			{
				switch (blendFactor)
				{
				case BlendType::Zero:             return GL_ZERO;
				case BlendType::One:              return GL_ONE;
				case BlendType::SrcColor:         return GL_SRC_COLOR;
				case BlendType::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
				case BlendType::DstColor:         return GL_DST_COLOR;
				case BlendType::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
				case BlendType::SrcAlpha:         return GL_SRC_ALPHA;
				case BlendType::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
				case BlendType::DstAlpha:         return GL_DST_ALPHA;
				case BlendType::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
				default:
					LOG_ERROR("Invalid value for BlendType.");
					return GL_ZERO;
				}
			}

			// Convert an :BlendMode constant to the corresponding OpenGL constant.
			inline const GLenum primitiveToGlConstant(const PrimitiveType primitiveType)
			{
				switch (primitiveType)
				{
				case PrimitiveType::Points:             return GL_POINTS;
				case PrimitiveType::Lines:              return GL_LINES;
				case PrimitiveType::LinesStrip:         return GL_LINE_STRIP;
				case PrimitiveType::Triangles:			return GL_TRIANGLES;
				case PrimitiveType::TrianglesStrip:     return GL_TRIANGLE_STRIP;
				case PrimitiveType::TrianglesFan:		return GL_TRIANGLE_FAN;
				default:
					LOG_ERROR("Invalid value for PrimitiveType");
					return GL_POINTS;
				}
			}
		}

		RenderManager::RenderManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		RenderManager::~RenderManager()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void RenderManager::Init()
		{
			AppService::Init();
		}

		void RenderManager::startFrame(sptr<Camera> &camera)
		{

		}

		void RenderManager::finishFrame()
		{

		}

		void RenderManager::setCamera(const sptr<Camera> &camera)
		{
			m_camera = camera.get();
		}

		void RenderManager::preRenderNode(const sptr<RenderNode> &node, const RenderStates &rStates)
		{

			rStates.currentTarget->draw(node->vertexArray(), rStates);
		}

		void RenderManager::preRenderNode(const sptr<RenderNode> &node)
		{
			m_renderList.push_back(node.get());
//			rStates.currentTarget->draw(node->vertexArray(), rStates);
		}

		void RenderManager::renderAll()
		{
			for (auto renderNode : m_renderList)
			{
				renderOne(renderNode);
			}
//			service<Window>()->
//			renderTarget.get()->
//			appController()->driver()-> renderAll(m_renderList);
		}

		void popGLStates()
		{
//			if (activate(true))
//			{
				glCheck(glMatrixMode(GL_PROJECTION));
				glCheck(glPopMatrix());
				glCheck(glMatrixMode(GL_MODELVIEW));
				glCheck(glPopMatrix());
				glCheck(glMatrixMode(GL_TEXTURE));
				glCheck(glPopMatrix());
#ifndef SFML_OPENGL_ES
				glCheck(glPopClientAttrib());
				glCheck(glPopAttrib());
#endif
//			}
		}

		void applyTransform(const Transformation& transform)
		{
			transform;
			glCheck(glLoadMatrixf(transform.data()));
		}

		void RenderManager::renderOne(const RenderNode *node)
		{
			if (!node->vertexArray().size())
				return;

			applyTransform(node->globalTransformation());
//			applyCurrentView();

			auto textureId = node->texture() ? node->texture() : 0;
			textureId;
//			applyTexture(textureId);
			const char* data = reinterpret_cast<const char*>(node->vertexArray().data());
			data;
			glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex), data + 0));
			glCheck(glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), data + sizeof(GLfloat)*2/*8*/));
			glCheck(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), data + (sizeof(GLfloat) * 2) + (sizeof(GLubyte)*4) /*+12*/));

			// Draw the primitives
			glCheck(glDrawArrays(primitiveToGlConstant(node->vertexArray().getPrimitiveType()), 0, node->vertexArray().size()));
//			applyTexture(NULL);
		}
	}
}
