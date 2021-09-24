#include "Api.h"

void PluginSystem::create()
{
}

void PluginSystem::OnLoad()
{
}

void PluginSystem::OnClose()
{
}

void PluginSystem::OnUpdate()
{
}

void PluginSystem::OnMain()
{
}

dllexport PluginSystem* NPluginSystem()
{
	return new PluginSystem();
}
