#pragma once

#include "il2cpp.hpp"
#include "Dpr/MsgWindow/MsgTextContainer.hpp"

namespace Dpr
{
    namespace MsgWindow
    {
        struct WindowMessage_Fields
        {
            UnityEngine_MonoBehaviour_Fields super;
            MsgTextContainer_o* textContainer;
            struct Dpr_Message_MessageTextLineDataModel_array* textLineDataArray;
            struct Dpr_Message_MessageTextLineDataModel_o* currentLineData;
            int32_t currentMsgEventId;
            struct WaitTimer_o* waitTimer;
            int32_t currentMsgState;
            float playLineMsgTime;
            float showMsgTime;
            float fastForwardMagnification;
            int32_t lineDataIndex;
            int32_t useTextIndex;
            int32_t currentLineStrNum;
            bool isChangeTextColor;
            bool playSpeedUpFlag;
            struct System_Action_float__o* onMsgCallBack;
            struct System_Action_o* onFinishedShowOneLine;
        };

        struct WindowMessage_RGCTXs
        {
        };

        struct WindowMessage_VTable
        {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };

        struct WindowMessage_c
        {
            Il2CppClass_1 _1;
            struct WindowMessage_StaticFields* static_fields;
            WindowMessage_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            WindowMessage_VTable vtable;
        };

        struct WindowMessage_o
        {
            WindowMessage_c *klass;
            void *monitor;
            WindowMessage_Fields fields;
        };

        struct WindowMessage_StaticFields
        {
        };
    }
}
