#ifndef NODE_H
#define NODE_H
template <class T>
class Node
{
private:
    T *Object;
    Node *Next;
    Node *Prev;

public:
    Node()
    {
        this->Object = 0;
        this->Next = 0;
        this->Prev = 0;
    }
    Node(T *object)
    {
        this->Object = object;
        this->Next = 0;
        this->Prev = 0;
    }
    Node *getNext() { return this->Next; }
    Node *getPrev() { return this->Prev; }
    T *getObject() { return this->Object; }
    void setNext(Node *next)
    {
        this->Next = next;
    }
    void setPrev(Node *prev)
    {
        this->Prev = prev;
    }
};
/*
template <class T>
Node<T>* Node<T>::getNext()
{return this->Next;}
*/
#endif // NODE_H
