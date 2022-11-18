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
		
	}
}