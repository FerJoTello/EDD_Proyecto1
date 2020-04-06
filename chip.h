#ifndef CHIP_H
#define CHIP_H
#include <QChar>
class Chip
{
public:
    int Points;
    QChar Letter;
    bool Enqueued;
    Chip()
    {
        Points = -1;
        Letter = ' ';
        Enqueued = false;
    }
    Chip(int points, QChar letter)
    {
        Points = points;
        Letter = letter;
        Enqueued = false;
    }
};
#endif // CHIP_H
#ifndef BOX_H
#define BOX_H
class Box
{
public:
    int XPos, YPos, Multiplier;
    Box()
    {
        XPos = -1;
        YPos = -1;
        Multiplier = -1;
    }
    Box(int xpos, int ypos, int multi)
    {
        XPos = xpos;
        YPos = ypos;
        Multiplier = multi;
    }
};
#endif //BOX_H
