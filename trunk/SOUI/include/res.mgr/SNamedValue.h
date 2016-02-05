//////////////////////////////////////////////////////////////////////////
//   File Name: SNamedValue.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "core/SSingleton.h"
#include "helper/color.h"

#define GETSTRING(p1) SNamedString::getSingleton().Get(p1)
#define GETCOLOR(p1) SNamedColor::getSingleton().Get(p1)

namespace SOUI
{
    #define  MAX_NAME   50
    
    template<class T>
    struct TNAMEDVALUE
    {
        wchar_t strName[MAX_NAME+1];
        T      value;
    };
    
    template<class T2,class T,class ValueParser >
    class SNamedValue : public SSingleton< T2 >
    {
    public:
        typedef TNAMEDVALUE<T> NAMEDVALUE;

        BOOL Init(pugi::xml_node xmlNode)
        {
            if(!xmlNode) return FALSE;

            for (pugi::xml_node xmlStr=xmlNode.first_child(); xmlStr; xmlStr=xmlStr.next_sibling())
            {
                NAMEDVALUE namedValue;
                wcscpy_s(namedValue.strName,MAX_NAME,xmlStr.name());
                namedValue.value= ValueParser::ParseValue(xmlStr.attribute(L"value").as_string());
                m_lstNamedValue.Add(namedValue);
            }
            qsort(m_lstNamedValue.GetData(),m_lstNamedValue.GetCount(),sizeof(NAMEDVALUE),Compare);
            return TRUE;
        }
        
        const T  String2Value(const SStringW &strName) const
        {
            NAMEDVALUE target;
            wcscpy_s(target.strName,MAX_NAME,strName);
            NAMEDVALUE *pFind = (NAMEDVALUE *)bsearch(&target,m_lstNamedValue.GetData(),m_lstNamedValue.GetCount(),sizeof(NAMEDVALUE),Compare);
            if(!pFind) return ValueParser::GetNullValue();
            return pFind->value;
        }
        
    protected:
        
        static int Compare(const void * p1,const void * p2)
        {
            const NAMEDVALUE * pData1 = (const NAMEDVALUE*)p1;
            const NAMEDVALUE * pData2 = (const NAMEDVALUE*)p2;
            return wcscmp(pData1->strName,pData2->strName);
        }
        
        SArray<NAMEDVALUE> m_lstNamedValue;
    };
    
    class SIntParser
    {
    public:
        static int ParseValue(const SStringW & strValue)
        {
            return _wtoi(strValue);
        }
        
        static int GetNullValue()
        {
            return 0;
        }
    };
    
    
    class SColorParser
    {
    public:
        static COLORREF ParseValue(const SStringW & strValue)
        {
            int r,g,b,a=255;
            int nSeg=0;
            SStringW strValueL = strValue;
            strValueL.MakeLower();
            if(strValueL.Left(1)==L"#")
            {
                nSeg = swscanf(strValueL,L"#%02x%02x%02x%02x",&r,&g,&b,&a);
            }else if(strValueL.Left(4).CompareNoCase(L"rgba")==0)
            {
                nSeg = swscanf(strValueL,L"rgba(%d,%d,%d,%d)",&r,&g,&b,&a);                
            }else if(strValueL.Left(3).CompareNoCase(L"rgb")==0)
            {
                nSeg = swscanf(strValueL,L"rgb(%d,%d,%d)",&r,&g,&b);                
            }
            if(nSeg!=3 && nSeg != 4)
            {
                SASSERT_FMT(FALSE,TEXT("ParseColor Failed with [%s]"),S_CW2T(strValue));
                return CR_INVALID;
            }else
            {
                return RGBA(r,g,b,a);
            }
        }
        
        static COLORREF GetNullValue()
        {
            return CR_INVALID;
        }
    };
    
    class SStringParser
    {
    public:
        static SStringW ParseValue(const SStringW & strValue)
        {
            return strValue;
        }
        
        static SStringW GetNullValue()
        {
            return SStringW();
        }

    };

    class SOUI_EXP SNamedID : public SNamedValue<SNamedID,int,SIntParser>
    {
    public:
        //从数组里初始化命名ID列表
        //TNAMEDVALUE<int> *pValue:数组
        //int nCount:数组长度
        //BOOL bSorted:数组关键字从小到大已经有序
        void Init2(const NAMEDVALUE *pValue,int nCount,BOOL bSorted);
    }; 
    
    class SOUI_EXP SNamedColor : public SNamedValue<SNamedColor,COLORREF,SColorParser>
    {
    public:
        //自动转换@color/namedcolor
        COLORREF Get(const SStringW & strValue) const;
    }; 

    class SOUI_EXP SNamedString :public SNamedValue<SNamedString,SStringW,SStringParser>
    {
    public:
        //自动转换@string/namedstring
        SStringW Get(const SStringW & strValue) const;
    };

}//namespace SOUI