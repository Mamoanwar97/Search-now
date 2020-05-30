#include "handletextfield.h"
#include<QFile>
#include<QDir>
#include<trienode.h>
#include<string>
#include<QTime>
#include<QCoreApplication>
#include <bits/stdc++.h>
#include<iostream>
using namespace std;

HandleTextField::HandleTextField(QObject *parent) :
    QObject(parent)
{
}
void HandleTextField::delay() //delay function to allow gui respond to incomes
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


string HandleTextField::ReadFile(QString fileName)
{
        QFile myFile(fileName);
        if(!myFile.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << "Cant Open This File" ;
            return "-1" ;
        }
        QTextStream in (&myFile);
        QString myText = in.readAll();
        myFile.close();
        return myText.toStdString() ;
}

void HandleTextField::handleSearchTextField(const QString &word)
{
   vector<pair<string,int>> input;
   input=trie->search(word.toStdString());
   if(input.size()==0)
       emit setTextField("Sorry :( your word is not here");
   else{
       emit setTextField(word+" is found " +QString::number(input.size())+" times");
       emit setTextField("your files are listed click open to view it");
   }
   for(int i=0;i<input.size();i++)
   {
       emit listFileNames(QString::fromStdString(input[i].first.substr(input[i].first.rfind('/')+1)));
   }
}

void HandleTextField::handleSubmitTextField(const QString& file)//for loading files in the dir to
{                                                                                   //the trie
    emit setTextField("buildingfile please wait until it ends");
    delay();
    string path=file.toStdString();
    path.erase(0,8);
    QString qstr = QString::fromStdString(path);
    QDir directory(qstr);
    QStringList filters;
    filters << "*.txt";
    QStringList text = directory.entryList(filters,QDir::Files);
    int i=1;
    int j=10000;
    qDebug()<<text.size();
    foreach (QString file, text) {

        QString absolutePath = directory.absoluteFilePath(file);
        string name = absolutePath.toStdString();
        string File = ReadFile(absolutePath);

        trie->Insert_File(File,name);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
        if(i==j)
        {
            emit setTextField("Finished "+QString::number(i)+" file from "+QString::number(text.length()));
            QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
            j+=10000;
        }
        i++;
    }

    emit setTextField("wohooo Great!! Building File is finished please enter a word");
}

void HandleTextField::handleOpenFileInQml(const QString &filename,const QString &fileUrl){

    //takes file name from item button and open it
    string path=fileUrl.toStdString();
    path.erase(0,8);
    QString qstr = QString::fromStdString(path);
    qstr.append("/"+filename);
    string theText = ReadFile(qstr);
    emit viewFileInTextArea(QString::fromStdString(theText));//in text area

}
