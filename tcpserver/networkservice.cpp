#include "networkservice.h"
#include <QDataStream>
#include <QDebug>
#include <QCryptographicHash>
#define END_OF_DATA "END_OF_DATA"

NetworkService::NetworkService(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{

    connect(socket, &QTcpSocket::connected, this, &NetworkService::onConnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &NetworkService::onErrorOccurred);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkService::onReadyRead);


}

NetworkService::~NetworkService() {
    delete socket;
    socket =nullptr;
}

bool NetworkService::connectToServer(const QString &host, quint16 port) {
    socket->connectToHost(host, port);
    serverHost =host;
    serverPort = port;

//    bool socket_result = socket->waitForConnected(1000);
//    if (!socket_result)
//    {
//        attemptReconnect();
//    }
    return true;
}

void NetworkService::sendMessage(const QString &message, char messageType) {
    //------类型-----字节长度:1
    QByteArray data = message.toUtf8();
    QByteArray dataType;
    dataType.append(messageType);
   //------长度-----字节长度:2
    quint16 dataLength = data.size();
    QByteArray dataLengthBytes;
    QDataStream lengthStream(&dataLengthBytes, QIODevice::WriteOnly);
    lengthStream << dataLength;
   //------md5-----字节长度:16
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(data);
    QByteArray dataChecksum = hash.result();
    socket->write(dataType);
    socket->write(dataLengthBytes);
    socket->write(dataChecksum);
    int byte_length =4096;
    int offset = 0;
    while (offset < data.size()) {
        QByteArray dataBlock = data.mid(offset, byte_length);
        socket->write(dataBlock);
        offset += byte_length;
    }
    QByteArray endSignal = END_OF_DATA;
    socket->write(endSignal);
}

void NetworkService::sendMessageQByteArray(const QByteArray &message, char messageType) {
    //------类型-----字节长度:1
    QByteArray data =message;
    QByteArray dataType;
    dataType.append(messageType);
   //------长度-----字节长度:2
    quint16 dataLength = data.size();
    QByteArray dataLengthBytes;
    QDataStream lengthStream(&dataLengthBytes, QIODevice::WriteOnly);
    lengthStream << dataLength;
   //------md5-----字节长度:16
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(data);
    QByteArray dataChecksum = hash.result();
    socket->write(dataType);
    socket->write(dataLengthBytes);
    socket->write(dataChecksum);
    int byte_length =4096;
    int offset = 0;
    while (offset < data.size()) {
        QByteArray dataBlock = data.mid(offset, byte_length);
        socket->write(dataBlock);
        offset += byte_length;
    }
    QByteArray endSignal = END_OF_DATA;
    socket->write(endSignal);
}






void NetworkService::disconnectFromHost() {
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}




void NetworkService::onConnected() {
    qDebug() << "----Connected to server.-";
    emit connected_state(true);
    emit connected();
}

void NetworkService::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError)
    qDebug() << "Socket error:" << socket->errorString();
    if (socketError == QAbstractSocket::RemoteHostClosedError) {
        attemptReconnect();
    }
    emit connected_state(false);
    emit errorOccurred(socket->errorString());
}

void NetworkService::onReadyRead() {

    buffer.append(socket->readAll());
    int endIndex = 0;
    while ((endIndex = buffer.indexOf(END_OF_DATA)) != -1) {
        QByteArray packet = buffer.left(endIndex);
        buffer.remove(0, endIndex + QString(END_OF_DATA).length());

        if (!packet.isEmpty()) {
            char dataType = packet.at(0);
            packet.remove(0, 1); // 移除类型
            quint16 dataLength;
            QDataStream lengthStream(&packet, QIODevice::ReadOnly);
            lengthStream >> dataLength;
            packet.remove(0, 2); // 移除长度字段
            QByteArray dataChecksum = packet.left(16);
            packet.remove(0, 16); // 移除校验和字段
            bool islen = false;
            bool ismd5 = false;
            if (dataLength == packet.size()) {
                islen = true;
            }
            QCryptographicHash hash(QCryptographicHash::Md5);
            hash.addData(packet);
            if (hash.result() == dataChecksum) {
                ismd5 = true;
            }
            emit commandReceived(dataType, packet, islen, ismd5);
        }
    }
}



void NetworkService::attemptReconnect()
{
    if (reconnectTimer == nullptr) {
        reconnectTimer = new QTimer(this);
        connect(reconnectTimer, &QTimer::timeout, this, [this]() {
            if (socket->state() != QTcpSocket::ConnectedState) {
                qDebug() << "Attempting to reconnect to" << this->serverHost << "on port" << this->serverPort;
                this->connectToServer(this->serverHost, this->serverPort);
            } else {
                reconnectTimer->stop();
                emit connected_state(true);
                qDebug() << "Connected to server, stopping reconnect timer.";
                delete reconnectTimer;
                reconnectTimer =nullptr;
            }
        });
    }
    if (!reconnectTimer->isActive()) {
        reconnectTimer->start(5000);
    }
}
