#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "System/String.hpp"

namespace XLSXContent
{
    struct UIDatabase_SheetUIWindow_o;
    struct UIDatabase_SheetTransition_o;
    struct UIDatabase_SheetSpriteAtlas_o;
    struct UIDatabase_SheetSharedSprite_o;
    struct UIDatabase_SheetCommonSprite_o;
    struct UIDatabase_SheetPokemonIcon_o;
    struct UIDatabase_SheetAshiatoIcon_o;
    struct UIDatabase_SheetPokemonVoice_o;
    struct UIDatabase_SheetMonsterBall_o;
    struct UIDatabase_SheetContextMenu_o;
    struct UIDatabase_SheetKeyguide_o;

    struct UIDatabase_SheetCharacterBag_Fields
    {
        int32_t Index;
        System::String * XMenuDefault;
        System::String * XMenuSelect;
        System::String * XMenuShadow;
        System::String * BagHeader;
        System::String * BagBase;
        System::Array<System::String *> * BagPockets;
    };

    struct UIDatabase_SheetCharacterBag_c;

    struct UIDatabase_SheetCharacterBag_o
    {
        UIDatabase_SheetCharacterBag_c *klass;
        void *monitor;
        UIDatabase_SheetCharacterBag_Fields fields;
    };

    struct UIDatabase_SheetZukanDisplay_o;
    struct UIDatabase_SheetZukanComparePlayer_o;
    struct UIDatabase_SheetZukanCompareHeight_o;
    struct UIDatabase_SheetZukanCompareWeight_o;
    struct UIDatabase_SheetFloorDisplay_o;
    struct UIDatabase_SheetShopMessage_o;
    struct UIDatabase_SheetPlaceMark_o;
    struct UIDatabase_SheetMarkColor_o;
    struct UIDatabase_SheetWallpaper_o;
    struct UIDatabase_SheetBox_o;
    struct UIDatabase_SheetPokeColor_o;
    struct UIDatabase_SheetDistributionMapchip_o;
    struct UIDatabase_SheetPolishedBadge_o;
    struct UIDatabase_SheetSearchPokeIconSex_o;
    struct UIDatabase_SheetHideWazaName_o;
    struct UIDatabase_SheetHideTokusei_o;
    struct UIDatabase_SheetZukanRating_o;
    struct UIDatabase_SheetBoxOpenParam_o;
    struct UIDatabase_SheetSealTemplate_o;
    struct UIDatabase_SheetRankingDisplay_o;

    struct UIDatabase_Fields
    {
        void* super;
        System::Array<UIDatabase_SheetUIWindow_o*>* UIWindow;
        System::Array<UIDatabase_SheetTransition_o*>* Transition;
        System::Array<UIDatabase_SheetSpriteAtlas_o*>* SpriteAtlas;
        System::Array<UIDatabase_SheetSharedSprite_o*>* SharedSprite;
        System::Array<UIDatabase_SheetCommonSprite_o*>* CommonSprite;
        System::Array<UIDatabase_SheetPokemonIcon_o*>* PokemonIcon;
        System::Array<UIDatabase_SheetAshiatoIcon_o*>* AshiatoIcon;
        System::Array<UIDatabase_SheetPokemonVoice_o*>* PokemonVoice;
        System::Array<UIDatabase_SheetMonsterBall_o*>* MonsterBall;
        System::Array<UIDatabase_SheetContextMenu_o*>* ContextMenu;
        System::Array<UIDatabase_SheetKeyguide_o*>* Keyguide;
        System::Array<UIDatabase_SheetCharacterBag_o*>* CharacterBag;
        System::Array<UIDatabase_SheetZukanDisplay_o*>* ZukanDisplay;
        System::Array<UIDatabase_SheetZukanComparePlayer_o*>* ZukanComparePlayer;
        System::Array<UIDatabase_SheetZukanCompareHeight_o*>* ZukanCompareHeight;
        System::Array<UIDatabase_SheetZukanCompareWeight_o*>* ZukanCompareWeight;
        System::Array<UIDatabase_SheetFloorDisplay_o*>* FloorDisplay;
        System::Array<UIDatabase_SheetShopMessage_o*>* ShopMessage;
        System::Array<UIDatabase_SheetPlaceMark_o*>* PlaceMark;
        System::Array<UIDatabase_SheetMarkColor_o*>* MarkColor;
        System::Array<UIDatabase_SheetWallpaper_o*>* Wallpaper;
        System::Array<UIDatabase_SheetBox_o*>* Box;
        System::Array<UIDatabase_SheetPokeColor_o*>* PokeColor;
        System::Array<UIDatabase_SheetDistributionMapchip_o*>* DistributionMapchip;
        System::Array<UIDatabase_SheetPolishedBadge_o*>* PolishedBadge;
        System::Array<UIDatabase_SheetSearchPokeIconSex_o*>* SearchPokeIconSex;
        System::Array<UIDatabase_SheetHideWazaName_o*>* HideWazaName;
        System::Array<UIDatabase_SheetHideTokusei_o*>* HideTokusei;
        System::Array<UIDatabase_SheetZukanRating_o*>* ZukanRating;
        System::Array<UIDatabase_SheetBoxOpenParam_o*>* BoxOpenParam;
        System::Array<UIDatabase_SheetSealTemplate_o*>* SealTemplate;
        System::Array<UIDatabase_SheetRankingDisplay_o*>* RankingDisplay;
    };

    struct UIDatabase_c;
    
    struct UIDatabase_o {
        UIDatabase_c *klass;
        void *monitor;
        UIDatabase_Fields fields;
    };
}
