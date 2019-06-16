#include "server.h"

server::server(){
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

server::~server() {}

void server::sockDisc()
{
    socket->deleteLater();
}

void server::sockReady(){
    qDebug() << "reading!";
    if (socket->waitForConnected(500))
    {
        qDebug() << "Connection ready!!";
//        QMessageBox::information(this,"Информация","Соединение установлено");
//        QByteArray arr;
//        arr = socket->readAll();
//        ui->label->setText(arr.data());

        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug() << "Recieved data: " << Data;
        doc = QJsonDocument::fromJson(Data,&docError);

        if(docError.errorString()=="no error occurred"){
            if((doc.object().value("type").toString() == "connect" ) && (doc.object().value("status").toString() == "yes")){
                QMessageBox::information(this, "Информация","Соединение установлено");
            }
            else{
                if((doc.object().value("type").toString() == "connect" ) && (doc.object().value("status").toString() == "no")){
                    QMessageBox::warning(this, "Информация","Соединение НЕ установлено!!");
                }
                else{
                    if((doc.object().value("type").toString()=="game") && (doc.object().value("who").toString()=="X")){
                        emit sendRecievedRole("X");
                        qDebug() << "You go FIRST";
                        socket->write("{\"type\":\"game\",\"sendWho\":\"FIRST\",\"what\":\"chooseReady\"}");
                        socket->flush();
                    }
                    if((doc.object().value("type").toString()=="game") && (doc.object().value("who").toString()=="O")){
                         emit sendRecievedRole("O");
                        qDebug() << "You go SECOND";
                        socket->write("{\"type\":\"game\",\"sendWho\":\"SECOND\",\"what\":\"chooseReady\"}");
                        socket->flush();
                    }

                    if(doc.object().value("type").toString()=="game" && doc.object().value("what").toString()=="turn"){

                    }
                }
            }
        }

    }
    else{
        QMessageBox::information(this,"Информация","Соединение НЕ установлено");
    }
}

//void MainWindow::on_pushButton_2_clicked()
//{
//        if(socket->isOpen()){
//        socket->write("{\"type\":\"text\"}");
//        socket->flush();
//        socket->waitForBytesWritten(500);
//    }
//    else{
//        QMessageBox::warning(this,"Информация","Соединение не установленно(Из отправки))");
//    }
//}

void server::start(){
    socket->connectToHost("127.0.0.1",5555);
}


