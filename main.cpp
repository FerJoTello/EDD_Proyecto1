#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QString>
#include <chrono>
#include <thread>
#include "iostream"
#include "EDD/doublecirclelinkedlist.h"
#include "EDD/queue.h"
#include "EDD/binarysearchtree.h"
#include "EDD/linkedlist.h"
#include "EDD/dispersedmatrix.h"
#include "EDD/doublelinkedlist.h"
#include "chip.h"
#include "player.h"
#include <random>
#include <vector> //Utilizado unicamente en el aleatorio de las fichas
using namespace std;
DoubleCircleLinkedList<QString> *Dictionary = new DoubleCircleLinkedList<QString>();
DoubleCircleLinkedList<Box> *SpecialBoxes = new DoubleCircleLinkedList<Box>();
BinarySearchTree<Player> *PlayersTree = new BinarySearchTree<Player>();
Queue<Chip> *ChipsQueue = new Queue<Chip>();
int Dimention;
bool ReadedFile = false;
int myrandom (int i) { return std::rand()%i;}
void readJson(QString filename){
    QFile file;
    QString val;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = d.object();
    Dimention = jsonObject.value(QStringLiteral("dimension")).toInt();
    //qDebug()<< "Dimension:";
    //qDebug()<< jsonObject.value(QStringLiteral("dimension")).toInt();

    QJsonObject casilla = jsonObject["casillas"].toObject();
    QJsonArray jsonArray3 = casilla["dobles"].toArray();
    QJsonArray jsonArray4 = casilla["triples"].toArray();

    foreach (const QJsonValue & value, jsonArray3) {
        QJsonObject obj = value.toObject();
        int x = obj.value(QStringLiteral("x")).toInt();
        int y = obj.value(QStringLiteral("y")).toInt();
        SpecialBoxes->AddLast(new Box(x,y,2), "nA");
        QJsonArray arrayEvento = obj["dobles"].toArray();
        //qDebug()<< "Coordenada doble x y ";
        //qDebug()<< obj.value(QStringLiteral("x")).toInt();
        //qDebug()<< obj.value(QStringLiteral("y")).toInt();
    }
    foreach (const QJsonValue & value, jsonArray4) {
        QJsonObject obj = value.toObject();
        int x = obj.value(QStringLiteral("x")).toInt();
        int y = obj.value(QStringLiteral("y")).toInt();
        SpecialBoxes->AddLast(new Box(x,y,3), "nA");
        QJsonArray arrayEvento = obj["triples"].toArray();
        //qDebug()<< "Coordenada trple x y ";
        //qDebug()<< obj.value(QStringLiteral("x")).toInt();
        //qDebug()<< obj.value(QStringLiteral("y")).toInt();
    }
    QJsonArray jsonArray5 = jsonObject["diccionario"].toArray();
    //qDebug()<< "DICCIONARIO";
    foreach (const QJsonValue & value, jsonArray5) {
        QJsonObject obj = value.toObject();
        QJsonObject palabra = obj["palabra"].toObject();
        Dictionary->AddLast(new QString(obj.value(QStringLiteral("palabra")).toString()), QString(obj.value(QStringLiteral("palabra")).toString()));
        //qDebug()<< "Palabra de diccionario";
        //qDebug() << obj.value(QStringLiteral("palabra")).toString();
    }

}
int menu()
{
    int selection;
    do
    {
        cout << "Selecciona una opcion:" <<endl;
        cout << "1. Leer Archivo." <<endl;
        cout << "2. Jugar." <<endl;
        cout << "3. Reportes." <<endl;
        cout << "4. Salir." << endl;
        cin >> selection;
        if (selection == 2 && !ReadedFile)
        {
            cout << "No ha sido cargado ningun archivo de entrada." << endl;
        }
    }while(selection<1 && selection>4 && !ReadedFile);
    return selection;
}
void newGame()
{
    cout << "Para iniciar una partida es necesario que primero se ingrese el nombre de los jugadores." <<endl;
    bool player1Valid = false;
    bool player2Valid = false;
    Player *player1;
    Player *player2;
    do
    {
        cout << "Jugador 1, ingresa tu nombre:" << endl;
        std::string inputName;
        try {
            cin >> inputName;
            QString name = QString::fromStdString(inputName);
            player1 = new Player(name);
            PlayersTree->Add(player1, name);
            player1Valid = true;
        } catch (int a) {
            if(a==0)
            {
                cout << "Al parecer ese usuario ya existe. No se ha podido ingresar." <<endl;
            }
        }
    }while(!player1Valid);
    do
    {
        cout << "Jugador 2, ingresa tu nombre:" << endl;
        std::string inputName;
        try {
            cin >> inputName;
            QString name = QString::fromStdString(inputName);
            player2 = new Player(name);
            PlayersTree->Add(player2, name);
            player2Valid = true;
        } catch (int a) {
            if(a==0)
            {
                cout << "Al parecer ese usuario ya existe. No se ha podido ingresar." <<endl;
            }
        }
    }while(!player2Valid);

    Chip *chips[94];
    chips[0] = new Chip(1, 'a');
    chips[1] = new Chip(1, 'a');
    chips[2] = new Chip(1, 'a');
    chips[3] = new Chip(1, 'a');
    chips[4] = new Chip(1, 'a');
    chips[5] = new Chip(1, 'a');
    chips[6] = new Chip(1, 'a');
    chips[7] = new Chip(1, 'a');
    chips[8] = new Chip(1, 'a');
    chips[9] = new Chip(1, 'a');
    chips[10] = new Chip(1, 'a');
    chips[11] = new Chip(1, 'a');//
    chips[12] = new Chip(1, 'e');
    chips[13] = new Chip(1, 'e');
    chips[14] = new Chip(1, 'e');
    chips[15] = new Chip(1, 'e');
    chips[16] = new Chip(1, 'e');
    chips[17] = new Chip(1, 'e');
    chips[18] = new Chip(1, 'e');
    chips[19] = new Chip(1, 'e');
    chips[20] = new Chip(1, 'e');
    chips[21] = new Chip(1, 'e');
    chips[22] = new Chip(1, 'e');
    chips[23] = new Chip(1, 'e');//
    chips[24] = new Chip(1, 'o');
    chips[25] = new Chip(1, 'o');
    chips[26] = new Chip(1, 'o');
    chips[27] = new Chip(1, 'o');
    chips[28] = new Chip(1, 'o');
    chips[29] = new Chip(1, 'o');
    chips[30] = new Chip(1, 'o');
    chips[31] = new Chip(1, 'o');
    chips[32] = new Chip(1, 'o');//
    chips[33] = new Chip(1, 'i');
    chips[34] = new Chip(1, 'i');
    chips[35] = new Chip(1, 'i');
    chips[36] = new Chip(1, 'i');
    chips[37] = new Chip(1, 'i');
    chips[38] = new Chip(1, 'i');//
    chips[39] = new Chip(1, 's');
    chips[40] = new Chip(1, 's');
    chips[41] = new Chip(1, 's');
    chips[42] = new Chip(1, 's');
    chips[43] = new Chip(1, 's');
    chips[44] = new Chip(1, 's');//
    chips[45] = new Chip(1, 'n');
    chips[46] = new Chip(1, 'n');
    chips[47] = new Chip(1, 'n');
    chips[48] = new Chip(1, 'n');
    chips[49] = new Chip(1, 'n');//
    chips[50] = new Chip(1, 'l');
    chips[51] = new Chip(1, 'l');
    chips[52] = new Chip(1, 'l');
    chips[53] = new Chip(1, 'l');//
    chips[54] = new Chip(1, 'r');
    chips[55] = new Chip(1, 'r');
    chips[56] = new Chip(1, 'r');
    chips[57] = new Chip(1, 'r');
    chips[58] = new Chip(1, 'r');//
    chips[59] = new Chip(1, 'u');
    chips[60] = new Chip(1, 'u');
    chips[61] = new Chip(1, 'u');
    chips[62] = new Chip(1, 'u');
    chips[63] = new Chip(1, 'u');//
    chips[64] = new Chip(1, 't');
    chips[65] = new Chip(1, 't');
    chips[66] = new Chip(1, 't');
    chips[67] = new Chip(1, 't');//
    chips[68] = new Chip(2, 'd');
    chips[69] = new Chip(2, 'd');
    chips[70] = new Chip(2, 'd');
    chips[71] = new Chip(2, 'd');
    chips[72] = new Chip(2, 'd');//
    chips[73] = new Chip(2, 'g');
    chips[74] = new Chip(2, 'g');//
    chips[75] = new Chip(3, 'c');
    chips[76] = new Chip(3, 'c');
    chips[77] = new Chip(3, 'c');
    chips[78] = new Chip(3, 'c');//
    chips[79] = new Chip(3, 'b');
    chips[80] = new Chip(3, 'b');//
    chips[81] = new Chip(3, 'm');
    chips[82] = new Chip(3, 'm');//
    chips[83] = new Chip(3, 'p');
    chips[84] = new Chip(3, 'p');//
    chips[85] = new Chip(4, 'h');
    chips[86] = new Chip(4, 'h');//
    chips[87] = new Chip(4, 'f');//
    chips[88] = new Chip(4, 'v');//
    chips[89] = new Chip(4, 'y');//
    chips[90] = new Chip(5, 'q');//
    chips[91] = new Chip(8, 'j');//
    chips[92] = new Chip(8, 'x');//
    chips[93] = new Chip(10, 'z');//
    //VECTOR UTILIZADO UNICAMENTE PARA OBTENER FUNCION RANDOM_SHUFFLE
    //QUE ES CAPAZ DE ORDENAR LOS ELEMENTOS DE UN VECTOR DE FORMA ALEATORIA.
    std::vector<int> myvector;
    //SE LLENA EL VECTOR ENTEROS QUE REPRESENTAN UNA POSICION EN EL ARREGLO 'chips'
    for (int i = 0; i < 94; i++)
    {
        myvector.push_back(i);
    }
    //LOS ORDENA ALEATORIAMENTE
    std::random_shuffle ( myvector.begin(), myvector.end());
    std::random_shuffle ( myvector.begin(), myvector.end(), myrandom);
    //CON ELLO, SE OBTIENE EL ELEMENTO 'a' DEL VECTOR QUE INDICA UNA POSICION EN EL ARREGLO 'chips[]'
    //Y ESA POSICION ES LA QUE SE INSERTA EN LA COLA. Y DE ESA FORMA QUEDAN ORDENADOS ALEATORIAMENTE COMO SE SOLICITA.
    for (int i = 0; i< 94; i++)
    {
        int a = myvector.at(i);
        ChipsQueue->Enqueue(chips[a], QString(chips[a]->Letter) + QString(" X %1").arg(chips[a]->Points));
        //std::cout << a << endl;
    }
    delete [] *chips;
    ChipsQueue->GenerateGraph("Fichas");
    DoubleLinkedList<Chip> *player1Chips = new DoubleLinkedList<Chip>();
    DoubleLinkedList<Chip> *player2Chips = new DoubleLinkedList<Chip>();
    for(int i=0; i<7; i++)
    {
        Chip *dequeuedChip = ChipsQueue->GetDequeuedObject();
        player1Chips->AddLast(dequeuedChip, QString(QString(dequeuedChip->Letter) + "X%1").arg(dequeuedChip->Points));
    }
    player1Chips->GenerateGraph("Fichas_Jugador_1");
    for(int i=0; i<7; i++)
    {
        Chip *dequeuedChip = ChipsQueue->GetDequeuedObject();
        player2Chips->AddLast(dequeuedChip, QString(QString(dequeuedChip->Letter) + "X%1").arg(dequeuedChip->Points));
    }
    player2Chips->GenerateGraph("Fichas_Jugador_2");

}
void reports()
{

}
int main(int argc, char *argv[])
{
    std::srand(std::time(0));
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
*/
    int selection = -1;
    cout << "Este es un proyecto realizado por Fernando Tello - 201800714" <<endl;
    cout << "Bienvenido a Scrabble++" <<endl;
    while(selection != 4)
    {
        selection = menu();
        switch (selection)
        {
        case 1:
            cout << "Leyendo archivo de entrada..." <<endl;
            readJson("entrada.json");
            ReadedFile = true;
            cout << "*Se ha leido el archivo de entrada*" <<endl;
            break;
        case 2:
            if(ReadedFile)
            {
                newGame();
            }
            break;
        case 3:
            reports();
            break;
        }
    }
    cout << "!Hasta Luego! :D" << endl;
    return a.exec();
}
