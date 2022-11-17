#include "il2cpp.hpp"
#include "il2cpp-api.h"
#include "Dpr/UI/PoketchButton.hpp"
#include "Dpr/UI/PoketchWindow.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "logger.hpp"
#include "System/Type.hpp"

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
	Dpr::UI::PoketchButton *backButton = (Dpr::UI::PoketchButton*) parentTransform->getChild(parentTransform->get_childCount(nullptr) - 1, nullptr)->GetComponent(System::Type::GetType(System::String::CreateString("Dpr.UI.PoketchButton, Assembly-CSharp, Version=1.6.28.12450, Culture=neutral, PublicKeyToken=null"), nullptr), nullptr);

	// Set up new unity action callback
	UnityEngine::Events::UnityAction *backButtonCallback = (UnityEngine::Events::UnityAction*) il2cpp_object_new(UnityEngine::Events::UnityAction_TypeInfo);
	// Add the callback function to the UnityAction
	backButtonCallback->fields.super.super.m_target = nullptr;
	backButtonCallback->fields.super.super.method_ptr = (intptr_t)&*goToPreviousPoketchApp;
	backButtonCallback->fields.super.super.method = (intptr_t)*goToPreviousPoketchApp;

	// Call the initialize method on the previous button
	backButton->Initialize(backButtonCallback, seEventId, nullptr);
}

void goToPreviousPoketchApp(MethodInfo *method) {
	Dpr::UI::PoketchWindow::get_Instance(nullptr).SelectApp(false, nullptr);
}