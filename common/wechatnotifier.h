#ifndef WECHATNOTIFIER_H
#define WECHATNOTIFIER_H


#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeChatMessageSender : public QObject
{
    Q_OBJECT
public:
    explicit WeChatMessageSender(QObject *parent = nullptr);

signals:
    void messageSent(QString result);

public slots:
    void sendMessage(const QString& messageContent);

private:
    QNetworkAccessManager *m_manager;
};


#endif // WECHATNOTIFIER_H
