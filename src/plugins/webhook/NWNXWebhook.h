/***************************************************************************
    NWNXWebhook.h: interface for the CNWNXWebhook class.
    (c) 2020 by Edward Burke (tinygiant)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***************************************************************************/

#if !defined(NWNXWEBHOOK_H_)
#define NWNXWEBHOOK_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "stdafx.h"
#include "IniFile.h"
#include "NWNXBase.h"
#include <algorithm>
#include <vector>
#include <string>

#define CURL_STATICLIB
#include <curl.h>

#ifdef _DEBUG
#pragma comment (lib, "libcurl_a_debug.lib")
#else
#pragma comment (lib, "libcur_a.lib")
#endif

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

using namespace std;

class CNWNXWebhook : public CNWNXBase
{
public:
    CNWNXWebhook();
    virtual ~CNWNXWebhook();

    BOOL OnCreate(const char* LogDir);
	BOOL OnRelease();
	
	char* OnRequest(char* gameObject, char* Request, char* Parameters);
    
    void WriteLogHeader();
    void SetDelimiter(string delimiter, string value);
    void SetEnclosure(string type, string value);
    void AddMessageElement(string Elements);
    void BuildWebhookMessage();
    void SendWebhook(string message);

    string BuildMessageChunk(string parentToken);
private:
    vector<string> messageVector;

    string pairDelimiter{};
	string valueDelimiter{};
	string arrayDelimiter{};
	string elementDelimiter{};
    string replace = "*****";
    string arrayDelimiters{};
    string objectDelimiters{};


};

#endif

