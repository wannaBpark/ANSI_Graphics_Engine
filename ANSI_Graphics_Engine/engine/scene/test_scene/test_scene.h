#pragma once

#include "scene/ansi_scene.h"

#include "core/ansi_core.h"
#include "core/timer/ansi_timer.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

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

		Object* m_rectangle{ nullptr };

	};
}