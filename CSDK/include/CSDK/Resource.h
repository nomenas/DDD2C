//
// Created by Naum Puroski on 18/10/2016.
//

#ifndef DDD2C_RESOURCE_H
#define DDD2C_RESOURCE_H

#include "Core.h"

#ifdef __cplusplus
extern "C" {
#endif

    HANDLE resource_create(HANDLE object, const char* name);
    void resource_destory(HANDLE handle);

    const char* resource_get_name(HANDLE handle);
    void resource_set_name(HANDLE handle, const char* name);

#ifdef __cplusplus
}
#endif


#endif //DDD2C_RESOURCE_H
