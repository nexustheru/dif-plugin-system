#include "ScriptHandler.h"

ScriptHandler::ScriptHandler()
{

	Scriptnames=new QStringList();
	ScriptnamesCompiled = new QStringList();
	Scannfolder();
}

void ScriptHandler::ExecuteLua(QString filename)
{
	lscript = new LuaScript();
	lscript->simplefunction(filename.toStdString());
}
void ScriptHandler::ExecuteLuaModule(QString filename)
{
	lscript = new LuaScript();
	lscript->simplemodule(filename.toStdString());
}

void ScriptHandler::CompileRaw()
{
	system("compile.bat");
}

void ScriptHandler::ExecuteMono(QString filename)
{
	mscript = new MonoScript();
	mscript->SimplemonoCs(filename.toStdString());
}
void ScriptHandler::ExecuteDll(QString filename)
{
	mscript = new MonoScript();
	mscript->SimplemonoCs(filename.toStdString());
}

QStringList* ScriptHandler::getCompiled()
{
	return ScriptnamesCompiled;
}

QStringList* ScriptHandler::getRaw()
{
	return Scriptnames;
}

void ScriptHandler::Scannfolder()
{
	QDir scriptDir(QString::fromStdString(ScriptFolder));
	QStringList scripts = scriptDir.entryList(QStringList() << "*.vb" << "*.cs" << "*.dll" << "*.lua",QDir::Files);
	foreach(QString filename, scripts)
	{
		if (filename.contains(".dll"))
		{
			ScriptnamesCompiled->append("Scripts\\" + filename);
		}
		else
		{
		   Scriptnames->append("Scripts\\" + filename);
		}

	}
	std::cout << "done";
}