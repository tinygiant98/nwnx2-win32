/***************************************************************************
    NWNX FOR LINUX SortSet plugin Class
    Copyright (C) 2004 John Klar (paladin at projectplasma dot com)

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

#include <stdio.h>

#include "stdafx.h"
#include "NWNXSortSet.h"

CNWNXSortSet::CNWNXSortSet() {
}

CNWNXSortSet::~CNWNXSortSet() {
}

BOOL CNWNXSortSet::OnCreate(const char *LogDir)
{
	char log[128];
	sprintf (log, "%s/nwnx_sortset.txt", LogDir);

	// call the base class function
	if (!CNWNXBase::OnCreate(log))
		return false;

	// spelunk nwnx2.ini for a connection section
	if (!Configure())
		return false;

	return true;
}


char *CNWNXSortSet::GetNextArg(char *start, char *dest, int width) {
	char *pos;
	int len;
	if((pos=strchr(start,'!'))!=NULL) {
		len= pos-start;
		++pos;
	} else {
		len= strlen(start);
	}
	if(len>width) len=width;
	strncpy(dest, start, len);
	dest[len]=0;

	return pos;
}

char *CNWNXSortSet::OnRequest(char *gameObject, char *SetName, char* Parameters) {
	char setkey[32], name[22], cmd[32], arg1[32], arg2[32], arg3[32], *lastarg, *pos;


	arg1[0]=0;
	arg2[0]=0;
	arg3[0]=0;

	// Request should be the name: "ARMOR"
	// Parameters are the call "ADD!value", "GET!15", "LENGTH", etc.
	
	GetNextArg(SetName, name, 22);
	results = Parameters;

	Log("SetName: %s\n",SetName);
	Log("Params : %s\n",Parameters);

	sprintf(setkey,"%08x-%s",gameObject,name);

	Log("key=%s\n",setkey);
	
	lastarg= Parameters;
	if((pos=GetNextArg(Parameters, cmd, 31))!=NULL) {
		lastarg= pos;
		if((pos=GetNextArg(pos, arg1, 31))!=NULL) {
			lastarg= pos;
			if((pos=GetNextArg(pos, arg2, 31))!=NULL) {
				lastarg= pos;
				if((pos=GetNextArg(pos, arg3, 31))!=NULL) {
					lastarg= pos;
				}
			}
		}
	}

	Log("key=%s cmd=%s arg1=%s arg2=%s arg3=%s last='%s'\n",setkey,cmd,arg1,arg2,arg3,lastarg);

	if(strcmp("INIT",cmd)==0) {
		SetInit(setkey);
	} else
	if(strcmp("EXISTS",cmd)==0) {
		Exists(setkey,arg1);
	} else
	if(strcmp("LENGTH",cmd)==0) {
		Length(setkey);
	} else
	if(strcmp("ADD",cmd)==0) {
		Add(setkey,arg1,arg2,arg3);
	} else
	if(strcmp("SETBYIDX",cmd)==0) {
		SetByIdx(setkey,arg1,arg2,arg3);
	} else
	if(strcmp("SETBYTAG",cmd)==0) {
		SetByTag(setkey,arg1,arg2,arg3);
	} else
	if(strcmp("REMOVE",cmd)==0) {
		Remove(setkey,arg1);
	} else
	if(strcmp("GETBYIDX",cmd)==0) {
		GetByIdx(setkey,arg1);
	} else
	if(strcmp("GETBYTAG",cmd)==0) {
		GetByTag(setkey,arg1);
	} else
	if(strcmp("SORT",cmd)==0) {
		Sort(setkey);
	} else {
		sprintf(Parameters, "[%s] bad command", cmd);
		Log("[%s] %s\n",setkey,Parameters);
	}

	return NULL;
}

bool CNWNXSortSet::Configure() {

	/*
	// if(nwnxConfig->exists("MNX")) {
		srvcname = "localhost"; // (char*)((*nwnxConfig)["MNX"]["service"].c_str());
		hostport = "localhost:1302"; // (char*)((*nwnxConfig)["MNX"]["hostname"].c_str());

		// this shouldn't cause a fatal error, so 
		// we don't care about the return code
		ClientInit(srvcname,hostport);
	// }
	*/

	return true;
}

bool CNWNXSortSet::SetInit(const char *setkey) {
	sets[setkey];
	return true;
};

bool CNWNXSortSet::Length(const char *setkey) {
	sprintf(results,"%d",sets[setkey].Length());
	return true;
};

bool CNWNXSortSet::Add(const char *setkey, const char *key, const char *sort, const char *value) {
	sprintf(results,"%d",sets[setkey].Add(key,sort,value));
	return true;
};

bool CNWNXSortSet::SetByIdx(const char *setkey, const char *index, const char *sort, const char *value) {
	int idx = atol(index);
	sprintf(results,"%d",sets[setkey].Set(idx,sort,value));
	return true;
};

bool CNWNXSortSet::SetByTag(const char *setkey, const char *resref, const char *sort, const char *value) {
	ssElement *sptr = sets[setkey].Get(resref);
	if(sptr!=NULL) {
		sptr->sort = sort;
		sptr->value = value;
	}
	sprintf(results,"%d", sptr==NULL?-1:0);
	return true;
};

bool CNWNXSortSet::Remove(const char *setkey, const char *index) {
	int idx = atol(index);
	sprintf(results,"%d",sets[setkey].Remove(idx));
	return true;
};

bool CNWNXSortSet::GetByIdx(const char *setkey, const char *index) {
	int idx = atol(index);

	Log("Calling SortSet::Get(%d);\n",idx);

	ssElement *sptr = sets[setkey].Get(idx);

	Log("Returned 0x%08x from SortSet::Get(%d);\n",sptr,idx);

	if(sptr == NULL) {
		results[0]= 0;
		return false;
	}

	Log("key=%s sort=%s value=%s\n",
		sptr->key.c_str(),
		sptr->sort.c_str(),
		sptr->value.c_str());

	sprintf(results,"%s!%s!%s",
		sptr->key.c_str(),
		sptr->sort.c_str(),
		sptr->value.c_str());

	return true;
};

bool CNWNXSortSet::GetByTag(const char *setkey, const char *resref) {
	ssElement *sptr = sets[setkey].Get(resref);

	if(sptr == NULL) {
		results[0]= 0;
		return false;
	}
	
	sprintf(results,"%s!%s!%s",
		sptr->key.c_str(),
		sptr->sort.c_str(),
		sptr->value.c_str());
	return true;
};

bool CNWNXSortSet::Exists(const char *setkey, const char *resref) {
	sprintf(results,"%d",sets[setkey].Exists(resref)?1:0);
	return true;
};

bool CNWNXSortSet::Sort(const char *setkey) {
	sets[setkey].Sort();
	return true;
};
