//
// Created by Naum Puroski on 18/10/2016.
//

#include <unordered_set>
#include <domain/Connection.h>
#include <factory/ConnectionFactory.h>
#include "../include/CSDK/Connection.h"

static std::unordered_set<Connection*> cache;
Connection* connection(HANDLE handle) {
    Connection* res = static_cast<Connection*>(handle);
    return handle && cache.find(res) != cache.end() ? res : nullptr;
}

using namespace std::placeholders;
extern void notify(Object* object, int event, int propertyID, const void* data);
extern Device* device(HANDLE handle);
extern HANDLE deviceHandle(Device* device);

HANDLE connection_create(HANDLE device, unsigned short channel) {
    HANDLE returnValue = 0;

    if (auto obj = ::device(device)) {
        if (auto connection = ConnectionFactory::Create(ConnectionConfig{obj, channel}))
        {
            cache.insert(connection);
            connection->addObserver(std::bind(notify, _1, _2, _3, _4));
            returnValue = connection;
        }
    }

    return returnValue;
}

void connection_destory(HANDLE handle) {
    auto iter = cache.find(static_cast<Connection*>(handle));
    if (iter != cache.end()) {
        cache.erase(iter);
        delete *iter;
    }
}

void connection_post_request(HANDLE handle, int request, PostRequestCallback callback) {
    if (auto conn = connection(handle)) {
        conn->postRequest(request, [&](int response){callback(handle, request, response);});
    }
}

HANDLE connection_get_device(HANDLE handle) {
    return connection(handle) ? deviceHandle(connection(handle)->device()) : 0;
}

unsigned short connection_get_channel(HANDLE handle) {
    return connection(handle) ? connection(handle)->channel() : 0;
}