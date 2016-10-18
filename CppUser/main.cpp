//
// Created by Naum Puroski on 15/10/2016.
//
#include <iostream>

#include <domain/Device.h>
#include <factory/DeviceFactory.h>

int main() {
    auto deviceDelegate = [](int event, int property, const void* data) {
        std::cout << "Event received: " << event << ", property = " << property << ", data = " << (long) data << std::endl;
    };
    // test creation of device object with valid configuration
    std::unique_ptr<Device> device{DeviceFactory::Create(DeviceConfig{"192.168.1.100", 50}, deviceDelegate)};
    std::cout << "device name " << device->name.value() << ", readOnly = " << device->readOnlyProperty.value() << std::endl;

    // test creation of device object with invalid object
    std::unique_ptr<Device> invalidDevice{DeviceFactory::Create(DeviceConfig{}, deviceDelegate)};
    std::cout << "invalid device address " << (long) invalidDevice.get() << std::endl;

    return 0;
}