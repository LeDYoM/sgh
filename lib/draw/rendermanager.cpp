#include "rendermanager.hpp"
#include <lib/core/log.hpp>
#include "renderstates.hpp"
#include "rendernode.hpp"
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

#define glCheck(x) x
inline bool activate(const bool p) { return p; }

namespace lib
{
	namespace draw
	{

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

		void RenderManager::startFrame()
		{

		}

		void RenderManager::finishFrame()
		{

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

			}
//			service<Window>()->
//			renderTarget.get()->
//			appController()->driver()-> renderAll(m_renderList);
		}

		void RenderManager::renderOne(const RenderNode *node)
		{

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
		void RenderManager::renderOne(const RenderNode *node)
		{
			// Nothing to draw?
			if (!node->vertexArray().getVertexCount())
				return;

			if (true)//renderTarget->activate(true))
			{
				// First set the persistent OpenGL states if it's the very first call
//				if (!m_cache.glStatesSet)
//					resetGLStates();

				// Check if the vertex count is low enough so that we can pre-transform them
				/*
				bool useVertexCache = (vertexCount <= StatesCache::VertexCacheSize);
				if (useVertexCache)
				{
					// Pre-transform the vertices and store them into the vertex cache
					for (std::size_t i = 0; i < vertexCount; ++i)
					{
						Vertex& vertex = m_cache.vertexCache[i];
						vertex.position = states.transform * vertices[i].position;
						vertex.color = vertices[i].color;
						vertex.texCoords = vertices[i].texCoords;
					}

					// Since vertices are transformed, we must use an identity transform to render them
					if (!m_cache.useVertexCache)
						applyTransform(Transform::Identity);
				}
				else
				{*/
					applyTransform(states.transform);
//				}

				// Apply the view
//				if (m_cache.viewChanged)
					applyCurrentView();

				// Apply the blend mode
				if (states.blendMode != m_cache.lastBlendMode)
					applyBlendMode(states.blendMode);

				// Apply the texture
				Uint64 textureId = states.texture ? states.texture->m_cacheId : 0;
				if (textureId != m_cache.lastTextureId)
					applyTexture(states.texture);

				// Apply the shader
				if (states.shader)
					applyShader(states.shader);

				// If we pre-transform the vertices, we must use our internal vertex cache
				if (useVertexCache)
				{
					// ... and if we already used it previously, we don't need to set the pointers again
					if (!m_cache.useVertexCache)
						vertices = m_cache.vertexCache;
					else
						vertices = NULL;
				}

				// Setup the pointers to the vertices' components
				if (vertices)
				{
					const char* data = reinterpret_cast<const char*>(vertices);
					glCheck(glVertexPointer(2, GL_FLOAT, sizeof(Vertex), data + 0));
					glCheck(glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), data + 8));
					glCheck(glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), data + 12));
				}

				// Find the OpenGL primitive type
				static const GLenum modes[] = { GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES,
					GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS };
				GLenum mode = modes[type];

				// Draw the primitives
				glCheck(glDrawArrays(mode, 0, vertexCount));

				// Unbind the shader, if any
				if (states.shader)
					applyShader(NULL);

				// If the texture we used to draw belonged to a RenderTexture, then forcibly unbind that texture.
				// This prevents a bug where some drivers do not clear RenderTextures properly.
				if (states.texture && states.texture->m_fboAttachment)
					applyTexture(NULL);

				// Update the cache
				m_cache.useVertexCache = useVertexCache;
			}
		}
		*/
	}
}
