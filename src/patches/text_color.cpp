#include "il2cpp.hpp"
#include "Dpr/Message/FontManager.hpp"
#include "Dpr/MsgWindow/MsgTextContainer.hpp"
#include "Dpr/MsgWindow/WindowMessage.hpp"
#include "Dpr/MsgWindow/WindowMsgText.hpp"
#include "SmartPoint/AssetAssistant/SingletonMonoBehavior.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Component.hpp"
#include "UnityEngine/RectTransform.hpp"

#include "util.hpp"

void WindowMsgText_Initialize(Dpr::MsgWindow::WindowMsgText_o *__this, MethodInfo *method)
{
    system_load_typeinfo((void *)0xab43);
    
    UnityEngine::RectTransform_o *rectTransform = (UnityEngine::RectTransform_o *)
        ((UnityEngine::Component_o *)__this)->GetComponent(*UnityEngine::PTR_Component_RectTransform_GetComponent);
    __this->fields.textRect = rectTransform;

    TMPro::TextMeshProUGUI_o *textMesh = (TMPro::TextMeshProUGUI_o *)
        ((UnityEngine::Component_o *)__this)->GetComponent(*UnityEngine::PTR_Component_TextMeshProUGUI_GetComponent);
    
    TMPro::TextMeshProUGUI_o **textMeshPtr = &__this->fields.text;
    *textMeshPtr = textMesh;

    // New regular text color (scale from 0-1)
    __this->fields.defaultColor.fields.r = 1;
    __this->fields.defaultColor.fields.g = 1;
    __this->fields.defaultColor.fields.b = 1;
    __this->fields.defaultColor.fields.a = 1;

    Dpr::Message::FontManager_o * fontManager = (Dpr::Message::FontManager_o *)
        SmartPoint::AssetAssistant::SingletonMonoBehaviour::get_Instance
            (*SmartPoint::AssetAssistant::PTR_SingletonMonoBehaviour_FontManager_get_Instance);
    fontManager->ChangeFontMaterial(*textMeshPtr, 0, nullptr);

    __this->ResetColor(nullptr);
}
