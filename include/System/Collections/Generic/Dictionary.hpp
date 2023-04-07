#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"

namespace System
{
    namespace Collections
    {
        namespace Generic
        {
            struct IEqualityComparer_TKey__o;
            struct Dictionary_Entry_TKey__TValue__array; // Should be System::Array but doubt that would work for the template
            struct Dictionary_KeyCollection_TKey__TValue__o;
            struct Dictionary_ValueCollection_TKey__TValue__o;

            struct Dictionary_int__int__Fields {
                System::Array<int32_t> * _buckets;
                Dictionary_Entry_TKey__TValue__array * _entries;
                int32_t _count;
                int32_t _version;
                int32_t _freeList;
                int32_t _freeCount;
                IEqualityComparer_TKey__o* _comparer;
                Dictionary_KeyCollection_TKey__TValue__o * _keys;
                Dictionary_ValueCollection_TKey__TValue__o * _values;
                Il2CppObject * _syncRoot;
            };

            struct Dictionary_int__int__c;

            struct Dictionary_int__int__o {
                Dictionary_int__int__c *klass;
                void *monitor;
                Dictionary_int__int__Fields fields;

                void Clear(MethodInfo *method);
                bool ContainsKey(int key, MethodInfo *method);
                int get_Item(int key, MethodInfo *method);
                void set_Item(int key, int value, MethodInfo *method);
                void Add(int key, int value, MethodInfo *method);
                int Count(MethodInfo *method);
            };
        }
    }
}
