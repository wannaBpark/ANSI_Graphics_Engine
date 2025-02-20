#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	class Object;

	class Scene
	{
	public:
		explicit Scene();
		virtual ~Scene();

		virtual bool CreateResources();
		virtual bool Initialize();
		virtual bool OnUpdate();
		virtual bool OnRenderGui();

		bool OnDefaultUpdate();

		template<typename T>
		T* AddObject(T* object)
		{
			return static_cast<T*>(m_objects[object->GetName()] = object);
		}

		template<typename T>
		T* FindObject(const std::string& name)
		{
			if (m_objects.count(name) == 0) {
				return nullptr;
			}
			return static_cast<T*>(m_objects[name]);
		}

	private:
		std::unordered_map<std::string, Object* > m_objects;
	};
}

