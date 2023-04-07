#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "DpData.hpp"

namespace System
{
    namespace Collections
    {
        namespace Generic
        {
            template <typename T>
            struct List_Fields {
                System::Array<T> * _items;
                int32_t _size;
                int32_t _version;
                Il2CppObject * _syncRoot;
            };

            struct List_c;

            template <typename T>
            struct List {
                List_c *klass;
                void *monitor;
                List_Fields<T> fields;

                // Add Methods here
            };

            
            struct List_UgSecretBase__Fields {
                System::Array<DPData::UgSecretBase_o> * _items;
                int32_t _size;
                int32_t _version;
                Il2CppObject * _syncRoot;
            };

            struct List_UgSecretBase__c;

            struct List_UgSecretBase__o {
                List_UgSecretBase__c *klass;
                void *monitor;
                List_UgSecretBase__Fields fields;

                // Add Methods here
            };
        }
    }
}
