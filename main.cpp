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
        cout << "2. Agregar Usuarios." <<endl;
        cout << "3. Jugar." <<endl;
        cout << "4. Reportes." << endl;
        cout << "5. Salir." << endl;
        cin >> selection;
        if (selection == 2 && !ReadedFile)
        {
            cout << "No ha sido cargado ningun archivo de entrada." << endl;
        }
    }while(selection<1 && selection>5 && !ReadedFile);
    return selection;
}
void addChips(DoubleLinkedList<Chip> *playerChips)
{
    if(ChipsQueue->GetSize()>=7)
    {
        for(int i=0; i<7; i++)
        {
            Chip *dequeuedChip = ChipsQueue->GetDequeuedObject();
            playerChips->AddLast(dequeuedChip, QString(QString(dequeuedChip->Letter) + " X %1").arg(dequeuedChip->Points));
        }
    }
    else
    {
        if(ChipsQueue->GetSize()!=0)
        {
            cout << "Quedan pocas fichas en la cola" << endl;
            while(ChipsQueue->GetSize()!=0)
            {
                Chip *dequeuedChip = ChipsQueue->GetDequeuedObject();
                playerChips->AddLast(dequeuedChip, QString(QString(dequeuedChip->Letter) + "X%1").arg(dequeuedChip->Points));
            }
        }
        else
        {
            cout << "Ya no hay fichas D:" << endl;
        }
    }
    //ChipsQueue->GenerateGraph("Fichas");
}
void returnChips(DoubleLinkedList<Chip> *playerChips)
{
    int originalSize = playerChips->GetSize();
    for(int i=0; i<originalSize; i++)
    {
        Chip *returnedChip = playerChips->DeappendObjectAt(0);
        ChipsQueue->Enqueue(returnedChip, returnedChip->Letter + QString(" X %1").arg(returnedChip->Points));
    }
}
void newTurn(Player *player, DoubleLinkedList<Chip> *playerChips, int &points, DispersedMatrix<Chip> board)
{
    bool turnEnded = false;
    while(!turnEnded)
    {
        playerChips->GenerateGraph("Fichas_"+player->Name);
        int selectionPlayer1 = 0;
        do
        {
            cout << "Es tu turno, " << player->Name.toStdString() << endl;
            cout << "Escoge una opcion:" << endl;
            cout << "1. Formar palabra." << endl;
            cout << "2. Cambiar fichas por nuevas y terminar turno." << endl;
            cin >> selectionPlayer1;
        }while(selectionPlayer1<1 || selectionPlayer1>2);
        if(selectionPlayer1==1)
        {
            cout << "Forma una palabra con tus fichas indicando la posicion" << endl;
            bool placingChips = true;
            int turnPoints = -0;
            int *turnPointsP = &points;
            //Indicate where the word is going to start and where is going to end (at the matrix).
            int xStart, yStart, xEnd, yEnd;
            //The player has to add at least 2 letters at the matrix to check the word and orientation.
            int letters = 0;
            board.GenerateGraph("Tablero");
            DoubleLinkedList<Chip> placedChips;
            LinkedList<Box> chipsPosition;
            while(placingChips)
            {
                playerChips->GenerateGraph(QString("Fichas_") + player->Name);
                int chip = -1;
                int x = -1;
                int y = -1;
                cout << "Indica el numero de tu ficha" << endl;
                cin >> chip;
                do
                {
                    cout << "Indica la posicion en X de tu ficha" <<endl;
                    cin >> x;
                }
                while(x<1 || x>Dimention);
                do
                {
                    cout << "Indica la posicion en Y de tu ficha" <<endl;
                    cin >> y;
                }
                while(y<1 || y>Dimention);
                Chip *selectedChip = playerChips->DeappendObjectAt(chip);
                placedChips.AddLast(selectedChip, "removed");
                int multiplier = 1;
                Box *newBox = new Box(x, y, 0);
                chipsPosition.AddLast(newBox, "");
                for(int i = 0; i < SpecialBoxes->GetSize(); i++)
                {
                    //Checking if the box has a multiplier.
                    Box *checkBox = SpecialBoxes->GetObjectAt(i);
                    if(checkBox->XPos==x && checkBox->YPos==y)
                    {
                        multiplier = checkBox->Multiplier;
                        break;
                    }
                }
                try
                {
                    board.Add(x,y,selectedChip, QString(selectedChip->Letter).toStdString(), multiplier);
                    board.GenerateGraph("Tablero");
                    if(letters==0)
                    {
                        xStart = x;
                        yStart = y;
                    }
                    letters++;
                    int input;
                    do
                    {
                        cout << "Escoge entre las opciones:" << endl;
                        cout << "1. Si quieres seguir colocando fichas" << endl;
                        cout << "2. Para verificar que la palabra sea correcta" << endl;
                        cin >> input;
                    }while(input<1 || input>2);
                    if(input==2)
                    {
                        placingChips=false;
                        //validating word
                        bool validWord = false;
                        xEnd = x;
                        yEnd = y;
                        FourLinksNode<Chip> *auxChipNode = board.GetNodeAt(xStart, yStart);
                        QString auxWord = "";
                        if(xStart==xEnd)
                        {
                            //vertical
                            bool checkingUp = true;
                            while(auxChipNode!=0)
                            {
                                if(checkingUp && auxChipNode->Up->YPos!=0 && auxChipNode->Up->YPos==auxChipNode->YPos-1)
                                {
                                    auxChipNode = auxChipNode->Up;
                                }
                                else
                                {
                                    checkingUp = false;
                                }
                                //checking down
                                if(!checkingUp)
                                {
                                    if (auxChipNode->AddedPreviously)
                                    {
                                        auxWord+= auxChipNode->getObject()->Letter;
                                        turnPoints += auxChipNode->getObject()->Points*auxChipNode->Multiplier;
                                    }
                                    else if((auxChipNode->Left->XPos==0 || auxChipNode->Left->XPos!=auxChipNode->XPos-1) && (auxChipNode->Right==0 || auxChipNode->Right->XPos!=auxChipNode->XPos+1))
                                    {
                                        auxWord+= auxChipNode->getObject()->Letter;
                                        turnPoints += auxChipNode->getObject()->Points*auxChipNode->Multiplier;
                                        auxChipNode->AddedPreviously = true;
                                    }
                                    auxChipNode = auxChipNode->Down;
                                }
                            }
                        }

                        else if(yStart==yEnd)
                        {
                            bool checkingLeft = true;
                            while(auxChipNode!=0)
                            {
                                if(checkingLeft && auxChipNode->Left->XPos!=0 && auxChipNode->Left->XPos==auxChipNode->XPos-1)
                                {
                                    auxChipNode = auxChipNode->Left;
                                }
                                else
                                {
                                    checkingLeft = false;
                                }
                                //checking right
                                if(!checkingLeft)
                                {
                                    if (auxChipNode->AddedPreviously)
                                    {
                                        auxWord+= auxChipNode->getObject()->Letter;
                                        turnPoints += auxChipNode->getObject()->Points*auxChipNode->Multiplier;
                                    }
                                    else if((auxChipNode->Up->YPos==0 || auxChipNode->Up->YPos!=auxChipNode->YPos-1) && (auxChipNode->Down==0 || auxChipNode->Down->YPos!=auxChipNode->YPos+1))
                                    {
                                        auxWord+= auxChipNode->getObject()->Letter;
                                        turnPoints += auxChipNode->getObject()->Points*auxChipNode->Multiplier;
                                        auxChipNode->AddedPreviously = true;
                                    }
                                    auxChipNode = auxChipNode->Right;
                                }
                            }
                        }
                        else
                        {
                            //undefined (not valid)
                            cout << "Las fichas que colocaste no presentan un orden valido" << endl;
                            cout << "No se pudo validar tu palabra" <<endl;
                            int originalSize = placedChips.GetSize();
                            for(int i=0; i<originalSize; i++)
                            {
                                Chip *auxChip = placedChips.GetObjectAt(i);
                                playerChips->AddLast(auxChip, QString(auxChip->Letter) + QString("X%1").arg(auxChip->Points));
                            }
                        }
                        DoubleNode<QString> *auxDictionaryNode = Dictionary->First;
                        //checkig if the word is on the dictionary
                        int count = 0;
                        while(count!=Dictionary->GetSize())
                        {
                            QString *dictionaryWord = auxDictionaryNode->getObject();
                            if(auxWord.compare(dictionaryWord) == 0)
                            {
                                validWord = true;
                                break;
                            }
                            auxDictionaryNode = auxDictionaryNode->getNext();
                            count++;
                        }
                        if(validWord)
                        {
                            cout << "La palabra: " << auxWord.toStdString() << ", es valida" << endl;
                            cout << "Tus fichas sobrantes se agregaran a la cola y se te asignaran unas nuevas" <<endl;
                            points += turnPoints;
                            player->ScoreHistory->AddFirst(turnPointsP, QString("%1").arg(points));
                            returnChips(playerChips);
                            addChips(playerChips);
                            ChipsQueue->GenerateGraph("Fichas");
                            turnEnded = true;
                        }
                        else
                        {
                            cout << "La palabra: " << auxWord.toStdString() << ", no es valida" << endl;
                            int originalSize = placedChips.GetSize();
                            for(int i=0; i<originalSize; i++)
                            {
                                Chip *auxChip = placedChips.GetObjectAt(i);
                                playerChips->AddLast(auxChip, QString(auxChip->Letter) + QString("X%1").arg(auxChip->Points));
                            }
                            SimpleNode<Box> *removedChip = chipsPosition.First;
                            while(removedChip!=0)
                            {
                                board.DeleteAt(removedChip->getObject()->XPos, removedChip->getObject()->YPos);
                                removedChip = removedChip->getNext();
                            }
                        }
                    }
                    else if(input==1)
                    {
                        placingChips=true;
                    }
                }
                catch (int e)
                {
                    //continues on placing chips
                    if(e==-1)
                    {
                        cout << "Ya hay una ficha en esa posicion" <<endl;
                        cout << "Debes de indicar nuevamente tu ficha y su posicion" <<endl;
                        playerChips->AddLast(selectedChip, QString(QString(selectedChip->Letter) + "X%1").arg(selectedChip->Points));
                    }
                }
            }
        }
        else if(selectionPlayer1==2)
        {
            returnChips(playerChips);
            addChips(playerChips);
            ChipsQueue->GenerateGraph("Fichas");
            turnEnded=true;
        }
    }
}
void debugGame()
{
    cout << "Para iniciar una partida es necesario que primero selecciones tu usuario. Ingresa el numero de tu usuario." <<endl;
    LinkedList<BinaryTreeNode<Player>> inorder = PlayersTree->GetInOrder();
    inorder.GenerateGraph("Usuarios");
    Player *player1 = inorder.GetObjectAt(0)->getObject();
    Player *player2 = inorder.GetObjectAt(1)->getObject();
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

    ChipsQueue->Enqueue(chips[78], QString(chips[78]->Letter) + QString(" X %1").arg(chips[78]->Points));
    ChipsQueue->Enqueue(chips[0], QString(chips[0]->Letter) + QString(" X %1").arg(chips[0]->Points));
    ChipsQueue->Enqueue(chips[45], QString(chips[45]->Letter) + QString(" X %1").arg(chips[45]->Points));
    ChipsQueue->Enqueue(chips[51], QString(chips[51]->Letter) + QString(" X %1").arg(chips[51]->Points));
    ChipsQueue->Enqueue(chips[1], QString(chips[1]->Letter) + QString(" X %1").arg(chips[1]->Points));
    ChipsQueue->Enqueue(chips[46], QString(chips[46]->Letter) + QString(" X %1").arg(chips[46]->Points));
    ChipsQueue->Enqueue(chips[2], QString(chips[2]->Letter) + QString(" X %1").arg(chips[2]->Points));
    ChipsQueue->Enqueue(chips[3], QString(chips[3]->Letter) + QString(" X %1").arg(chips[3]->Points));//primero
    ChipsQueue->Enqueue(chips[83], QString(chips[83]->Letter) + QString(" X %1").arg(chips[83]->Points));
    ChipsQueue->Enqueue(chips[12], QString(chips[12]->Letter) + QString(" X %1").arg(chips[12]->Points));
    ChipsQueue->Enqueue(chips[93], QString(chips[93]->Letter) + QString(" X %1").arg(chips[93]->Points));
    ChipsQueue->Enqueue(chips[85], QString(chips[85]->Letter) + QString(" X %1").arg(chips[85]->Points));
    ChipsQueue->Enqueue(chips[24], QString(chips[24]->Letter) + QString(" X %1").arg(chips[24]->Points));
    ChipsQueue->Enqueue(chips[52], QString(chips[52]->Letter) + QString(" X %1").arg(chips[52]->Points));    //segundo
    DoubleLinkedList<Chip> *player1Chips = new DoubleLinkedList<Chip>();
    DoubleLinkedList<Chip> *player2Chips = new DoubleLinkedList<Chip>();
    addChips(player1Chips);
    addChips(player2Chips);
    DispersedMatrix<Chip> board;
    /*
    board.Add(1,1,chips[75], QString(chips[75]->Letter).toStdString(), 3);
    board.Add(2,1,chips[4], QString(chips[4]->Letter).toStdString(), 1);
    board.Add(3,1,chips[47], QString(chips[47]->Letter).toStdString(), 3);
    board.Add(5,3,chips[84], QString(chips[84]->Letter).toStdString(), 1);
    board.Add(6,3,chips[13], QString(chips[13]->Letter).toStdString(), 1);
    board.Add(7,3,chips[93], QString(chips[93]->Letter).toStdString(), 3);
    board.Add(6,7,chips[50], QString(chips[50]->Letter).toStdString(), 1);
    board.Add(6,8,chips[5], QString(chips[5]->Letter).toStdString(), 1);
    board.Add(6,9,chips[47], QString(chips[47]->Letter).toStdString(), 1);
    board.Add(6,10,chips[6], QString(chips[6]->Letter).toStdString(), 3);
    */
    int initialTurn = myrandom(2) + 1;
    //turn1 determines if the player1 has the initial turn. if don't the turn is for player2.
    bool turn1 = false;
    bool gameEnded = false;
    if(initialTurn==1)
    {
        turn1 = true;
    }
    //game starts
    int points1 = 0;
    int points2 = 0;
    do
    {
        cout << "Puntos de " << player1->Name.toStdString() <<": " << points1 <<endl;
        cout << "Puntos de " << player2->Name.toStdString() <<": " << points2 <<endl;
        cout << "Escoge entre las opciones:\n1. Colocar ficha.\n2. Terminar partida." << endl;
        int selection = 0;
        cin >> selection;
        if(selection==1 && turn1)
        {
            newTurn(player1,player1Chips,points1,board);
        }
        else if(selection==1 && !turn1)
        {
            newTurn(player2,player2Chips,points2,board);
        }
        else if(selection==2)
        {
            gameEnded=true;
        }
        turn1 = !turn1;
    }while(!gameEnded);
    if(points1>points2)
    {
        cout << "El ganador es: " << player1->Name.toStdString() <<". Con " << points1 << " puntos!"<<endl;
    }
    else if(points1<points2)
    {
        cout << "El ganador es: " << player2->Name.toStdString() <<". Con " << points2 << " puntos!"<<endl;
    }
    else
    {
        cout << "Hay empate!" << endl;
    }
    cout << "Buen juego :D" << endl;
}
void newGame()
{
    cout << "Para iniciar una partida es necesario que primero selecciones tu usuario." <<endl;
    LinkedList<BinaryTreeNode<Player>> inorder = PlayersTree->GetInOrder();
    inorder.GenerateGraph("Usuarios");
    int selection1, selection2;
    do
    {
        cout << "Jugador 1, selecciona tu usuario" <<endl;
        cin >> selection1;
    }
    while(selection1<0 || selection1>=PlayersTree->GetSize());
    Player *player1 = inorder.GetObjectAt(selection1)->getObject();
    do
    {
        cout << "Jugador 2, selecciona tu usuario" <<endl;
        cin >> selection2;
    }
    while(selection2<0 || selection2>=PlayersTree->GetSize() || selection1==selection2);
    Player *player2 = inorder.GetObjectAt(selection2)->getObject();
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
    addChips(player1Chips);
    addChips(player2Chips);
    DispersedMatrix<Chip> board;
    int initialTurn = myrandom(2) + 1;
    //turn1 determines if the player1 has the initial turn. if don't the turn is for player2.
    bool turn1 = false;
    bool gameEnded = false;
    if(initialTurn==1)
    {
        turn1 = true;
    }
    //game starts
    int points1 = 0;
    int points2 = 0;
    do
    {
        cout << "Puntos de " << player1->Name.toStdString() <<": " << points1 <<endl;
        cout << "Puntos de " << player2->Name.toStdString() <<": " << points2 <<endl;
        cout << "Escoge entre las opciones:\n1. Colocar ficha.\n2. Terminar partida." << endl;
        int selection = 0;
        cin >> selection;
        if(selection==1 && turn1)
        {
            newTurn(player1,player1Chips,points1,board);
        }
        else if(selection==1 && !turn1)
        {
            newTurn(player2,player2Chips,points2,board);
        }
        else if(selection==2)
        {
            gameEnded=true;
        }
        turn1 = !turn1;
    }while(!gameEnded);
    if(points1>points2)
    {
        cout << "El ganador es: " << player1->Name.toStdString() <<". Con " << points1 << " puntos!"<<endl;
    }
    else if(points1<points2)
    {
        cout << "El ganador es: " << player2->Name.toStdString() <<". Con " << points2 << " puntos!"<<endl;
    }
    else
    {
        cout << "Hay empate!" << endl;
    }
    cout << "Buen juego :D" << endl;
}
void reports()
{
    int selection;
    do
    {
        cout << "Para ver reportes, selecciona un numero" << endl;
        cout << "1. Diccionario (Doble Circular)." << endl;
        cout << "2. Usuarios (Arbol binario)" << endl;
        cout << "3. Recorrido Preorder" << endl;
        cout << "4. Recorrido Inorder" << endl;
        cout << "5. Recorrido Postorder" << endl;
        cout << "6. Historial de puntajes (Lista Simple Ordenada)" << endl;
        cout << "7. Scoreboard (Lista Simple Ordenada)" << endl;
        cin >> selection;
    }
    while(selection<1 || selection>7);
    switch(selection)
    {
    case 1:
        Dictionary->GenerateGraph("Diccionario");
    break;
    case 2:
        PlayersTree->GenerateTreeGraph("Usuarios");
    break;
    case 3:
        PlayersTree->GetPreOrder().GenerateGraph("Usuarios_PreOrder");
    break;
    case 4:
        PlayersTree->GetInOrder().GenerateGraph("Usuarios_InOrder");
    break;
    case 5:
        PlayersTree->GetPostOrder().GenerateGraph("Usuarios_PostOrder");
    break;
    case 6:{
        int player;
        do
        {
            cout << "De la lista InOrder indica la posicion del usuario" << endl;
            cin >> player;
        }
        while(player<0 || player>=PlayersTree->GetSize());
        Player *selectedPlayer = PlayersTree->GetInOrder().GetObjectAt(player)->getObject();
        selectedPlayer->ScoreHistory->GenerateGraph(QString("Puntajes_") + selectedPlayer->Name);
    }
        break;
    case 7:

        BinarySearchTree<Player> *scoreboardTree = new BinarySearchTree<Player>();
        LinkedList<BinaryTreeNode<Player>> inorder = PlayersTree->GetInOrder();
        for(int i = 0; i < inorder.GetSize(); i++)
        {
            Player *aPlayer = inorder.GetObjectAt(i)->getObject();
            int *value = aPlayer->ScoreHistory->GetObjectAt(0);
            scoreboardTree->Add(aPlayer, QString("%1puntos: ").arg(*value) + aPlayer->Name);
        }
        scoreboardTree->GetInOrder().GenerateGraph("Scoreboard");
    break;

    }
}
int main(int argc, char *argv[])
{
    std::srand(std::time(0));
    QCoreApplication a(argc, argv);
    int selection = -1;
    cout << "Este es un proyecto realizado por Fernando Tello - 201800714" <<endl;
    cout << "Bienvenido a Scrabble++" <<endl;
    while(selection != 5)
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
        case 2:{
            cout << "Coloca el nombre de tu usuario" << endl;
            string name;
            cin >> name;
            Player *newPlayer = new Player(QString(name.c_str()));
            try {
                PlayersTree->Add(newPlayer, QString(name.c_str()));
            } catch (int a) {
                cout << "Ya existe un usuario con ese nombre" <<endl;
            }
        }
            break;
        case 3:
            if(ReadedFile)
            {
                if(PlayersTree->GetSize()>=2)
                {
                    newGame();
                }
                else
                {
                    cout << "Parece ser que no hay suficientes usuarios creados. Crea uno nuevo." << endl;
                }
            }
            break;
        case 4:
            reports();
            break;
        }
    }
    cout << "!Hasta Luego! :D" << endl;
    return a.exec();
}
