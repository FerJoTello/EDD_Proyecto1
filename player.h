#ifndef PLAYER_H
#define PLAYER_H
#include <EDD/binarysearchtree.h>
class Player
{
public:
    QString Name;
    BinarySearchTree<int> *ScoreHistory;
    Player()
    {
        Name = "";
        ScoreHistory = new BinarySearchTree<int>();
    }
    Player(QString name)
    {
        Name = name;
        ScoreHistory = new BinarySearchTree<int>();
    }
};
#endif // PLAYER_H
