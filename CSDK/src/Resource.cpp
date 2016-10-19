//
// Created by Naum Puroski on 18/10/2016.
//

#include "../include/CSDK/Resource.h"

#include <domain/Device.h>
#include <domain/Resource.h>
#include <factory/ResourceFactory.h>

#include <unordered_set>

extern Object* object(HANDLE handle);

static std::unordered_set<Resource*> cache;
Resource* resource(HANDLE handle) {
    Resource* res = static_cast<Resource*>(handle);
    return handle && cache.find(res) != cache.end() ? res : nullptr;
}

using namespace std::placeholders;
extern void notify(Object* object, int event, int propertyID, const void* data);

HANDLE resource_create(HANDLE handle, const char* name) {
    HANDLE returnValue = 0;

    if (auto obj = object(handle)) {
        if (auto resource = ResourceFactory::Create(ResourceConfig{obj, name}))
        {
            cache.insert(resource);
            resource->addObserver(std::bind(notify, _1, _2, _3, _4));
            returnValue = resource;
        }
    }

    return returnValue;
}

void resource_destory(HANDLE handle) {
    auto iter = cache.find(static_cast<Resource*>(handle));
    if (iter != cache.end()) {
        cache.erase(iter);
        delete *iter;
    }
}

const char* resource_get_name(HANDLE handle) {
    return resource(handle) ? resource(handle)->name.value().c_str() : 0;
}

void resource_set_name(HANDLE handle, const char* name) {
    if (auto res = resource(handle)) {
        res->name = name;
    }
}