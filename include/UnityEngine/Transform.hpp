#pragma once

#include "il2cpp.hpp"
#include "UnityEngine/Component.hpp"

namespace UnityEngine
{
    struct Transform_Fields
    {
	    Component_Fields super;
    };

    struct Transform_RGCTXs
    {
    };

    struct Transform_VTable
    {
        VirtualInvokeData _0_Equals;
        VirtualInvokeData _1_Finalize;
        VirtualInvokeData _2_GetHashCode;
        VirtualInvokeData _3_ToString;
        VirtualInvokeData _4_GetEnumerator;
    };

    struct Transform_c
    {
        Il2CppClass_1 _1;
        struct Transform_StaticFields* static_fields;
        Transform_RGCTXs* rgctx_data;
        Il2CppClass_2 _2;
        Transform_VTable vtable;
    };

    struct Transform_o
    {
        Transform_c *klass;
        void *monitor;
        Transform_Fields fields;
    };

    struct Transform_StaticFields
    {
    };
}
