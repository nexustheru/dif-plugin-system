#include "MonoScript.h"
static int malloc_count = 0;

MonoScript::MonoScript()
{
   
}
string MonoScript::GetEnvironment(const char* variable)
{
    char* buf = nullptr;
    size_t sz = 0;
    _dupenv_s(&buf, &sz, variable);
    return buf;
    free(buf);
}
MonoString* MonoScript::Bark()
{
    return mono_string_new(mono_domain_get(), "Simplecsharp!");
}

void MonoScript::output_methods(MonoClass* klass)
{
    MonoMethod* method;
    void* iter = NULL;

    while ((method = mono_class_get_methods(klass, &iter)))
    {
        UINT32 flags, iflags;
        flags = mono_method_get_flags(method, &iflags);
        printf("Method: %s, flags 0x%x, iflags 0x%x\n",
            mono_method_get_name(method), flags, iflags);
    }
}
void* MonoScript::custom_malloc(size_t bytes)
{
    ++malloc_count;
    return malloc(bytes);
}
QList<MonoClass*> MonoScript::GetAssemblyClassList(MonoImage* image)
{
    QList<MonoClass*> class_list;

    const MonoTableInfo* table_info = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);

    int rows = mono_table_info_get_rows(table_info);

    /* For each row, get some of its values */
    for (int i = 0; i < rows; i++)
    {
        MonoClass* _class = nullptr;
        uint32_t cols[MONO_TYPEDEF_SIZE];
        mono_metadata_decode_row(table_info, i, cols, MONO_TYPEDEF_SIZE);
        const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
        const char* name_space = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
        _class = mono_class_from_name(image, name_space, name);
        class_list.push_back(_class);
    }
    return class_list;
}

bool MonoScript::SimplemonoCs(string filename)
{
    mono_set_dirs("Mono/lib", "Mono/etc");
    mono_config_parse(NULL);
    int retval = 0;
    MonoDomain* domain = mono_jit_init("testlmonocs");
    cout << "check" << std::endl;
    MonoAssembly* assembly = mono_domain_assembly_open(domain, filename.c_str());//or dll or exe sourcefile
    if (!assembly)
    {
        cout << "Can't load assembly" << endl;
        return false;
    }
    cout << "assmbly loaded" << endl;
    MonoImage* image = mono_assembly_get_image(assembly);
    if (!image)
    {
        cout << "Can't load image" << endl;
        return false;
    }
    
    cout << "image loaded" << endl;
    MonoClass* dogClass = mono_class_from_name(image, "MonoTest", "Dog");
    if (!dogClass)
    {
        cout << "Can't load class" << endl;
        return false;
    }
    
    cout << "class loaded" << endl;
    MonoMethodDesc* defaultDesc = mono_method_desc_new("MonoTest.Dog:Bark()", false);
    
    if (!defaultDesc)
    {
        cout << "Can't load description" << endl;
        return false;
    }
    cout << "description loaded" << endl;
    MonoMethod* defaultMethod = mono_method_desc_search_in_class(defaultDesc, dogClass);
    if (!defaultMethod)
    {
        cout << "Can't load method" << endl;
        return false;
    }
    cout << "method loaded" << endl;
    cout << defaultDesc;
    cout << defaultMethod;

    return true;

    mono_jit_cleanup(domain);
}

MonoClass* MonoScript::returnClasses(MonoImage* image)
{
    QList<MonoClass*> netclasses = GetAssemblyClassList(image);
    for (int i = 0; i < netclasses.count(); i++)
    {
        return netclasses.at(i);
     
    }
    return NULL;
}

