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

#include "NWNXBase.h"
#include <string>
#include <unordered_map>

#if _MSC_VER > 1000
#pragma once
#endif

class CNWNXWebhook : public CNWNXBase
{
public:
    CNWNXWebhook();
    virtual ~CNWNXWebhook();

    BOOL OnCreate(const char* LogDir);
    char* OnRequest(char* gameObject, char* Request, char* Parameters);

    void LoadConfiguration();
    BOOL OnRelease();
    void WriteLogHeader();
    void AddMessageElement(char* Element, char* Value);
    std::string BuildMessageChunk(std::string parentToken);
    std::string BuildWebhookMessage();
    void SetArrayTokens(char* Parameters);

private:
    std::string Payload{};

    const char cDelimiter = '!';
    std::string sDelimiter = std::string(1, cDelimiter);


   // const char elementDelimiter = '!';
    //std::string elementDelimiter = "!";
    std::unordered_map<std::string, std::string> messageMap;
    std::string arrayTokens{};
};

#endif

