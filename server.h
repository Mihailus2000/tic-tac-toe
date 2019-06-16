#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QStandardItem>
#include <QJsonArray>

//#include "ui_connection.h"



class server : public QWidget
{
    Q_OBJECT

public:
    explicit server();
    ~server();
    void start();


public slots:
    void sockReady();
    void sockDisc();

private:


    QString ip,host;
    QTcpSocket* socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
signals:
    void sendRecievedRole(QString);
};


#endif // SERVER_H
