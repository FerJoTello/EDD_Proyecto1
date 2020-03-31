#include <QCoreApplication>
#include <QString>
#include <chrono>
#include <thread>
#include "iostream"
#include "EDD/doublecirclelinkedlist.h"
#include "EDD/queue.h"
#include "EDD/binarysearchtree.h"
#include "EDD/linkedlist.h"
#include "EDD/dispersedmatrix.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    DoubleCircleLinkedList<QString> *doblecircular = new DoubleCircleLinkedList<QString>();
    QString *obj1 = new QString("1");
    QString *obj2 = new QString("2");
    QString *obj3 = new QString("3");
    QString *obj4 = new QString("4");
    QString *obj5 = new QString("5");
    QString *obj6 = new QString("6");
    doblecircular->AddFirst(obj1, "es");
    doblecircular->AddLast(obj2, "una");
    doblecircular->AddFirst(obj3, "Esto");
    doblecircular->AddLast(obj4, "lista");
    doblecircular->AddAt(obj5, "nueva", 3);
    doblecircular->AddAt(obj6, ":v", 5);
    QString salida = doblecircular->GenerateGraph("Mi_DCLL01"); //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    cout << salida.toStdString().c_str() << endl;

    Queue<QString> *cola = new Queue<QString>();
    QString *obj11 = new QString("1");
    QString *obj21 = new QString("2");
    QString *obj31 = new QString("3");
    QString *obj41 = new QString("4");
    QString *obj51 = new QString("5");
    QString *obj61 = new QString("6");
    cola->Enqueue(obj11, "Esto");
    cola->Enqueue(obj21, "es");
    cola->Enqueue(obj31, "una");
    cola->Enqueue(obj41, "nueva");
    cola->Enqueue(obj51, "cola");
    cola->Enqueue(obj61, ":v");
    QString salidax = cola->GenerateGraph("Mi_Cola01"); //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    cout << salidax.toStdString().c_str() << endl;
    cola->GetDequeuedObject();
    cola->GetDequeuedObject();
    QString salid2 = cola->GenerateGraph("Mi_Cola02"); //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    cout << salid2.toStdString().c_str() << endl;

    BinarySearchTree<QString> *arbol = new BinarySearchTree<QString>();
    QString *obj12 = new QString("1");
    QString *obj22 = new QString("2");
    QString *obj32 = new QString("3");
    QString *obj42 = new QString("4");
    QString *obj52 = new QString("5");
    QString *obj62 = new QString("6");
    QString *obj72 = new QString("7");
    QString *obj82 = new QString("8");
    arbol->Add(obj12, "Pablo");
    arbol->Add(obj22, "Andres");
    arbol->Add(obj32, "Fernando");
    arbol->Add(obj42, "Josue");
    arbol->Add(obj52, "Sergio");
    arbol->Add(obj62, "Carlos");
    arbol->Add(obj72, "Kevin");
    arbol->Add(obj82, "Zucely");
    QString salidaArbol = arbol->GenerateTreeGraph("Mi_Arbol02");
    cout << "Ruta de la imagen:" << endl;
    cout << salidaArbol.toStdString().c_str() << endl;
    QString salidaArbolPreOrder = arbol->GeneratePreOrderGraph("Mi_PreOrder02");
    cout << "Ruta de la imagen:" << endl;
    cout << salidaArbolPreOrder.toStdString().c_str() << endl;
    QString salidaArbolInOrder = arbol->GenerateInOrderGraph("Mi_InOrder02");
    cout << "Ruta de la imagen:" << endl;
    cout << salidaArbolInOrder.toStdString().c_str() << endl;
    QString salidaArbolPostOrder = arbol->GeneratePostOrderGraph("Mi_PostOrder02");
    cout << "Ruta de la imagen:" << endl;
    cout << salidaArbolPostOrder.toStdString().c_str() << endl;

    LinkedList<QString> *lista = new LinkedList<QString>();
    QString *obj10 = new QString("1");
    QString *obj20 = new QString("2");
    QString *obj30 = new QString("3");
    QString *obj40 = new QString("4");
    QString *obj50 = new QString("5");
    QString *obj60 = new QString("6");
    lista->AddFirst(obj10, "es");
    lista->AddLast(obj20, "una");
    lista->AddFirst(obj30, "Esto");
    lista->AddLast(obj40, "lista");
    lista->AddAt(obj50, "nueva", 3);
    lista->AddAt(obj60, ":v", 5);
    QString sal = lista->GenerateGraph("Mi_lista01"); //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    cout << sal.toStdString().c_str() << endl;
*/
    DispersedMatrix<QString> *matriz = new DispersedMatrix<QString>();
    QString *obj1m = new QString("1");
    QString *obj2m = new QString("2");
    QString *obj3m = new QString("3");
    QString *obj4m = new QString("4");
    QString *obj5m = new QString("5");
    QString *obj6m = new QString("6");
    QString *obj7m = new QString("7");
    QString *obj8m = new QString("8");
    QString *obj9m = new QString("9");
    QString *obj10m = new QString("10");
    //QString *obj11m = new QString("11");
    matriz->Add(2,2,obj1m,"X=2, Y=2",1);
    matriz->Add(3,2,obj2m,"X=3, Y=2",1);
    matriz->Add(4,2,obj3m,"X=4, Y=2",1);
    matriz->Add(5,2,obj4m,"X=5, Y=2",1);
    QString salidamatriz = matriz->GenerateGraph("Fila1");
    cout << "Ruta de la imagen:" << endl;
    cout << salidamatriz.toStdString().c_str() << endl;
    matriz->Add(4,1,obj5m,"X=4, Y=1",1);
    matriz->Add(4,3,obj6m,"X=4, Y=3",1);
    matriz->Add(4,4,obj7m,"X=4, Y=4",1);
    salidamatriz = matriz->GenerateGraph("Columna1");
    cout << "Ruta de la imagen:" << endl;
    cout << salidamatriz.toStdString().c_str() << endl;
    matriz->Add(5,4,obj8m,"X=5, Y=4",1);
    matriz->Add(6,4,obj9m,"X=6, Y=4",1);
    matriz->Add(7,4,obj10m,"X=7, Y=4",1);
    salidamatriz = matriz->GenerateGraph("Fila2");
    cout << "Ruta de la imagen:" << endl;
    cout << salidamatriz.toStdString().c_str() << endl;

    return a.exec();
}
