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

	class Scene_A : public Scene
	{
	public:
		virtual bool Initialize() override;
		virtual bool OnUpdate() override;
		virtual bool OnRenderGui() override;
	};

	class Scene_B : public Scene
	{
	public:
		virtual bool Initialize() override;
		virtual bool OnUpdate() override;
		virtual bool OnRenderGui() override;
	};
}

