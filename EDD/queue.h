#ifndef QUEUE_H
#define QUEUE_H
/** Queue
  * Dynamic structure that holds simple nodes (see SimpleNode).
  * FIFO (First In, First Out) behavior
  * Atributes:
  *     *Private*
  *     ->  SimpleNode<T> *First: The first node on the queue and the only one who can be accessed with Dequeue().
  *     ->  SimpleNode<T> *Last: The last node on the queue who was added to the queue.
  *     ->  int Size: The number of nodes/objects/elements on the queue.
  * Functions:
  *     *Public*
  *     ->  Queue(): Constructor. Initializes its values to future assignations.
  *     ->  int GetSize(): Returns the size of the queue.
  *     ->  void Enqueue(T object, QString representation): Creates a new node on the end of the queue.
  *     ->  T *GetDequeuedObject(): Returns the object of the first node, removing it from the queue.
  *     ->  QString GenerateGraph(QString name): Generates a visual representation of the objects that are on the queue.
  *     *Private*
  *     ->  bool IsEmpty(): Checks if the size equals 0, meaning that the queue has 0 nodes.
  *     ->  SimpleNode<T> *Dequeue(): Returns the first node removing it from the queue.
**/
#include <QString>
#include "simplenode.h"
#include "../grapher.h"
template <class T>
class Queue
{
public:
    Queue()
    {
        First = 0;
        Last = 0;
        Size = 0;
    }
    int GetSize(){ return Size; }
    void Enqueue(T *object, QString representation)
    {
        SimpleNode<T> *newNode = new SimpleNode<T>(object, representation);
        if(IsEmpty())
        {
            First = newNode;
            Last = newNode;
            Size++;
        }
        else
        {
            Last->setNext(newNode);
            Last = newNode;
            Size++;
        }
    }
    T *GetDequeuedObject()
    {
        T *object = this->Dequeue()->getObject();
        return object;
    }
    QString GenerateGraph(QString name)
    {
        QString dot = "digraph Report{\n"
                      "\tGraph[label = \"Cola:" + name + "\" fontname=Arial];\n"
                      "\tnode [colorscheme = rdbu11 color=10 style= filled shape=record fontname=Arial fontcolor=6];\n"
                      "\tedge [colorscheme = rdbu11 color=10];\n";
        if(GetSize()>0)
        {
            int count = 0;
            SimpleNode<T> *auxNode = First;
            while(count!=GetSize())
            {
                QString gNode = QString("\tn%1").arg(count);//Appends "n" with count (gNode = "n0").
                //Using the representation indicated previously on the creation of the node.
                QString object = auxNode->getRepresentation();
                dot+=gNode+"[label = \""+ object +"\"];\n";//Appends dot with gNode and auxNode's Object to set label
                if(count!=GetSize()-1)
                {
                    //This is to point to the nextNode
                    dot+="\t" + gNode + " -> " + QString("n%1").arg(count+1) + ";\n";//Appends gNode with his nextNode ("n0->n1").
                }
                auxNode = auxNode -> getNext();
                count++;
            }
        }
        else
        {
            dot+="\tn0[shape=none; label=\"null\"]\n";
        }
        dot += "}";
        Grapher *grapher = new Grapher(name);
        return grapher->GenerateGraph(dot);
    }
private:
    SimpleNode<T> *First, *Last;
    int Size;
    bool IsEmpty(){ return Size == 0; }
    SimpleNode<T> *Dequeue()
    {
        if(!IsEmpty())
        {
            SimpleNode<T> *newNode = First;
            First = First->getNext();
            this->Size--;
            return newNode;
        }
        else
        {
            //Posible exception. The Queue does not have any object
            throw -1;
        }
    }
};

#endif // QUEUE_H
