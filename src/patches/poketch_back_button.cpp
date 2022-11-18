#include "il2cpp.hpp"
#include "il2cpp-api.h"
#include "Dpr/UI/PoketchButton.hpp"
#include "Dpr/UI/PoketchWindow.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "logger.hpp"
#include "System/Type.hpp"
#include "util.hpp"

Dpr::UI::PoketchButton *backButton = nullptr;

void goToPreviousPoketchApp(Dpr::UI::PoketchWindow *_this, MethodInfo *method) {
	Dpr::UI::PoketchWindow::get_Instance(nullptr).SelectApp(false, nullptr);
}

// Hook called when poketch next button initialized during poketch window onCreate
// Dpr.UI.PoketchWindow$$OnCreate
// bl Dpr.UI.PoketchButton$$Initialize
// 01e66b5c
void poketchNextButtonInitializeHook(Dpr::UI::PoketchButton *__this, UnityEngine::Events::UnityAction *callback, uint32_t seEventId, MethodInfo *method) {
	socket_log_fmt("Hook Called: Initialize called on poketch next button");

	// Call the original initialize method for the next button
	__this->Initialize(callback, seEventId, method);
	
	// Find the previous button (Final sibling of next button)
	UnityEngine::Transform *parentTransform = __this->get_transform(nullptr)->getParent(nullptr);
	System::Type *poketchButtonType = __this->GetType(nullptr);
	int32_t childCount = parentTransform->get_childCount(nullptr);
	UnityEngine::Transform *childTransform = parentTransform->getChild(childCount - 1, nullptr);
	backButton = (Dpr::UI::PoketchButton*) childTransform->GetComponent(poketchButtonType, nullptr);

	// Set up new unity action callback
	UnityEngine::Events::UnityAction *backButtonCallback = (UnityEngine::Events::UnityAction*) il2cpp_object_new(UnityEngine::Events::UnityAction_TypeInfo);
	// Add the callback function to the UnityAction
	backButtonCallback->ctor(nullptr, copyMethodInfo(Dpr::UI::Dpr_UI_PoketchWindow__OnCreate_b__90_0, (Il2CppMethodPointer) &goToPreviousPoketchApp));

	// Call the initialize method on the previous button
	backButton->Initialize(backButtonCallback, seEventId, nullptr);
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