
/***************************************************************************
    NWNXTMI.h - Interface for the CNWNXTMI class.
    Copyright (C) 2008 David Strait (addicted2rpg)  (duckbreath@yahoo.com)


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

#if !defined(NWNXTMIX_H_)
#define NWNXTMIX_H_

#if _MSC_VER > 1000
#pragma once
#endif

#if _MSC_VER < 1900 
#define snprintf _snprintf
#endif

#include "StdAfx.h"
#include "IniFile.h"
#include "NWNXBase.h"

class CNWNXTMIX : public CNWNXBase
{
public:
    CNWNXTMIX();
    virtual ~CNWNXTMIX();

    BOOL OnCreate(const char* LogDir);
    char* OnRequest(char* gameObject, char* Request, char* Parameters);

    void WriteLogHeader();

protected:
    void GetTMILimit(char* value);
    void SetTMILimit(char* value);

private:
    unsigned long orig_TMI;
};

#endif

