#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__

#include <cassert>
#include <sstream>

#include "defines.hpp"
#include "exception.hpp"

template <class T> class LinkedListNode;

template <class T>
class ILinkedList
{
public:
    ILinkedList(bool deleteOnDestroy = true) :
        _deleteOnDestroy(deleteOnDestroy) {}
    virtual ~ILinkedList() {}

    virtual unsigned size() const = 0;
    virtual bool contains(LinkedListNode<T> *element) = 0;
    virtual void remove(LinkedListNode<T> *element) = 0;
    virtual void clear(bool thorough = true) = 0;
    virtual void addFront(LinkedListNode<T> *element) = 0;
    virtual void addBack(LinkedListNode<T> *element) = 0;
    virtual T *getFront() const = 0;
    virtual T *getBack() const = 0;
    virtual std::string toString();

protected:
    bool _deleteOnDestroy;
};

template <class T>
class LinkedList : public ILinkedList<T>
{
public:
    LinkedList(bool deleteOnDestroy = true);
    ~LinkedList();

    unsigned size() const;

    bool contains(LinkedListNode<T> *element) const;

    void remove(LinkedListNode<T> *element);
    void clear(bool thorough = true);

    void addFront(LinkedListNode<T> *element);
    void addBack(LinkedListNode<T> *element);

    inline T *getFront() const;
    inline T *getBack() const;

private:
    LinkedListNode<T> *_head, *_tail;
};

template <class T>
class LinkedListNode
{
    template <class U> friend class LinkedList;

public:
    LinkedListNode() : _prev(NULL), _next(NULL) {}
    virtual ~LinkedListNode() {}

    inline LinkedListNode<T> *getPrev() const { return _prev; }
    inline LinkedListNode<T> *getNext() const { return _next; }

    virtual std::string toString() = 0;

protected:
    LinkedListNode<T> *_prev, *_next;
};

template <class T>
LinkedList<T>::LinkedList(bool deleteOnDestroy) :
        ILinkedList(deleteOnDestroy),
        _head(NULL),
        _tail(NULL)
{
}

template <class T>
LinkedList<T>::~LinkedList()
{
    clear(true);
}

template <class T>
unsigned LinkedList<T>::size() const
{
    unsigned count = 0;

    if (_head == NULL)
    {
        count = 0;
    }
    else if (_head == _tail)
    {
        count = 1;
    }
    else
    {
        auto *current = _head;
        while (current != NULL)
        {
            count++;
            current = current->_next;
        }
    }

    return count;
}

template <class T>
bool LinkedList<T>::contains(LinkedListNode<T> *element) const
{
    assert(element);

    bool ret = false;
    auto *current = _head;
    while (current != NULL)
    {
        if (current == element)
        {
            ret = true;
            break;
        }
        current = current->_next;
    }

    return ret;
}

template <class T>
void LinkedList<T>::remove(LinkedListNode<T> *element)
{
    assert(element);

    bool found = false;

    if (_head == element)
    {
        if (_head == _tail)
        {
            _head = _tail = NULL;
            found = true;
        }
        else
        {
            _head = _head->_next;
            _head->_prev = NULL;
            element->_next = element->_prev = NULL;
            found = true;
        }
    }
    else if (_tail == element)
    {
        if (_head == _tail)
        {
            _head = _tail = NULL;
            found = true;
        }
        else
        {
            _tail = _tail->_prev;
            _tail->_next = NULL;
            element->_next = element->_prev = NULL;
            found = true;
        }
    }
    else
    {
        auto *current = _head->_next;
        while (current != NULL)
        {
            if (current == element)
            {
                current->_prev->_next = current->_next;
                current->_next->_prev = current->_prev;
                current->_next = current->_prev = NULL;
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        ostringstream ss;
        ss << "Element "
        throw ListException("Element is not a member ");
    }

    if (_deleteOnDestroy)
        delete element;
}

template <class T>
void LinkedList<T>::clear(bool thorough)
{
    if (thorough)
    {
        auto *current = _head;
        LinkedListNode<T> *next = NULL;
        while (current != NULL)
        {
            next = current->_next;
            current->_prev = current->_next = NULL;
            if (_deleteOnDestroy)
                delete current;
            current = next;
        }
    }

    _head = _tail = NULL;
}

template <class T>
void LinkedList<T>::addFront(LinkedListNode<T> *element)
{
    assert(element);

    if (_tail == NULL)
    {
        assert(_head == NULL);
        _tail = _head = element;
    }
    else
    {
        assert(element->_prev == NULL && element->_next == NULL);

        _head->_prev = element;
        element->_next = _head;
        _head = element;
    }
}

template <class T>
void LinkedList<T>::addBack(LinkedListNode<T> *element)
{
    assert(element);

    if (_head == NULL)
    {
        assert(_tail == NULL);
        _head = _tail = element;
    }
    else
    {
        assert(element->_prev == NULL && element->_next == NULL);

        _tail->_next = element;
        element->_prev = _tail;
        _tail = element;
    }
}

template <class T>
T *LinkedList<T>::getFront() const
{
    return static_cast<T>(_head);
}

template <class T>
T *LinkedList<T>::getBack() const
{
    return static_cast<T>(_tail);
}

#endif
