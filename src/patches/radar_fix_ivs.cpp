#include "il2cpp.hpp"
#include "logger.hpp"
#include "util.hpp"
#include "Dpr/Field/SwayGrass.hpp"

// extern Dpr_Field_SwayGrass_c * SwayGrass_InfoType;

extern void * DAT_7104cbc6f7;
using namespace Dpr::Field;
uint8_t Dpr_Field_SwayGrass_RensaTalent(MethodInfo *method)
{
    char isSwaying; 
    uint chainLength;
    uint32_t count;
    SwayGrass_StaticFields *staticFields;
    
    // data load as per original code
    system_load_typeinfo(DAT_7104cbc6f7);
    // system_load_typeinfo((void *) 0x8259);

    if ((SwayGrass_InfoType->_2).cctor_finished != 0) {
        staticFields = SwayGrass_InfoType->static_fields;
    }  else {
        il2cpp_runtime_class_init((void *) SwayGrass_InfoType);
        staticFields = SwayGrass_InfoType->static_fields;
    }

    isSwaying = staticFields->is_swaygrass_flag;
    count = staticFields->rensa_count;

    // ghidra extracted code. chain length logic
    chainLength = 99999999;
    if (count + 1 < 99999999) {
      chainLength = count + 1;
    }

    // checks if the SwayGrass_InfoType chain is active
    // returns IVs based on chain length
    if (isSwaying != '\0') {
        if (chainLength<20){ // 0-20
            return 0;
        }
        if (chainLength<40){ // 20-40
            return 1;
        }
        if (chainLength<60){ // 40-60
            return 2;
        }
        if (chainLength<80){// 60-80
            return 3;
        }
        if (chainLength<100){// 80-100
            return 4;
        }
        if (chainLength>=100){
            return 5;
        }
    }
    return 0;
}

