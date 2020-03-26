#ifndef DOUBLECIRCLELINKEDLIST_H
#define DOUBLECIRCLELINKEDLIST_H
#include "Node.h"
#include "../grapher.h"
#include <QString>
#include <string>
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
    void AddFirst(T *object)
    {
        Node<T> *newNode = new Node<T>(object);
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
            Last->setNext(newNode);   //newNode is Last's nextNode
            First = newNode;         //newNode is now First
            Size++;
        }
    }
    void AddLast(T *object)
    {
        if (IsEmpty())
        {
            //Since is the same algorithm...
            AddFirst(object);
        }
        else
        {
            Node<T> *newNode = new Node<T>(object);
            newNode->setNext(First); //First is newNode's nextNode
            newNode->setPrev(Last);  //Last is newNode's prevNode
            Last->setNext(newNode);   //newNode is Last's nextNode
            First->setPrev(newNode); //newNode is First's prevNode
            Last = newNode;          //newNode is now Last
            Size++;
        }
    }
    void AddAt(T *object, int index)
    {
        if (index == 0)
        {
            //Since the algorithm is better and doesn't have to iterate...
            AddFirst(object);
        }
        else if (index == this->GetSize() - 1)
        {
            //Since the algorithm is better and doesn't have to iterate...
            AddLast(object);
        }
        else if (index > 0 && index < GetSize() - 1)
        {
            //auxNode should be the Node that is being pushed one position forward
            Node<T> *auxNode = GetNodeAt(index);
            Node<T> *newNode = new Node<T>(object);
            auxNode->getPrev()->setNext(newNode); //newNode is the nextNode of auxNode's prevNode
            newNode->setPrev(auxNode->getPrev()); //auxNode's prevNode is the prevNode of newNode
            newNode->setNext(auxNode);            //auxNode is newNode's nextNode
            auxNode->setPrev(newNode);            //newNode is auxNode's prevNode
            Size++;
        }
        else
        {
            //Posible exception. The index is out of bounds.
            throw index;
        }
    }
    Node<T> *GetNodeAt(int index)
    {
        if (index == 0)
        {
            return First;
        }
        else if (index == this->GetSize() - 1)
        {
            return Last;
        }
        else if (index > 0 && index < GetSize() - 1)
        {
            int count = 0;
            Node<T> *auxNode = First;
            //Advancing in the list to obtain the required auxNode
            while (count != index)
            {
                auxNode = auxNode->getNext();
                count++;
            }
            return auxNode;
        }
        else
        {
            //Posible exception. The index is out of bounds.
            throw index;
        }
    }
    QString GenerateGraph(QString name)
    {
        QString dot = "digraph Report{\n"
                      "\trankdir = LR;\n"
                      "\tGraph[label = \"Reporte:" + name + "\" fontname=Arial];\n"
                      "\tnode [colorscheme = rdbu11 color=10 style= filled shape=record fontname=Arial fontcolor=6];\n";
        if(GetSize()>0)
        {
            int count = 0;
            Node<T> *auxNode = First;
            while (count!=GetSize())
            {
                QString gNode = QString("\tn%1").arg(count);//Appends "n" with count (gNode = "n0").
                //This should not be a problem. DoubleCircleLinkedList is used only to contain QString values (Dictionary words) (FOR THIS PROJECT*).
                QString *object = auxNode->getObject();
                dot+=gNode+"[label = \""+ object +"\"];\n";//Appends dot with gNode and auxNode's Object to set label
                //This is to point to the nextNode
                if(count==GetSize()-1)
                {
                    //It's the Last Node so it needs to point First Node
                    dot+="\t" + gNode + " -> " + QString("n%1").arg(0) + "[colorscheme = rdbu11 color = 10];\n";//Appends gNode with his nextNode (in this case is the First "n0").
                }
                else
                {
                    //It's any other node
                    dot+="\t" + gNode + " -> " + QString("n%1").arg(count+1) + "[colorscheme = rdbu11 color = 10];\n";//Appends gNode with his nextNode ("n0->n1").
                }
                //This is to point to the prevNode
                if(count==0)
                {
                    //It's the First Node so it needs to point the Last Node
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(GetSize()-1) + "[colorscheme = rdbu11 color = 9];\n";//Appends gNode with his prevNode (in this case is the Last "n"+GetSize()-1).
                }
                else
                {
                    //It's any other node
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(count-1) + "[colorscheme = rdbu11 color = 9];\n";//Appends gNode with his prevNode ("n1->n0").
                }
                auxNode = auxNode->getNext();
                count++;
            }
            dot += "}";
        }
        else
        {
            dot+="\tn0[shape=none; label=\"null\"]\n";
            dot+="}";
        }
        Grapher *grapher = new Grapher(name);
        return grapher->GenerateGraph(dot);
    }

private:
    Node<T> *First, *Last;
    int Size;
    bool IsEmpty()
    {
        return Size == 0;
    }
};
#endif // DOUBLECIRCLELINKEDLIST_H