#pragma once 

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"
#include "WazaParam.hpp"
#include "DmgAffRec.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_CheckNotEffect_Guard_o {
                bool isNoEffectByMamoru_Others(BTL_POKEPARAM_o *attacker, BTL_POKEPARAM_o *target, WazaParam_o *wazaParam, DmgAffRec_o *affinityRecorder, MethodInfo *method);
                void onMamoruSuccess(BTL_POKEPARAM_o *attacker, BTL_POKEPARAM_o *target, WazaParam_o *wazaParam, MethodInfo *method);
            };
        }
    }
}