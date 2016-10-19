//
// Created by Naum Puroski on 19/10/2016.
//

#ifndef DDD2C_UTILITY_H
#define DDD2C_UTILITY_H

#include <core/Object.h>
#include <vector>

template <typename T>
std::vector<T*> children(const std::vector<Object*>& objects) {
    std::vector<T*> returnValue;

    for (auto item : objects) {
        if (auto concreteItem = dynamic_cast<T*>(item)) {
            returnValue.push_back(concreteItem);
        }
    }

    return returnValue;
}
#endif //DDD2C_UTILITY_H
