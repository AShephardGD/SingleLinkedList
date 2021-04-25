#ifndef SINGLELINKEDLIST_H_INCLUDED
#define SINGLELINKEDLIST_H_INCLUDED

#include <cstdlib>
#include <iostream>

using ValueType = int;

class SingleLinkedList {
private:
    class Node {
    public:
        Node* _next;
        ValueType _data;
        Node(const ValueType& data);
        ~Node();
    };

    Node* _head;
    size_t _size;

public:
    class ListIterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = ValueType;
            using pointer           = ValueType*;
            using reference         = ValueType&;

            ListIterator(Node* ptr, size_t index);

            ValueType& operator*();
            ValueType* operator->();
            ListIterator& operator++();
            ListIterator operator++ (int notUsed);
            bool operator!=(ListIterator& other);
            bool operator==(ListIterator& other);
            std::ptrdiff_t operator-(ListIterator& other);

            size_t getNodeIndex() const;
        private:
            Node* _ptr;
            size_t _index;
    };
    SingleLinkedList();
    SingleLinkedList(const SingleLinkedList& other);
    SingleLinkedList(SingleLinkedList&& other) noexcept;

    SingleLinkedList& operator=(const SingleLinkedList& other);
    SingleLinkedList& operator=(SingleLinkedList&& other) noexcept;

    ~SingleLinkedList();

    ValueType& operator[](const size_t pos);
    const ValueType& operator[](const size_t pos) const;
    size_t size() const;
    ListIterator getNode(const size_t pos) const;

    bool find(const ValueType& needle) const;
    bool isEmpty() const;

    void pushBack(const ValueType& data);
    void pushFront(const ValueType& data);
    void insert(const ValueType& data, size_t pos);
    void insertAfter(const ValueType& data, ListIterator it);

    void clear();
    void popBack();
    void popFront();
    void remove(size_t pos);
    void removeAfter(ListIterator it);
    void remove(ListIterator it);

    void print(std::ostream& stream = std::cout) const;

    friend std::ostream& operator<<(std::ostream& stream, const SingleLinkedList& list);

    void forEach(ValueType& (*fn)(ValueType&));
    SingleLinkedList map(ValueType& (*fn)(ValueType&)) const;
    void filter(bool (*fn)(ValueType&));

    void reverse();
    void reverse(size_t start, size_t end);
    SingleLinkedList getReverseList() const;
    SingleLinkedList getReverseList(size_t start, size_t end) const;

    ListIterator begin() const;
    ListIterator end() const;
};




#endif // SINGLELINKEDLIST_H_INCLUDED
