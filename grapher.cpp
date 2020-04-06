#include "grapher.h"
#include "iostream"
#include <chrono>
#include <thread>
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
    std::string cmd1 = "dot.exe -Tpng \"" + pathDot.toStdString() + "\" -o \"" + pathPng.toStdString() + "\" ";
    std::string cmd2 = "start Graphviz\\" + Name.toStdString() + ".png";
    //For debuggin'
    //std::cout<<"El Dot antes:"<<std::endl;
    //std::cout<<cmd.c_str()<<std::endl;
    const char *cmd1Char = cmd1.c_str();
    const char *cmd2Char = cmd2.c_str();
    //std::cout<<"El Dot despues:"<<std::endl;
    //std::cout<<cmdCharPointer<<std::endl;
    system(cmd1Char);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system(cmd2Char);
}
