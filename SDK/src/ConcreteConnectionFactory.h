#ifndef FRIENDLYWITHC_CONCRETECONNECTIONFACTORY_H
#define FRIENDLYWITHC_CONCRETECONNECTIONFACTORY_H

#include "ConcreteConnection.h"
#include "ConcreteDevice.h"
#include <factory/ConnectionFactory.h>

struct ConcreteConnectionFactory {
    ConcreteConnectionFactory() {
        ConnectionFactory ::SetFactory([](const ConnectionConfig& config) -> Connection* {
            return dynamic_cast<ConcreteDevice*>(config.device) ? new ConcreteConnection(config.device, config.channel) : nullptr;
        });
    }
    ~ConcreteConnectionFactory() {
        ConnectionFactory::SetFactory(nullptr);
    }
};

#endif // FRIENDLYWITHC_CONCRETECONNECTIONFACTORY_H
