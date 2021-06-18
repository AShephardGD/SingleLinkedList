#include "SingleLinkedList.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
SingleLinkedList<T>::SingleLinkedList() {
    _head = nullptr;
    _size = 0;
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList& other) {
    _size = other._size;
    if (!other._head) {
        _head = nullptr;
        return;
    }
    Node* curOther = other._head;
    Node* cur = new Node(curOther->_data);
    _head = cur;
    while (curOther->_next) {
        curOther = curOther->_next;
        cur->_next = new Node(curOther->_data);
        cur = cur->_next;
    }
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList&& other) noexcept {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
}



template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList& other) {
    delete _head;
    _size = other._size;
    if (!other._head) {
        _head = nullptr;
        return *this;
    }
    Node* curOther = other._head;
    Node* cur = new Node(curOther->_data);
    _head = cur;
    while (curOther->_next) {
        curOther = curOther->_next;
        cur->_next = new Node(curOther->_data);
        cur = cur->_next;
    }
    return *this;
}

template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList&& other) noexcept {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
    delete other._head;
    other._head = nullptr;
    other._size = 0;
    return *this;
}



template <typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    delete _head;
}



template <typename T>
T& SingleLinkedList<T>::operator[](const size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    Node* res = _head;
    for (size_t i = 0; i < pos; ++i) {
        res = res->_next;
    }
    return res->_data;
}

template <typename T>
const T& SingleLinkedList<T>::operator[](const size_t pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    Node* res = _head;
    for (size_t i = 0; i < pos; ++i) {
        res = res->_next;
    }
    return res->_data;
}

template <typename T>
size_t SingleLinkedList<T>::size() const {
    return _size;
}

template <typename T>
typename SingleLinkedList<T>::ListIterator SingleLinkedList<T>::getNode(const size_t pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    ListIterator it = begin();
    for (size_t i = 0; i < pos; ++i) {
        ++it;
    }
    return it;
}



template <typename T>
bool SingleLinkedList<T>::find(const T& needle) const {
    if (!_head) {
        return false;
    }
    Node* cur = _head;
    while (cur->_next) {
        if (cur->_data == needle) {
            return true;
        }
        cur = cur->_next;
    }
    return false;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const {
    return !_head;
}



template <typename T>
void SingleLinkedList<T>::pushBack(const T& data) {
    insert(data, size());
}

template <typename T>
void SingleLinkedList<T>::pushFront(const T& data) {
    insert(data, 0);
}

template <typename T>
void SingleLinkedList<T>::insert(const T& data, size_t pos) {
    ++_size;
    if (!_head) {
        _head = new Node(data);
        return;
    }
    Node* cur = _head;
    Node* saved;
    if (!pos) {
        saved = _head;
        _head = new Node(data);
        _head->_next = saved;
        return;
    }
    --pos;
    while (pos-- && cur->_next) {
        cur = cur->_next;
    }
    saved = cur->_next;
    cur->_next = new Node(data);
    cur->_next->_next = saved;
}

template <typename T>
void SingleLinkedList<T>::insertAfter(const T& data, SingleLinkedList::ListIterator it) {
    insert(data, it.getNodeIndex() + 1);
}



template <typename T>
void SingleLinkedList<T>::clear() {
    delete _head;
    _head = nullptr;
    _size = 0;
}

template <typename T>
void SingleLinkedList<T>::popBack() {
    remove(size() - 1);
}

template <typename T>
void SingleLinkedList<T>::popFront() {
    remove(0);
}

template <typename T>
void SingleLinkedList<T>::remove(size_t pos) {
    if (pos >= size()) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    --_size;
    Node* saved = _head->_next;
    Node* cur = _head;
    if (!pos) {
        _head = saved;
        cur->_next = nullptr;
        delete cur;
        return;
    }
    --pos;
    while (pos--) {
        cur = cur->_next;
    }
    saved = cur->_next->_next;
    cur->_next->_next = nullptr;
    delete cur->_next;
    cur->_next = saved;
}

template <typename T>
void SingleLinkedList<T>::removeAfter(SingleLinkedList::ListIterator it) {
    remove(it.getNodeIndex() + 1);
}

template <typename T>
void SingleLinkedList<T>::remove(SingleLinkedList::ListIterator it) {
    remove(it.getNodeIndex());
}



template <typename T>
void SingleLinkedList<T>::print(std::ostream& stream) const {
    if(!_head) {
        stream << "(nullptr)";
        return;
    }
    Node* cur = _head;
    do {
        stream << cur->_data << " -> ";
        cur = cur->_next;
    } while(cur);
    stream << "(nullptr)";
}



template <typename Type>
std::ostream& operator<<(std::ostream& stream, const SingleLinkedList<Type>& list) {
    list.print(stream);
    return stream;
}



template <typename T>
void SingleLinkedList<T>::forEach(T& (*fn)(T&)) {
    if (!_head) {
        return;
    }
    Node* cur = _head;
    do {
        cur->_data = fn(cur->_data);
        cur = cur->_next;
    } while (cur);
}

template <typename T>
SingleLinkedList<T> SingleLinkedList<T>::map(T& (*fn)(T&)) const {
    SingleLinkedList list = *this;
    list.forEach(fn);
    return list;
}

template <typename T>
void SingleLinkedList<T>::filter(bool (*fn)(T&)) {
    if (!_head) {
        return;
    }
    Node* cur = _head;
    while (!fn(_head->_data)) {
        if (_head->_next) {
            _head = _head->_next;
            cur->_next = nullptr;
            delete cur;
            cur = _head;
        }
        else {
            delete _head;
            _head = nullptr;
        }
    }
    while (cur) {
        if (!cur->_next) {
            break;
        }
        if (!fn((cur->_next)->_data)) {
            if ((cur->_next)->_next) {
                Node* temp = (cur->_next)->_next;
                (cur->_next)->_next = nullptr;
                delete cur->_next;
                cur->_next = temp;
            }
            else {
                delete cur->_next;
                cur->_next = nullptr;
            }
        }
        cur = cur->_next;
    }
}



template <typename T>
void SingleLinkedList<T>::reverse() {
    if (!_head) {
        return;
    }
    Node* cur = _head;
    Node* last = nullptr;
    Node* saved;
    while (cur->_next) {
        saved = cur->_next;
        cur->_next = last;
        last = cur;
        cur = saved;
    }
    cur->_next = last;
    _head = cur;
}

template <typename T>
void SingleLinkedList<T>::reverse(size_t start, size_t end) {
    if (start >= size()) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    Node* last = _head;
    for (size_t i = 0; i <= end && last != nullptr; ++i) {
        last = last->_next;
    }
    end -= start;
    Node* cur = _head;
    Node* startNode = nullptr;
    while (start-- && cur->_next) {
        startNode = cur;
        cur = cur->_next;
    }
    Node* saved;
    while (cur->_next && end--) {
        saved = cur->_next;
        cur->_next = last;
        last = cur;
        cur = saved;
    }
    cur->_next = last;
    if (startNode) {
        startNode->_next = cur;
    }
    else {
        _head = cur;
    }
}

template <typename T>
SingleLinkedList<T> SingleLinkedList<T>::getReverseList() const {
    SingleLinkedList list = *this;
    list.reverse();
    return list;
}

template <typename T>
SingleLinkedList<T> SingleLinkedList<T>::getReverseList(size_t start, size_t end) const {
    SingleLinkedList list = *this;
    list.reverse(start, end);
    return list;
}


template <typename T>
typename SingleLinkedList<T>::ListIterator SingleLinkedList<T>::begin() const {
    return SingleLinkedList::ListIterator(_head, 0);
}

template <typename T>
typename SingleLinkedList<T>::ListIterator SingleLinkedList<T>::end() const {
    return SingleLinkedList::ListIterator(nullptr, size());
}


template <typename T>
SingleLinkedList<T>::Node::Node(const T& data)  {
    _data = data;
    _next = nullptr;
}

template <typename T>
SingleLinkedList<T>::Node::~Node() {
    delete _next;
}

template <typename T>
SingleLinkedList<T>::ListIterator::ListIterator(Node* ptr, size_t index) : _ptr(ptr), _index(index) {}



template <typename T>
T& SingleLinkedList<T>::ListIterator::operator*() {
    return _ptr->_data;
}

template <typename T>
T* SingleLinkedList<T>::ListIterator::operator->() {
    return &(_ptr->_data);
}

template <typename T>
typename SingleLinkedList<T>::ListIterator& SingleLinkedList<T>::ListIterator::operator++() {
    _ptr = _ptr->_next;
    ++_index;
    return *(this);
}

template <typename T>
typename SingleLinkedList<T>::ListIterator SingleLinkedList<T>::ListIterator::operator++(int notUsed) {
    ListIterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
bool SingleLinkedList<T>::ListIterator::operator!=(SingleLinkedList::ListIterator& other) {
    return _ptr != other._ptr;
}

template <typename T>
bool SingleLinkedList<T>::ListIterator::operator==(SingleLinkedList::ListIterator& other) {
    return _ptr == other._ptr;
}

template <typename T>
std::ptrdiff_t SingleLinkedList<T>::ListIterator::operator-(SingleLinkedList::ListIterator& other) {
    return _ptr - other._ptr;
}



template <typename T>
size_t SingleLinkedList<T>::ListIterator::getNodeIndex() const {
    return _index;
}
