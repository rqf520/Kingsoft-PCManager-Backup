// Copyright (c) 2010 Kingsoft Corporation. All rights reserved.
// Copyright (c) 2010 The KSafe Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _FILEOPT_H_
#define _FILEOPT_H_

#include <Windows.h>
#include <atlstr.h>
#include <process.h>
#include <atlconv.h>
#include "CleanProc.h"

typedef BOOL (WINAPI *EnumerateFunc) (LPCTSTR lpFileOrPath, void* pUserData,LARGE_INTEGER iFileSize);
typedef BOOL (WINAPI *EnumerateFuncEx) (int iType,LPCTSTR lpFileOrPath, void* pUserData,LARGE_INTEGER iFileSize);

class CFileOpt
{
public:
	CFileOpt(){ s_bUserBreak = FALSE; };
	~CFileOpt(){};
public:
	void		UserBreadFlag(BOOL bUserBreak) { s_bUserBreak = bUserBreak; };
	//全路径枚举
	

	void		DoFileEnumeration(LPCTSTR lpPath,BOOL bRecursion, BOOL bEnumFiles,EnumerateFunc pFunc, void* pUserData);
	
	//通配符枚举
	void		DoFileEnumeration(LPCTSTR lpPath,CSimpleArray<CString>& vec_wildCard ,BOOL bRecursion, BOOL bEnumFiles, EnumerateFunc pFunc, void* pUserData);
	
	//自带类型枚举
	void		DoFileEnumerationEx(LPCTSTR lpPath,CSimpleArray<FILEEXTS_IN>& vec_wildCard ,BOOL bRecursion, BOOL bEnumFiles, EnumerateFuncEx pFunc, void* pUserData);
	
	//枚举文件夹
	void		DoFileFolder(LPCTSTR lpPath,CSimpleArray<CString>& vec_folder,BOOL bRecursion=FALSE,BOOL bFullPath  = TRUE);
	
	//删除空文件夹
	void		DeleteEmptyDirectories(LPCTSTR dir);

	BOOL		DeleteDirectory(LPCTSTR *DirName);
	
	BOOL		ConvetPath(CString& strSourcPath);

	BOOL		s_bUserBreak;
};

#endif //_FILEOPT_H_