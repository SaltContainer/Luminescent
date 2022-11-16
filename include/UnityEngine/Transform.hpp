#pragma once

#include "Component.hpp"

namespace UnityEngine {
	struct Transform : Component
	{
		Transform* getChild(int32_t index, MethodInfo *method);
		Transform* getParent(MethodInfo *method);
		int32_t get_childCount(MethodInfo *method);
	};
	
}