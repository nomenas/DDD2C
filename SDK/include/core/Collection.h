//
// Created by Naum Puroski on 16/10/2016.
//

#ifndef FRIENDLYWITHC_COLLECTION_H
#define FRIENDLYWITHC_COLLECTION_H

#include <vector>

#include "Permission.h"

template <typename TYPE, int ID, Permission PERMISSION = Permission::ReadWrite>
class Collection {
public:
    using const_iterator = typename std::vector<TYPE>::const_iterator;
    using const_reverse_iterator = typename std::vector<TYPE>::const_reverse_iterator;

    Collection(Object* object)
    : m_object(object) {}

    const_iterator begin() const {
        return m_data.begin();
    }

    const_iterator end() const {
        return m_data.end();
    }

    const_reverse_iterator rbegin() const {
        return m_data.rbegin();
    }

    const_reverse_iterator rend() const {
        return m_data.end();
    }

    const std::vector<TYPE>& data() const {
        return m_data;
    }

    void add(const TYPE& element) {
        if (m_object->onCollectionAboutToChange(ID, Object::ItemAboutToAdd, &element)) {
            m_object->notify(ID, Object::ItemAboutToAdd, &element);
            m_data.push_back(element);
            m_object->notify(m_object, ID, Object::ItemAdded, nullptr);
        }
    }

    void remove(const TYPE& element) {
        if (m_object->onCollectionAboutToChange(ID, Object::ItemAboutToRemove, &element)) {
            auto iter = std::find(m_data.begin(), m_data.end(), element);
            if (iter != m_data.end()) {
                m_object->notify(m_object, ID, Object::ItemAboutToRemove, &element);
                m_data.erase(iter);
                m_object->notify(m_object, ID, Object::ItemRemoved, nullptr);
            }
        }
    }

    void clear() {
        if (m_object->onCollectionAboutToChange(ID, Object::CollectionAboutToClear, nullptr)) {
            m_object->notify(m_object, ID, Object::CollectionAboutToClear, nullptr);
            m_data.clear();
            m_object->notify(m_object, ID, Object::CollectionCleared, nullptr);
        }
    }

    void set(const std::vector<TYPE>& data) {
        if (m_object->onCollectionAboutToChange(ID, Object::CollectionAboutToUpdate, &data)) {
            m_object->notify(m_object, ID, Object::CollectionAboutToUpdate, nullptr);
            m_data = data;
            m_object->notify(m_object, ID, Object::CollectionUpdated, nullptr);
        }
    }

private:
    Object* m_object;
    std::vector<TYPE> m_data;
};

template <typename TYPE, int ID>
class Collection<TYPE, ID, Permission::ReadOnly> {
    friend class Object;

public:
    using const_iterator = typename std::vector<TYPE>::const_iterator;
    using const_reverse_iterator = typename std::vector<TYPE>::const_reverse_iterator;

    Collection(Object* object)
            : m_object(object) {}

    const_iterator begin() const {
        return m_data.begin();
    }

    const_iterator end() const {
        return m_data.end();
    }

    const_reverse_iterator rbegin() const {
        return m_data.rbegin();
    }

    const_reverse_iterator rend() const {
        return m_data.end();
    }

    const std::vector<TYPE>& data() const {
        return m_data;
    }

private:
    void add(const TYPE& element) {
        if (m_object->onCollectionAboutToChange(ID, Object::ItemAboutToAdd, &element)) {
            m_object->notify(m_object, ID, Object::ItemAboutToAdd, &element);
            m_data.push_back(element);
            m_object->notify(m_object, ID, Object::ItemAdded, nullptr);
        }
    }

    void remove(const TYPE& element) {
        if (m_object->onCollectionAboutToChange(ID, Object::ItemAboutToRemove, &element)) {
            auto iter = std::find(m_data.begin(), m_data.end(), element);
            if (iter != m_data.end()) {
                m_object->notify(m_object, ID, Object::ItemAboutToRemove, &element);
                m_data.erase(iter);
                m_object->notify(m_object, ID, Object::ItemRemoved, nullptr);
            }
        }
    }

    void clear() {
        if (m_object->onCollectionAboutToChange(ID, Object::CollectionAboutToClear, nullptr)) {
            m_object->notify(m_object, ID, Object::CollectionAboutToClear, nullptr);
            m_data.clear();
            m_object->notify(m_object, ID, Object::CollectionCleared, nullptr);
        }
    }

    void set(const std::vector<TYPE>& data) {
        if (m_object->onCollectionAboutToChange(ID, Object::CollectionAboutToUpdate, &data)) {
            m_object->notify(m_object, ID, Object::CollectionAboutToUpdate, nullptr);
            m_data = data;
            m_object->notify(m_object, ID, Object::CollectionUpdated, nullptr);
        }
    }

    Object* m_object;
    std::vector<TYPE> m_data;
};

#endif //FRIENDLYWITHC_COLLECTION_H
