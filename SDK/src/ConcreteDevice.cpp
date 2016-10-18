//
// Created by Naum Puroski on 15/10/2016.
//

#include "ConcreteDevice.h"


ConcreteDevice::ConcreteDevice(const std::string& ip, unsigned short port)
 : m_ip(ip)
 , m_port(port) {
    setProperty(name, "Router 123");
    setProperty(readOnlyProperty, "test");
}

bool ConcreteDevice::connect() {
    notify(Connected);
    return true;
}

bool ConcreteDevice::disconnect() {
    notify(Disconnected);
    return true;
}
