#include <exception>
#include <iostream>

#include "ScriptHandler.h"
#include "PluginHandler.h"

#include <QtWidgets/qapplication.h>

#include "Container.h"

typedef void* (__cdecl* OnMain)(void);

using namespace std;
int main(int argc, char* argv[])
{  
    try
    {   
        cout << "Initializing the ScriptSystem" << endl;
        ScriptHandler* shandle = new ScriptHandler();
        for (int i = 0; i < shandle->getCompiled()->count(); i++)
        {
            shandle->ExecuteDll(shandle->getCompiled()->at(i));
        }
        for (int i = 0; i < shandle->getRaw()->count(); i++)
        {
            if (shandle->getRaw()->at(i).contains(".lua"))
            {
               QString module=shandle->getRaw()->at(i);
               if (module.contains("module"))
               {
                shandle->ExecuteLuaModule(shandle->getRaw()->at(i));
               }
               else
               {
                shandle->ExecuteLua(shandle->getRaw()->at(i));
               }

            }
                
        }
       cout << "Initializing the PluginSystem" << endl;   
       PluginHandler* phandle = new PluginHandler();
       std::vector<HINSTANCE> modules;
       std::vector<std::unique_ptr<PluginSystem>> objs;
       objs = phandle->getPlugins(modules);
      
       for (auto& x : objs)
       {
           x->OnMain();
           x->create();
           x->OnLoad();
           x->OnUpdate();
           x->OnMain();
       }
       std::cout << "Initializing OpenGlSystem" << std::endl;
       glutInit(&argc, argv);
       QApplication a(argc, argv);

       Container OpenglApp;
       OpenglApp.show();
       return a.exec();
    }
    catch (exception* err)
    {
        cout << err->what();
    }

    system("pause");
}