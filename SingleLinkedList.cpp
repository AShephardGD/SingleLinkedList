#include "SingleLinkedList.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

SingleLinkedList::SingleLinkedList() {
    _head = nullptr;
    _size = 0;
}

SingleLinkedList::SingleLinkedList(const SingleLinkedList& other) {
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

SingleLinkedList::SingleLinkedList(SingleLinkedList&& other) noexcept {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
}



SingleLinkedList& SingleLinkedList::operator=(const SingleLinkedList& other) {
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

SingleLinkedList& SingleLinkedList::operator=(SingleLinkedList&& other) noexcept {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
    delete other._head;
    other._head = nullptr;
    other._size = 0;
    return *this;
}



SingleLinkedList::~SingleLinkedList() {
    delete _head;
}



ValueType& SingleLinkedList::operator[](const size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    Node* res = _head;
    for (size_t i = 0; i < pos; ++i) {
        res = res->_next;
    }
    return res->_data;
}

const ValueType& SingleLinkedList::operator[](const size_t pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    Node* res = _head;
    for (size_t i = 0; i < pos; ++i) {
        res = res->_next;
    }
    return res->_data;
}

size_t SingleLinkedList::size() const {
    return _size;
}

SingleLinkedList::ListIterator SingleLinkedList::getNode(const size_t pos) const {
    if (pos >= _size) {
        throw std::out_of_range("Out of SingleLinkedList's range");
    }
    ListIterator it = begin();
    for (size_t i = 0; i < pos; ++i) {
        ++it;
    }
    return it;
}



bool SingleLinkedList::find(const ValueType& needle) const {
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



void SingleLinkedList::pushBack(const ValueType& data) {
    insert(data, size());
}

void SingleLinkedList::pushFront(const ValueType& data) {
    insert(data, 0);
}

void SingleLinkedList::insert(const ValueType& data, size_t pos) {
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

void SingleLinkedList::insertAfter(const ValueType& data, SingleLinkedList::ListIterator it) {
    insert(data, it.getNodeIndex() + 1);
}



void SingleLinkedList::clear() {
    delete _head;
    _head = nullptr;
    _size = 0;
}

void SingleLinkedList::popBack() {
    remove(size() - 1);
}

void SingleLinkedList::popFront() {
    remove(0);
}

void SingleLinkedList::remove(size_t pos) {
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

void SingleLinkedList::removeAfter(SingleLinkedList::ListIterator it) {
    remove(it.getNodeIndex() + 1);
}

void SingleLinkedList::remove(SingleLinkedList::ListIterator it) {
    remove(it.getNodeIndex());
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



void SingleLinkedList::forEach(ValueType& (*fn)(ValueType&)) {
    if (!_head) {
        return;
    }
    Node* cur = _head;
    do {
        cur->_data = fn(cur->_data);
        cur = cur->_next;
    } while (cur);
}

SingleLinkedList SingleLinkedList::map(ValueType& (*fn)(ValueType&)) const {
    SingleLinkedList list = *this;
    list.forEach(fn);
    return list;
}

void SingleLinkedList::filter(bool (*fn)(ValueType&)) {
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



void SingleLinkedList::reverse() {
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

void SingleLinkedList::reverse(size_t start, size_t end) {
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

SingleLinkedList SingleLinkedList::getReverseList() const {
    SingleLinkedList list = *this;
    list.reverse();
    return list;
}

SingleLinkedList SingleLinkedList::getReverseList(size_t start, size_t end) const {
    SingleLinkedList list = *this;
    list.reverse(start, end);
    return list;
}



SingleLinkedList::ListIterator SingleLinkedList::begin() const {
    return SingleLinkedList::ListIterator(_head, 0);
}

SingleLinkedList::ListIterator SingleLinkedList::end() const {
    return SingleLinkedList::ListIterator(nullptr, size());
}



SingleLinkedList::Node::Node(const ValueType& data)  {
    _data = data;
    _next = nullptr;
}

SingleLinkedList::Node::~Node() {
    delete _next;
}


SingleLinkedList::ListIterator::ListIterator(Node* ptr, size_t index) : _ptr(ptr), _index(index) {}



ValueType& SingleLinkedList::ListIterator::operator*() {
    return _ptr->_data;
}

ValueType* SingleLinkedList::ListIterator::operator->() {
    return &(_ptr->_data);
}

SingleLinkedList::ListIterator& SingleLinkedList::ListIterator::operator++() {
    _ptr = _ptr->_next;
    ++_index;
    return *(this);
}

SingleLinkedList::ListIterator SingleLinkedList::ListIterator::operator++(int notUsed) {
    ListIterator tmp = *this;
    ++(*this);
    return tmp;
}

bool SingleLinkedList::ListIterator::operator!=(SingleLinkedList::ListIterator& other) {
    return _ptr != other._ptr;
}

bool SingleLinkedList::ListIterator::operator==(SingleLinkedList::ListIterator& other) {
    return _ptr == other._ptr;
}

std::ptrdiff_t SingleLinkedList::ListIterator::operator-(SingleLinkedList::ListIterator& other) {
    return _ptr - other._ptr;
}



size_t SingleLinkedList::ListIterator::getNodeIndex() const {
    return _index;
}
