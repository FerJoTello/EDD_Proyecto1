#include <QCoreApplication>
#include <QString>
#include <chrono>
#include <thread>
#include "iostream"
#include "EDD/doublecirclelinkedlist.h"
#include "EDD/queue.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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
    QString salida = doblecircular->GenerateGraph("Mi_DCLL01");  //Careful with the names. Should not use whitespace on it.
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
    QString salidax = cola->GenerateGraph("Mi_Cola01");  //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    cout << salidax.toStdString().c_str() << endl;
    cola->GetDequeuedObject();
    cola->GetDequeuedObject();
    QString salid2 = cola->GenerateGraph("Mi_Cola02");  //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    cout << salid2.toStdString().c_str() << endl;
    return a.exec();
}
