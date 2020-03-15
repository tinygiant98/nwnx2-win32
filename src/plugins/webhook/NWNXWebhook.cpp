/***************************************************************************
	NWNXWebhook.cpp: implementation of the CNWNXWebhook class.
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

#pragma warning(disable : 4996)

#include "NWNXWebhook.h"

using namespace std;

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
		return elements;

	int i = 0;
	int k = 0;
	while (i < strleng)
	{
		int j = 0;
		while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
			j++;
		if (j == delleng)
		{
			elements.push_back(str.substr(k, i - k));
			i += delleng;
			k = i;
		}
		else
			i++;
	}
	elements.push_back(str.substr(k, i - k));
	return elements;
}

char* CNWNXWebhook::OnRequest(char* gameObject, char* Request, char* Parameters)
{
	Log(0, "Request: %s\n", Request);
	Log(0, "Parameters: %s\n", Parameters);

	string sRequest = string(Request);
	string sParameters = string(Parameters);

	string fSetDelimiter = "SETDELIMITER";
	string fAddMessageElement = "ADDMESSAGEELEMENT";
	string fBuildMessage = "BUILDMESSAGE";
	string fSetEnclosure = "SETENCLOSURE";
	   
	if (sRequest.find(fSetDelimiter) != string::npos)
	{
		sRequest.erase(sRequest.begin(), sRequest.begin() + fSetDelimiter.length() + 1);
		SetDelimiter(sRequest, sParameters);
	}
	else if (sRequest.find(fAddMessageElement) != string::npos)
		AddMessageElement(sParameters);
	else if (sRequest.find(fBuildMessage) != string::npos)
		BuildWebhookMessage();
	else if (sRequest.find(fSetEnclosure) != string::npos)
	{
		sRequest.erase(sRequest.begin(), sRequest.begin() + fSetEnclosure.length() + 1);
		SetEnclosure(sRequest, sParameters);
	}

	/*
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
*/

	return NULL;
}

BOOL CNWNXWebhook::OnCreate(const char* LogDir)
{
	// call the base class function
	char log[MAX_PATH];
	sprintf(log, "%s\\nwnx_webhook.txt", LogDir);
	if (!CNWNXBase::OnCreate(log))
		return false;

	//strings are exploded based on these delimiters, so having them in passed strings may not be the best idea.
	//Some freedoms/limitations:
	//	the pairDelmiter is only used to exploded key:value pairs, so using the array/element/value delimiter charcters in the value portion should be okay
	//	You should not use any of these characters in the key portion
	SetDelimiter("array", "#");
	SetDelimiter("pair", ";");
	SetDelimiter("element", "!");
	SetDelimiter("value", ":");

	SetEnclosure("object", "{}");
	SetEnclosure("array", "[]");

	WriteLogHeader();
	return true;
}

BOOL CNWNXWebhook::OnRelease()
{
	Log("o Shutting down\n");

	// call base class function
	return CNWNXBase::OnRelease();
}

void CNWNXWebhook::SetDelimiter(string delimiter, string value)
{
	if (delimiter.find("array") != string::npos)
		arrayDelimiter = value;
	else if (delimiter.find("value") != string::npos)
		valueDelimiter = value;
	else if (delimiter.find("element") != string::npos)
		elementDelimiter = value;
	else if (delimiter.find("pair") != string::npos)
		pairDelimiter = value;
}

void CNWNXWebhook::SetEnclosure(string type, string value)
{
	if (type.find("object") != string::npos)
		objectDelimiters = value;
	else if (type.find("array") != string::npos)
		arrayDelimiters = value;
}

void CNWNXWebhook::WriteLogHeader()
{
	Log(0, "NWNX Webhook plugin V.0.2\n");
	Log(0, "(c) 2020 by Edward Burke (tinygiant)\n");
	Log(0, "Visit the Dragon Myrth PW forums at forum.blue-field.dk\n\n");
}

void CNWNXWebhook::AddMessageElement(string Elements)
{
	vector<string> pairs;

	pairs = explode(pairDelimiter, Elements);
	for (auto it = pairs.begin(); it != pairs.end(); ++it)
	{
		messageVector.emplace_back(*it);
		Log(0, "Message element added to vector: %s\n", it->data());
	}
}

string buildValueString(string input)
{
	if (input == "true" || input == "false")
		return input;
	else
		return "\"" + input + "\"";
}

string enclose(string message, string delimiters)
{
	if (delimiters.length() == 2)
		return delimiters.front() + message + delimiters.back();
	else
		return string();
}

string CNWNXWebhook::BuildMessageChunk(string parentToken)

{
	string messageChunk{};

	vector<string> pair;
	vector<string> vectorTokens;
	vector<string> parentTokens;

	for (auto it = messageVector.begin(); it != messageVector.end(); ++it)
	{
		if (*it == replace) 
			continue;
		
		if (!parentToken.empty())
		{
			pair = explode(valueDelimiter, *it);					
			if (pair[0].find(parentToken) != string::npos)
			{
				vectorTokens = explode(elementDelimiter, pair[0]);		
				parentTokens = explode(elementDelimiter, parentToken);	
				if (vectorTokens.size() == parentTokens.size() + 1)
				{
					messageChunk += (messageChunk.size() > 0 ? string(",") : string()) + string("\"") + vectorTokens.back() + string("\":") + buildValueString(pair[1]);
					*it = replace;
				}
			}
		}
		else
		{
			pair = explode(valueDelimiter, *it);
			if (count(pair[0].begin(), pair[0].end(), elementDelimiter.front()) == 0)
			{
				messageChunk += (messageChunk.size() > 0 ? string(",") : string()) + string("\"") + pair[0] + string("\":") + buildValueString(pair[1]);
				*it = replace;
			}
		}
	}

	if (!messageChunk.empty())
		return messageChunk;
	else return string();
}

void CNWNXWebhook::BuildWebhookMessage()
{
	if (messageVector.size() == 0)
	{
		Log(0, "...Mesage Vector is empty, no message created.");
		return;
	}

	vector<string> pair;
	vector<string> keyTokens;

	string fullKey{};
	string partialKey{};
	string targetToken{};

	string sentence{};
	string paragraph{};
	string message{};
	string draft{};
	string payload{};

	for (auto it1 = messageVector.begin(); it1 != messageVector.end(); ++it1)
	{
		if (*it1 == replace) 
			continue;	
		
		pair = explode(valueDelimiter, *it1);
		keyTokens = explode(elementDelimiter, pair[0]);
		if (keyTokens.size() == 1)
			payload = BuildMessageChunk(string()) + (payload.length() > 0 ? string(",") + payload : string());
		else 
		{
			if (pair[0].front() == arrayDelimiter.front())
			{
				partialKey = keyTokens[0];		
				if (isdigit(partialKey.back()))	
					partialKey.pop_back();
				
				targetToken = keyTokens[0].substr(1, keyTokens[0].length() - (isdigit(keyTokens[0].back()) ? 2 : 1));
				for (auto it2 = it1; it2 != messageVector.end(); ++it2)
				{
					if (*it2 == replace) 
						continue;

					pair = explode(valueDelimiter, *it2);
					keyTokens = explode(elementDelimiter, pair[0]);
					if (pair[0].find(partialKey) != string::npos)
					{
						fullKey = keyTokens[0];	
						for (auto it3 = it2; it3 != messageVector.end(); ++it3)
						{
							if (*it3 == replace) 
								continue;

							pair = explode(valueDelimiter, *it3);
							keyTokens = explode(elementDelimiter, pair[0]);
							if (pair[0].find(fullKey) != string::npos)
							{
								if (keyTokens.size() == 3)
								{
									fullKey = pair[0].substr(0, pair[0].find_last_of(elementDelimiter));	
									if (keyTokens[1].front() == arrayDelimiter.front())						
									{
										partialKey = fullKey;	
										if (isdigit(partialKey.back())) 
											partialKey.pop_back();											
										
										for (auto it4 = it3; it4 != messageVector.end(); ++it4)				
										{
											if (*it4 == replace) 
												continue;

											pair = explode(valueDelimiter, *it4);
											if (pair[0].find(partialKey) != string::npos)				
											{																
												fullKey = pair[0].substr(0, pair[0].find_last_of(elementDelimiter));	
												sentence = BuildMessageChunk(fullKey);			
												if (!sentence.empty())
												{
													sentence = enclose(sentence, objectDelimiters);
													paragraph += (paragraph.length() > 0 ? string(",") : string()) + sentence;	
													sentence = string();
												}														
											}
										}
										paragraph = enclose(paragraph, arrayDelimiters);
										paragraph = string("\"") + keyTokens[1].substr(1, keyTokens[1].length() - (isdigit(keyTokens[1].back()) ? 2 : 1)) + string("\":") + paragraph;
										message += (message.length() > 0 ? string(",") : string()) + paragraph;
										paragraph = string();
									}
									else
									{
										paragraph = BuildMessageChunk(fullKey);	
										if (!paragraph.empty())
										{
											paragraph = enclose(paragraph, objectDelimiters);
											paragraph = string("\"") + keyTokens[1] + string("\":") + paragraph;	
											message += (message.length() > 0 ? string(",") : string()) + paragraph;	
											paragraph = string();
										}
									}
								}
								else if (keyTokens.size() == 2)
								{
									message += (message.length() > 0 ? string(",") : string()) + BuildMessageChunk(fullKey);
								}
							}
						}
						message = enclose(message, objectDelimiters);
						draft += (draft.length() > 0 ? string(",") : string()) + message;
						message = string();
					}    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ So need this here when the inner loop is not run

				}			// but down here when it is, but not both at the same time?  Need some serious debugging with some test messages to figure this one out.
				//message = enclose(message, objectDelimiters);
				//draft += (draft.length() > 0 ? string(",") : string()) + message;
				//message = string();
			}
		}
	}
	if (!draft.empty())
	{
		draft = enclose(draft, arrayDelimiters);
		draft = string("\"") + targetToken + string("\":") + draft;
		payload += (payload.length() > 0 ? string(",") : string()) + draft;
		draft = string();
	}

	payload = enclose(payload, objectDelimiters);
	messageVector.clear();

	SendWebhook(payload);
	Log(0, "Created payload: %s\n", payload.data());
}

void CNWNXWebhook::SendWebhook(string message)
{
	string discordurl = "https://discordapp.com/api/webhooks/688525447318994959/XdOaqoj2UaL07G46nBka03ECa5cAQZcopJ5XV4xAtTwRqTh4EqV35k-Je_R32z7jUsNJ";

	CURL* curl;
	CURLcode res;
	struct curl_slist *headers = NULL;

	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		
		headers = curl_slist_append(headers, "Content-Type: application/json");
		
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */
		curl_easy_setopt(curl, CURLOPT_URL, discordurl.c_str());
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str());

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			Log(0, "\nWebhook send failed\n");

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

