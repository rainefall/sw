#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "sw.h"
#include <unordered_map>

namespace SouthwestEngine
{
    // Special thanks to gamedev.net!
    // Link below for more info
    // https://www.gamedev.net/tutorials/_/technical/game-programming/a-simple-fast-resource-manager-using-c-and-stl-r2503/

    class Resource
    {
        std::string m_fileName; // The name used for the asset on its own (ex. dummy.png)
        std::string m_filePath; // Path to the file in the file sys (ex. assets/)
        std::string m_fileLocation; // Name in the file sys (ex. assets/dummy.png)
        unsigned int m_handle; // UUID
        unsigned int m_instanceCount;
        std::unordered_map<std::string, unsigned int> m_dependencies; // "null_dep" and 00000000 00000000 00000000 00000000 for the UUID is treated as the end of the dep list

    public:
        Resource(const unsigned int handle, const std::unordered_map<std::string, unsigned int>& dependencies, const std::string& fileName, const std::string& filePath = "./") {
            // If the name isn't empty, store it
            if (!fileName.empty())
                m_fileName = fileName;

            if (!filePath.empty())
                m_filePath = filePath;

            m_handle = handle;

            // Appends path and name together to make its file name
            if (!fileName.empty() && !filePath.empty())
                m_fileLocation = filePath + fileName;

            m_dependencies = dependencies;
        }
        virtual ~Resource() = 0; // To be implemented by the derived class

        std::string GetFileName() { return m_fileName; }
        std::string GetFilePath() { return m_filePath; }
        std::string GetFileLocation() { return m_fileLocation; }
        unsigned int GetHandle() { return m_handle; }
        unsigned int GetInstanceCount() { return m_instanceCount; }
        void AddInstance() { m_instanceCount++; }
        void RemoveInstance() { 
            if (m_instanceCount > 0)
                m_instanceCount--;
            else
                assert(0 && "There are no more instances of this resource.");
        }
    };

    template <class T>
    class ResourceManager
    {
        typedef void (*CB_CreateResource)(T**, const unsigned int, const std::string&, const std::string&); // Callback function that is called by the resource manager when a resource is added
        CB_CreateResource m_CreateResourceFunc;
        // Maybe we should change this to std::function or smth
        // Set to null if it's not used
        std::unordered_map<unsigned int, T*>* m_handleMap; // The handle acts as the key in the map
        // Might consider changing from raw pointer to a smart pointer
    public:
        ResourceManager(CB_CreateResource CreateResourceFunc) {
            m_handleMap = new std::unordered_map<unsigned int, T*>;
            m_CreateResourceFunc = CreateResourceFunc;
        }
        ~ResourceManager() {
            ClearResourceList();
            SW_SAFE_DELETE(m_handleMap);
        }

        // @ret Returns -1 if the handle map is not initialized or if the name/path is empty. Returns the handle otherwise.
        unsigned int AddResource(const std::string& fileName, const std::string& filePath = "./") {
            if (m_handleMap == nullptr || fileName.empty() || filePath.empty())
                return -1;

            // Checks if the resource already exists, then returns a pointer if it does exist
            T* resource = GetResource(fileName, filePath);
            if (resource != nullptr) {
                resource->AddInstance();
                return resource->GetHandle();
            }

            m_handleMap->emplace(resource->GetHandle(), resource);
        }

        void RemoveResource(const unsigned int handle) {
            // Returns if the handle map is empty
            if (m_handleMap->empty()) {
                std::cerr << "ERROR: Attempted to remove a resource when there are no resources present." << std::endl;
                return;
            }

            T* resource = (*m_handleMap)[handle];
            resource->RemoveInstance();

            if (resource->GetInstanceCount() == 0) {
                delete resource;
                (*m_handleMap)[handle] = nullptr;
            }
        }

        void ClearResourceList() {
            for (int i = 0; i < m_handleMap->end(); i++) {
                SW_SAFE_DELETE( (*m_handleMap)[i] );
            }
        }

        T* GetResource(const int handle) { // Get resource by handle, will in theory run faster
            if ((*m_handleMap)[handle] != nullptr)
                return (*m_handleMap)[handle];

            return nullptr;
        }
        T* GetResource(const std::string& fileName, const std::string& filePath); // Overlaid func, get resource by file name and path
        std::unordered_map<unsigned int, T*>* GetHandleMap() { return m_handleMap; }
    };
}

#endif