//Yassin Younis 22101310

#ifndef MOVIERENTALSYSTEM_SORTEDLINKEDLIST_H
#define MOVIERENTALSYSTEM_SORTEDLINKEDLIST_H

#include <iostream>

template<class object>
struct Node {
    object* obj;
    Node<object>* next;

    Node(object* obj) : obj(obj), next(nullptr) {}
    Node(object* obj, Node<object>* nextI) : obj(obj), next(nextI) {}

    ~Node() {
        delete obj;
    }
};

template<class object>
class LinkedList {

private:
    Node<object>* pHead;
    int mCount;

public:
    LinkedList() : mCount(0), pHead(nullptr) {}

    ~LinkedList()
    {
        Node<object>* temp0 = pHead;
        Node<object>* temp1;
        for (int i=0; i<mCount; i++)
        {
            temp1 = temp0->next;
            delete temp0;
            temp0 = temp1;
        }
    }

    int getCount() const
    {
        return  mCount;
    }

    bool add(object* entry)
    {
        Node<object>* temp = pHead;

        if (mCount==0 || *(pHead->obj) >= *entry)
        {
            pHead = new Node<object>(entry);
            pHead->next = temp;
        }
        else
        {
            while (temp->next != nullptr && *(temp->next->obj) <= *entry)
            {
                temp = temp->next;
            }
            Node<object>* temp0 = temp->next;
            temp->next = new Node<object>(entry, temp0);
        }

        mCount++;
        return true;
    }

    bool remove(object entry)
    {
        Node<object>* temp0 = pHead;
        Node<object>* temp1 = pHead;

        if (*(temp0->obj)==entry)  //if entry to remove is the first element.
        {
            pHead = pHead->next;
            delete temp0;
            mCount--;
            return true; //successful operation.
        }
        else
        {
            while (temp1->next != nullptr && *(temp1->next->obj) != entry)
            {
                temp1 = temp1->next;
            }

            if (temp1->next == nullptr) return false;

            temp0 = temp1->next->next;
            delete temp1->next;

            temp1->next = temp0;
            mCount--;

            return true; //successful operation.
        }
    }

    object* get(int pos) const { // assuming correct index is passed

        Node<object>* temp = pHead;

        for (int i = 0; i < pos; i++)
        {
            temp = temp->next;
        }

        return (temp->obj);
    }

};

#endif //MOVIERENTALSYSTEM_SORTEDLINKEDLIST_H
