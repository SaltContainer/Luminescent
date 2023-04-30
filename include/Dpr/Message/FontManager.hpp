#pragma once

#include "il2cpp.hpp"
#include "SmartPoint/AssetAssistant/SingletonMonoBehavior.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

namespace Dpr
{
    namespace Message
    {
        struct FontManager_Fields
        {
            SmartPoint::AssetAssistant::SingletonMonoBehaviour_FontManager_Fields super;
            struct TextFontData_o* textFontData;
            struct FontMaterialData_o* fontMaterialData;
            struct TMPro_TMP_SpriteAsset_o* spriteFontAsset;
            struct System_Collections_Generic_Dictionary_int__FontAssetInfo__o* fontInfoTable;
            struct System_Collections_Generic_Dictionary_int__FontMaterialProperty__o* materialPropertyTable;
            struct System_Collections_Generic_Dictionary_int__Material__o* materialTable;
            struct FontAssetLoader_o* fontAssetLoader;
            int32_t useEFIGSCount;
        };

        struct FontManager_RGCTXs
        {
        };

        struct FontManager_VTable
        {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
            VirtualInvokeData _4_Awake;
            VirtualInvokeData _5_OnApplicationQuit;
        };

        struct FontManager_c
        {
            Il2CppClass_1 _1;
            struct FontManager_StaticFields* static_fields;
            FontManager_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            FontManager_VTable vtable;
        };

        struct FontManager_o
        {
            FontManager_c *klass;
            void *monitor;
            FontManager_Fields fields;

            // 01cab970
            void ChangeFontMaterial(TMPro::TextMeshProUGUI_o *text, int32_t materialIndex, MethodInfo *method);
        };

        struct FontManager_StaticFields
        {
        };
    }
}
