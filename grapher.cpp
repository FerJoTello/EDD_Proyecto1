#include "grapher.h"
#include "iostream"
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
    //For debuggin'
    QString cmd = "dot.exe -Tpng \"" + pathDot + "\" -o \"" + pathPng + "\" ";
    //std::cout<<"El Dot antes:"<<std::endl;
    //std::cout<<cmd.toStdString().c_str()<<std::endl;
    const char* cmdCharPointer = cmd.toStdString().c_str();
    //std::cout<<"El Dot despues:"<<std::endl;
    //std::cout<<cmdCharPointer<<std::endl;
    system(cmdCharPointer);
}
