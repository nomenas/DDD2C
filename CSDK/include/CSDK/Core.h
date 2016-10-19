//
// Created by Naum Puroski on 18/10/2016.
//

#ifndef DDD2C_WRAPPER_H
#define DDD2C_WRAPPER_H

typedef void* HANDLE;

#ifdef __cplusplus
extern "C" {
#endif

    void init_sdk();
    void release_sdk();

#ifdef __cplusplus
}
#endif

#endif //DDD2C_WRAPPER_H
