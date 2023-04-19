#include "il2cpp.hpp"

#include "System/Array.hpp"
#include "System/String.hpp"
#include "PlayerWork.hpp"
#include "Dpr/UI/UIManager.hpp"
#include "XLSXContent/UIDatabase.hpp"

#include "logger.hpp"
#include "util.hpp"

System::String* ReturnWeightSpriteName(System::String *format, Il2CppObject *arg0, Il2CppObject *arg1, MethodInfo *method)
{
    if (PlayerWork::get_playerSex(nullptr))
    {
        // Lucas
        return System::String::CreateString("dex_ico_compare_player_01_000_00");
    }
    else
    {
        // Dawn
        return System::String::CreateString("dex_ico_compare_player_01_100_00");
    }
}

System::String* ReturnTownMapSpriteName(System::String *format, Il2CppObject *arg0, Il2CppObject *arg1, MethodInfo *method)
{
    if (PlayerWork::get_playerSex(nullptr))
    {
        // Lucas
        return System::String::CreateString("map_ico_player_01_000_00");
    }
    else
    {
        // Dawn
        return System::String::CreateString("map_ico_player_01_100_00");
    }
}

XLSXContent::UIDatabase_SheetCharacterBag_o* FindBagDataById(System::Array<XLSXContent::UIDatabase_SheetCharacterBag_o*> * source, int id)
{
    for (int i=0; i<source->max_length; i++)
    {
        XLSXContent::UIDatabase_SheetCharacterBag_o * item = source->m_Items[i];
        if (item->fields.Index == id) return item;
    }

    socket_log_fmt("Could not find bag data for id: %d\n", id);
    return nullptr;
}

XLSXContent::UIDatabase_SheetCharacterBag_o* ReturnBaseUIDatabaseBag(Dpr::UI::UIManager_o *__this, int32_t characterDressId, MethodInfo *method)
{
    system_load_typeinfo((void *)0x9bd6);

    // For some reason the structs are not well formed.
    // This is supposed to be __this->fields._mdUis->fields.CharacterBag
    // Offset 0x30 of __this, then offset 0x70 of _mdUis to get CharacterBag.
    ulong mdUiAddress = *((ulong *)(((ulong)__this) + 48));
    System::Array<XLSXContent::UIDatabase_SheetCharacterBag_o*> * characterBagAddress = *((System::Array<XLSXContent::UIDatabase_SheetCharacterBag_o*> **)(mdUiAddress + 112));

    if (PlayerWork::get_playerSex(nullptr))
    {
        // Lucas
        XLSXContent::UIDatabase_SheetCharacterBag_o * item = FindBagDataById(characterBagAddress, 0);
        if (item != nullptr) return item;
        else return characterBagAddress->m_Items[0]; // Shouldn't happen
    }
    else
    {
        // Dawn
        XLSXContent::UIDatabase_SheetCharacterBag_o * item = FindBagDataById(characterBagAddress, 100);
        if (item != nullptr) return item;
        else return characterBagAddress->m_Items[0]; // Shouldn't happen
    }
}
