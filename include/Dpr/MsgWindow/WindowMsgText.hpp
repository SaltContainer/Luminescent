#pragma once

#include "il2cpp.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/RectTransform.hpp"

namespace Dpr
{
    namespace MsgWindow
    {
        struct WindowMsgText_Fields
        {
            UnityEngine_MonoBehaviour_Fields super;
            struct TMPro::TextMeshProUGUI_o* text;
            struct UnityEngine::RectTransform_o* textRect;
            struct UnityEngine::Color_o defaultColor;
        };

        struct WindowMsgText_RGCTXs
        {
        };

        struct WindowMsgText_VTable
        {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };

        struct WindowMsgText_c
        {
            Il2CppClass_1 _1;
            struct WindowMsgText_StaticFields* static_fields;
            WindowMsgText_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            WindowMsgText_VTable vtable;
        };

        struct WindowMsgText_o
        {
            WindowMsgText_c *klass;
            void *monitor;
            WindowMsgText_Fields fields;

            // 01dddf00
            void ResetColor(MethodInfo *method);
        };

        struct WindowMsgText_StaticFields
        {
        };
    }
}
