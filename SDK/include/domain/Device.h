//
// Created by Naum Puroski on 15/10/2016.
//

#ifndef FRIENDLYWITHC_DEVICE_H
#define FRIENDLYWITHC_DEVICE_H

#include <string>

#include <core/Object.h>
#include <core/Property.h>
#include <core/Collection.h>

class Resource;
class Connection;

class Device : public Object {
public:
    enum Event {
        Connected = Object::Domain,
        Disconnected
    };

    enum PropertyID {
        NameProperty,
        ReadOnlyFieldProperty,
        CollectionProperty,
    };

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;

    virtual std::vector<Resource*> resources() = 0;
    virtual std::vector<Connection*> connections() = 0;

    Property<std::string, NameProperty> name{this, ""};
    Property<std::string, ReadOnlyFieldProperty, Permission::ReadOnly> readOnlyProperty{this, ""};
    Collection<int, CollectionProperty, Permission::ReadOnly> collection{this};
};


#endif //FRIENDLYWITHC_DEVICE_H
