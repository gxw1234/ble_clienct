#include "tcpdebug.h"

NetworkThread::NetworkThread(QObject *parent) : QThread(parent)
{

}

void NetworkThread::run()
{

//    socket = new QTcpSocket;
//    connect(socket, &QTcpSocket::connected, this, &NetworkThread::onConnected);
//    connect(socket, &QTcpSocket::readyRead, this, &NetworkThread::onReadyRead);

//    socket->connectToHost(host, 12345);


//    bool socket_result = socket->waitForConnected(1000);
//    if (!socket_result)
//    {
//        attemptReconnect();
//    }

}

bool NetworkThread::connectToServer(const QString &host, quint16 port)
{

}

void NetworkThread::sendMessage(const QString &message, char messageType)
{

}
void NetworkThread::onConnected() {
    qDebug() << "----Connected to server.-";

}

void NetworkThread::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError)


}

void NetworkThread::onReadyRead() {


}

