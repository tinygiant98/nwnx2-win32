/***************************************************************************
    NWNXReset.h - Interface for the CNWNXReset class.
    Copyright (C) 2005 Fay Smith (Asmodae)
    Copyright (C) 2006, 2012 virusman (virusman@virusman.ru)

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

#if !defined(RESETPLUGIN_H_)
#define RESETPLUGIN_H_

#include <windows.h>
#include "NWNXBase.h"

class CNWNXReset : public CNWNXBase  
{
public:
	CNWNXReset();
	virtual ~CNWNXReset();

	BOOL OnCreate(const char* LogDir);
	char* OnRequest(char *gameObject, char* Request, char* Parameters);
	BOOL OnRelease();

	void WriteLogHeader();
};

#endif

