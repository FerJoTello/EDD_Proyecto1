#include <QCoreApplication>
#include <QString>
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
    QString *obj5 = new QString("nueva");
    QString *obj6 = new QString("cola");
    QString *obj7 = new QString(":v");
    cola->Enqueue(obj1);
    cola->Enqueue(obj2);
    cola->Enqueue(obj3);
    cola->Enqueue(obj5);
    cola->Enqueue(obj6);
    cola->Enqueue(obj7);
    QString salida = cola->GenerateGraph("Mi Cola 01");
    cout << "Ruta de la imagen:" << endl;
    cout << salida.toStdString().c_str() << endl;
    return a.exec();
}
