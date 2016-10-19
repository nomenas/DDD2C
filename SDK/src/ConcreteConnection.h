//
// Created by Naum Puroski on 15/10/2016.
//

#ifndef FRIENDLYWITHC_CONCRETECONNECTION_H
#define FRIENDLYWITHC_CONCRETECONNECTION_H

#include <domain/Connection.h>

class Device;
class ConcreteDevice;

class ConcreteConnection : public Connection {
public:
    ConcreteConnection(Device* device, unsigned short channel);

    void postRequest(int request, std::function<void(int)> response) override;

    Device* device() const override;
    unsigned short channel() const override;

private:
    unsigned _channel = 0;
};

#endif //FRIENDLYWITHC_CONCRETECONNECTION_H
