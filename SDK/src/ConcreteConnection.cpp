//
// Created by Naum Puroski on 15/10/2016.
//

#include "ConcreteConnection.h"
#include "ConcreteDevice.h"
#include <future>

ConcreteConnection::ConcreteConnection(Device* device, unsigned short channel)
        : Connection(device)
        , _channel(channel) {
}

void ConcreteConnection::postRequest(int request, std::function<void(int)> response) {
    response(request * 10);
}

Device *ConcreteConnection::device() const {
    return dynamic_cast<Device*>(m_parent);
}

unsigned short ConcreteConnection::channel() const {
    return _channel;
}


