//
// Created by Naum Puroski on 15/10/2016.
//

#ifndef FRIENDLYWITHC_CONCRETEDEVICE_H
#define FRIENDLYWITHC_CONCRETEDEVICE_H

#include "Utility.h"

#include <domain/Device.h>
#include <domain/Connection.h>
#include <domain/Resource.h>

class ConcreteDevice : public Device {
public:
    explicit ConcreteDevice(const std::string& ip, unsigned short port);

    bool connect() override;
    bool disconnect() override;

    std::vector<Resource*> resources() override {
        return children<Resource>(m_children);
    }

    std::vector<Connection*> connections() override {
        return children<Connection>(m_children);
    }

private:
    std::string m_ip;
    unsigned short m_port;
};


#endif //FRIENDLYWITHC_CONCRETEDEVICE_H
