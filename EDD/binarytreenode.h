#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
/** BinaryTreeNode
 *  Template that can hold any type of objects.
 *  It's used on binary search trees. Has two BinaryTreeNodes for the left and right node as the binary tree requieres.
 *  Atributes:
 *      *Private*
 *      ->  T *Object: The object of any type that it's being holded on the node.
 *      ->  QString Representation: The string which is used to create the graphic.
 *      ->  BinaryTreeNode<T> *LeftNode: The left node of the actual node from the binary tree.
 *      ->  BinaryTreeNode<T> *RightNode: The right node of the actual node from the binary tree.
 *  Functions:
 *      *Public*
 *      ->  BinaryTreeNode(): It's the constructor, initializes its values for future assignation.
 *      ->  BinaryTreeNode(T* object, QString representation): It's the constructor, initializes Object with the object on the parameter and with its representation.
 *      ->  BinaryTreeNode *getLeft(): Returns LeftNode.
 *      ->  BinaryTreeNode *getRight(): Returns RightNode
 *      ->  T *getObject(): Returns Object.
 *      ->  QString getRepresentation(): Return the representation used on the graphic.
 *      ->  void setLeft(BinaryTreeNode *leftNode): Assigns the left node of the actual node.
 *      ->  void setRight(BinaryTreeNode *rightNode): Assigns the right node of the actual node.
*/
#include <QString>
template <class T>
class BinaryTreeNode
{
public:
    BinaryTreeNode()
    {
        this->Object = 0;
        this->Representation = "";
        this->LeftNode = 0;
        this->RightNode = 0;
    }
    BinaryTreeNode(T *object, QString representation)
    {
        this->Object = object;
        this->Representation = representation;
        this->LeftNode = 0;
        this->RightNode = 0;
    }
    BinaryTreeNode *getLeft() { return this->LeftNode; }
    BinaryTreeNode *getRight() { return this->RightNode; }
    T *getObject() { return this->Object; }
    QString getRepresentation() { return this->Representation; }
    void setLeft(BinaryTreeNode *leftNode)
    {
        this->LeftNode = leftNode;
    }
    void setRight(BinaryTreeNode *rightNode)
    {
        this->RightNode = rightNode;
    }

private:
    T *Object;
    QString Representation;
    BinaryTreeNode<T> *LeftNode;
    BinaryTreeNode<T> *RightNode;
};
#endif // BINARYTREENODE_H
