#include "Object.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "System/Type.hpp"

namespace UnityEngine {
	struct Component : Object
	{
		GameObject* get_gameObject(MethodInfo *method);
		Transform* get_transform(MethodInfo *method);
		Component* GetComponent(System::Type *type, MethodInfo *method);
	};
	
}