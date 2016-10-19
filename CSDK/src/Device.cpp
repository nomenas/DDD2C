//
// Created by Naum Puroski on 18/10/2016.
//

#include "../include/CSDK/Device.h"
#include "PtrHolder.h"

#include <unordered_map>
#include <domain/Device.h>
#include <factory/DeviceFactory.h>

using DeviceHolder = PtrHolder<std::unique_ptr<Device>>;
static std::unordered_map<void*, PtrHolder<std::unique_ptr<Device>>*> cache;
Device* device(HANDLE handle) {
    return handle && cache.find(handle) != cache.end() ? static_cast<DeviceHolder*>(handle)->ptr.get() : nullptr;
}
HANDLE deviceHandle(Device* device) {
    for (auto item : cache) {
        if (item.second->ptr.get() == device) {
            return item.first;
        }
    }

    return nullptr;
}

using namespace std::placeholders;
extern void notify(Object* object, int event, int propertyID, const void* data);

HANDLE device_create(const char* address, unsigned short port) {
    auto holder = ptrHolder(DeviceFactory::Create({address, port}));

    if (holder) {
        cache[holder] = holder;
        device(holder)->addObserver(std::bind(notify, _1, _2, _3, _4));
    }

    return holder;
}

void device_destory(HANDLE handle) {
    auto iter = cache.find(handle);
    if (iter != cache.end()) {
        cache.erase(iter);
        delete iter->second;
    }
}

int device_connect(HANDLE handle) {
    return device(handle) ? device(handle)->connect() : 0;
}

int device_disconnect(HANDLE handle) {
    return device(handle) ? device(handle)->disconnect() : 0;
}

const char* device_get_name(HANDLE handle) {
    return device(handle) ? device(handle)->name.value().c_str() : 0;
}

void device_set_name(HANDLE handle, const char* name) {
    if (auto d = device(handle)) {
        d->name = name;
    }
}

const char* device_get_read_only(HANDLE handle) {
    return device(handle) ? device(handle)->readOnlyProperty.value().c_str() : 0;
}

unsigned device_resources_size(HANDLE handle) {
    return device(handle) ? device(handle)->resources().size() : 0;
}

void device_get_resources(HANDLE handle, HANDLE* buffer, unsigned bufferSize) {
    if (auto d = device(handle)) {
        auto resources = d->resources();
        std::copy(resources.begin(), resources.end(), buffer);
    }
}

unsigned device_connections_size(HANDLE handle) {
    return device(handle) ? device(handle)->connections().size() : 0;
}

void device_get_connections(HANDLE handle, HANDLE* buffer, unsigned bufferSize) {
    if (auto d = device(handle)) {
        auto connections = d->connections();
        std::copy(connections.begin(), connections.end(), buffer);
    }
}

unsigned device_collection_size(HANDLE handle) {
    return device(handle) ? device(handle)->collection.data().size() : 0;
}

void device_get_collection(HANDLE handle, int* buffer, unsigned bufferSize) {
    if (auto d = device(handle)) {
        std::copy(d->collection.begin(), d->collection.end(), buffer);
    }
}
