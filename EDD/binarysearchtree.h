#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "binarytreenode.h"
#include "../grapher.h"
#include "linkedlist.h"
template <class T>
class BinarySearchTree
{
public:
    BinarySearchTree()
    {
        this->Root = 0;
        this->Size = 0;
    }
    void Add(T *object, QString representation)
    {
        BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(object, representation);
        if (IsEmpty())
        {
            this->Root = newNode;
            Size++;
        }
        else
        {
            AddRecursively(this->Root, newNode);
        }
    }
    QString GenerateTreeGraph(QString name)
    {
        QString dot = "digraph Report{\n"
                      "\tGraph[label = \"Arbol:" +
                      name + "\" fontname=Arial];\n"
                             "\tnode [colorscheme = rdbu11 color=10 style= filled fontname=Arial fontcolor=6];\n"
                             "\tedge [colorscheme = rdbu11 color=10];\n";
        if (!IsEmpty())
        {
            int count = 0;
            dot += GetRepresentationRecursively(this->Root, count);
        }
        else
        {
            dot += "\tn0[shape=none; label=\"null\"]\n";
        }
        dot += "}";
        Grapher *grapher = new Grapher(name);
        return grapher->GenerateGraph(dot);
    }
    QString GeneratePreOrderGraph(QString name)
    {
        LinkedList<BinaryTreeNode<T>> preOrderList{};
        if (!IsEmpty())
        {
            this->AddPreOrder(Root, preOrderList);
        }
        return preOrderList.GenerateGraph(name);
    }
    QString GenerateInOrderGraph(QString name)
    {
        LinkedList<BinaryTreeNode<T>> inOrderList{};
        if (!IsEmpty())
        {
            this->AddInOrder(Root, inOrderList);
        }
        return inOrderList.GenerateGraph(name);
    }
    QString GeneratePostOrderGraph(QString name)
    {
        LinkedList<BinaryTreeNode<T>> postOrderList{};
        if (!IsEmpty())
        {
            this->AddPostOrder(Root, postOrderList);
        }
        return postOrderList.GenerateGraph(name);
    }

private:
    BinaryTreeNode<T> *Root;
    int Size;
    bool IsEmpty() { return Size == 0; }
    void AddRecursively(BinaryTreeNode<T> *actualNode, BinaryTreeNode<T> *newNode)
    {
        //The newNode is less than the actualNode.
        if (newNode->getRepresentation().compare(actualNode->getRepresentation()) < 0)
        {
            //It's sent to occuppy the leftNode.
            if (actualNode->getLeft() == 0)
            {
                //If the leftNode is empty it's placed here.
                actualNode->setLeft(newNode);
                this->Size++;
            }
            else
            {
                //The leftNode is not empty so it's sent to AddRecursively again until it finds an empty node.
                AddRecursively(actualNode->getLeft(), newNode);
            }
        }
        //The newNode is greater than the actualNode
        else if (newNode->getRepresentation().compare(actualNode->getRepresentation()) > 0)
        {
            //It's sent to occuppy the rightNode.
            if (actualNode->getRight() == 0)
            {
                //If the leftNode is empty it's placed here.
                actualNode->setRight(newNode);
                this->Size++;
            }
            else
            {
                //The rightNode is not empty so it's sent to AddRecursively again until it finds an empty node.
                AddRecursively(actualNode->getRight(), newNode);
            }
        }
        else
        {
            //The newNode is exactly the same as the actualNode so it's a duplicate value. It's not added to the tree.
            throw 0;
        }
    }
    QString GetRepresentationRecursively(BinaryTreeNode<T> *actualNode, int &count)
    {
        QString gNode = QString("\tn%1").arg(count++); //Appends "n" with count (gNode = "n0") and incresases count (count++).
        QString object = actualNode->getRepresentation();
        QString dotContinuation = gNode + "[label = \"" + object + "\"];\n";
        if (actualNode->getLeft() != 0)
        {
            dotContinuation += "\t" + gNode + " -> " + QString("n%1").arg(count) + ";\n"; //"n0->n1;"
            dotContinuation += GetRepresentationRecursively(actualNode->getLeft(), count);
        }
        if (actualNode->getRight() != 0)
        {
            dotContinuation += "\t" + gNode + " -> " + QString("n%1").arg(count) + ";\n";
            dotContinuation += GetRepresentationRecursively(actualNode->getRight(), count);
        }
        return dotContinuation;
    }
    void AddPreOrder(BinaryTreeNode<T> *actualNode, LinkedList<BinaryTreeNode<T>> &list)
    {
        //PreOrder: Root, Left, Right.
        list.AddLast(actualNode, actualNode->getRepresentation()); //Adds Root
        if (actualNode->getLeft() != 0)
        {
            //There are more nodes so it's called AddPreOrder again
            AddPreOrder(actualNode->getLeft(), list); //Adds Left
        }
        if (actualNode->getRight() != 0)
        {
            //There are more nodes so it's called the AddPreOrder again
            AddPreOrder(actualNode->getRight(), list); //Adds Right
        }
    }
    void AddInOrder(BinaryTreeNode<T> *actualNode, LinkedList<BinaryTreeNode<T>> &list)
    {
        //InOrder: Left, Root, Right.
        if (actualNode->getLeft() != 0)
        {
            //There are more nodes so it's called AddInOrder again
            AddInOrder(actualNode->getLeft(), list); //Adds Left
        }
        list.AddLast(actualNode, actualNode->getRepresentation()); //Adds Root
        if (actualNode->getRight() != 0)
        {
            //There are more nodes so it's called the AddInOrder again
            AddInOrder(actualNode->getRight(), list); //Adds Right
        }
    }
    void AddPostOrder(BinaryTreeNode<T> *actualNode, LinkedList<BinaryTreeNode<T>> &list)
    {
        //PostOrder: Left, Right, Root.
        if (actualNode->getLeft() != 0)
        {
            //There are more nodes so it's called AddPostOrder again
            AddPostOrder(actualNode->getLeft(), list); //Adds Left
        }
        if (actualNode->getRight() != 0)
        {
            //There are more nodes so it's called the AddPostOrder again
            AddPostOrder(actualNode->getRight(), list); //Adds Right
        }
        list.AddLast(actualNode, actualNode->getRepresentation()); //Adds Root
    }
};
#endif // BINARYSEARCHTREE_H
