//
// Created by Naum Puroski on 15/10/2016.
//

#ifndef FRIENDLYWITHC_CONNECTION_H
#define FRIENDLYWITHC_CONNECTION_H

#include <core/Property.h>

#include <domain/Device.h>

class Connection : public Object {
    enum PropertyID {
        DeviceProperty,
        PortProperty
    };

    Connection(Device* device) : Object(device) {}

    Property<Device*, DeviceProperty, Permission::ReadOnly> device{this, nullptr};
    Property<unsigned short, PortProperty, Permission::ReadOnly> port{this , 0};
};

#endif //FRIENDLYWITHC_CONNECTION_H
