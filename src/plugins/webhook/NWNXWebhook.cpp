/***************************************************************************
	NWNXWebhook.cpp: implementation of the CNWNXWebhook class.
	(c) 2005 by Ingmar Stieger (Papillon)

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

#pragma warning(disable : 4996)

#include "stdafx.h"
#include "NWNXWebhook.h"
#include "IniFile.h"
#include <algorithm>
#include <vector>

using namespace std;

struct vectorComparator
{
	bool operator ()(const string& string1, const string& string2)
	{
		//if (count(begin(string1), end(string1), "!") < count(begin(string2), end(string2), "!") + 1)
		//	return string1 < string2;
		return string1 < string2;
	}
};

CNWNXWebhook::CNWNXWebhook()
{
	confKey = "WEBHOOK";
}

CNWNXWebhook::~CNWNXWebhook()
{
	OnRelease();
}

vector<string> explode(const string& delimiter, const string& str)
{
	vector<string> elements;

	int strleng = str.length();
	int delleng = delimiter.length();
	if (delleng == 0)
		return elements;//no change

	int i = 0;
	int k = 0;
	while (i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng)//found delimiter
		{
			elements.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else
		{
			i++;
		}
	}
	elements.push_back(str.substr(k, i - k));
	return elements;
}

char* CNWNXWebhook::OnRequest(char* gameObject, char* Request, char* Parameters)
{
	// This assumes you call SetLocalString like this
	// SetLocalString(oObject, "NWNX!WEBHOOK!TESTFUNCTION", "...................................");

/*
	if (strncmp(Request, "POST", 4) == 0)
		Execute(Parameters);
	else if (strncmp(Request, "ISLOADED", 8) == 0)
		Fetch(Parameters, strlen(Parameters));
	else if (strncmp(Request, "XXXX", 12) == 0)
		SetScorcoSQL(Parameters);
	else if (strncmp(Request, "YYYY", 7) == 0)
		GetHash(Parameters);

	return NULL;
*/

	if (Request)
	{
		// This will output "TESTFUNCTION" as request
		Log("* Got request: %s.\n", Request);
	}

	if (Parameters)
	{
		// This is the space where data can be exchanged with NWN
		Log("* Got parameters: %s.\n", Parameters);
		strncpy(Parameters, "THIS IS MY ANSWER TO NWN", strlen(Parameters));
	}

	return NULL;
}

BOOL CNWNXWebhook::OnCreate(const char* LogDir)
{
	// call the base class function
	char log[MAX_PATH];
	sprintf(log, "%s\\nwnx_webhook.txt", LogDir);
	if (!CNWNXBase::OnCreate(log))
		return false;

	LoadConfiguration();
	WriteLogHeader();
	return true;
}

BOOL CNWNXWebhook::OnRelease()
{
	Log("o Shutting down\n");

	// call base class function
	return CNWNXBase::OnRelease();
}

/*void CNWNXWebhook::PostWebhook(Parameters)
{





}*/

void CNWNXWebhook::LoadConfiguration()
{
	//CIniFile iniFile("nwnx.ini");

	// read log file setting
	//m_LogLevel = iniFile.ReadLong(confKey, "LogLevel", 0);
//	if (!m_LogLevel) m_LogLevel = debuglevel;
	//iniFile.ReadString(confKey, "webhook_target", servScript, 17, "server_script");

	/*if (m_LogLevel > 0)
	{
		fprintf(m_fFile, "Settings:\n");
		fprintf(m_fFile, "chat_script: %s\n", chatScript);
		fprintf(m_fFile, "server_script: %s\n", servScript);
		fprintf(m_fFile, "max_msg_len: %d\n", maxMsgLen);
		fprintf(m_fFile, "processnpc: %d\n", processNPC);
		fprintf(m_fFile, "ignore_silent: %d\n\n", processNPC);
	}*/
}

void CNWNXWebhook::WriteLogHeader()
{
	Log(0, "NWNX Webhook plugin V.0.1\n");
	Log(0, "(c) 2020 by Edward Burke (tinygiant)\n");
	Log(0, "Visit the Dragon Myrth PW forums at forum.blue-field.dk\n\n");
}

void CNWNXWebhook::SetArrayTokens(char* Parameters)
{
	arrayTokens = Parameters;
}

void CNWNXWebhook::AddMessageElement(char* Request, char* Parameters)
{
	messageMap.emplace(Request, Parameters);
}

string buildParentToken(vector<string> elements, string elementDelimiter)
{
	string result{};
	
	if (elements.size() == 1)
		return "";
	else
	{
		for (int i = 1; i = elements.size() - 1; i++)
		{
			result = elements[i] + (i == elements.size() - 1 ? "" : elementDelimiter);
		}
		return result;
	}
}

string buildValueString(string input)
{
	if (input == "true" || input == "false")
		return input;
	else
		return '\"' + input + '\"';
}

string CNWNXWebhook::BuildMessageChunk(string parentToken)
{
	string messageChunk{};
	vector<string> tokens;

	for (auto it = messageMap.begin(); it != messageMap.end(); ++it)
		if (it->first.find(parentToken) != string::npos && 
			count(it->first.begin(), it->first.end(), elementDelimiter) == count(parentToken.begin(), parentToken.end(), elementDelimiter) + 1)
		{
			tokens = explode(elementDelimiter, it->first);
			messageChunk += (messageChunk.size() > 0 ? "," : "") + '\"' + tokens[tokens.size()] + "\":" + buildValueString(it->second);
			messageMap.erase(it);
		}

	messageChunk = '{' + messageChunk + '}';

	if (arrayTokens.find(tokens[tokens.size() - 1]) != string::npos)
		messageChunk += '\"' + tokens[tokens.size() - 1] + "\":[" + messageChunk + ']';
	else messageChunk += '\"' + tokens[tokens.size() - 1] + "\":" + messageChunk;

	return messageChunk;
}

string CNWNXWebhook::BuildWebhookMessage()
{
	vector<string> orderedKeys;
	string payload{};
	string message{};

	//create a vector and sort the keys so we can access a little more quickly.
	orderedKeys.reserve(messageMap.size());
	for (auto& it : messageMap) {orderedKeys.push_back(it.first);}
	sort(orderedKeys.begin(), orderedKeys.end(), vectorComparator());

	for (auto it = orderedKeys.begin(); it != orderedKeys.end(); ++it)
	{
		Log(0, *it);
	}
	/*

	//iterate through the sorted vector and build the appropriate message segments.
	for (auto it = messageMap.begin(); it != messageMap.end(); ++it)
	{
		if (count(it->first.begin(), it->first.end(), elementDelimiter) == 2);  //replace with loop counter
		string parentToken = buildParentToken(explode(it->first, elementDelimiter), elementDelimiter);

		message = BuildMessageChunk(parentToken);

	}

	*/
}


