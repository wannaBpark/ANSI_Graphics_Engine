#pragma once

namespace ansi
{
	class Scene
	{
	public:
		explicit Scene();
		virtual ~Scene();

		virtual bool CreateResources();
		virtual bool Initialize();
		virtual bool OnUpdate();
		virtual bool OnRenderGui();

	};
}

