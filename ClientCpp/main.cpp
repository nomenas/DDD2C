//
// Created by Naum Puroski on 15/10/2016.
//
#include <iostream>
#include <mutex>
#include <condition_variable>

#include <SDK.h>

#include <domain/Device.h>
#include <domain/Connection.h>
#include <domain/Resource.h>

#include <factory/DeviceFactory.h>
#include <factory/ConnectionFactory.h>
#include <factory/ResourceFactory.h>

int main() {
    // Init SDK, in case we will use static linkage in future
    SDK initSDK;

    // Test factory and properties
    auto deviceDelegate = [](Object*, int event, int property, const void* data) {
        std::cout << "Event received: " << event << ", property = " << property << ", data = " << (long) data << std::endl;
    };

    // Observe factories
    DeviceFactory::SetObserver([](const std::unique_ptr<Device>& object) {
        std::cout << "Device object created! " << (long) object.get() << std::endl;
    });

    // test creation of device object with valid configuration
    std::unique_ptr<Device> device{DeviceFactory::Create(DeviceConfig{"192.168.1.100", 50}, deviceDelegate)};
    std::cout << "device name " << device->name.value() << ", readOnly = " << device->readOnlyProperty.value() << std::endl;

    // test creation of device object with invalid object
    std::unique_ptr<Device> invalidDevice{DeviceFactory::Create(DeviceConfig{}, deviceDelegate)};
    std::cout << "invalid device address " << (long) invalidDevice.get() << std::endl;

    // post command callbacks
    auto connection =  ConnectionFactory::Create(ConnectionConfig{device.get(), 12}, [](Object*, int event, int property, const void* data) {
        if (event == Object::AboutToDestory) {
            std::cout << "Connection about to destroy" << std::endl;
        } else if (event == Object::Destroyed) {
            std::cout << "Connection destroyed" << std::endl;
        }
    });

    connection->postRequest(12, [](int response) { std::cout << "request 12, response " << response << std::endl; });

    // notifications, std::bind may be used for class members
    auto resource = ResourceFactory::Create(ResourceConfig{device.get(), "resource name"}, [](Object*, int event, int property, const void* data) {
        if (event == Object::AboutToDestory) {
            std::cout << "Resource about to destroy" << std::endl;
        } else if (event == Object::Destroyed) {
            std::cout << "Resource destroyed" << std::endl;
        }
    });
    resource->addObserver([&resource](Object*, int event, int property, const void* data) {
        if (event == Object::PropertyChanged) {
            if (property == Resource::NameProperty) {
                std::cout << "property name has been changed" << resource->name.value() << std::endl;
            }
        }
    });

    resource->name = "new name";

    std::cout << "\nDevice status:\n";
    std::cout << " \t Connections: " << device->connections().size() << std::endl;
    std::cout << " \t Resources:   " << device->resources().size() << std::endl << std::endl;

    std::cout << "delete connection manually and check status" << std::endl;
    delete connection;

    std::cout << "\nDevice status:\n";
    std::cout << " \t Connections: " << device->connections().size() << std::endl;
    std::cout << " \t Resources:   " << device->resources().size() << std::endl << std::endl;

    return 0;
}