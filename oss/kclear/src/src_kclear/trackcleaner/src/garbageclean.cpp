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


#include "stdafx.h"
#include "garbageclean.h"

CGarbageClean::CGarbageClean()
{
	m_bScan = TRUE;
}

CGarbageClean::~CGarbageClean()
{

}

//BOOL CGarbageClean::TEST()
//{	
//
//	USERDATA userData;
//	userData.pObject= this;
//
//	userData.iType = REGCLEAN_INVALIDDLL;
//	
//	CSimpleArray<CString> vec_fileExts;
//
//	CString strExts = _T("*.??$");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.tmp");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.~*");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.---");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.^*");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.??~");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.??$");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*._mp");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.temp");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.~mp*");
//	vec_fileExts.Add(strExts);
//	strExts = _T("*.bak");
//	vec_fileExts.Add(strExts);
//	strExts = _T("thumbs.db");
//	vec_fileExts.Add(strExts);
//
//
//	m_fileOpt.DoFileEnumeration(_T("C:\\"),vec_fileExts,TRUE,TRUE,myEnumerateFile,&userData);
//	return TRUE;
//}


BOOL CGarbageClean::ScanGarbageFile(LPCTSTR lpScanPath,CSimpleArray<FILEEXTS_IN>& vec_fileExts_In)
{	
	if (m_bScan ==FALSE)
		return TRUE;
	
	try
	{
		USERDATA userData;
		userData.pObject= this;
		userData.iType = FILEGARBAGE;
	
		if (vec_fileExts_In.GetSize() ==0)
		{	
			FILEEXTS_IN  file;
			file.iType =0;
			file.strFileExts= _T("*.*");

			vec_fileExts_In.Add(file);
		}

		m_fileOpt.DoFileEnumerationEx(lpScanPath,vec_fileExts_In,TRUE,TRUE,myEnumerateFileEx,&userData);		
	}
	catch (...)
	{	
		return FALSE;		
	}

	return TRUE;
}

BOOL CGarbageClean::GarbageFile(int iType,LPCTSTR lpFileOrPath,LARGE_INTEGER filesize)
{	
	if (m_bScan ==FALSE)
		return FALSE;

	return g_fnScanFile(g_pMain,iType,lpFileOrPath,filesize.LowPart,filesize.HighPart);
}

BOOL CGarbageClean::myEnumerateFile(LPCTSTR lpFileOrPath, void* _pUserData,LARGE_INTEGER filesize)
{	
	if (_pUserData ==NULL)
	{
		return TRUE;
	}

	USERDATA* pUserData = (USERDATA*) _pUserData;
	CGarbageClean* pObject = (CGarbageClean*) pUserData->pObject;
	
	return TRUE;
}

BOOL CGarbageClean::myEnumerateFileEx(int iType,LPCTSTR lpFileOrPath, void* _pUserData,LARGE_INTEGER filesize)
{	
	if (_pUserData == NULL)
	{
		return TRUE;
	}

	USERDATA* pUserData = (USERDATA*) _pUserData;
	CGarbageClean* pObject = (CGarbageClean*) pUserData->pObject;

	return pObject->GarbageFile(iType,lpFileOrPath,filesize);;
}

/****************************************************************
* NAME     : strcmpEx
* FUNCTION    : ???????????,*????????????????
* PROCESS    : ??
* INPUT     : str1:????????1????????*,??? 
*        str1:????????????????*,??? 
* OUTPUT    : 
* EXTERN    : ??
* UPDATE    : ??
* RETURN    : 0:??????1:??????????
* PROGRAMMED   : ZhitengLin
* DATE(ORG)    : 2008-10-16
* CALL     : ??
* SYSTEM    : ??
****************************************************************/
TCHAR strcmpEx( const TCHAR *str1, const TCHAR *str2) 
{ 
	size_t slen1 = 0; 
	size_t slen2 = 0; 

	/*????????????????*/
	size_t lbound = 0; 
	size_t upbound = 0; 

	size_t i, j, k;

	/*??????????????strl????????????????????????*/ 
	TCHAR *matchmap = NULL;
	TCHAR cRet;
	size_t maxLen = 0;
	slen1 = wcslen(str1); 
	slen2 = wcslen(str2); 
	maxLen = slen1>=slen2?slen1:slen2;
	maxLen++;
	matchmap = (TCHAR*)malloc(maxLen*maxLen);

	wmemset(matchmap, 0, maxLen*maxLen); 

	/*??????????????????*/
	for(i = 0; i< slen1; ++i) { 
		/*????????????*/
		size_t bMatched = 0; 
		size_t upthis = upbound; 
		for(j = lbound; j<=upthis ; ++j) { 
			/*????????????*/ 
			if(str1[i] == str2[j] || str2[j] == '?') { 
				*(matchmap+i*maxLen+j) = 1; 
				if(0 == bMatched) { 
					lbound = j+1; 
				} 
				upbound = j+1; 
				bMatched = 1; 
				if(i == slen1 - 1){ 
					/*??????????*??????????*/
					for(k = j+1 ; k < slen2 && '*' == str2[k] ; ++k) { 
						*(matchmap+i*maxLen+k) = 1;
					} 
				} 
			}else if(str2[j] == '*') { 
				if(0 == bMatched) { 
					lbound = j; 
				} 
				/*??????????????????????????????????????*/
				for(k = i; k< slen1; ++k) { 
					*(matchmap+k*maxLen+j) = 1;
				} 
				k = j; 
				while( '*' == str2[++k]) { 
					*(matchmap+i*maxLen+k) = 1;
				} 
				if(str1[i] == str2[k] || str2[k] == '?') { 
					*(matchmap+i*maxLen+k) = 1;
					upbound = k+1; 
					if(i == slen1 - 1) { 
						/*??????????*??????????*/
						for(k = k+1 ; k < slen2 && '*' == str2[k] ; ++k){ 
							*(matchmap+i*maxLen+k) = 1;
						} 
					} 
				}else{ 
					upbound = k; 
				} 
				bMatched = 1; 
			} 
		} 
		/*??????????*/
		if(!bMatched ) { 
			free(matchmap);
			return 1; 
		} 
	}
	cRet = *(matchmap+(slen1-1)*maxLen+slen2-1);
	free(matchmap);

	return (cRet==0?1:0); 
}
