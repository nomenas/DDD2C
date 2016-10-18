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
    static PRODUCT Create(const CONFIG& config, Object::Observer observer = Object::Observer()) {
        PRODUCT returnValue{instance().FactoryMethod(config)};

        if (returnValue && observer) {
            returnValue->addObserver(observer);
            observer(Object::Created, -1, nullptr);
        }
        return returnValue;
    }

    static void SetFactory(Type factoryMethod) {
        instance().FactoryMethod = factoryMethod;
    }

private:
    static Factory<PRODUCT, CONFIG>& instance() {
        static Factory<PRODUCT, CONFIG> _instance;
        return _instance;
    }

    Type FactoryMethod;
};

#endif //FRIENDLYWITHC_FACTORY_H
