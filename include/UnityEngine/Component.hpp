#pragma once
#include "Object.hpp"
#include "System/Type.hpp"

namespace UnityEngine {
	class GameObject;
	class Transform;

	struct Component_Fields {
		Object_Fields super;
	};

	struct Component : Object
	{
		GameObject* get_gameObject(MethodInfo *method);
		Transform* get_transform(MethodInfo *method);
		Component* GetComponent(System::Type *type, MethodInfo *method);
	};
	
}