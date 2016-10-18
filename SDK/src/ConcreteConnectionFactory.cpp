//
// Created by Naum Puroski on 17/10/2016.
//

#include "ConcreteConnection.h"
#include <factory/ConnectionFactory.h>

struct ConcreteConnectionFactory {
    ConcreteConnectionFactory() {
        ConnectionFactory ::SetFactory([](const ConnectionConfig& config) -> Connection* {
            return nullptr;
        });
    }
    ~ConcreteConnectionFactory() {
        ConnectionFactory::SetFactory(nullptr);
    }
};

//static const ConcreteConnectionFactory _concreteConnectionFactory;