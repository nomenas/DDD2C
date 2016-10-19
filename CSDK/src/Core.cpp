//
// Created by Naum Puroski on 18/10/2016.
//
#include "../include/CSDK/Core.h"
#include <SDK.h>

#include <domain/Device.h>
#include <domain/Connection.h>
#include <domain/Resource.h>

void init_sdk() {
    SDK::Init();
}

void release_sdk() {
    SDK::Release();
}


extern Device* device(HANDLE handle);

extern Object* object(HANDLE handle) {
    Object* returnValue = 0;

    if (auto dev = device(handle)) {
        returnValue = dev;
    }

    return returnValue;
}
