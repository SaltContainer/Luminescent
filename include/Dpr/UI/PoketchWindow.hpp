#pragma once
#include "UnityEngine/MonoBehaviour.hpp"

namespace Dpr {
	namespace UI {
		struct PoketchWindow : UnityEngine::MonoBehaviour
		{
			static PoketchWindow get_Instance(MethodInfo *method);
			void SelectApp(bool isForward, MethodInfo *method);
			bool IsInRange(PoketchButton *target, float posX, float posY, MethodInfo *method);
		};

		extern MethodInfo* Dpr_UI_PoketchWindow__OnCreate_b__90_0;
	}
}