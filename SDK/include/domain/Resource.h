//
// Created by Naum Puroski on 17/10/2016.
//

#ifndef FRIENDLYWITHC_RESOURCE_H
#define FRIENDLYWITHC_RESOURCE_H

#include <core/Object.h>
#include <core/Property.h>

#include <string>

class Resource : public Object {
public:
    enum PropertyID {
        NameProperty
    };

    Resource(Object* object) : Object(object) {}

    Property<std::string, NameProperty> name{this, ""};
};

#endif //FRIENDLYWITHC_RESOURCE_H
