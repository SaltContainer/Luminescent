#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "System/String.hpp"

namespace XLSXContent
{
    struct StatueEffectRawData_Sheettable_Fields {
        uint16_t statueId;
        int32_t UgItemID;
        uint16_t monsId;
        uint8_t rarity;
        uint8_t shader;
        uint8_t width;
        uint8_t height;
        uint8_t resultCameraNo;
        int8_t type1Id;
        int8_t type2Id;
        System::Array<int16_t>* pokeTypeEffect;
        int32_t MSLabelId;
        System::String * motion;
        int32_t frame;
        UnityEngine_Vector3_o offset;
        float cameraDistance;
        uint16_t FormNo;
        uint8_t Sex;
        bool Rare;
        int32_t ratio1;
        int32_t ratio2;
        int32_t ratio3;
        int32_t ratio4;
        int32_t ratio5;
        int32_t ratio6;
        float fieldScale;
    };

    struct StatueEffectRawData_Sheettable_c;
    
    struct StatueEffectRawData_Sheettable_o {
        StatueEffectRawData_Sheettable_c *klass;
        void *monitor;
        StatueEffectRawData_Sheettable_Fields fields;
    };

    struct StatueEffectRawData_Fields {
        UnityEngine_ScriptableObject_Fields super;
        System::Array<StatueEffectRawData_Sheettable_o*> * table;
    };

    struct StatueEffectRawData_c;

    struct StatueEffectRawData_o {
        StatueEffectRawData_c *klass;
        void *monitor;
        StatueEffectRawData_Fields fields;
    };
}
