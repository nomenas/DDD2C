//
// Created by Naum Puroski on 18/10/2016.
//

#include "../include/CSDK/Callback.h"
#include <core/Object.h>

CallbackType _callback = 0;

void set_callback(CallbackType callback) {
    _callback = callback;
}

void notify(Object* handle, int event, int propertyID, const void* data) {
    if (_callback) {
        _callback(handle, event, propertyID, data);
    }
}
