#include "il2cpp.hpp"
#include "util.hpp"
#include "System/Array.hpp"
#include "Dpr/UnderGround/StatueBuff.hpp"
#include "Dpr/UnderGround/UgFieldManager.hpp"
#include "XLSXContent/StatueEffectRawData.hpp"
#include "logger.hpp"

using namespace Dpr::UnderGround;
void Dpr_UnderGround_StatueBuff_CalcStatueData(StatueBuff_o *__this, MethodInfo *method)
{
    system_load_typeinfo((void *)0x8064);

    __this->fields.statueGridNum = 0;
    __this->fields.AddTypeKakurituDic->Clear(nullptr);

    socket_log_fmt("__this->fields.secretBases->fields._size: %d\n", __this->fields.secretBases->fields._size);

    if (__this->fields.secretBases->fields._size < 1) return;

    for (int i=0; i<__this->fields.secretBases->fields._size; i++)
    {
        DPData::UgSecretBase_o base = __this->fields.secretBases->fields._items->m_Items[i];

        socket_log_fmt("base.fields.ugStoneStatue->max_length: %08X\n", base.fields.ugStoneStatue->max_length);
        socket_log_fmt("base.fields.ugStoneStatue->bounds->length: %08X\n", base.fields.ugStoneStatue->bounds->length);
        socket_log_fmt("base.fields.ugStoneStatue->bounds->lower_bound: %08X\n", base.fields.ugStoneStatue->bounds->lower_bound);
        socket_log_fmt("base.fields.ugStoneStatue->obj: %08X\n", base.fields.ugStoneStatue->obj);

        for (int j=0; j<base.fields.ugStoneStatue->max_length; j++)
        {
            DPData::UgStoneStatue_o statue = base.fields.ugStoneStatue->m_Items[j];
            socket_log_fmt("statue.fields.statueId: %d\n", statue.fields.statueId);

            system_load_typeinfo((void *)0x806c);

            System::Array<XLSXContent::StatueEffectRawData_Sheettable_o*> *statueEffects = UgFieldManager_InfoType->static_fields->Instance->fields.ugStatueEffectData->fields.table;
            socket_log_fmt("statueEffects->max_length: %d\n", statueEffects->max_length);

            for (int k=0; k<statueEffects->max_length; k++)
            {
                if ((int32_t)(statueEffects->m_Items[k]->fields.statueId) == statue.fields.statueId)
                {
                    socket_log_fmt("About to find the mon id\n");
                    uint16_t monId = statueEffects->m_Items[k]->fields.monsId;
                    socket_log_fmt("MonID is: %d\n", monId);
                    if (!__this->fields.AddTypeKakurituDic->ContainsKey(monId, (MethodInfo*)0x04c6eab8))
                    {
                        socket_log_fmt("Adding statue: %d\n", monId);
                        __this->fields.AddTypeKakurituDic->Add(monId, 0, nullptr);
                    }

                    socket_log_fmt("Size: %d\n", statueEffects->m_Items[k]->fields.width * statueEffects->m_Items[k]->fields.height);
                    __this->fields.statueGridNum += statueEffects->m_Items[k]->fields.width * statueEffects->m_Items[k]->fields.height;
                    break;
                }
            }
        }
    }

    socket_log_fmt("Dictionary Count: %d\n", __this->fields.AddTypeKakurituDic->Count(nullptr));
}
