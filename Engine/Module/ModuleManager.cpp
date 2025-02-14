#include "Engine/Module/ModuleManager.h"
#include "Engine/Core.h"
#include "Engine/Logger.h"
#include "Engine/Module/Module.h"
#include "Engine/Time.h"

#include <unordered_set>

bool DetectCycle(const std::unordered_map<std::string, std::vector<std::string>> &graph,
                 const std::string &module,
                 std::unordered_set<std::string> &visited,
                 std::unordered_set<std::string> &inStack,
                 std::vector<std::string> &cycleStack)
{
    if (inStack.find(module) != inStack.end())
    {
        cycleStack.push_back(module);
        return true;
    }

    if (visited.find(module) != visited.end())
    {
        return false;
    }

    visited.insert(module);
    inStack.insert(module);

    for (const std::string &dep : graph.at(module))
    {
        if (DetectCycle(graph, dep, visited, inStack, cycleStack))
        {
            cycleStack.push_back(module);
            return true;
        }
    }

    inStack.erase(module);
    return false;
}

std::vector<std::string> FindCyclicDependencies(const std::unordered_map<std::string, std::vector<std::string>> &dependencies)
{
    std::unordered_set<std::string> visited;
    std::unordered_set<std::string> inStack;
    std::vector<std::string> cycleStack;
    std::vector<std::string> allCyclicDependencies;

    std::function<bool(const std::unordered_map<std::string, std::vector<std::string>> &,
                       const std::string &,
                       std::unordered_set<std::string> &,
                       std::unordered_set<std::string> &,
                       std::vector<std::string> &)>
        DetectCycle;

    DetectCycle = [&](const std::unordered_map<std::string, std::vector<std::string>> &graph,
                      const std::string &module,
                      std::unordered_set<std::string> &visited,
                      std::unordered_set<std::string> &inStack,
                      std::vector<std::string> &cycleStack) -> bool
    {
        if (inStack.find(module) != inStack.end())
        {
            cycleStack.push_back(module);
            return true;
        }

        if (visited.find(module) != visited.end())
        {
            return false;
        }

        visited.insert(module);
        inStack.insert(module);

        for (const std::string &dep : graph.at(module))
        {
            if (DetectCycle(graph, dep, visited, inStack, cycleStack))
            {
                cycleStack.push_back(module);
                return true;
            }
        }

        inStack.erase(module);
        return false;
    };

    for (const auto &module : dependencies)
    {
        if (visited.find(module.first) == visited.end())
        {
            cycleStack.clear();
            if (DetectCycle(dependencies, module.first, visited, inStack, cycleStack))
            {
                std::string cycleString = "Found cyclic dependencies: ";
                bool first = true;
                for (auto it = cycleStack.rbegin(); it != cycleStack.rend() - 1; ++it)
                {
                    if (!first)
                        cycleString += " > ";
                    cycleString += *it;
                    first = false;
                    allCyclicDependencies.push_back(*it);
                }

                cycleString += " > " + std::string(cycleStack.rbegin()->data());
                LOG_INFO(cycleString);

                cycleStack.clear();
            }
        }
    }

    return allCyclicDependencies;
}

std::vector<Ref<IModule>> ModuleManager::m_LoadedModules;

void ModuleManager::Init()
{
    Time::Start();
    ModuleManager &manager = ModuleManager::Get();

    LOG_INFO("Loading modules...");

    const auto &dependencies = manager.GetModuleDependencies();
    auto cyclicDependencies = FindCyclicDependencies(dependencies);

    auto moduleNames = manager.GetModuleNames();

    for (const auto &name : moduleNames)
    {
        if (auto it = std::find(cyclicDependencies.begin(), cyclicDependencies.end(), name) != cyclicDependencies.end())
        {
            continue;
        }

        Ref<IModule> module = manager.CreateModule(name);
        if (module)
        {
            LOG_INFO("Loading module: {}", name);
            module->OnInitialize();
            m_LoadedModules.push_back(module);
        }
    }

    LOG_INFO("Modules finished loading in {:.8f}s", Time::End());
}

void ModuleManager::Shutdown()
{
    for (Ref<IModule> &module : m_LoadedModules)
    {
        module->OnShutdown();
    }
}
