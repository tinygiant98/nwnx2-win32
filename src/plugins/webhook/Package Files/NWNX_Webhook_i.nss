// Name     : NWNX_Webhook_i
// Purpose  : Include file for NWNX Webhook plugin
// Authors  : Edward Burke (tinygiant)
// Modified : 20200305

// This file is licensed under the terms of the
// GNU GENERAL PUBLIC LICENSE (GPL) Version 2

// Some of the following code was shamelessly stolen or modeled from the
//  NWNX:EE implmentation of webhook.  It has been modified heavily (or
//  in some cases, slightly, or not at all!) to fit within the more limited
//  construct/implementation of NWNX2.

//The payloads sent to slack and discord (and other services that will acccept
//  basic webhook messages) are typically json and contain many elements.  The
//  variaous elements generally are not required to be in a particular order as
//  long as they contain the appropriate minimum requirements.

//An element includes an identifier and a value.  Because the elements can be
//  sent to the plug-in in any order, parent/child relationships must be established
//  when the elements are added.  This is done throught the use of text delimiters.
//  Elements that have no descendants do not require delimiters.

//Example (no descendants):  username                :: AddMessageElement("username", "value");
//                           embed color             :: AddMessageElement("#embeds1!color", "value");
//                           embed field description :: AddMessageElement("#embeds1!#fields1!description", "value"); 

//The ! delimiter (in this example) tells the plug-in that this is a parent-child relationship.
//The # delimiter (in this example) tells the plug-in that this should be an array element.
//You can modify the delimiters by setting the appropriate constants below and then sending them
//  to the plug-in via SetMessageDelimiters(). 

#include "NWNX_Webhook_c"

const string WEBHOOK_DELIMITER_ELEMENT = "!";
const string WEBHOOK_DELIMITER_ARRAY = "#";

const string WEBHOOK_DESTINATION_DISCORD = "discordapp.com";
const string WEBHOOK_DESTINATION_SLACK = "";

const string WH_COLOR_DEFAULT = "0";
const string WH_COLOR_GREEN = "3066993";
const string WH_COLOR_RED = "15158332";
const string WH_COLOR_BLUE = "3447003";
const string WH_COLOR_PURPLE = "10181046";
const string WH_COLOR_ORANGE = "15105570";
const string WH_COLOR_GREY = "9807270";
const string WH_COLOR_GOLD = "15844367";
const string WH_COLOR_AQUA = "1752220";
const string WH_COLOR_NAVY = "3426654";

void wh_SetMessageDelimiters()
{
    SetLocalString(GetModule(), "NWNX!WEBHOOK!SETELEMENTDELIMITER", WEBHOOK_DELIMITER_ELEMENT);
    SetLocalString(GetModule(), "NWNX!WEBHOOK!SETARRAYDELIMITER", WEBHOOK_DELIMITER_ARRAY);

    DeleteLocalString(GetModule(), "NWNX!WEBHOOK!SETELEMENTDELIMITER");
    DeleteLocalString(GetModule(), "NWNX!WEBHOOK!SETARRAYDELIMITER");
}

void AddMessageElements(string elements, string value);
{
    SetLocalString("NWNX!WEBHOOK!ADDMESSAGEELEMENT!" + elements, value);
}

void SendWebhook()
{
    SetLocalString("NWNX!WEBHOOK!SENDWEBHOOK");
}