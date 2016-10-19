//
// Created by Naum Puroski on 18/10/2016.
//

#ifndef DDD2C_CALLBACK_H
#define DDD2C_CALLBACK_H

#include "Core.h"

// object handle, event type, property, data
typedef void (*CallbackType)(HANDLE, int, int, const void*);

#ifdef __cplusplus
extern "C" {
#endif

    void set_callback(CallbackType callback);

#ifdef __cplusplus
}
#endif

#endif //DDD2C_CALLBACK_H
