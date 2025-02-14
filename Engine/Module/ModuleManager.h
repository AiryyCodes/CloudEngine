#pragma once

#include "Engine/Core.h"
#include "Engine/Module/Module.h"

#include <functional>
#include <string>
#include <unordered_map>

using ModuleFactory = std::function<Ref<IModule>()>;

class ModuleManager
{
public:
    static void Init();
    static void Shutdown();

    static ModuleManager &Get()
    {
        static ModuleManager instance;
        return instance;
    }

    void RegisterModule(const std::string &name, ModuleFactory factory, const std::vector<std::string> &dependencies)
    {
        if (m_Factories.contains(name))
            return;

        m_Factories[name] = factory;
        m_Dependencies[name] = dependencies;
    }

    std::vector<std::string> GetModuleNames() const
    {
        std::vector<std::string> names;
        for (const auto &pair : m_Factories)
            names.push_back(pair.first);
        return names;
    }

    Ref<IModule> CreateModule(const std::string &name)
    {
        if (m_Factories.find(name) != m_Factories.end())
            return m_Factories[name]();
        return nullptr;
    }

    const std::unordered_map<std::string, std::vector<std::string>> &GetModuleDependencies() const
    {
        return m_Dependencies;
    }

private:
    std::unordered_map<std::string, ModuleFactory> m_Factories;
    std::unordered_map<std::string, std::vector<std::string>> m_Dependencies;

    static std::vector<Ref<IModule>> m_LoadedModules;
};

#define REGISTER_MODULE(ModuleClass, Dependencies)                                                                                  \
    static bool ModuleClass##_registered = []() {                                                                                   \
        ModuleManager::Get().RegisterModule(#ModuleClass, []() -> Ref<IModule> { return CreateRef<ModuleClass>(); }, Dependencies); \
        return true;                                                                                                                \
    }();
