#ifndef SINGLELINKEDLIST_H_INCLUDED
#define SINGLELINKEDLIST_H_INCLUDED

#include <cstdlib>
#include <iostream>

class SingleLinkedList {
public:
    SingleLinkedList();
    SingleLinkedList(const SingleLinkedList& other);
    SingleLinkedList(SingleLinkedList&& other) noexcept;

    SingleLinkedList& operator=(const SingleLinkedList& other);
    SingleLinkedList& operator=(SingleLinkedList&& other) noexcept;

    ~SingleLinkedList();

    void append(int data);

    bool find(int needle) const;
    bool isEmpty() const;

    void clear();
    int popBack();

    void print(std::ostream& stream = std::cout) const;

    friend std::ostream& operator<<(std::ostream& stream, const SingleLinkedList& list);

    void forEach(int (*fn)(int));
    SingleLinkedList map(int (*fn)(int)) const;
    void filter(bool (*fn)(int));

private:
    class Node {
    public:
        Node* _next;
        int _data;
        Node(int data) {
            _data = data;
            _next = nullptr;
        }

        ~Node() {
            delete _next;
        }
    };
    Node* _head;
};




#endif // SINGLELINKEDLIST_H_INCLUDED
