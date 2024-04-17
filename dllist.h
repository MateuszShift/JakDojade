#pragma once
#include <iostream>
#include "Coordinate.h"

template <class T>
class listNode
{
public:
    T *data;
    listNode<T> *next;
    listNode<T> *previous;

    listNode(T *data)
    {
        this->data = data;
        next = nullptr;
        previous = nullptr;
    }
    ~listNode() {}

    listNode<T> &operator=(const listNode<T> &other)
    {
        if (this != &other)
        {
            data = other.data;
            next = other.next;
            previous = other.previous;
        }
        return *this;
    }

    bool operator==(const listNode<T> &other) const
    {
        return data == other.data;
    }

    bool operator==(const char *name) const
    {
        return *data == name;
    }

    friend std::ostream &operator<<(std::ostream &out, const listNode<T> *node)
    {
        out << node->data;
        return out;
    }
};

template <class T>
class DoublyLinkedList
{
private:
    int size;

public:
    listNode<T> *head;
    listNode<T> *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoublyLinkedList()
    {
        listNode<T> *curr = head;
        listNode<T> *temp;
        while (curr != nullptr)
        {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    listNode<T> *add(T *data)
    {
        listNode<T> *newNode = new listNode<T>(data);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        size++;
        return newNode;
    }

    void remove(listNode<T> *node)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->previous == nullptr)
        {
            head = node->next;
        }
        else
        {
            node->previous->next = node->next;
        }
        if (node->next == nullptr)
        {
            tail = node->previous;
        }
        else
        {
            node->next->previous = node->previous;
        }
        delete node;
        size--;
    }

    void printList()
    {
        listNode<T> *curr = head;
        while (curr != nullptr)
        {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
    }
    bool operator==(const DoublyLinkedList<T> &other)
    {
        return true;
    }

    listNode<T> *find(const char *name)
    {
        listNode<T> *node = head;

        while (node)
        {
            if (*(node->data) == name)
            {
                return node;
            }
            node = node->next;
        }
        return NULL;
    }

    listNode<T> *find(const Coordinate &coord)
    {
        listNode<T> *node = head;

        while (node)
        {
            if (*(node->data) == coord)
            {
                return node;
            }
            node = node->next;
        }
        return NULL;
    }
    // dopisac szukanie przez wspolrzedne
};

template <class T>
class DoublyLinkedContainer
{
private:
    int size;

public:
    listNode<T> *head;
    listNode<T> *tail;

public:
    DoublyLinkedContainer()
    {
        this->clean();
    }

    ~DoublyLinkedContainer()
    {
    }

    void clean()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    listNode<T> *put(listNode<T> *newNode)
    {
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            newNode->previous = nullptr;
            newNode->next = nullptr;
        }
        else
        {
            tail->next = newNode;
            newNode->previous = tail;
            newNode->next = nullptr;
            tail = newNode;
        }
        size++;
        return newNode;
    }

    listNode<T> *putSorted(listNode<T> *newNode, bool asc)
    {
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            newNode->previous = nullptr;
            newNode->next = nullptr;

            size++;
            return newNode;
        }
        else
        {
            listNode<T> *node = head;

            while (node)
            {
                if (asc)
                {
                    if (*(node->data) >= *(newNode->data))
                    {
                        listNode<T> *previous = node->previous;

                        if (node == head)
                        {
                            newNode->previous = nullptr;
                            newNode->next = node;
                            node->previous = newNode;
                            head = newNode;
                        }
                        else
                        {
                            newNode->previous = previous;
                            newNode->next = node;
                            node->previous = newNode;
                            previous->next = newNode;
                        }

                        size++;
                        return newNode;
                    }
                }
                node = node->next;
            }
        }
        tail->next = newNode;
        newNode->previous = tail;
        newNode->next = nullptr;
        tail = newNode;

        size++;
        return newNode;
    }

    listNode<T> *get(listNode<T> *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->previous == nullptr)
        {
            head = node->next;
        }
        else
        {
            node->previous->next = node->next;
        }
        if (node->next == nullptr)
        {
            tail = node->previous;
        }
        else
        {
            node->next->previous = node->previous;
        }
        size--;
        return node;
    }

    void printList()
    {
        listNode<T> *curr = head;
        while (curr != nullptr)
        {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
    }
    bool operator==(const DoublyLinkedList<T> &other)
    {
        return true;
    }

    listNode<T> *find(const char *name)
    {
        listNode<T> *node = head;

        while (node)
        {
            if (*(node->data) == name)
            {
                return node;
            }
            node = node->next;
        }
        return NULL;
    }

    listNode<T> *find(const Coordinate &coord)
    {
        listNode<T> *node = head;

        while (node)
        {
            if (*(node->data) == coord)
            {
                return node;
            }
            node = node->next;
        }
        return NULL;
    }
};
