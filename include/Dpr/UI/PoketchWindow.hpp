#include "UnityEngine/MonoBehaviour.hpp";

namespace Dpr {
	namespace UI {
		struct PoketchWindow : UnityEngine::MonoBehaviour
		{
			static PoketchWindow get_Instance(MethodInfo *method);
		};
		
	}
}