//
// Created by Naum Puroski on 16/10/2016.
//

#include "ConcreteDevice.h"
#include <factory/DeviceFactory.h>

struct ConcreteDeviceFactory {
    ConcreteDeviceFactory() {
        DeviceFactory::SetFactory([](const DeviceConfig& config) -> std::unique_ptr<Device> {
            return std::unique_ptr<Device>{(config.port && !config.ip.empty()) ?
                new ConcreteDevice(config.ip, config.port) : nullptr};
        });
    }
    ~ConcreteDeviceFactory() {
        DeviceFactory::SetFactory(nullptr);
    }
};

static const ConcreteDeviceFactory _concreteDeviceFactory;