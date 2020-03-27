#ifndef GRAPHER_H
#define GRAPHER_H
#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
class Grapher
{
public:
    Grapher(QString name);
    QString GenerateGraph(QString text);
private:
    QString Path, Name, DotText;
    void GenerateDot(QString pathDot, QString pathPng);
};

#endif // GRAPHER_H
