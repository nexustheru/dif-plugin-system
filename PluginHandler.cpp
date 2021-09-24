#include "PluginHandler.h"

void PluginHandler::ScannPlugins()
{

	QDir PluginDir(QString::fromStdString("Plugins\\"));
	QStringList plugins = PluginDir.entryList(QStringList() << "*.dll", QDir::Files);
	foreach(QString filename, plugins)
	{
		if (filename.contains(".dll"))
		{
			QString fname = "Plugins\\" + filename;
			
			PluginFiles.push_back(fname);
		}

	}
}

PluginHandler::PluginHandler()
{
	ScannPlugins();
}

QString PluginHandler::retriveDLL()
{
	for (int i = 0; i < PluginFiles.count(); i++)
	{
		return PluginFiles.at(i);
	}
	return NULL;
}

std::vector<std::unique_ptr<PluginSystem>> PluginHandler::getPlugins(std::vector<HINSTANCE>& modules)
{
	std::vector<std::unique_ptr<PluginSystem>> ret;
	modules.clear();
	string fname=retriveDLL().toStdString();
	std::wstring stemp = std::wstring(fname.begin(), fname.end());
	LPCWSTR sw = stemp.c_str();

	auto mod = LoadLibrary(sw);
	if (mod == NULL)
	{
		auto err = GetLastError();
		std::cout << "cant load plugin ErrorCode:" << err << std::endl;
		FreeLibrary(mod);
		
	}
	else
	{
       typedef std::unique_ptr<PluginSystem>(__cdecl* ObjProc)(void);
	   typedef std::string(__cdecl* NameProc)(void);

	   ObjProc objFunc = (ObjProc)GetProcAddress(mod, "?getObj@@YA?AV?$unique_ptr@VPluginSystem@@U?$default_delete@VPluginSystem@@@std@@@std@@XZ");
	   NameProc nameFunc = (NameProc)GetProcAddress(mod, "?getName@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
	   cout << nameFunc << " is loaded" << endl;
	   ret.push_back(objFunc());
	   modules.push_back(mod);
	}
	return ret;
}
