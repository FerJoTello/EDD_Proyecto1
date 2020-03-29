#ifndef DOUBLECIRCLELINKEDLIST_H
#define DOUBLECIRCLELINKEDLIST_H
/** DoubleCircleLinkedList
 *
**/
#include <QString>
#include <string>
#include "doublenode.h"
#include "../grapher.h"
template <class T>
class DoubleCircleLinkedList
{
public:
    DoubleCircleLinkedList()
    {
        First = 0;
        Last = 0;
        Size = 0;
    }
    int GetSize()
    {
        return Size;
    }
    void AddFirst(T *object, QString representation)
    {
        DoubleNode<T> *newNode = new DoubleNode<T>(object, representation);
        if (IsEmpty())
        {
            //Assigns newNode as First and Last and links them respectively
            newNode->setNext(newNode);
            newNode->setPrev(newNode);
            First = newNode;
            Last = newNode;
            Size++;
        }
        else
        {
            First->setPrev(newNode); //newNode is First's prevNode
            newNode->setNext(First); //First is newNode's nextNode
            newNode->setPrev(Last);  //Last is newNode's prevNode
            Last->setNext(newNode);  //newNode is Last's nextNode
            First = newNode;         //newNode is now First
            Size++;
        }
    }
    void AddLast(T *object, QString representation)
    {
        if (IsEmpty())
        {
            //Since is the same algorithm...
            AddFirst(object, representation);
        }
        else
        {
            DoubleNode<T> *newNode = new DoubleNode<T>(object, representation);
            newNode->setNext(First); //First is newNode's nextNode
            newNode->setPrev(Last);  //Last is newNode's prevNode
            Last->setNext(newNode);  //newNode is Last's nextNode
            First->setPrev(newNode); //newNode is First's prevNode
            Last = newNode;          //newNode is now Last
            Size++;
        }
    }
    void AddAt(T *object, QString representation, int index)
    {
        if (index > 0 && index < GetSize())
        {
            //auxNode should be the DoubleNode that is being pushed one position forward
            DoubleNode<T> *auxNode = GetNodeAt(index);
            DoubleNode<T> *newNode = new DoubleNode<T>(object, representation);
            auxNode->getPrev()->setNext(newNode); //newNode is the nextNode of auxNode's prevNode
            newNode->setPrev(auxNode->getPrev()); //auxNode's prevNode is the prevNode of newNode
            newNode->setNext(auxNode);            //auxNode is newNode's nextNode
            auxNode->setPrev(newNode);            //newNode is auxNode's prevNode
            Size++;
        }
        else if (index == 0)
        {
            //Since the algorithm is better and doesn't have to iterate...
            AddFirst(object, representation);
        }
        else if (index == this->GetSize())
        {
            //Since the algorithm is better and doesn't have to iterate...
            AddLast(object, representation);
        }
        else
        {
            //Posible exception. The index is out of bounds.
            throw index;
        }
    }
    T *GetObjectAt(int index)
    {
        return GetNodeAt(index)->getObject();
    }
    QString GenerateGraph(QString name)
    {
        QString dot = "digraph Report{\n"
                      "\trankdir = LR;\n"
                      "\tGraph[label = \"DobleCircular:" +
                      name + "\" fontname=Arial];\n"
                             "\tnode [colorscheme = rdbu11 color=10 style= filled shape=record fontname=Arial fontcolor=6];\n"
                             "\tedge [colorscheme = rdbu11 color=10];\n";
        if (GetSize() > 0)
        {
            int count = 0;
            DoubleNode<T> *auxNode = First;
            while (count != GetSize())
            {
                QString gNode = QString("\tn%1").arg(count); //Appends "n" with count (gNode = "n0").
                QString object = auxNode->getRepresentation();
                dot += gNode + "[label = \"" + object + "\"];\n"; //Appends dot with gNode and auxNode's Object to set label
                //This is to point to the nextNode
                //(the "arrow" is darker)
                if (count == GetSize() - 1)
                {
                    //It's the Last DoubleNode so it needs to point First DoubleNode
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(0) + ";\n"; //Appends gNode with his nextNode (in this case is the First "n0").
                }
                else
                {
                    //It's any other node
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(count + 1) + ";\n"; //Appends gNode with his nextNode ("n0->n1").
                }
                //This is to point to the prevNode
                //(the "arrow" is lighter)
                if (count == 0)
                {
                    //It's the First node so it needs to point the Last DoubleNode
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(GetSize() - 1) + "[color = 9];\n"; //Appends gNode with his prevNode (in this case is the Last "n"+GetSize()-1).
                }
                else
                {
                    //It's any other node
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(count - 1) + "[color = 9];\n"; //Appends gNode with his prevNode ("n1->n0").
                }
                auxNode = auxNode->getNext();
                count++;
            }
        }
        else
        {
            dot += "\tn0[shape=none; label=\"null\"]\n";
        }
        dot += "}";
        Grapher *grapher = new Grapher(name);
        return grapher->GenerateGraph(dot);
    }

private:
    DoubleNode<T> *First, *Last;
    int Size;
    bool IsEmpty()
    {
        return Size == 0;
    }
    DoubleNode<T> *GetNodeAt(int index)
    {
        if (index > 0 && index < GetSize() - 1)
        {
            int count = 0;
            DoubleNode<T> *auxNode = First;
            //Advancing in the list to obtain the required auxNode
            while (count != index)
            {
                auxNode = auxNode->getNext();
                count++;
            }
            return auxNode;
        }
        else if (index == 0)
        {
            return First;
        }
        else if (index == this->GetSize() - 1)
        {
            return Last;
        }
        else
        {
            //Posible exception. The index is out of bounds.
            throw index;
        }
    }
};
#endif // DOUBLECIRCLELINKEDLIST_H
