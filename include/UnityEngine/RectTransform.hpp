#pragma once

#include "il2cpp.hpp"
#include "UnityEngine/Transform.hpp"

namespace UnityEngine
{
    struct RectTransform_Fields
    {
	    Transform_Fields super;
    };

    struct RectTransform_RGCTXs
    {
    };

    struct RectTransform_VTable
    {
        VirtualInvokeData _0_Equals;
        VirtualInvokeData _1_Finalize;
        VirtualInvokeData _2_GetHashCode;
        VirtualInvokeData _3_ToString;
        VirtualInvokeData _4_GetEnumerator;
    };

    struct RectTransform_c
    {
        Il2CppClass_1 _1;
        struct RectTransform_StaticFields* static_fields;
        RectTransform_RGCTXs* rgctx_data;
        Il2CppClass_2 _2;
        RectTransform_VTable vtable;
    };

    struct RectTransform_o
    {
        RectTransform_c *klass;
        void *monitor;
        RectTransform_Fields fields;
    };

    struct RectTransform_StaticFields
    {
        struct RectTransform_ReapplyDrivenProperties_o* reapplyDrivenProperties;
    };
}
