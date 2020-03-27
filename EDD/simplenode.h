#ifndef SIMPLENODE_H
#define SIMPLENODE_H
/** SimpleNode
 *  Template that can hold any type of objects.
 *  Since it's used on dynamic structures that can only be accessed by moving forward through each node, only has one pointer to the next node.
 *  Atributes:
 *      *Private*
 *      ->  T *Object: The object of any type that it's being holded on the node.
 *      ->  SimpleNode *Next: The next node on the structure that follows this.
 *  Functions:
 *      *Public*
 *      ->  SimpleNode(): Constructor. Initializes values for future assignations.
 *      ->  SimpleNode(T object): Contructor. Initializes values with the object that's being holded.
 *      ->  SimpleNode *getNext(): Returns the node following it.
 *      ->  T *getObject(): Returns the object that's being contained on the node.
 *      ->  void setNext(SimpleNode *next): Assigns the next node.
**/
template <class T>
class SimpleNode
{
private:
    T *Object;
    SimpleNode *Next;
public:
    SimpleNode()
    {
        this->Object = 0;
        this->Next = 0;
    }
    SimpleNode(T *object)
    {
        this->Object = object;
        this->Next = 0;
    }
    SimpleNode *getNext() { return this->Next; }
    T *getObject() { return this->Object; }
    void setNext(SimpleNode *next)
    {
        this->Next = next;
    }
};
#endif // SIMPLENODE_H
