#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "System/String.hpp"

struct System_Func_string__SoftwareKeyboard_ErrorState__ValueTuple_bool__string___o
{
    // 0x02ab3f30
    void ctor(void * __this, MethodInfo * delegate, MethodInfo * method);
};

struct UnityEngine_Events_UnityAction_bool__string__o
{
    // 0x02850f20
    void ctor(void * __this, MethodInfo * delegate, MethodInfo * method);
};

using OnInputCheckFunc_t = System_Func_string__SoftwareKeyboard_ErrorState__ValueTuple_bool__string___o;
using OnCompleteAction_t = UnityEngine_Events_UnityAction_bool__string__o;

// 0x04b78330
extern void ** PTR_OnInputCheckFunc_TypeInfo;
// 0x04b78348
extern void ** PTR_OnCompleteAction_TypeInfo;
// 04b78338
extern MethodInfo ** PTR_OnInputCheckFunc_MethodInfo;
// 04b78340
extern MethodInfo ** PTR_OnInputCheckFuncCtor_MethodInfo;
// 04b9c4b0
extern MethodInfo ** PTR_OnCompleteAction_MethodInfo;
// 04b78358
extern MethodInfo ** PTR_OnCompleteActionCtor_MethodInfo;

namespace Dpr
{
    namespace UI 
    {
        struct SoftwareKeyboard_Param_Fields
        {
            int32_t preset;
            int32_t keyboardMode;
            bool isPredictionEnabled;
            int32_t invalidCharFlag;
            int32_t initialCursorPos;
            int32_t textMaxLength;
            int32_t textMinLength;
            int32_t passwordMode;
            int32_t inputFormMode;
            bool isUseNewLine;
            bool isUseBlurBackground;
            struct System::Array<int32_t>* separateTextPos;
            System::String* text;
            System::String* guideText;
            System::String* headerText;
            System::String* subText;
            System::String* okText;
            int32_t disableErrorChecks;
        };

        struct SoftwareKeyboard_Param_RGCTXs
        {
        };

        struct SoftwareKeyboard_Param_VTable
        {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };

        struct SoftwareKeyboard_Param_c
        {
            Il2CppClass_1 _1;
            struct SoftwareKeyboard_Param_StaticFields* static_fields;
            SoftwareKeyboard_Param_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            SoftwareKeyboard_Param_VTable vtable;
        };

        struct SoftwareKeyboard_Param_o
        {
            SoftwareKeyboard_Param_c *klass;
            void *monitor;
            SoftwareKeyboard_Param_Fields fields;

            // 0184abe0
            void ctor(MethodInfo *method);
        };

        struct SoftwareKeyboard_Param_StaticFields
        {
        };

        struct SoftwareKeyboard_Fields
        {
        };

        struct SoftwareKeyboard_RGCTXs
        {
        };

        struct SoftwareKeyboard_VTable
        {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };

        struct SoftwareKeyboard_c
        {
            Il2CppClass_1 _1;
            struct SoftwareKeyboard_StaticFields* static_fields;
            SoftwareKeyboard_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            SoftwareKeyboard_VTable vtable;
        };

        struct SoftwareKeyboard_o
        {
            SoftwareKeyboard_c *klass;
            void *monitor;
            SoftwareKeyboard_Fields fields;

            // 018485e0
            static System::String * GetMessageText(System::String *messageLabel, MethodInfo *method);
            // 
            static int32_t LanguageMaxLength(int32_t maxLength,int32_t langId, MethodInfo *method);
            // 
            static bool Open(SoftwareKeyboard_Param_o *param, OnInputCheckFunc_t *onInputCheck, OnCompleteAction_t *onComplete, MethodInfo *method);
        };

        struct SoftwareKeyboard_StaticFields
        {
            // TODO: Add Static Fields
        };

        // 04c5ee00
        extern void * SoftwareKeyboard_Param_TypeInfo;
    }
}
