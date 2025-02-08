#include "tcp/tcpserver.h"

#include <QDataStream>
#include <QDebug>
#include <QCryptographicHash>

TcpServer::TcpServer(QObject *parent) :
    QObject(parent),
    server(new QTcpServer(this)),
    socket(nullptr)
{
    ismd5 =false;
    islen = false;
    connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection);
}

TcpServer::~TcpServer()
{
    server->close();
}

bool TcpServer::startServer(quint16 port)
{
    if (!server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start!";
        return false;
    } else {
        qDebug() << "Server started!";
        return true;
    }
}

void TcpServer::sendResponse(QTcpSocket* clientSocket, const QByteArray &data)
{
    if (clientSocket && clientSocket->isOpen()) {
        clientSocket->write(data);
        clientSocket->flush();
    }
}

void TcpServer::sendCommand(int type, const QString &command)
{
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_10);
        out << quint8(type);
        out << QString(command);
        socket->write(block);
        socket->flush();
}

void TcpServer::newConnection()
{
    if (socket != nullptr) {
        socket->deleteLater();
    }
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::readData);
}

void TcpServer::readData()
{
    buffer.append(socket->readAll());
    if (buffer.endsWith("END_OF_DATA")) {
        buffer.chop(QString("END_OF_DATA").length());
        if (!buffer.isEmpty()) {
            char dataType = buffer.at(0);
            buffer.remove(0, 1); // 移除类型
            quint16 dataLength;
            QDataStream lengthStream(&buffer, QIODevice::ReadOnly);
            lengthStream >> dataLength;
            buffer.remove(0, 2); // 移除长度字段
            QByteArray dataChecksum = buffer.left(16);
            buffer.remove(0, 16); // 移除校验和字段
            if (dataLength == buffer.size()) {
                islen =true;
            }
           QCryptographicHash hash(QCryptographicHash::Md5);
           hash.addData(buffer);
           if (hash.result() == dataChecksum) {
               ismd5 =true;
           }
//            QString message = QString::fromUtf8(buffer);
            emit dataReceived(dataType ,buffer ,islen,ismd5);
        }
        buffer.clear();
        ismd5 =false;
        islen = false;
    }
}
