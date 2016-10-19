//
// Created by Naum Puroski on 15/10/2016.
//

#ifndef FRIENDLYWITHC_CONNECTION_H
#define FRIENDLYWITHC_CONNECTION_H

#include <core/Property.h>

#include "Device.h"

class Connection : public Object {
public:
    enum PropertyID {
        DeviceProperty,
        ChannelProperty
    };

    Connection(Device* device) : Object(device) {}

    virtual void postRequest(int request, std::function<void(int)> response) = 0;

    // if we don't want notifications
    virtual Device* device() const = 0;
    virtual unsigned short channel() const = 0;
};

#endif //FRIENDLYWITHC_CONNECTION_H
