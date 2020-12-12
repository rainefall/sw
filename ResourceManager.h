#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "sw.h"

namespace Southwest
{
    // Special thanks to gamedev.net!
    // Link below for more info
    // https://www.gamedev.net/tutorials/_/technical/game-programming/a-simple-fast-resource-manager-using-c-and-stl-r2503/

    class Resource
    {
        std::string m_name; // The actual name used for the asset (ex. DummyScreen)
        std::string m_fileName; // Name in the file sys (ex. dummy.png)
        std::string m_filePath; // Path to the file in the file sys (ex. assets/dummy.png)
        unsigned int m_handle; // UUID
        unsigned long m_instanceCount;

    public:
        Resource(const unsigned int handle, const std::string& name, const std::string& path);
        ~Resource();

        std::string GetName() { return m_name; }
        std::string GetFileName() { return m_fileName; }
        std::string GetFilePath() { return m_filePath; }
        unsigned int GetHandle() { return m_handle; }
        unsigned long GetInstanceCount() { return m_instanceCount; }
        void AddInstance();
        void RemoveInstance();
    };

    template <class T>
    class ResourceManager
    {
        void (*CB_CreateResource)(T**, const unsigned int, const std::string&, const std::string&); // Callback function that is called by the resource manager when a resource is added
        // Maybe we should change this to std::function or smth
        // Set to null if it's not used
        std::unordered_map<T*>* m_handleMap;

    public:
        ResourceManager(void(*)(T**, const unsigned int, const std::string&, const std::string&) CreateResourceFunction);
        ~ResourceManager();
        unsigned int AddResource(const std::string& name, const std::string& path = "./"); // Defaults to the root path
        void RemoveResource(const unsigned int handle);
        void ClearResourceList();
        T* GetResource(const int handle); // Get resource by handle, will in theory run faster
        T* GetResource(const std::string& name, const std::string& path); // Overlaid func, get resource by file name and path
        std::vector<T*>* GetHandleMap();
        T* operator [](unsigned int handle) // Allows you to get the resource at the specified handle using the [] operator
    };
}

#endif