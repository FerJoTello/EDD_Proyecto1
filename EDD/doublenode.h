#ifndef DOUBLENODE_H
#define DOUBLENODE_H
/** DoubleNode
    Used only by DoubleCircleLinkedList in a private way.
    The user doesn't have interactions with it but with the objects (that's the reason why pointers are used on the object).
    It's a template so can be used dynamically (can operate with any type of object).
    Atributes:
        ->  T *Object: The object that the node is about to "hold".
        ->  QString Representation: The string which is used to create the graphic.
        ->  DoubleNode *Next: The next node that continues on the list.
        ->  DoubleNode *Prev: The previous node that comes from the list.
    Functions:
        ->  DoubleNode(): It's the constructor, initializes its values for future assignation.
        ->  DoubleNode(T* object, QString graphicRepresentation): It's the constructor, initializes Object with the object on the parameter and with its representation.
        ->  DoubleNode *getNext(): Returns Next.
        ->  DoubleNode *getPrev(): Returns Prev.
        ->  T* getObject(): Returns Object.
        ->  void setNext(DoubleNode *next): Assigns the next node.
        ->  void setPrev(DoubleNode *prev): Assigns the previous node.
**/
#include <QString>
template <class T>
class DoubleNode
{
private:
    T *Object;
    QString Representation;
    DoubleNode *Next;
    DoubleNode *Prev;

public:
    DoubleNode()
    {
        this->Object = 0;
        this->Representation = "";
        this->Next = 0;
        this->Prev = 0;
    }
    DoubleNode(T *object, QString representation)
    {
        this->Object = object;
        this->Representation = representation;
        this->Next = 0;
        this->Prev = 0;
    }
    DoubleNode *getNext() { return this->Next; }
    DoubleNode *getPrev() { return this->Prev; }
    T *getObject() { return this->Object; }
    QString getRepresentation() { return this->Representation; }
    void setNext(DoubleNode *next)
    {
        this->Next = next;
    }
    void setPrev(DoubleNode *prev)
    {
        this->Prev = prev;
    }
};
/*
template <class T>
DoubleNode<T>* DoubleNode<T>::getNext()
{return this->Next;}
*/
#endif // DOUBLENODE_H
