//
// Created by Naum Puroski on 18/10/2016.
//

#ifndef DDD2C_CONNECTION_H
#define DDD2C_CONNECTION_H

#include "Core.h"

#ifdef __cplusplus
extern "C" {
#endif

    HANDLE connection_create(HANDLE device, unsigned short channel);
    void connection_destory(HANDLE handle);

    // callback arguments (request, response)
    typedef void (*PostRequestCallback)(HANDLE, int, int);
    void connection_post_request(HANDLE handle, int request, PostRequestCallback callback);

    HANDLE connection_get_device(HANDLE handle);
    unsigned short connection_get_channel(HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif //DDD2C_CONNECTION_H
