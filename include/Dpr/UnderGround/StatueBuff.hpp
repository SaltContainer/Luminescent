#pragma once

#include "System/String.hpp"
#include "il2cpp.hpp"
#include "System/Collections/Generic/Dictionary.hpp"
#include "System/Collections/Generic/List.hpp"
#include "DpData.hpp"

namespace Dpr
{
    namespace UnderGround
    {
        struct UnityEngine_GameObject_o;
        struct UnityEngine_U2D_SpriteAtlas_o;
        struct Dpr_UnderGround_UgPokeLottery_PokeSlot_array;
        struct UIStatueBuffIcon_o;

        struct StatueBuff_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            UnityEngine_Transform_o * IconsParent;
            UnityEngine_GameObject_o * IconPrefab;
            System::Collections::Generic::List<UIStatueBuffIcon_o> * Icons;
            UnityEngine_U2D_SpriteAtlas_o * IconAtlas;
            int32_t statueGridNum;
            Dpr_UnderGround_UgPokeLottery_PokeSlot_array * DebugPokeSlots;
            System::Collections::Generic::Dictionary_int__int__o * AddTypeKakurituDic;
            System::Collections::Generic::List<DPData::UgSecretBase_o> * secretBases;
            int32_t Button01;
            int32_t Button02;
            int32_t Button03;
        };

        struct StatueBuff_Fields_c;

        struct StatueBuff_o {
            StatueBuff_Fields_c *klass;
            void *monitor;
            StatueBuff_Fields fields;
        };
    }
}
