#pragma once

#include "common/ansi_common.h"

namespace ansi
{
	using namespace std;
	class Component;
	class Transform;

	class Object
	{
	public:
		explicit Object(const std::string& name);
		virtual ~Object();

		virtual bool OnUpdate();

		bool OnDefaultUpdate();

		template <typename T, typename ... Args>
		T* AddComponent(Args ... args)
		{
			return static_cast<T*>(m_components[typeid(T)] = new T(this, args ...));
		}

		template <typename T>
		T* FindComponent()
		{
			if (m_components.count(typeid(T)) == 0) { return nullptr; }
			return static_cast<T*>(m_components[typeid(T)]);
		}

		template <typename T>
		T* AddChild(T* object)
		{
			object->m_parent = this;
			return static_cast<T*>(m_children[object->GetName()] = object);
		}

		template <typename T>
		T* FindChild(const string& name)
		{
			if (m_children.count(name) == 0) { return nullptr; }
			return static_cast<T*>(m_children[name]);
		}

		void SetIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }
		void SetIsDeleted(bool isDeleted) { m_isDeleted = isDeleted; }

		bool GetIsEnabled() const { return m_isEnabled; }
		bool GetIsDeleted() const { return m_isDeleted; }
		const string& GetName() const { return m_name; }
		const unordered_map<string, Object*>& GetChildren() const { return m_children; }
		const unordered_map<type_index, Component*>& GetComponents() const { return m_components; }
		Object* GetParent() const { return m_parent; }
		Transform* GetTransform() const { return m_transform; }

	private:
		bool m_isEnabled;
		bool m_isDeleted;
		string m_name;
		unordered_map<string, Object*> m_children;
		unordered_map<type_index, Component*> m_components;
		Object* m_parent;
		Transform* m_transform;
	};

}

