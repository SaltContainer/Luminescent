#include "il2cpp.hpp"
#include "il2cpp-api.h"
#include "Dpr/UI/PoketchAppBase.hpp"
#include "Dpr/UI/PoketchButton.hpp"
#include "Dpr/UI/PoketchWindow.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "logger.hpp"
#include "System/Type.hpp"
#include "util.hpp"

UnityEngine::Events::UnityAction *backButtonAction = nullptr;
Dpr::UI::PoketchButton *backButton = nullptr;
Dpr::UI::PoketchButton *changeButton = nullptr;
int count = 0;

// Function called when back button is pressed
void goToPreviousPoketchApp(Dpr::UI::PoketchWindow *__this, MethodInfo *method) {
	socket_log_fmt("Hook Called: Poketch Back Button Pressed");

	// Call SelectApp with isForward set to false
	__this->SelectApp(false, nullptr);
}

// Hook called when poketch next button Unity Action created during poketch window onCreate
// Dpr.UI.PoketchWindow$$OnCreate
// bl UnityEngine.Events.UnityAction$$.ctor
// 01e66b4c
void poketchNextButtonUnityActionConstructorHook(UnityEngine::Events::UnityAction *__this, Il2CppObject *target, MethodInfo *method) {
	socket_log_fmt("Hook Called: Unity Action Constructor called on Poketch Next Button");

	// Set up the original Unity Action
	__this->ctor(target, method);

	// Use the current methodinfo to create our new methodinfo
	MethodInfo *backButtonMethodInfo = copyMethodInfo(method, (Il2CppMethodPointer) &goToPreviousPoketchApp);

	// Create a new Unity Object
	backButtonAction = (UnityEngine::Events::UnityAction*) il2cpp_object_new(UnityEngine::Events::UnityAction_TypeInfo);

	// Set up the new Unity Action
	backButtonAction->ctor(target, backButtonMethodInfo);
}


// Hook called when poketch next button initialized during poketch window onCreate
// Dpr.UI.PoketchWindow$$OnCreate
// bl Dpr.UI.PoketchButton$$Initialize
// 01e66b5c
void poketchNextButtonInitializeHook(Dpr::UI::PoketchButton *__this, UnityEngine::Events::UnityAction *callback, uint32_t seEventId, MethodInfo *method) {
	socket_log_fmt("Hook Called: Initialize called on poketch next button");

	// Call the original initialize method for the next button
	__this->Initialize(callback, seEventId, method);
	changeButton = __this;
	
	// Find the back button (Final sibling of next button)
	UnityEngine::Transform *parentTransform = __this->get_transform(nullptr)->getParent(nullptr);
	System::Type *poketchButtonType = __this->GetType(nullptr);
	int32_t childCount = parentTransform->get_childCount(nullptr);
	UnityEngine::Transform *childTransform = parentTransform->getChild(childCount - 1, nullptr);
	backButton = (Dpr::UI::PoketchButton*) childTransform->GetComponent(poketchButtonType, nullptr);

	// Call the initialize method on the previous button
	backButton->Initialize(backButtonAction, seEventId, nullptr);
}

// Hook into IsInRange check of Poketch Next Button
// Dpr.UI.PoketchWindow$$OnUpdate
// bl Dpr.UI.PoketchWindow$$IsInRange
// 01e67a3c
bool poketchCheckIfPressButton(Dpr::UI::PoketchWindow *__this, Dpr::UI::PoketchButton *target, float posX, float posY, MethodInfo *method) {
	socket_log_fmt("Hook Called: IsInRange called on Poketch Next Button");

	// Check if we are in range of the next button
	// If so process as normal
	bool isInRangeNextButton = __this->IsInRange(target, posX, posY, method);
	if (isInRangeNextButton)
	{
		return true;
	}

	// Check if we are in range of the back button
	// If so, process back buttons on push function
	bool isInRangeBackButton = __this->IsInRange(backButton, posX, posY, method);
	if (isInRangeBackButton)
	{
		backButton->OnPush(nullptr);
	}

	// return as normal
	return false;
}

void poketchButtonCheckLoopSetCount() {
	// set our count to 0
	count = 0;
	// set the original variable to 0
	__asm("mov x27,xzr");
}

void poketchButtonCheckLoopAddCountOne() {
	// increment our count
	count++;
	// increment the original variable
	__asm("add x27,x27,#0x1");
}

// bl poketchButtonCheckIfFinal
// 01e67cc0:
Dpr::UI::PoketchButton** poketchButtonCheckIfFinal(Dpr::UI::PoketchAppBase *app) {
	// Get the number of buttons from the currently selected app
	long numberOfButtons = app->fields.Buttons->max_length;
	if (count == numberOfButtons)
	{
		// set forward button
		return &changeButton;
	} else if (count > numberOfButtons) {
		// set the back button
		return &backButton;
	} else {
		// Return null to check app buttons
		return nullptr;
	}
}