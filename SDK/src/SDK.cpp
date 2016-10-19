//
// Created by Naum Puroski on 18/10/2016.
//

#include "SDK.h"

#include "ConcreteDeviceFactory.h"
#include "ConcreteConnectionFactory.h"
#include "ConcreteResourceFactory.h"

static std::unique_ptr<ConcreteDeviceFactory> _concreteDeviceFactory;
static std::unique_ptr<ConcreteConnectionFactory> _concreteConnectionFactory;
static std::unique_ptr<ConcreteResourceFactory> _concreteResourceFactory;

SDK::SDK() {
    SDK::Init();
}

SDK::~SDK() {
    SDK::Release();
}

void SDK::Init() {
    _concreteDeviceFactory.reset(new ConcreteDeviceFactory);
    _concreteConnectionFactory.reset(new ConcreteConnectionFactory);
    _concreteResourceFactory.reset(new ConcreteResourceFactory);
}

void SDK::Release() {
    _concreteDeviceFactory.reset();
    _concreteConnectionFactory.reset();
    _concreteResourceFactory.reset();
}
