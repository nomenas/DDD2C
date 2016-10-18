//
// Created by Naum Puroski on 15/10/2016.
//

#ifndef FRIENDLYWITHC_OBJECT_H
#define FRIENDLYWITHC_OBJECT_H

#include <functional>
#include <map>
#include <vector>

class Object {
public:
    using Observer = std::function<void(int event, int property, const void* data)>;

    enum Event {
        Created,
        Destroyed,
        PropertyAboutToChange,
        PropertyChanged,
        ItemAboutToAdd,
        ItemAdded,
        ItemAboutToRemove,
        ItemRemoved,
        CollectionAboutToClear,
        CollectionCleared,
        CollectionAboutToUpdate,
        CollectionUpdated,
        Domain = 1000
    };

    Object(Object* parent = nullptr) {
        if ((m_parent = parent)) {
            parent->m_children.push_back(this);
        }
    }

    virtual ~Object() {
        std::for_each(m_children.begin(), m_children.end(), std::default_delete<Object>());
        notify(Event::Destroyed);
    }

    int addObserver(Observer observer) {
        m_observers.insert({m_maxObserverID, observer});
        return m_maxObserverID++;
    }

    void removeObserver(int id) {
        m_observers.erase(id);
    }

    virtual bool onPropertyAboutToChange(int propertyID, const void* data) {
        return true;
    }

    virtual bool onCollectionAboutToChange(int propertyID, int eventID, const void* data) {
        return true;
    }

    void notify(int event, int property = -1, const void* data = nullptr) {
        for (auto iter : m_observers) {
            iter.second(event, property, data);
        }
    }

protected:
    template <typename T, typename V>
    void setProperty(T& property, const V& value) {
        property.set(value);
    }

private:
    Object* m_parent;
    std::vector<Object*> m_children;
    unsigned int m_maxObserverID = 0;
    std::map<unsigned int, Observer> m_observers;
};

#endif //FRIENDLYWITHC_OBJECT_H
