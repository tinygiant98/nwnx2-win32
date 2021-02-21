/***************************************************************************
    Chat plugin for NWNX - Entry point for the DLL application.
    (c) 2005,2006 dumbo (dumbo@nm.ru)
    (c) 2006-2007 virusman (virusman@virusman.ru)
    
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

#include "stdafx.h"
#include "NWNXChat.h"

CNWNXChat chat;
extern "C" __declspec(dllexport) CNWNXBase* GetClassObject()
{
	return &chat;
}

BOOL APIENTRY DllMain (HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}