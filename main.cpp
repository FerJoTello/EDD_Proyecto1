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

    Queue<QString> *cola = new Queue<QString>();
    QString *obj1 = new QString("Esto");
    QString *obj2 = new QString("es");
    QString *obj3 = new QString("una");
    QString *obj4 = new QString("nueva");
    QString *obj5 = new QString("cola");
    QString *obj6 = new QString(":v");
    cola->Enqueue(obj1);
    cola->Enqueue(obj2);
    cola->Enqueue(obj3);
    cola->Enqueue(obj4);
    cola->Enqueue(obj5);
    cola->Enqueue(obj6);
    QString salida = cola->GenerateGraph("Mi_Cola01");  //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    cout << salida.toStdString().c_str() << endl;
    //sleep_for(seconds(5));
    cola->GetDequeuedObject();
    cola->GetDequeuedObject();
    QString salid2 = cola->GenerateGraph("Mi_Cola02");  //Careful with the names. Should not use whitespace on it.
    cout << "Ruta de la imagen:" << endl;
    //sleep_for(seconds(5));
    cout << salid2.toStdString().c_str() << endl;
    return a.exec();
}
