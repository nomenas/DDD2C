//
// Created by Naum Puroski on 18/10/2016.
//

#ifndef DDD2C_SMARTPOINTERHOLDER_H_H
#define DDD2C_SMARTPOINTERHOLDER_H_H

#include <utility>

template <typename T>
struct PtrHolder {
    T ptr;
};

template <typename T>
PtrHolder<T>* ptrHolder(T&& ptr) {
    PtrHolder<T>* returnValue = nullptr;

    if (ptr) {
        returnValue = new PtrHolder<T>{std::move(ptr)};
    }

    return returnValue;
}

#endif //DDD2C_SMARTPOINTERHOLDER_H_H
