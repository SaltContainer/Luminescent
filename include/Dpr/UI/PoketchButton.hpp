#pragma once
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Events/UnityAction.hpp"

namespace Dpr {
	namespace UI {
		struct PoketchButton : UnityEngine::MonoBehaviour
		{
			void Initialize(UnityEngine::Events::UnityAction *callback, uint32_t seEventId, MethodInfo *method);
			void OnPush(MethodInfo *method);
		};
		
		struct PoketchButton_array
		{
			Il2CppObject obj;
			Il2CppArrayBounds *bounds;
			il2cpp_array_size_t max_length;
			PoketchButton* m_Items[65535];
		};
		
	}
}