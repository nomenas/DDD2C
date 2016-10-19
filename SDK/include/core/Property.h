//
// Created by Naum Puroski on 16/10/2016.
//

#ifndef FRIENDLYWITHC_PROPERTY_H
#define FRIENDLYWITHC_PROPERTY_H

#include "Object.h"
#include "Permission.h"

template <class TYPE, int ID, Permission PERMISSION = Permission::ReadWrite>
class Property {
public:
    Property(Object* object, const TYPE& value)
            : m_object(object)
            , m_value(value) {}

    operator const TYPE& () const {
        return m_value;
    }

    Property<TYPE, ID>& operator=(const TYPE& value) {
        if (m_value != value && m_object->onPropertyAboutToChange(ID, &value)) {
            m_object->notify(m_object, Object::PropertyAboutToChange, ID, &value);
            m_value = value;
            m_object->notify(m_object, Object::PropertyChanged, ID, nullptr);
        }
        return *this;
    }

    const TYPE& value() const {
        return m_value;
    }

    void set(const TYPE& value) {
        *this = value;
    }

private:
    Object* m_object;
    TYPE m_value;
};

template <typename TYPE, int ID>
class Property<TYPE, ID, Permission::ReadOnly> {
    friend class Object;
public:
    Property(Object* object, const TYPE& value)
            : m_object(object)
            , m_value(value) {}

    operator const TYPE& () const {
        return m_value;
    }

    const TYPE& value() const {
        return m_value;
    }

private:
    Property<TYPE, ID, Permission::ReadOnly>& operator=(const TYPE& value) {
        if (m_value != value) {
            m_value = value;
            m_object->notify(m_object, Object::PropertyChanged, ID, nullptr);
        }
        return *this;
    }

    void set(const TYPE& value) {
        *this = value;
    }

    Object* m_object;
    TYPE m_value;
};

#endif //FRIENDLYWITHC_PROPERTY_H
