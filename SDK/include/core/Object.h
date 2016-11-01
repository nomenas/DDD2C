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
    using Observer = std::function<void(Object* object, int event, int property, const void* data)>;

    enum Event {
        AboutToDestory,
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
        ParentAboutToChange,
        ParentChanged,
        ChildAboutToAdd,
        ChildAdded,
        ChildAboutToRemove,
        ChildRemoved,
        Domain = 1000
    };

    Object(Object* parent = nullptr)
        : m_parent(parent) {
        if (m_parent) {
            m_parent->addChild(this);
        }
    }

    virtual ~Object() {
        notify(this, Event::AboutToDestory);

        std::for_each(m_children.begin(), m_children.end(), std::default_delete<Object>());

        if (m_parent) {
            m_parent->removeChild(this);
        }

        notify(this, Event::Destroyed);
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

    void notify(Object* object, int event, int property = -1, const void* data = nullptr) {
        for (auto iter : m_observers) {
            iter.second(object, event, property, data);
        }
    }

protected:
    template <typename T, typename V>
    void setProperty(T& property, const V& value) {
        property.set(value);
    }

    virtual bool onChildAboutToRemove(Object* object) {return true;}
    virtual bool onChildRemoved(Object* object) {return true;}
    virtual bool onChildAboutToAdd(Object* object) {return true;}
    virtual void onChildAdded(Object* object) {};

    void addChild(Object* object) {
        auto iter = std::find(m_children.begin(), m_children.end(), object);
        if (iter == m_children.end()) {
            if (onChildAboutToAdd(object)) {
                notify(this, ChildAboutToAdd, -1, object);
                notify(object, ParentAboutToChange, -1, this);
                m_children.push_back(object);
                object->m_parent = this;
                notify(object, ParentChanged, -1, this);
                onChildAdded(object);
                notify(this, ChildAdded, -1, object);
            }
        }
    }

    void removeChild(Object* object) {
        auto iter = std::find(m_children.begin(), m_children.end(), object);
        if (iter != m_children.end()) {
            if (onChildAboutToRemove(object)) {
                notify(this, ChildAboutToRemove, -1, object);
                notify(object, ParentAboutToChange, -1, nullptr);
                m_children.erase(iter);
                object->m_parent = nullptr;
                notify(object, ParentChanged, -1, this);
                onChildRemoved(object);
                notify(this, ChildRemoved, -1, object);
            }
        }
    }

    Object* m_parent;
    std::vector<Object*> m_children;
    unsigned int m_maxObserverID = 0;
    std::map<unsigned int, Observer> m_observers;
};

#endif //FRIENDLYWITHC_OBJECT_H
