#pragma once

#include <iostream>

#include <QtCore/qdir.h>
#include <QtCore/QFile.h>
#include <QtCore/QFileInfo>
#include <QtCore/QDirIterator>
#include <QtCore/QString>
#include <QtCore/qlist.h>


#include "MonoScript.h"
#include "LuaScript.h"



class ScriptHandler
{
public:
	ScriptHandler();
	void ExecuteLua(QString filename);
	void ExecuteMono(QString filename);
	void ExecuteDll(QString filename);
	void ExecuteLuaModule(QString filename);
	void CompileRaw();
	QStringList* getCompiled();
	QStringList* getRaw();
private:
	string ScriptFolder  = "Scripts\\";
	QStringList* Scriptnames;
	QStringList* ScriptnamesCompiled;
	void Scannfolder();
	MonoScript* mscript ;
	LuaScript* lscript ;
};

