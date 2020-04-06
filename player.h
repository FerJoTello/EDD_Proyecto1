#ifndef PLAYER_H
#define PLAYER_H
#include <EDD/linkedlist.h>
class Player
{
public:
    QString Name;
    LinkedList<int> *ScoreHistory;
    Player()
    {
        Name = "";
        ScoreHistory = new LinkedList<int>();
    }
    Player(QString name)
    {
        Name = name;
        ScoreHistory = new LinkedList<int>();
    }
};
#endif // PLAYER_H
