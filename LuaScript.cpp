#include "LuaScript.h"

bool Compiled;
lua_Debug info;
int level = 0;

LuaScript::LuaScript()
{
}
void LuaScript::debug(lua_State* state)
{
    while (lua_getstack(state, level, &info))
    {
        lua_getinfo(state, "nSl", &info);
        fprintf(stderr, "  [%d] %s:%d -- %s [%s]\n",
            level, info.short_src, info.currentline,
            (info.name ? info.name : "<unknown>"), info.what);
        ++level;
    }
}
bool LuaScript::Checkstate(bool status, lua_State* state)
{
    if (status != LUA_OK)
    {
        debug(state);
        const char* message = lua_tostring(state, -1);
        puts(message);
        lua_pop(state, 1);
        Compiled = false;
        return 1;
    }
    else
    {
        Compiled = true;
        return 0;
    }

}
lua_State* LuaScript::loadfileLua(const char* filename)
{
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);
    int result;
    result = luaL_loadfile(state, filename);
    bool res = Checkstate(result, state);
    if (res == LUA_OK)
    {
        result = lua_pcall(state, 0, LUA_MULTRET, 0);
        return state;
    }
    return NULL;
}
void LuaScript::simplemodule(string filename)
{
    lua_State* state1 = luaL_newstate();
    luaL_openlibs(state1);
    bool res = luaL_dofile(state1,filename.c_str());
    if (res == LUA_OK)
    {
        lua_setglobal(state1, "mymodule");
        lua_settop(state1, 0);
        lua_getglobal(state1, "mymodule");
        lua_getfield(state1, -1, "sayhello");
        lua_call(state1, 0, 0);
    }

    lua_close(state1);
}
void LuaScript::simplefunction(string filename)
{
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);
    state = loadfileLua(filename.c_str());

    if (Compiled == true)
    {
        lua_getglobal(state, "sayhello");
        lua_call(state, 0, 0);
        lua_pop(state, 0);
    }
    lua_close(state);
}

