//
// Created by Naum Puroski on 18/10/2016.
//

#include <stdio.h>

#include <CSDK/Callback.h>
#include <CSDK/Device.h>
#include <CSDK/Resource.h>
#include <CSDK/Connection.h>

void callback(HANDLE handle, int event, int propertyID, const void* data) {
    printf("* NOTIFY: %ld, %d, %d, %ld\n", (long) handle, event, propertyID, (long) data);
}

static void connection_post_response(HANDLE handle, int request, int response) {
    printf("I have gotten response %d for request %d on channel %hu\n", request, response, connection_get_channel(handle));
}

int main() {
    init_sdk();
    set_callback(callback);

    HANDLE hDevice = device_create("192.168.0.1", 80);
    {
        printf("device is created, its name is: %s\n", device_get_name(hDevice));
        printf("now I will change device name, expect callback\n");
        device_set_name(hDevice, "my new c name\n");

        // create resource
        HANDLE hResource = resource_create(hDevice, "RESOURCE 123");
        printf("I have created new device resource, its name is: %s\n", resource_get_name(hResource));
        resource_set_name(hResource, "NEW NAME");

        HANDLE hConnection = connection_create(hDevice, 12);
        printf("I have created new device connection, it works on channel number: %hu\n", connection_get_channel(hConnection));
        printf("Device handles %ld %ld\n", (long) hDevice, (long) connection_get_device(hConnection));

        printf("Test call with invalid handle %ld\n", (long) connection_get_device(hDevice));

        connection_post_request(hConnection, 12, connection_post_response);

        connection_destory(hConnection);
        printf("\nDevice status:\n");
        printf(" \t Connections: %u\n", device_connections_size(hDevice));
        printf(" \t Resources:   %u\n\n", device_resources_size(hDevice));
    }
    device_destory(hDevice);

    release_sdk();

    return 0;
}