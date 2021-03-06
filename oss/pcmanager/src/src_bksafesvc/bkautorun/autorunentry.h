/**
* @file    autorunentry.h
* @brief   ...
* @author  zhangrui
* @date    2009-04-26  17:11
*/

#ifndef AUTORUNENTRY_H
#define AUTORUNENTRY_H

#include "skylark2\skylarkbase.h"
#include "skylark2\slatruns.h"



struct SLATR_ENTRY_DATA;

class IAutorunContext
{
public:
    virtual void STDMETHODCALLTYPE Append_RegValue_As_Startup(
        const SLATR_ENTRY_DATA* pEntry,
        HKEY                    hKeyRoot,
        LPCWSTR                 lpszRegPath,
        LPCWSTR                 lpszValueName,
        LPCWSTR                 lpszValue) = 0;

    //virtual void STDMETHODCALLTYPE Append_RegValueName_As_Startup(
    //    const SLATR_ENTRY_DATA* pEntry,
    //    HKEY                    hKeyRoot,
    //    LPCWSTR                 lpszRegPath,
    //    LPCWSTR                 lpszValueName) = 0;

    virtual void STDMETHODCALLTYPE Append_Service(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszServiceName,
        DWORD                   dwServiceType,
        DWORD                   dwServiceStart,
        LPCWSTR                 lpszImagePath,
        LPCWSTR                 lpszServiceDll,
        LPCWSTR                 lpszServiceDisplayName,
        LPCWSTR                 lpszServiceDescription) = 0;

    virtual void STDMETHODCALLTYPE Append_Scheduled_Task(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszTaskName,
        LPCWSTR                 lpszApplicationName) = 0;

    virtual void STDMETHODCALLTYPE Append_Startup_Folder_File(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszStartupFolder,
        LPCWSTR                 lpszFilePath) = 0;

    virtual void STDMETHODCALLTYPE Append_Startup_Ini_File(
        const SLATR_ENTRY_DATA* pEntry,
        LPCWSTR                 lpszIniFile,
        LPCWSTR                 lpszIniApp,
        LPCWSTR                 lpszIniKey,
        LPCWSTR                 lpszFilePath) = 0;
};


typedef HRESULT (*PFN_EntryScanHandler)(IAutorunContext* pContext, const SLATR_ENTRY_DATA* pEntry);
typedef HRESULT (*PFN_EntryDisableHandler)(IAutorunContext* pContext, const SLATR_ENTRY_DATA* pEntry);
typedef HRESULT (*PFN_EntryFixHandler)(IAutorunContext* pContext, const SLATR_ENTRY_DATA* pEntry);


/// ??????????????
struct SLATR_ENTRY_DATA
{
    DWORD                   m_dwEntryID;                ///< ????????ID
    PFN_EntryScanHandler    m_pfnEntryScanHandler;      ///< ????entry??????
    PFN_EntryDisableHandler m_pfnEntryDisableHandler;   ///< ????entry??????
    PFN_EntryFixHandler     m_pfnEntryFixHandle;        ///< ????entry??????

    // ??????????
    HKEY                    m_hRootKey;                 ///< ????????
    LPCWSTR                 m_lpszRegParentKeyName;     ///< ??????
    LPCWSTR                 m_lpszRegSubKeyName;        ///< ??????
    LPCWSTR                 m_lpszRegValueName;         ///< ????
    BOOL                    m_bCanBeZeroFiles;          ///< ????????????????
    
    // ????????????
    int                     m_nFolderCSIDL;             ///< ??????????
};





#endif//AUTORUNENTRY_H