// Name     : NWNX_Webhook_i
// Purpose  : Include file for NWNX Webhook plugin
// Authors  : Edward Burke (tinygiant)
// Modified : 20200305

// This file is licensed under the terms of the
// GNU GENERAL PUBLIC LICENSE (GPL) Version 2

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

struct WebHook_Message {
    string Username = WH_DEFAULT_USERNAME;
    string Content; ///< https://birdie0.github.io/discord-webhooks-guide/structure/content.html
    string AvatarURL = WH_DEFAULT_AVATARURL;
    string EmbedColor; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/color.html
    string EmbedAuthor; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/author.html
    string EmbedAuthorURL; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/author.html
    string EmbedAuthorIconURL; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/author.html
    string EmbedTitle; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/title.html
    string EmbedURL; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/url.html
    string EmbedDescription; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/description.html
    string EmbedThumbnailURL; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/thumbnail.html
    string EmbedImageURL; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/image.html
    string EmbedFooterText; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/footer.html
    string EmbedFooterIconURL; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/footer.html
    int Timestamp; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/timestamp.html
    string Field1Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field1Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field1Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field2Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field2Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field2Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field3Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field3Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field3Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field4Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field4Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field4Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field5Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field5Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field5Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field6Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field6Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field6Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field7Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field7Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field7Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field8Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field8Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field8Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field9Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field9Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field9Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field10Name; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    string Field10Value; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
    int Field10Inline; ///< https://birdie0.github.io/discord-webhooks-guide/structure/embed/fields.html
};

string IntToBoolString(int iBool)
{
    return iBool == 0 ? "false" : "true";
}

//Determines whether the minimum values have been set in the struct Webhook_Message variable stMessage
int wh_IsChunkValid(int ChunkType, struct Webhook_Message stMessage)
{
    switch (ChunkType)
    {
        case WH_CHUNK_INTRO:
            if (stMessage.UserName != "" && stMessage.Content != "") return TRUE;
        case WH_CHUNK_EMBED:
            if (stMessage.EmbedDescription != "") return TRUE;
        case WH_CHUNK_FOOTER:
            if (stMessage.FooterText != "") return TRUE;
        default:
            return FALSE;
    }  
}

string wh_CreateMessageFields(struct Webhook_Message stMessage)
{
    // Fields to handle
    if (stMessage.sField1Name != "")
    {
        message = message + ",\"fields\": [";
        message = message + "{\"name\": \"" + stMessage.Field1Name + "\",\"value\": \"" + stMessage.Field1Value + "\",\"inline\": " + IntToBoolString(stMessage.Field1Inline) + "}";
        if (stMessage.Field2Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field2Name + "\",\"value\": \"" + stMessage.Field2Value + "\",\"inline\": " + IntToBoolString(stMessage.Field2Inline) + "}";
        if (stMessage.Field3Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field3Name + "\",\"value\": \"" + stMessage.Field3Value + "\",\"inline\": " + IntToBoolString(stMessage.Field3Inline) + "}";
        if (stMessage.Field4Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field4Name + "\",\"value\": \"" + stMessage.Field4Value + "\",\"inline\": " + IntToBoolString(stMessage.Field4Inline) + "}";
        if (stMessage.Field5Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field5Name + "\",\"value\": \"" + stMessage.Field5Value + "\",\"inline\": " + IntToBoolString(stMessage.Field5Inline) + "}";
        if (stMessage.Field6Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field6Name + "\",\"value\": \"" + stMessage.Field6Value + "\",\"inline\": " + IntToBoolString(stMessage.Field6Inline) + "}";
        if (stMessage.Field7Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field7Name + "\",\"value\": \"" + stMessage.Field7Value + "\",\"inline\": " + IntToBoolString(stMessage.Field7Inline) + "}";
        if (stMessage.Field8Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field8Name + "\",\"value\": \"" + stMessage.Field8Value + "\",\"inline\": " + IntToBoolString(stMessage.Field8Inline) + "}";
        if (stMessage.Field9Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field9Name + "\",\"value\": \"" + stMessage.Field9Value + "\",\"inline\": " + IntToBoolString(stMessage.Field9Inline) + "}";
        if (stMessage.Field10Name != "")
            message = message + ",{\"name\": \"" + stMessage.Field10Name + "\",\"value\": \"" + stMessage.Field10Value + "\",\"inline\": " + IntToBoolString(stMessage.Field10Inline) + "}";
        // Close fields array
        message = message + "]";
    }
    else return "";
}

string wh_BuildMessage(struct Webhook_Message stMessage = "", sDestinationHost = "", sDestinationPath = "", int UseMarkDown = TRUE)
{
    string sPayload = "";
    string sMessageChunk;

    //Setup default destination if it wasn't passed.
    if (sDestinationHost == "") sDestinationHost = WEBHOOK_DESTINATION_DISCORD;

    //Let's start with the message prefix, this includes username, avatar, content
    if (wh_IsChunkValid(WH_CHUNK_INTRO, stMessage))
    {
        sMessageChunk = "{\"username\":\""  + stMessage.UserName  + "\"," +
                        stMessage.AvatarURL != "" ? "\"avatar_url\":\"" + stMessage.AvatarURL + "\"" : "" +
                        ",\"content\":\""    + stMessage.Text      + "\"";
        sPayLoad += sMessageChunk;
    }
    else return "";

    if (wh_IsChunkValid(WH_CHUNK_EMBED, stMessage))
    {
        sPayload += ",\"embeds\":[{";

        if (stMessage.EmbedAuthor != "")
        {
            sMessageChunk = "\"name\":\"" + stMessage.EmbedAuthor + "\"," +
                            stMessage.EmbedAuthorURL != "" ? ",\"url\":\"" + stMessage.EmbedAuthorURL + "\"," : "" +
                            stMessage.EmbedAuthorIconURL != "" ? ",\"icon_url\":\"" + stMessage.EmbedAuthorIconURL + "\"" : "";
            sPayload += "\"author\":{" + sMessageChunk + "}"
        }

        sMessageChunk = stMessage.EmbedTitle != "" ? "\"title\":\"" + stMessage.EmbedTitle + "\"," : "" +
                        stMessage.EmbedURL != "" ? "\"url\":\"" + stMessage.EmbedURL + "\"," : "" +
                        "\"description\":\"" + stMessage.EmbedDescription + "\"" +
                        stMessage.EmbedColor != "" ? ",\"color\":\"" + stMessage.EmbedColor + "\"" : "";
        sPayload += sMessageChunk;

        sMessageChunk = wh_CreateMessageFields(stMessage);
        if (GetStringLength(sMessageChunk) > 0)
            sPayload += "," + sMessageChunk;

        sMessageChunk = stMessage.EmbedThumbnailURL != "" ? "\"thumbnail\":{"\"url\":\"" + stMessage.EmbedThumbnailURL + "\"}" : "" +
                        stMessage.EmbedImageURL != "" ? "\"image\":{"\"url\":\"" + stMessage.EmbedImageURL + "\"}" : "";

        if (sMessageChunk != "")
            sPayload += "," + sMessageChunk;

        if (wh_IsChunkValid(WH_CHUNK_FOOTER, stMessage)
            sMessageChunk = "\"footer\":{\"text\":\"" + stMessage.FooterText + "\"" +
            stMessage.FooterIconURL != "" ? "\"icon_url\":\"" + stMessage.FooterIconURL + "\"" : "";

        sPayload += "," + sMessageChunk + "}}]}";
    }

    return sPayload;
}
