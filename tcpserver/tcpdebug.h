#ifndef TCPDEBUG_H
#define TCPDEBUG_H


#include <QThread>
#include <QTcpSocket>

class NetworkThread : public QThread
{
    Q_OBJECT
public:
    explicit NetworkThread(QObject *parent = nullptr);
    void run() override;

    bool connectToServer(const QString &host, quint16 port);
    void sendMessage(const QString &message, char messageType);

private slots:
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onReadyRead();

private:
    QTcpSocket *socket;
    QByteArray buffer;

    QString serverHost;
    quint16 serverPort;
};
#endif // TCPDEBUG_H
