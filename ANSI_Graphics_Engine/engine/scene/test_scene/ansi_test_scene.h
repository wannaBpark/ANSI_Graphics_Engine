#pragma once

#include "scene/ansi_scene.h"

namespace ansi
{
	class TestScene: public Scene
	{
	public:
		explicit TestScene();
		virtual ~TestScene();

		virtual bool CreateResources();
		virtual bool Initialize();
		virtual bool OnUpdate();
		virtual bool OnRenderGui();

	private:
		unsigned m_shaderId;
		unsigned m_vertexBufferId;
		unsigned m_indexBufferId;
		unsigned m_vertexArrayId;

	};
}