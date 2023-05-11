#pragma once

#include "il2cpp.hpp"

#include "System/Array.hpp"
#include "UnityEngine/Color.hpp"

struct UnityEngine_MaterialPropertyBlock_o;

struct ColorVariation_Property_MaskColor_Fields
{
	int32_t materialIndex;
	int32_t channel;
	struct UnityEngine::Color_o color;
};

struct ColorVariation_Property_MaskColor_RGCTXs
{
};

struct ColorVariation_Property_MaskColor_VTable
{
	VirtualInvokeData _0_Equals;
	VirtualInvokeData _1_Finalize;
	VirtualInvokeData _2_GetHashCode;
	VirtualInvokeData _3_ToString;
};

struct ColorVariation_Property_MaskColor_c
{
	Il2CppClass_1 _1;
	struct ColorVariation_Property_MaskColor_StaticFields* static_fields;
	ColorVariation_Property_MaskColor_RGCTXs* rgctx_data;
	Il2CppClass_2 _2;
	ColorVariation_Property_MaskColor_VTable vtable;
};

struct ColorVariation_Property_MaskColor_o
{
	ColorVariation_Property_MaskColor_Fields fields;
};

struct ColorVariation_Property_MaskColor_StaticFields
{
};

struct ColorVariation_Property_Fields
{
	struct UnityEngine_Renderer_o* renderer;
	System::Array<ColorVariation_Property_MaskColor_o>* colors;
};

struct ColorVariation_Property_RGCTXs
{
};

struct ColorVariation_Property_VTable
{
	VirtualInvokeData _0_Equals;
	VirtualInvokeData _1_Finalize;
	VirtualInvokeData _2_GetHashCode;
	VirtualInvokeData _3_ToString;
};

struct ColorVariation_Property_c
{
	Il2CppClass_1 _1;
	struct ColorVariation_Property_StaticFields* static_fields;
	ColorVariation_Property_RGCTXs* rgctx_data;
	Il2CppClass_2 _2;
	ColorVariation_Property_VTable vtable;
};

struct ColorVariation_Property_o
{
	ColorVariation_Property_Fields fields;

    // 018ecef0
    void Update(UnityEngine_MaterialPropertyBlock_o *propertyBlock, MethodInfo *method);
};

struct ColorVariation_Property_StaticFields
{
};

struct ColorVariation_Fields
{
	UnityEngine_MonoBehaviour_Fields super;
	int32_t ColorIndex;
	UnityEngine_MaterialPropertyBlock_o* propertyBlock;
	System::Array<ColorVariation_Property_o>* Property00;
	System::Array<ColorVariation_Property_o>* Property01;
	System::Array<ColorVariation_Property_o>* Property02;
	System::Array<ColorVariation_Property_o>* Property03;
};

struct ColorVariation_RGCTXs
{
};

struct ColorVariation_VTable
{
	VirtualInvokeData _0_Equals;
	VirtualInvokeData _1_Finalize;
	VirtualInvokeData _2_GetHashCode;
	VirtualInvokeData _3_ToString;
};

struct ColorVariation_c
{
	Il2CppClass_1 _1;
	struct ColorVariation_StaticFields* static_fields;
	ColorVariation_RGCTXs* rgctx_data;
	Il2CppClass_2 _2;
	ColorVariation_VTable vtable;
};

struct ColorVariation_o
{
	ColorVariation_c *klass;
	void *monitor;
	ColorVariation_Fields fields;
};

struct ColorVariation_StaticFields
{
	int32_t _SkinColorID;
	int32_t _PrimaryColorID;
	int32_t _SecondaryColorID;
};
