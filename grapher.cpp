#include "grapher.h"

Grapher::Grapher(QString name)
{
    Name = name;
    Path = QCoreApplication::applicationDirPath() + "\\Graphviz";
    if (!QDir(Path).exists())
    {
        QDir().mkdir(Path);
    }
}
QString Grapher::GenerateGraph(QString dotText)
{
    DotText = dotText;
    QString pathDot = Path + "\\" + Name + ".dot";
    QString pathPng = Path + "\\" + Name + ".png";
    this->GenerateDot(pathDot, pathPng);
    return pathPng;
}

void Grapher::GenerateDot(QString pathDot, QString pathPng)
{
    QFile file(pathDot);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << DotText << endl;
    }
    file.close();
    QString cmd = "dot.exe -Tpng \"" + pathDot + "\" -o \"" + pathPng + "\" ";
    const char* cmdCharPointer = cmd.toStdString().c_str();

    system(cmdCharPointer);
}
