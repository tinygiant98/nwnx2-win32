/***************************************************************************
    NWNXDemoplugin.cpp: implementation of the CNWNXDemoplugin class.
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

#include "stdafx.h"
#include "NWNXDemoplugin.h"

CNWNXDemoplugin::CNWNXDemoplugin()
{
}

CNWNXDemoplugin::~CNWNXDemoplugin()
{
	OnRelease();
}

char* CNWNXDemoplugin::OnRequest(char *gameObject, char* Request, char* Parameters)
{
	// This assumes you call SetLocalString like this
	// SetLocalString(oObject, "NWNX!DEMOPLUGIN!TESTFUNCTION", "...................................");

	if (Request)
	{
		// This will output "TESTFUNCTION" as request
		Log("* Got request: %s.\n", Request);
	}

	if (Parameters)
	{
		// This is the space where data can be exchanged with NWN
		Log("* Got parameters: %s.\n", Parameters);
		strncpy(Parameters, "THIS IS MY ANSWER TO NWN", strlen (Parameters));
	}

	return NULL;
}

BOOL CNWNXDemoplugin::OnCreate(const char* LogDir)
{
	// call the base class function
	char log[MAX_PATH];
	sprintf (log, "%s\\nwnx_demoplugin.txt", LogDir);
	if (!CNWNXBase::OnCreate(log))
		return false;

	WriteLogHeader();
	return true;
}

BOOL CNWNXDemoplugin::OnRelease()
{
	Log("o Shutting down\n");

	// call base class function
	return CNWNXBase::OnRelease();
}

void CNWNXDemoplugin::WriteLogHeader()
{
	fprintf(m_fFile, "NWNX Demo plugin V.1.1.\n");
	fprintf(m_fFile, "(c) 2005 by Ingmar Stieger (Papillon)\n");
	fprintf(m_fFile, "visit us at http://www.nwnx.org\n\n");
}