#pragma once

#include "il2cpp.hpp"
#include "UnityEngine/Object.hpp"

namespace UnityEngine
{
    struct Component_Fields
    {
        Object_Fields super;
    };

    struct Component_RGCTXs
    {
    };

    struct Component_VTable
    {
        VirtualInvokeData _0_Equals;
        VirtualInvokeData _1_Finalize;
        VirtualInvokeData _2_GetHashCode;
        VirtualInvokeData _3_ToString;
    };

    struct Component_c
    {
        Il2CppClass_1 _1;
        struct Component_StaticFields* static_fields;
        Component_RGCTXs* rgctx_data;
        Il2CppClass_2 _2;
        Component_VTable vtable;
    };

    struct Component_o
    {
        Component_c *klass;
        void *monitor;
        Component_Fields fields;

        // 01f48340
        Il2CppObject* GetComponent(MethodInfo *method);
    };

    struct Component_StaticFields
    {
    };

    // 04b79950
    extern MethodInfo ** PTR_Component_RectTransform_GetComponent;
    // 04b79638
    extern MethodInfo ** PTR_Component_TextMeshProUGUI_GetComponent;
}
