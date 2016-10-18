//
// Created by Naum Puroski on 17/10/2016.
//

#ifndef FRIENDLYWITHC_RESOURCEFACTORY_H
#define FRIENDLYWITHC_RESOURCEFACTORY_H

#include <domain/Resource.h>
#include <core/Factory.h>

struct ResourceConfig {
    Object* object;
    std::string name;
};

using ResourceFactory = Factory<Resource*, ResourceConfig>;

#endif //FRIENDLYWITHC_RESOURCEFACTORY_H
