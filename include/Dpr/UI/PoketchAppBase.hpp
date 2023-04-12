#pragma once
#include "UnityEngine/MonoBehaviour.hpp"

namespace Dpr
{
	namespace UI
	{
		class PoketchButton;
		class PoketchButton_array;
		class PoketchWindow;

		struct PoketchAppBase_Klass
		{
			/* data */
		};
		
		struct PoketchAppBase_Fields
		{
			UnityEngine::MonoBehaviour_Fields super;
			struct PoketchButton_array* Buttons;
			int32_t _AppID_k__BackingField;
			struct PoketchWindow* _poketchInstance;
			bool isInitialized;
			struct PoketchButton* _PreButton_k__BackingField;
			int32_t _PreState_k__BackingField;
		};
		

		struct PoketchAppBase
		{
			PoketchAppBase_Klass* klass;
			void* monitor;
			PoketchAppBase_Fields fields;
		};
		
	} // namespace UI
	
} // namespace Dpr
