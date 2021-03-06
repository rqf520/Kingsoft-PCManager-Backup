/********************************************************************
* CreatedOn: 2006-12-12   17:44
* FileName:  KDOMDataExchange.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KDOMDataExchange_H_
#define __KDOMDataExchange_H_

#include "KDOMBasic.h"
#include "KDOMMacro.h"
#include "KDOMAutoChild.h"
#include "KDOMAutoArrayElem.h"
#include "KDOMAutoMap.h"

#include <vector>
#include <list>
#include <map>
#include <utility>

#include <ctype.h>

_KAN_DOM_BEGIN

// bool
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, bool& bValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, bValue);
}

// short
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed short& sValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, sValue);
}

// unsigned short
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned short& usValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, usValue);
}

// int
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed int& nValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, nValue);
}

// unsigned int
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned int& unValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, unValue);
}

// long
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed long& lValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, lValue);
}

// unsigned long
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned long& ulValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, ulValue);
}

// __int64
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, __int64& i64Value, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, i64Value);
}

// char
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, char& cValue, bool bWrite)
{
    int nValue = cValue;    // char????????????????????

    long lRet = domCur.BasicDataExchange(bWrite, nValue);
    if (SUCCEEDED(lRet) && !bWrite)
    {   // ????????,????????????????
        if (nValue > SCHAR_MAX || nValue < SCHAR_MIN)
        {   // ????????????
            domCur.DumpPath();
            return E_KDOM_DATA_OUT_OF_RANGE;
        }
        else
        {
            cValue = nValue;
        }
    }

    return lRet;
}

// signed char
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, signed char& cValue, bool bWrite)
{
    int nValue = cValue;    // char????????????????????

    long lRet = domCur.BasicDataExchange(bWrite, nValue);
    if (SUCCEEDED(lRet) && !bWrite)
    {   // ????????,????????????????
        if (nValue > SCHAR_MAX || nValue < SCHAR_MIN)
        {   // ????????????
            domCur.DumpPath();
            return E_KDOM_DATA_OUT_OF_RANGE;
        }
        else
        {
            cValue = nValue;
        }
    }

    return lRet;
}

// unsigned char
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, unsigned char& ucValue, bool bWrite)
{
    unsigned int unValue = ucValue; // unsigned char????????????????????

    long lRet = domCur.BasicDataExchange(bWrite, unValue);
    if (SUCCEEDED(lRet) && !bWrite)
    {   // ????????,????????????????
        if (unValue > UCHAR_MAX)
        {   // ????????????
            domCur.DumpPath();
            return E_KDOM_DATA_OUT_OF_RANGE;
        }
        else
        {
            ucValue = unValue;
        }
    }
    
    return lRet;
}



//////////////////////////////////////////////////////////////////////////
// see MSDN about "/Zc"
#ifdef _NATIVE_WCHAR_T_DEFINED

// wchar_t
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, wchar_t& wcValue, bool bWrite)
{
    return domCur.BasicDataExchange(bWrite, wcValue);
}

#endif



// char*
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, const char* pszValue, bool bWrite)
{
    assert(bWrite);
    if (bWrite)
    {
        return domCur.SetObjValue(pszValue);
    }
    
    return E_KDOM_DATA_TYPE_DO_NOT_SUPPORT_WRITING;
}

// wchar_t*
template<class _KDOMCursor>
inline long KXMLDataExchange(_KDOMCursor& domCur, const wchar_t* pwszValue, bool bWrite)
{
    assert(bWrite);
    if (bWrite)
    {
        return domCur.SetObjValue(pwszValue);
    }

    return E_KDOM_DATA_TYPE_DO_NOT_SUPPORT_WRITING;
}








//////////////////////////////////////////////////////////////////////////
// std::xstring
template<class _KDOMCursor, class _CharType, class _Traits, class _Alloc>
inline long KXMLDataExchange(
    _KDOMCursor& domCur,
    std::basic_string<_CharType, _Traits, _Alloc>& strValue,
    bool bWrite
)
{
    return domCur.BasicDataExchange(bWrite, strValue);
}




//////////////////////////////////////////////////////////////////////////
// std::vector
template<class _KDOMCursor, class T, class _Alloc>
inline long KXMLDataExchange(_KDOMCursor& domCur, std::vector<T, _Alloc>& stlVec, bool bWrite)
{
    long lRet;

    //KANDOM::KDOMAutoArrayEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

    if (bWrite)
    {
        // ????????????,????????????????
        lRet = domCur.EraseAllChildren();
        if (FAILED(lRet))
        {
            domCur.DumpPath();
            return lRet;
        }

        // ????????????,??????????
        if (stlVec.empty())
        {
            return S_OK;
        }
    }
    else
    {   // ????????????,??vec??????????
        stlVec.clear();
    }

    {
        // ??????????????????????
        KANDOM::KDOMAutoArrayElemEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

        if (bWrite)
        {
            if (!stlVec.empty())
            {   // ????MoveToNext()??????????null????,??????????????????????????????
                std::vector<T, _Alloc>::iterator iter = stlVec.begin();

                lRet = domCur.ObjDataExchange(bWrite, *iter);
                if (FAILED(lRet))
                {
                    return lRet;
                }

                ++iter; // ????????????????????
                for (NULL; iter != stlVec.end(); ++iter)
                {
                    // domIter????????????????
                    domArrayIter.MoveToNext();

                    lRet = domCur.ObjDataExchange(bWrite, *iter);
                    if (FAILED(lRet))
                    {
                        return lRet;
                    }
                }
            }
        }
        else
        {
            while (!domArrayIter.End())
            {
                stlVec.push_back(T());
                lRet = domCur.ObjDataExchange(bWrite, stlVec.back());
                if (FAILED(lRet))
                {
                    return lRet;
                }

                // ????????????????
                domArrayIter.MoveToNext();
            }
        }


        // ??????autoChild????????????
    }

    return S_OK;
}








//////////////////////////////////////////////////////////////////////////
// std::list
template<class _KDOMCursor, class T, class _Alloc>
inline long KXMLDataExchange(_KDOMCursor& domCur, std::list<T, _Alloc>& stlList, bool bWrite)
{
    long lRet;

    KANDOM::KDOMAutoArrayEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

    if (bWrite)
    {
        // ????????????,????????????????
        lRet = domCur.EraseAllChildren();
        if (FAILED(lRet))
        {
            domCur.DumpPath();
            return lRet;
        }

        // ????????????,??????????
        if (stlList.empty())
        {
            return S_OK;
        }
    }
    else
    {   // ????????????,??vec??????????
        stlList.clear();
    }

    {
        // ??????????????????????
        KANDOM::KDOMAutoArrayElemEx<_KDOMCursor> domArrayIter(&domCur, bWrite);

        if (bWrite)
        {
            if (!stlList.empty())
            {   // ????MoveToNext()??????????null????,??????????????????????????????
                std::list<T, _Alloc>::iterator iter = stlList.begin();

                lRet = domCur.ObjDataExchange(bWrite, *iter);
                if (FAILED(lRet))
                {
                    return lRet;
                }

                ++iter; // ????????????????????
                for (NULL; iter != stlVec.end(); ++iter)
                {
                    // domIter????????????????
                    domArrayIter.MoveToNext();

                    lRet = domCur.ObjDataExchange(bWrite, *iter);
                    if (FAILED(lRet))
                    {
                        return lRet;
                    }
                }
            }
        }
        else
        {
            while (!domArrayIter.End())
            {
                stlVec.resize(stdVec.size());
                lRet = domCur.ObjDataExchange(bWrite, stlList.back());
                if (FAILED(lRet))
                {
                    return lRet;
                }

                // ????????????????
                domArrayIter.MoveToNext();
            }
        }


        // ??????autoChild????????????
    }

    return S_OK;
}





//////////////////////////////////////////////////////////////////////////
// std::map
template<class _KDOMCursor, class K, class T, class PR, class _Alloc>
inline long KXMLDataExchange(_KDOMCursor& domCur, std::map<K, T, PR, _Alloc>& stlMap, bool bWrite)
{
    long lRet;

    if (bWrite)
    {
        // ??????????????????????????array
        //// ????????????,????????????????
        //lRet = domCur.EraseAllChildren();
        //if (FAILED(lRet))
        //{
        //    domCur.DumpPath();
        //    return lRet;
        //}

        // ????????????,??????????
        if (stlMap.empty())
        {
            return S_OK;
        }
    }
    else
    {   // ????????????,??map??????????
        stlMap.clear();
    }

    {
        // ??????????????????????
        

        if (bWrite)
        {
            if (!stlMap.empty())
            {
                KANDOM::KDOMAutoMapEx<_KDOMCursor> autoMap(&domCur, bWrite);

                std::map<K, T, PR, _Alloc>::iterator iter = stlMap.begin();
                for (NULL; iter != stlMap.end(); ++iter)
                {
                    lRet = autoMap.SetMapElem(iter->first, iter->second);
                    if (FAILED(lRet))
                    {
                        return lRet;
                    }
                }
            }
        }
        else
        {
            KANDOM::KDOMAutoMapElemEx<_KDOMCursor> autoMapElem(&domCur, bWrite);

            while (!autoMapElem.End())
            {
                std::pair<K, T> value;


                lRet = autoMapElem.GetMapElem(value.first, value.second);
                if (FAILED(lRet))
                {
                    return lRet;
                }

                stlMap.insert(value);

                // ????????????????
                autoMapElem.MoveToNextElem();
            }
        }


        // ??????autoChild????????????
    }

    return S_OK;
}






_KAN_DOM_END

#endif//__KDOMDataExchange_H_
