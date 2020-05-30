#ifndef HANDLETEXTFIELD_H
#define HANDLETEXTFIELD_H

#include <QObject>
#include <QDebug>
#include<trienode.h>

using namespace std;
class HandleTextField : public QObject
{
    Q_OBJECT

TrieNode* trie=new TrieNode();
public:
    explicit HandleTextField(QObject *parent = 0);
    string ReadFile(QString fileName);
    void delay();

signals:
    void setTextField(QVariant text);
    void listFileNames(QVariant text);
    void viewFileInTextArea(QVariant);

public slots:
    void handleSubmitTextField(const QString&file);
    void handleSearchTextField(const QString &word);
    void handleOpenFileInQml(const QString &filename,const QString &fileUrl);
};

#endif // HANDLETEXTFIELD_H
