#pragma once

#include "il2cpp.hpp"
#include "UnityEngine/Color.hpp"

namespace Dpr
{
    namespace MsgWindow
    {
        struct MsgTextContainer_Fields
        {
            UnityEngine_MonoBehaviour_Fields super;
            struct UnityEngine_RectTransform_o* contentRect;
            struct WindowMsgText_array* uiTextArray;
            struct WindowMsgText_o* sizeTagText;
            struct TMPro_TMP_FontAsset_o* emptyFont;
            struct WaitTimer_o* msgTimer;
            struct UnityEngine_Vector2_o startPosition;
            float textHight;
            float scrollTextDuration;
            float textLinePaddingOffset;
            int32_t topTextObjIndex;
            int32_t defaultTextNum;
        };

        struct MsgTextContainer_RGCTXs
        {
        };

        struct MsgTextContainer_VTable
        {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };

        struct MsgTextContainer_c
        {
            Il2CppClass_1 _1;
            struct MsgTextContainer_StaticFields* static_fields;
            MsgTextContainer_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            MsgTextContainer_VTable vtable;
        };

        struct MsgTextContainer_o
        {
            MsgTextContainer_c *klass;
            void *monitor;
            MsgTextContainer_Fields fields;

            // 01fac3d0
            void SetTextColor(UnityEngine::Color_o newColor, MethodInfo *method);

            // 01fac020
            void ResetTextColor(MethodInfo *method);
        };

        struct MsgTextContainer_StaticFields
        {
        };
    }
}
