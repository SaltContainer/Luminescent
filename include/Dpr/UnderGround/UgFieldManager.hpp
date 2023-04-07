#pragma once

#include "il2cpp.hpp"
#include "XLSXContent/StatueEffectRawData.hpp"
#include "Dpr/UnderGround/StatueBuff.hpp"
#include "DpData.hpp"
#include "System/Array.hpp"
#include "System/String.hpp"

namespace Dpr
{
    namespace UnderGround
    {
        // Don't need to define these for now
        struct UgFieldManager_DigData_o;
        struct List_UgFieldManager_DigPointModel__o;
        struct UgNetworkManager_o;
        struct UgFieldDataManager_o;
        struct UgMiniMapComponent_o;
        struct Dpr_Field_Walking_WalkingAIManager_o;
        struct FieldObjectEntity_o;
        struct UgNetworkManager_UgOnlinePlayerData_o;
        struct System_Collections_Generic_List_UgFieldManager_SecretBaseModel__o;
        struct System_Collections_Generic_List_Vector2Int__o;
        struct Dpr_UI_ContextMenuWindow_o;
        struct Dpr_FieldObjectMove_o;
        struct Dpr_FieldObjectRotateYaw_o;
        struct UgNPCTalkModel_o;
        struct System_Action_o;

        struct Dpr_NetworkUtils_UgStationID_to_DigFossilIDList_Fields {
            System::Array<uint8_t> * DigFossilIDs;
        };

        struct Dpr_NetworkUtils_UgStationID_to_DigFossilIDList_o {
            Dpr_NetworkUtils_UgStationID_to_DigFossilIDList_Fields fields;
        };

        struct UgFieldManager_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            int32_t d_stationIndex;
            int32_t d_digGroupID;
            bool isUgExiting;
            bool isErrorDialogVisible;
            System_Action_o * OnCloseErrorDialog;
            bool IsClosableMessage;
            System_Action_o * OnFinishMsg;
            System_Action_o * OnFinishBusy;
            System_Action_o * OnCreateOtherSecretBase;
            bool IsBase;
            bool isLoadedOrVisit;
            UgNetworkManager_o * ugNetManager;
            float KousekiBonusTime;
            uint8_t KousekiCount;
            uint8_t BonusCount;
            XLSXContent::StatueEffectRawData_o * ugStatueEffectData;
            UgFieldDataManager_o * dataMng;
            UgMiniMapComponent_o * miniMap;
            int32_t prevZoneID;
            int32_t nowZoneType;
            Dpr_Field_Walking_WalkingAIManager_o * walkingManager;
            FieldObjectEntity_o * NpcEntity;
            StatueBuff_o * statueBuff;
            DPData::UgSecretBase_o nowBaseModel;
            int32_t nowBasePlayerIndex;
            UgNetworkManager_UgOnlinePlayerData_o * nowBasePlayerData;
            DPData::UgSecretBase_o EffectiveBase;
            int32_t _effectiveBasePlayerIndex_k__BackingField;
            System_Collections_Generic_List_UgFieldManager_SecretBaseModel__o * SecretBases;
            Dpr_NetworkUtils_UgStationID_to_DigFossilIDList_o ugDigGroupList;
            bool isDigCancel;
            int32_t targetStationIndex;
            System_Action_o * OnLeaveTargetPlayer;
            System_Action_o * OnDestroyCallBack;
            System_Action_o * OnZoneChangeCallBack;
            float OnZoneChangeTime;
            bool isDebugDraw;
            float duration;
            float searchSize;
            float searchDist;
            float TalkDistance;
            System_Collections_Generic_List_Vector2Int__o * buffPosList;
            bool isSearching;
            UnityEngine_Transform_o * _dummy;
            int32_t Button02;
            int32_t Button04;
            Dpr_UI_ContextMenuWindow_o * contextMenu;
            bool isContextMenuOpend;
            int32_t Button03;
            System_Action_o * OnComplete;
            Dpr_FieldObjectMove_o * move;
            Dpr_FieldObjectRotateYaw_o * rot;
            int32_t Button01;
            int32_t Button05;
            int32_t Button06;
            UgNPCTalkModel_o * NpcTalkModel;
            System::Array<bool> * results;
            int32_t button111;
            int32_t Button001;
            int32_t button01;
            int32_t button02;
            int32_t button03;
            int32_t Button010;
            bool _isInitAddUpdate;
        };
        struct UgFieldManager_RGCTXs {
        };
        struct UgFieldManager_VTable {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };
        struct UgFieldManager_c {
            Il2CppClass_1 _1;   
            struct UgFieldManager_StaticFields* static_fields;
            UgFieldManager_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            UgFieldManager_VTable vtable;
        };
        struct UgFieldManager_o {
            UgFieldManager_c *klass;
            void *monitor;
            UgFieldManager_Fields fields;
        };
        struct UgFieldManager_StaticFields {
            UgFieldManager_o *Instance;
            bool isFallEnter;
            bool isDebug_RarePoke;
            bool isForceRareColor;
            System::Array<System::String>* Y_MENU_LABEL;
            System::Array<System::String>* Y_MENU_LABEL_ONLINE;
            UgFieldManager_DigData_o * digData;
            List_UgFieldManager_DigPointModel__o * DigPoints;
            bool isEnableInput;
            bool isStartLeave;
            bool isGuruGuruAnimEnd;
            UnityEngine_Vector3_array * eightDirect;
        };
        extern UgFieldManager_c * UgFieldManager_InfoType;   
    }  
}
