Readme for Demo Plugin
======================

This plugin shows how one create a NWNX plugin. It also serves as a starting 
point for new NWNX plugins, since it is the reference implementation all other 
plugins should follow.

The structure of the ZIP file this package comes in should be used for new 
plugin releases: There is some documentation, a changelog, the GPL licence, a 
pre-compiled binary, and the source code in the directory src\. Of course, this 
is only a suggestion which developers might want to follow in order to present a 
coherent release to their users.

You will need the NWNX base package to compile this plugin, since some files it 
depends on are only in that package. The project files are for Visual Studio 6, 
but other versions should be no problem.

The most interesting file is NWNXDemoplugin.cpp and its header file 
NWNXDemoplugin.h. The functionality of your plugin will be implemented in these 
files.

Have fun and do not hesitate to contact me on http://nwnx.org for questions and
suggestions.

Papillon, 10.02.2005
