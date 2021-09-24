#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <crtdbg.h>
#include <fstream>
#include <iostream>
#include <shlobj.h>
#include <direct.h>
#include <shlwapi.h>
#include <objbase.h>
#include <shellapi.h>
#include <string>
#include <future>
#include <list>
#include <tchar.h>
#include <vector>
#include <iostream>

#include <QtCore/qdir.h>
#include <QtCore/QFile.h>
#include <QtCore/QFileInfo>
#include <QtCore/QDirIterator>
#include <QtCore/QString>
#include <QtCore/qlist.h>
#include "Api.h"


class PluginHandler
{
public:
	PluginHandler();
	void ScannPlugins();
	std::vector<std::unique_ptr<PluginSystem>> getPlugins(std::vector<HINSTANCE>& modules);

private:
	QList<QString> PluginFiles;
	QString retriveDLL();
};

