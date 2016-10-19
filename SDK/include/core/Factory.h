//
// Created by Naum Puroski on 16/10/2016.
//

#ifndef FRIENDLYWITHC_FACTORY_H
#define FRIENDLYWITHC_FACTORY_H

#include <functional>

template <typename PRODUCT, typename CONFIG>
class Factory {
    using Type = std::function<PRODUCT(const CONFIG&)>;

public:
    using Observer = std::function<void(const PRODUCT&)>;

    static PRODUCT Create(const CONFIG& config, Object::Observer observer = Object::Observer()) {
        PRODUCT returnValue{instance()._factoryMethod(config)};

        if (returnValue && observer) {
            returnValue->addObserver(observer);
        }
        return returnValue;
    }

    static void SetFactory(Type factoryMethod) {
        instance()._factoryMethod = factoryMethod;
    }

    static void SetObserver(Observer observer) {
        instance()._observer = observer;
    }

private:
    static Factory<PRODUCT, CONFIG>& instance() {
        static Factory<PRODUCT, CONFIG> _instance;
        return _instance;
    }

    Type _factoryMethod;
    Observer _observer;
};

#endif //FRIENDLYWITHC_FACTORY_H
