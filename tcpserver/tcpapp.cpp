#include "tcpapp.h"

Tcpapp::Tcpapp(QObject *parent):QObject(parent)
{
     networkService = new NetworkService;
}

Tcpapp::~Tcpapp()
{
    networkService->disconnectFromHost();
    delete  networkService;
    networkService =nullptr;
}


bool Tcpapp::connectAndSetupListenerapp(const QString &host, int port)
{

    connect(networkService,&NetworkService::commandReceived,this,&Tcpapp::onhandleDataReceivedapp);
    connect(networkService,&NetworkService::connected_state,this,&Tcpapp::onconnected_state);
    if (networkService->connectToServer(host, port))
    {

        getstate = true;
    }
    else {

        getstate = false;
    }
    return getstate;

}

bool Tcpapp::getconnectstateapp()
{

    return getstate;

}

void Tcpapp::sendMessageapp(const QString &message, char messageType)
{
    networkService->sendMessage(message,messageType);
}


void Tcpapp::sendMessageappQByteArray(const QByteArray &message, char messageType)
{
    networkService->sendMessageQByteArray(message,messageType);


}

void Tcpapp::startWorking(const QString &ip)
{
    connectAndSetupListenerapp(ip);
}

void Tcpapp::onConnectedapp()
{
     qDebug() << "----Connected to server.-----";
     getstate =true;
     emit connectedapp();
}

void Tcpapp::onErrorOccurredapp(QString errtext)
{
    emit errorOccurredapp(errtext);
}

void Tcpapp::onhandleDataReceivedapp(quint8 dataType, const QByteArray &buffer, bool islen_, bool ismd5_)
{
    emit  commandReceivedapp(dataType,buffer,islen_,ismd5_);
}

void Tcpapp::onconnected_state(bool state)
{
    emit m_connected_state(state);
}



