#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "simplenode.h"
#include "../grapher.h"
template <class T>
class LinkedList
{
public:
    LinkedList()
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
        SimpleNode<T> *newNode = new SimpleNode<T>(object, representation);
        if (IsEmpty())
        {
            //Assigns newNode as First and Last.
            First = newNode;
            Last = newNode;
            Size++;
        }
        else
        {
            newNode->setNext(First);
            First = newNode;
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
            SimpleNode<T> *newNode = new SimpleNode<T>(object, representation);
            Last->setNext(newNode);
            Last = newNode;
            Size++;
        }
    }
    void AddAt(T *object, QString representation, int index)
    {
        if (index > 0 && index < GetSize())
        {
            //Since GetNodeAt returns the node at the specified index it's necesary to obtain the node a position before the indicated index to add the new node to the list.
            SimpleNode<T> *auxNode = GetNodeAt(index - 1);
            SimpleNode<T> *newNode = new SimpleNode<T>(object, representation);
            newNode->setNext(auxNode->getNext()); //the nextNode of the auxNode is the nextNode of the newNode
            auxNode->setNext(newNode);            //the newNode is the nextNode of the auxNode.
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
                      "\tGraph[label = \"ListaSimple:" +
                      name + "\" fontname=Arial];\n"
                             "\tnode [colorscheme = rdbu11 color=10 style= filled shape=record fontname=Arial fontcolor=6];\n"
                             "\tedge [colorscheme = rdbu11 color=10];\n";
        if (GetSize() > 0)
        {
            int count = 0;
            SimpleNode<T> *auxNode = First;
            //Repeats the same algorithm except for the last node
            while (count != GetSize() - 1)
            {
                QString gNode = QString("\tn%1").arg(count++); //Appends "n" with count (gNode = "n0").
                QString object = auxNode->getRepresentation();
                dot += gNode + "[label = \"" + object + "\"];\n";                 //Appends dot with gNode and auxNode's Object to set label
                dot += "\t" + gNode + " -> " + QString("n%1").arg(count) + ";\n"; //Appends gNode with his nextNode ("n0->n1").
                auxNode = auxNode->getNext();
            }
            QString gNode = QString("\tn%1").arg(count++); //This is the last node.
            QString object = auxNode->getRepresentation();
            dot += gNode + "[label = \"" + object + "\"];\n"; //Appends dot with gNode and auxNode's Object to set label
            //Since the last node doesn't have a next node does not append anything else.
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
    SimpleNode<T> *First, *Last;
    int Size;
    bool IsEmpty()
    {
        return Size == 0;
    }
    SimpleNode<T> *GetNodeAt(int index)
    {
        if (index > 0 && index < GetSize())
        {
            int count = 0;
            SimpleNode<T> *auxNode = First;
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
        else if (index == this->GetSize())
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
#endif // LINKEDLIST_H
