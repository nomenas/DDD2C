//
// Created by Naum Puroski on 18/10/2016.
//

#ifndef DDD2C_DEVICE_H
#define DDD2C_DEVICE_H

#include <zconf.h>
#include "Core.h"

#ifdef __cplusplus
extern "C" {
#endif

    HANDLE device_create(const char* address, unsigned short port);
    void device_destory(HANDLE handle);

    int device_connect(HANDLE handle);
    int device_disconnect(HANDLE handle);

    const char* device_get_name(HANDLE handle);
    void device_set_name(HANDLE handle, const char* name);

    const char* device_get_read_only(HANDLE handle);

    unsigned device_resources_size(HANDLE handle);
    void device_get_resources(HANDLE handle, HANDLE* buffer, unsigned bufferSize);

    unsigned device_connections_size(HANDLE handle);
    void device_get_connections(HANDLE handle, HANDLE* buffer, unsigned bufferSize);

    unsigned device_collection_size(HANDLE handle);
    void device_get_collection(HANDLE handle, int* buffer, unsigned bufferSize);

#ifdef __cplusplus
}
#endif

#endif //DDD2C_DEVICE_H
