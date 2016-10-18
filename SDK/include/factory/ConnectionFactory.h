//
// Created by Naum Puroski on 17/10/2016.
//

#ifndef FRIENDLYWITHC_CONNECTIONFACTORY_H
#define FRIENDLYWITHC_CONNECTIONFACTORY_H

#include <domain/Connection.h>
#include <core/Factory.h>

struct ConnectionConfig {
    Device* device;
};

using ConnectionFactory = Factory<Connection*, ConnectionConfig>;


#endif //FRIENDLYWITHC_CONNECTIONFACTORY_H
