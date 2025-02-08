#include "wechatnotifier.h"



#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

WeChatMessageSender::WeChatMessageSender(QObject *parent) : QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
}

void WeChatMessageSender::sendMessage(const QString& messageContent)
{
    // 定义企业微信的Webhook URL
    QString webhookUrl = "https://qyapi.weixin.qq.com/cgi-bin/webhook/send?key=dbb6084e-74b9-44cd-b127-fc2a97622cba";

    // 定义要发送的消息内容
    QJsonObject message;
    message["msgtype"] = "text";
    QJsonObject content;
    content["content"] = messageContent;
    message["text"] = content;

    // 创建一个网络请求
    QNetworkRequest request;
    request.setUrl(QUrl(webhookUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送HTTP POST请求到企业微信的Webhook URL
    QNetworkReply *reply = m_manager->post(request, QJsonDocument(message).toJson());

    // 连接请求完成的信号
    connect(reply, &QNetworkReply::finished, this, [=]() {
        // 检查请求是否成功
        if (reply->error() == QNetworkReply::NoError) {
            emit messageSent("消息发送成功");
        } else {
            emit messageSent("消息发送失败: " + reply->errorString());
        }

        // 释放资源
        reply->deleteLater();
    });
}
