#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();
    bool startServer(quint16 port);
    void sendResponse(QTcpSocket* socket, const QByteArray &data);
    void sendCommand(int type,const QString &command);

signals:
    void dataReceived(quint8 dataType, const QByteArray& buffer,bool islen_,bool ismd5_);
public slots:
    void newConnection();
    void readData();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QByteArray buffer;
    bool ismd5;
    bool islen;
};
#endif // TCPSERVER_H
