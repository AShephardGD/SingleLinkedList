#ifndef SINGLELINKEDLIST_H_INCLUDED
#define SINGLELINKEDLIST_H_INCLUDED

#include <cstdlib>
#include <iostream>

template <typename T>
class SingleLinkedList {
private:
    class Node {
    public:
        Node* _next;
        T _data;
        Node(const T& data);
        ~Node();
    };

    Node* _head;
    size_t _size;

public:
    class ListIterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;

            ListIterator(Node* ptr, size_t index);

            T& operator*();
            T* operator->();
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

    T& operator[](const size_t pos);
    const T& operator[](const size_t pos) const;
    size_t size() const;
    ListIterator getNode(const size_t pos) const;

    bool find(const T& needle) const;
    bool isEmpty() const;

    void pushBack(const T& data);
    void pushFront(const T& data);
    void insert(const T& data, size_t pos);
    void insertAfter(const T& data, ListIterator it);

    void clear();
    void popBack();
    void popFront();
    void remove(size_t pos);
    void removeAfter(ListIterator it);
    void remove(ListIterator it);

    void print(std::ostream& stream = std::cout) const;

    template <typename Type>
    friend std::ostream& operator<<(std::ostream& stream, const SingleLinkedList<Type>& list);

    void forEach(T& (*fn)(T&));
    SingleLinkedList map(T& (*fn)(T&)) const;
    void filter(bool (*fn)(T&));

    void reverse();
    void reverse(size_t start, size_t end);
    SingleLinkedList getReverseList() const;
    SingleLinkedList getReverseList(size_t start, size_t end) const;

    ListIterator begin() const;
    ListIterator end() const;
};


#include "SingleLinkedList.inl"

#endif // SINGLELINKEDLIST_H_INCLUDED
