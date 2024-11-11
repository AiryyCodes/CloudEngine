#pragma once

#include "CloudEngine/utils.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>

inline void AddPathsToMap(std::map<std::string, std::vector<std::string>> &folderMap, const std::string &path)
{
    // Split the path into folder names
    std::vector<std::string> folders = Split(path, "/");

    // Ensure the first folder is added under the empty root
    if (!folders.empty() && std::find(folderMap[""].begin(), folderMap[""].end(), folders[0]) == folderMap[""].end())
    {
        folderMap[""].push_back(folders[0]);
    }

    // Iterate through the folders to build the map
    std::string currentPath = ""; // Start from the empty root
    for (size_t i = 0; i < folders.size(); ++i)
    {
        if (!currentPath.empty())
        {
            currentPath += '/';
        }
        currentPath += folders[i];

        if (i + 1 < folders.size())
        {
            std::string nextFolder = folders[i + 1];
            if (std::find(folderMap[currentPath].begin(), folderMap[currentPath].end(), nextFolder) == folderMap[currentPath].end())
            {
                folderMap[currentPath].push_back(nextFolder);
            }
        }
    }
};
