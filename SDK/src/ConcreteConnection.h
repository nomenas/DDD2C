//
// Created by Naum Puroski on 15/10/2016.
//

#ifndef FRIENDLYWITHC_CONCRETECONNECTION_H
#define FRIENDLYWITHC_CONCRETECONNECTION_H

#include <domain/Connection.h>

class Device;

class ConcreteConnection : public Connection {
public:
    ConcreteConnection(Device* device);


};


#endif //FRIENDLYWITHC_CONCRETECONNECTION_H
