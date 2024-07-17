#pragma once

#include <cstring>
#include <string>
#include <Windows.h>

using get_domain_t = void*(__fastcall*)(void);
using create_string_t = const char*(__fastcall*)(void* domain, const char* text);

inline get_domain_t get_domain = nullptr;
inline create_string_t create_string = nullptr;

class IL2CPPUtil
{
public:
    static void init();
    
    struct il2cppClass
    {
        void* m_pImage;
        void* m_pGC;
        const char* m_pName;
        const char* m_pNamespace;
        void* m_pValue;
        void* m_pArgs;
        il2cppClass* m_pElementClass;
        il2cppClass* m_pCastClass;
        il2cppClass* m_pDeclareClass;
        il2cppClass* m_pParentClass;
        void* m_pGenericClass;
        void* m_pTypeDefinition;
        void* m_pInteropData;
        void* m_pFields;
        void* m_pEvents;
        void* m_pProperties;
        void** m_pMethods;
        il2cppClass** m_pNestedTypes;
        il2cppClass** m_ImplementedInterfaces;
        void* m_pInterfaceOffsets;
        void* m_pStaticFields;
        void* m_pRGCTX;
    };

    struct il2cppObject
    {
        il2cppClass* m_pClass = nullptr;
        void* m_pMonitor = nullptr;
    };

    struct System_String : il2cppObject
    {
        int m_iLength;
        wchar_t m_wString[1024];

        void Clear()
        {
            if (!this) return;
            memset(m_wString, 0, static_cast<size_t>(m_iLength) * 2);
            m_iLength = 0;
        }

        std::string ToString()
        {
            if (!this) return "";
            std::string sRet(static_cast<size_t>(m_iLength) * 3 + 1, '\0');
            WideCharToMultiByte(CP_UTF8, 0, m_wString, m_iLength, &sRet[0], static_cast<int>(sRet.size()), 0, 0);
            return sRet;
        }
    };

    struct il2cppArrayBounds
    {
        uintptr_t m_uLength;
        int m_iLowerBound;
    };

    template<typename T>
    struct il2cppArray : il2cppObject
    {
        il2cppArrayBounds* m_pBounds = nullptr;
        uintptr_t m_uMaxLength = 0;
        T* m_pValues = nullptr;

        uintptr_t GetData()
        {
            return reinterpret_cast<uintptr_t>(&m_pValues);
        }

        T& operator[](unsigned int m_uIndex)
        {
            return *reinterpret_cast<T*>(GetData() + sizeof(T) * m_uIndex);
        }

        T& At(unsigned int m_uIndex)
        {
            return operator[](m_uIndex);
        }

        void Insert(T* m_pArray, uintptr_t m_uSize, uintptr_t m_uIndex = 0)
        {
            if ((m_uSize + m_uIndex) >= m_uMaxLength)
            {
                if (m_uIndex >= m_uMaxLength)
                    return;

                m_uSize = m_uMaxLength - m_uIndex;
            }

            for (uintptr_t u = 0; m_uSize > u; ++u)
                operator[](u + m_uIndex) = m_pArray[u];
        }

        void Fill(T m_tValue)
        {
            for (uintptr_t u = 0; m_uMaxLength > u; ++u)
                operator[](u) = m_tValue;
        }

        void RemoveAt(unsigned int m_uIndex)
        {
            if (m_uIndex >= m_uMaxLength)
                return;

            if (m_uMaxLength > (m_uIndex + 1))
            {
                for (unsigned int u = m_uIndex; (static_cast<unsigned int>(m_uMaxLength) - m_uIndex) > u; ++u)
                    operator[](u) = operator[](u + 1);
            }

            --m_uMaxLength;
        }

        void RemoveRange(unsigned int m_uIndex, unsigned int m_uCount)
        {
            if (m_uCount == 0)
                m_uCount = 1;

            unsigned int m_uTotal = m_uIndex + m_uCount;
            if (m_uTotal >= m_uMaxLength)
                return;

            if (m_uMaxLength > (m_uTotal + 1))
            {
                for (unsigned int u = m_uIndex; (static_cast<unsigned int>(m_uMaxLength) - m_uTotal) >= u; ++u)
                    operator[](u) = operator[](u + m_uCount);
            }

            m_uMaxLength -= m_uCount;
        }

        void RemoveAll()
        {
            if (m_uMaxLength > 0)
            {
                memset(GetData(), 0, sizeof(T) * m_uMaxLength);
                m_uMaxLength = 0;
            }
        }
    };

    // Defined here because its basically same shit
    template<typename T>
    struct il2cppList : il2cppObject
    {
        il2cppArray<T>* m_pListArray;
        il2cppArray<T>* ToArray() { return m_pListArray; }
    };

    template<typename TKey,typename TValue>
    struct il2cppDictionary : il2cppObject
    {
        struct Entry
        {
            int m_iHashCode;
            int m_iNext;
            TKey m_tKey;
            TValue m_tValue;
        };
        il2cppArray<int>* m_pBuckets;
        il2cppArray<Entry*>* m_pEntries;
        int m_iCount;
        int m_iVersion;
        int m_iFreeList;
        int m_iFreeCount;
        void* m_pComparer;
        void* m_pKeys;
        void* m_pValues;

        Entry* GetEntry()
        {
            return (Entry*)m_pEntries->GetData();
        }

        TKey GetKeyByIndex(int iIndex)
        {
            TKey tKey = { 0 };
			
            Entry* pEntry = GetEntry();
            if (pEntry)
                tKey = pEntry[iIndex].m_tKey;

            return tKey;
        }

        TValue GetValueByIndex(int iIndex)
        {
            TValue tValue = { 0 };

            Entry* pEntry = GetEntry();
            if (pEntry)
                tValue = pEntry[iIndex].m_tValue;

            return tValue;
        }

        TValue GetValueByKey(TKey tKey)
        {
            TValue tValue = { 0 };
            for (int i = 0; i < m_iCount; i++) {
                if (GetEntry()[i].m_tKey == tKey)
                    tValue =  GetEntry()[i].m_tValue;
            }
            return tValue;
        }
    };

    struct Color
    {
        float r, g, b, a;
        Color() { r = g = b = a = 0.f; }
        Color(float fRed = 0.f, float fGreen = 0.f, float fBlue = 0.f, float fAlpha = 1.f) { r = fRed; g = fGreen; b = fBlue; a = fAlpha; }
    };
};
