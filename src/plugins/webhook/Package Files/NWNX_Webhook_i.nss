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

#include "NWNX_Webhook_c"

const string WEBHOOK_DESTINATION_DISCORD = "discordapp.com";
const string WEBHOOK_DESTINATION_SLACK = "";

const int WH_CHUNK_INTRO = 1;
const int WH_CHUNK_EMBED = 2;
const int WH_CHUNK_FOOTER = 3;

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

void AddMessageElements(string elements, string value);
{
    SetLocalString("NWNX!WEBHOOK!ADDELEMENTS!" + elements, value);
}

void SendWebhook()
{
    SetLocalString("NWNX!WEBHOOK!SENDWEBHOOK");
}