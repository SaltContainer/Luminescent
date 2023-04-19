#pragma once

#include "System/Array.hpp"
#include "XLSXContent/UIDatabase.hpp"

struct UnityEngine_Transform_o;
struct Dpr_UI_UIModelViewController_o;
struct XLSXContent_TownMapGuideTable_o;
struct XLSXContent_TownMapTable_o;
struct XLSXContent_DistributionTable_o;
struct XLSXContent_PlaceNameTable_o;
struct XLSXContent_InputLimitTable_o;
struct System_Collections_Generic_HashSet_int__o;
struct XLSXContent_SearchIndexData_o;
struct System_Collections_Generic_Dictionary_BallId__UIManager_MonsterBallParam__o;
struct UnityEngine_Sprite_o;
struct System_Collections_Generic_List_UIManager_SpriteAtlasParam__o;
struct Dpr_UI_Keyguide_o;
struct UnityEngine_Events_UnityAction_UIWindow__o;
struct ObjectPool_UIWindowID__UIManager_UIInstance__o;
struct ObjectPool_TransitionID__UIManager_TransitionInstance__o;
struct System_Collections_Generic_List_UIManager_TransitionInstance__o;
struct Dpr_CacheList_UIManager_CacheSpritePokemonParam__o;
struct UnityEngine_UI_RawImage_o;
struct Dpr_UI_UIManager_BlugBgParam_o;
struct System_Collections_Generic_Dictionary_UIManager_AtlasSpriteKey__Sprite__o;
struct Dpr_UI_XMenuTop_o;
struct Dpr_UI_NowloadingController_o;
struct UIWindowID_o;

namespace Dpr
{
    namespace UI 
    {
        struct UIManager_Fields {
            void * super;
            UnityEngine_Transform_o * _activeRoot;
            Dpr_UI_UIModelViewController_o * _modelView;
            UnityEngine_Transform_o * _blurBgRoot;
            XLSXContent::UIDatabase_o * _mdUis;
            XLSXContent_TownMapGuideTable_o * _mdTownmapGuide;
            XLSXContent_TownMapTable_o * _mdTownmap;
            XLSXContent_DistributionTable_o * _mdDistribution;
            XLSXContent_PlaceNameTable_o * _mdPlaceName;
            XLSXContent_InputLimitTable_o * _mdInputLimit;
            System::Array<System_Collections_Generic_HashSet_int__o*> * _inputLimitHashSets;
            XLSXContent_SearchIndexData_o * _mdSearchIndexData;
            System_Collections_Generic_Dictionary_BallId__UIManager_MonsterBallParam__o * _spriteMonsterBallDict;
            UnityEngine_Sprite_o * _spriteMonsterBallStrange;
            UnityEngine_Sprite_o * _spriteMonsterBallIllegal;
            System_Collections_Generic_List_UIManager_SpriteAtlasParam__o * _spriteAtlasParams;
            Dpr_UI_Keyguide_o * _keyguide;
            int32_t _InitializeStateBits;
            UnityEngine_Events_UnityAction_UIWindow__o * onXMenuClosed;
            bool _fureaiLimit;
            ObjectPool_UIWindowID__UIManager_UIInstance__o * _objectPool;
            ObjectPool_TransitionID__UIManager_TransitionInstance__o * _objectPoolTransition;
            System_Collections_Generic_List_UIManager_TransitionInstance__o * _transitionInstances;
            int32_t _transitionId;
            bool _isFadeTransition;
            Dpr_CacheList_UIManager_CacheSpritePokemonParam__o * _cacheSpritePokemons;
            UnityEngine_UI_RawImage_o * _blurBg;
            Dpr_UI_UIManager_BlugBgParam_o * _blurBgParam;
            float _debugInstrument;
            System::Array<System::String*> * _databaseAssetBundleNames;
            bool _isLoadedDatabase;
            System_Collections_Generic_Dictionary_UIManager_AtlasSpriteKey__Sprite__o * _atlasSpriteDict;
            System::String * _assetPathIndexdata;
            System::Array<UIWindowID_o*> * _transitionWindowIds;
            Dpr_UI_XMenuTop_o * _xMenu;
            Dpr_UI_NowloadingController_o * _nowLoadingController;
        };

        struct UIManager_o {
            UIManager_Fields fields;
        };
    }
}
