#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "sw.h"
#include <unordered_map>

namespace SouthwestEngine
{
    // Special thanks to Robert Wells!
    // Link below for more info
    // https://thatgamesguy.co.uk/cpp-game-dev-9/

    class AssetBase
    {
        std::string m_assetName;
        unsigned int m_uuid;

    public:
        AssetBase(const std::string& assetName, const unsigned int uuid) {
            m_assetName = assetName;
            m_uuid = uuid;
        }
        virtual ~AssetBase() = 0; // To be implemented by the derived class
        virtual bool Load(unsigned int uuid) = 0; // Loading from UUID
        virtual bool Load(const std::string& fileName) = 0; // Loading from file
        const std::string& GetAssetName() const { return m_assetName; }
    };

    template <class T>
    class AssetManagerBase
    {
        unsigned int m_currentHandle;
        std::unordered_map<std::string, std::pair<unsigned int, std::shared_ptr<T>>> m_assetMap;

    public:
        AssetManagerBase() {}
        ~AssetManagerBase() {}
        
        unsigned int AddAsset(const std::string& fileName) {
            if (fileName.empty())
                assert(0 && "ERROR: File name is null");

            // Maybe we should add some util stuff for strings so we can
            // trim and force asset name case

            // Sees if the asset has already been loaded
            // and returns the loaded asset if it's been
            // loaded already
            auto it = m_assetMap.find(fileName);
            if (it != m_assetMap) {
                return it->second.first;
            }

            // Loads the asset if it hasn't already been
            // loaded then inserts it into m_assetHandleMap
            std::shared_ptr<T> asset = std::make_shared<T>();
            if (!asset->Load(fileName)) {
                return 0xFFFFFFFF; // Returns 0xFFFFFFFF on failure
            }

            m_assetMap.insert(fileName, std::make_pair(m_currentHandle, asset));
            return m_currentHandle++; // Returns m_currentHandle before incrementing it
        }

        // Returns true on success, false on failure
        void RemoveAsset(const unsigned int handle) {
            for (auto it = m_assetMap.begin(); it != m_assetMap.end(); ++it) {
                if (it->second.first == handle) {
                    m_assetMap.erase(it->first);
                    return true;
                }
            }
            return false;
        }

        std::shared_ptr<T> GetAsset(const unsigned int handle) {
            for (auto it = m_assetMap.begin(); it != m_assetMap.end(); ++it) {
                if (it->second.first == handle) {
                    return it->second.second;
                }
            }

            return nullptr;
        }

        bool ContainsAsset(const unsigned int handle) {
            return (GetAsset(handle) != nullptr);
        }
    };
}

#endif