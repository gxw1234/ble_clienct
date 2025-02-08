#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H


#include <QObject>
#include <QTcpSocket>
#include <QTimer>
class NetworkService : public QObject
{
    Q_OBJECT

public:
    explicit NetworkService(QObject *parent = nullptr);
    ~NetworkService();

    bool connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message, char messageType);
    void sendMessageQByteArray(const QByteArray &message, char messageType);
    void disconnectFromHost();

signals:
    void connected();
    void errorOccurred(QString errorString);
    void connected_state(bool state );
    void commandReceived(quint8 dataType, const QByteArray& buffer,bool islen_,bool ismd5_);

private slots:
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray buffer;
    void attemptReconnect();
    QString serverHost;
    quint16 serverPort;
    QTimer *reconnectTimer =nullptr ;
};
#endif // NETWORKSERVICE_H
