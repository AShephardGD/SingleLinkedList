#include "SingleLinkedList.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

SingleLinkedList::SingleLinkedList() {
    _head = nullptr;
}

SingleLinkedList::SingleLinkedList(const SingleLinkedList& other) {
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

SingleLinkedList::SingleLinkedList(SingleLinkedList&& other) noexcept {
    std::swap(_head, other._head);
}



SingleLinkedList& SingleLinkedList::operator=(const SingleLinkedList& other) {
    delete _head;
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

SingleLinkedList& SingleLinkedList::operator=(SingleLinkedList&& other) noexcept {
    std::swap(_head, other._head);
    delete other._head;
    other._head = nullptr;
    return *this;
}



SingleLinkedList::~SingleLinkedList() {
    delete _head;
}



void SingleLinkedList::append(int data) {
    if (!_head) {
        _head = new Node(data);
        return;
    }
    Node* cur = _head;
    while (cur->_next) {
        cur = cur->_next;
    }
    cur->_next = new Node(data);
}



bool SingleLinkedList::find(int needle) const {
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

bool SingleLinkedList::isEmpty() const {
    return !_head;
}



void SingleLinkedList::clear() {
    delete _head;
    _head = nullptr;
}

int SingleLinkedList::popBack() {
    if (!_head) {
        throw std::length_error("The SingleLinkedList is empty");
    }
    int res;
    if (!(_head->_next)) {
        res = _head->_data;
        delete _head;
        _head = nullptr;
        return res;
    }
    Node* cur = _head;
    while ((cur->_next)->_next) {
        cur = cur->_next;
    }
    res = (cur->_next)->_data;
    delete cur->_next;
    cur->_next = nullptr;
    return res;
}



void SingleLinkedList::print(std::ostream& stream) const {
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



std::ostream& operator<<(std::ostream& stream, const SingleLinkedList& list) {
    list.print(stream);
    return stream;
}



void SingleLinkedList::forEach(int (*fn)(int)) {
    if (!_head) {
        return;
    }
    Node* cur = _head;
    do {
        cur->_data = fn(cur->_data);
        cur = cur->_next;
    } while (cur);
}

SingleLinkedList SingleLinkedList::map(int (*fn)(int)) const {
    SingleLinkedList list = *this;
    list.forEach(fn);
    return list;
}

void SingleLinkedList::filter(bool (*fn)(int)) {
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
        std::cout << cur->_data << std::endl;
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
