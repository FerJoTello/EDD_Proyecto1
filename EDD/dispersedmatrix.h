#ifndef FOURLINKSNODE_H
#define FOURLINKSNODE_H
#include <QString>
#include <string>
#include "EDD/linkedlist.h"
#include "../grapher.h"
template <class T>
class FourLinksNode
{
private:
    T *Object;
    std::string Representation;

public:
    FourLinksNode *Left, *Right, *Up, *Down;
    int XPos, YPos;
    int Multiplier;
    bool AddedPreviously;
    FourLinksNode()
    {
        Left = Right = Up = Down = 0;
        Object = 0;
        Representation = "";
        XPos = YPos = -1;
        Multiplier = -1;
        AddedPreviously = false;
    }
    FourLinksNode(T *object, std::string representation, int multiplier)
    {
        Object = object;
        Representation = representation;
        Left = Right = Up = Down = 0;
        XPos = YPos = -1;
        Multiplier = multiplier;
        AddedPreviously = false;
    }
    T *getObject() { return this->Object; }
    std::string getRepresentation() { return this->Representation; }

};
#endif //FOURLINKSNODE_H
#ifndef DISPERSEDMATRIX_H
#define DISPERSEDMATRIX_H
template <class T>
class DispersedMatrix
{
public:
    FourLinksNode<T> *Head;
    DispersedMatrix()
    {
        Head = new FourLinksNode<T>(0, "X=0, Y=0", -1);
        Head->XPos = 0;
        Head->YPos = 0;
    }
    void Add(int x, int y, T *object, std::string representation, int multiplier)
    {
        FourLinksNode<T> *newNode = new FourLinksNode<T>(object, representation, multiplier);
        //CheckX
        try
        {
            CheckX(x);
        }
        catch (int)
        {
            //Does nothing. The exception indicates that the column already exists
            //But does not affect here.
        }
        //CheckY
        try
        {
            CheckY(y);
        }
        catch (int)
        {
            //Does nothing. The exception indicates that the column already exists
            //But does not affect here.
        }
        Insert(x, y, newNode);
    }
    QString GenerateGraph(QString name)
    {
        QString dot = "digraph Report{\n"
                      "\tGraph[label = \"Matriz:" + name + "\" fontname=Arial];\n"
                             "\tnode [colorscheme = rdbu11 color=11 style= filled shape=box fontname=Arial fontcolor=6];\n"
                             "\tedge [colorscheme = rdbu11 color=11];\n";
        FourLinksNode<T> *rowNode = Head;   //rowNode indicates which row is being iterated.
        //This will iterate until there are no more rows on the matrix
        while(rowNode!=0)
        {
            FourLinksNode<T> *columnNode = rowNode; //the rowNode is the first in the row.
            QString rowGroup = "{rank = same;";
            //This will iterate until there are no more elements (columns) on the row.
            while(columnNode!=0)
            {

                QString gNode = QString("\tn%1").arg(columnNode->XPos) + QString("_%1").arg(columnNode->YPos); //Appends "n" with XPos and YPos (gNode = "n0_0").
                QString object = columnNode->getRepresentation().c_str();
                if(columnNode->Multiplier==1)
                {
                    dot += gNode + QString("[label = \"" + object + "\" color = 8 group = %1];\n").arg(columnNode->XPos);
                }
                else if(columnNode->Multiplier==2)
                {
                    dot += gNode + QString("[label = \"" + object + "\" color = 4 group = %1];\n").arg(columnNode->XPos);
                }
                else if(columnNode->Multiplier==3)
                {
                    dot += gNode + QString("[label = \"" + object + "\" color = 2 group = %1];\n").arg(columnNode->XPos);
                }
                else
                {
                    dot += gNode + QString("[label = \"" + object + "\" group = %1];\n").arg(columnNode->XPos);   //Appends dot with gNode and auxNode's Object to set label
                }
                if(columnNode->Right!=0)
                {
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(columnNode->Right->XPos) + QString("_%1").arg(columnNode->Right->YPos)+ ";\n"; //Appends gNode with his right ("n0_0->n0_1").
                }
                if(columnNode->Left!=0)
                {
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(columnNode->Left->XPos) + QString("_%1").arg(columnNode->Left->YPos)+ ";\n"; //Appends gNode with his left.
                }
                if(columnNode->Up!=0)
                {
                    dot += "\t" + gNode + " -> " + QString("n%1").arg(columnNode->Up->XPos) + QString("_%1").arg(columnNode->Up->YPos)+ ";\n"; //Appends gNode with his up.
                }
                if(columnNode->Down!=0)
                {
                    if(columnNode->Down->XPos==0)
                    {
                        dot += "\t" + gNode + " -> " + QString("n%1").arg(columnNode->Down->XPos) + QString("_%1").arg(columnNode->Down->YPos)+ ";\n"; //Appends gNode with his down.
                    }
                    else if(columnNode->Down->XPos>0)
                    {
                        dot += "\t" + gNode + " -> " + QString("n%1").arg(columnNode->Down->XPos) + QString("_%1").arg(columnNode->Down->YPos)+ "[constraint = false];\n"; //Appends gNode with his down.
                    }
                }
                rowGroup += gNode;
                columnNode = columnNode->Right; //Repeats with the next node.
            }
            rowGroup +=  "}\n";
            dot += rowGroup;
            rowNode = rowNode->Down;
        }
        dot += "}";
        Grapher *grapher = new Grapher(name);
        return grapher->GenerateGraph(dot);
    }
    FourLinksNode<T> *GetNodeAt(int xstart, int ystart)
    {
        FourLinksNode<T> *columnNode = GetAuxX(Head, xstart + 1);           //columnNode is the column where the node requested was placed (since it's necessary to have the exact column, the index is 1 greater -> 'x + 1').
        FourLinksNode<T> *requestedNode = GetAuxY(columnNode, ystart + 1);  //requested node (since it's necessary to have the exact column, the index is 1 greater -> 'x + 1').
        return requestedNode;
    }
    void DeleteAt(int x, int y)
    {
        FourLinksNode<T> *columnNode = GetAuxX(Head, x + 1);        //columnNode is the column where the newNode is going to be added (since it's necessary to have the exact column, the index is 1 greater -> 'x + 1').
        FourLinksNode<T> *auxYNode = GetAuxY(columnNode, y +1);
        if(auxYNode->Right!=0)
        {
            auxYNode->Right->Left=auxYNode->Left;
            auxYNode->Left->Right=auxYNode->Right;
        }
        else if(auxYNode->Right==0)
        {
            auxYNode->Left->Right=0;
        }
        if(auxYNode->Down!=0)
        {
            auxYNode->Down->Up=auxYNode->Up;
            auxYNode->Up->Down=auxYNode->Down;
        }
        else if(auxYNode->Down==0)
        {
            auxYNode->Up->Down=0;
        }
        if(columnNode->Down==0)
        {
            if(columnNode->Right!=0)
            {
                columnNode->Right->Left=columnNode->Left;
                columnNode->Left->Right=columnNode->Right;
            }
            else if (columnNode->Right==0)
            {
                columnNode->Left->Right=0;
            }
        }
        FourLinksNode<T> *rowNode = GetAuxY(Head, y + 1);
        if(rowNode->Right==0)
        {
            if(rowNode->Down!=0)
            {
                rowNode->Down->Up=rowNode->Up;
                rowNode->Up->Down=rowNode->Down;
            }
            else if (rowNode->Down==0)
            {
                rowNode->Up->Down=0;
            }
        }
    }

private:
    int Rows, Columns;
    FourLinksNode<T> *GetAuxX(FourLinksNode<T> *start, int x)
    {
        //auxNode is the previous node according index 'x'
        FourLinksNode<T> *auxNode = start;
        //Obtaining the prevNode as requeried (important that the auxNode's Right can't have the same index as x and can't be greater).
        while(auxNode->Right!=0 && auxNode->Right->XPos < x)
        {
            auxNode = auxNode->Right;
        }
        return auxNode;
    }
    FourLinksNode<T> *GetAuxY(FourLinksNode<T> *start, int y)
    {
        //auxNode is the previous node according index 'y'
        FourLinksNode<T> *auxNode = start;
        //Obtaining the prevNode as requeried (important that the auxNode's Down can't have the same index as y and can't be greater).
        while(auxNode->Down!=0 && auxNode->Down->YPos < y)
        {
            auxNode = auxNode->Down;
        }
        return auxNode;
    }
    void CheckX(int x)
    {
        //auxNode is the previous node according index 'x'
        FourLinksNode<T> *auxNode = GetAuxX(Head, x);
        FourLinksNode<T> *newNode = new FourLinksNode<T>(0, QString("X=%1").arg(x).toStdString(), -1);
        AddX(newNode, x, 0, auxNode);
    }
    void CheckY(int y)
    {
        //auxNode is the previous node according index 'y'
        FourLinksNode<T> *auxNode = GetAuxY(Head, y);
        FourLinksNode<T> *newNode = new FourLinksNode<T>(0, QString("Y=%1").arg(y).toStdString(), -1);
        AddY(newNode, 0, y, auxNode);
    }
    void Insert(int x, int y, FourLinksNode<T> *newNode)
    {
        FourLinksNode<T> *columnNode = GetAuxX(Head, x + 1);        //columnNode is the column where the newNode is going to be added (since it's necessary to have the exact column, the index is 1 greater -> 'x + 1').
        FourLinksNode<T> *auxYNode = GetAuxY(columnNode, y);        //auxYNode is the previous node according to 'y'
        //This may throw an exception, indicating that the node already exists. Should be handled when the function 'Add' is called.
        AddY(newNode, x, y, auxYNode);
        FourLinksNode<T> *rowNode = GetAuxY(Head, y + 1);           //rowNode is the row where the newNode is going to be added (since it's necessary to have the exact column, the index is 1 greater -> 'y + 1').
        FourLinksNode<T> *auxXNode = GetAuxX(rowNode, x);           //auxXNode is the previous node according to 'x'
        //This may throw an exception, indicating that the node already exists. Should be handled when the function 'Add' is called.
        AddX(newNode, x, y, auxXNode);
    }
    void AddY(FourLinksNode<T> *newNode, int xIndex, int yIndex, FourLinksNode<T> *auxNode)
    {
        if (auxNode->Down==0 && auxNode->YPos!=yIndex)
        {
            //Appends a new node at the end of the column
            newNode->XPos = xIndex;
            newNode->YPos = yIndex;
            auxNode->Down = newNode;
            newNode->Up = auxNode;
        }
        //If the auxNode's Down has the same YPos as y means that can't be added because already exists.
        else if (auxNode->Down!=0 && auxNode->Down->YPos!=yIndex && auxNode->YPos!=yIndex)
        {
            //Appends a new node between the aux and his next
            newNode->XPos = xIndex;
            newNode->YPos = yIndex;
            newNode->Down = auxNode->Down;
            auxNode->Down->Up = newNode;
            auxNode->Down = newNode;
            newNode->Up = auxNode;
        }
        else
        {
            //It can't be added. A node with the same position already exists.
            throw -1;
        }
    }
    void AddX(FourLinksNode<T> *newNode, int xIndex, int yIndex, FourLinksNode<T> *auxNode)
    {
        if (auxNode->Right==0 && auxNode->XPos!=xIndex)
        {
            //Appends a new node at the end of the row
            newNode->XPos = xIndex;
            newNode->YPos = yIndex;
            auxNode->Right = newNode;
            newNode->Left = auxNode;
        }
        //If the auxNode's Right has the same XPos as x means that can't be added because already exists.
        else if(auxNode->Right!=0 && auxNode->Right->XPos!=xIndex && auxNode->XPos!=xIndex)
        {
            //Appends a new node between the aux and his next
            /*                  Example                      */
            //The nodes are actually like this: [1]<->[2]<->[5]
            //[2] is the auxNode
            //[4] is the newNode that is asked to add
            newNode->XPos = xIndex;
            newNode->YPos = yIndex;
            newNode->Right=auxNode->Right;  //[4]->[5]          ([5] is auxNode's Right)
            auxNode->Right->Left=newNode;   //[4]<->[5]         ([5]'s Left is newNode)
            auxNode->Right=newNode;         //[2]->[4]<->[5]    ([4] is the new auxNode's Right)
            newNode->Left=auxNode;          //[2]<->[4]<->[5]   ([2] is the new newNode's Left)
        }
        else
        {
            //It can't be added. A node with the same position already exists.
            throw -1;
        }
    }

};
#endif // DISPERSEDMATRIX_H
