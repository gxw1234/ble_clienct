#include "controller.h"
#include "common/datetimeutil.h"
Controller::Controller(QObject *parent) : QObject(parent)
{
    m_controller = NULL;
}

void Controller::ConnectDevice(QBluetoothDeviceInfo info)
{
    if(m_controller)
    {
        m_controller->disconnectFromDevice();
        delete m_controller;
        m_controller = NULL;

    }

    m_controller = QLowEnergyController::createCentral(info);
    connect(m_controller, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_controller, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(m_controller, SIGNAL(stateChanged(QLowEnergyController::ControllerState)), this, SLOT(onStateChanged(QLowEnergyController::ControllerState)));
    connect(m_controller, SIGNAL(error(QLowEnergyController::Error)), this, SLOT(onError(QLowEnergyController::Error)));
    connect(m_controller, SIGNAL(serviceDiscovered(QBluetoothUuid)), this, SLOT(onServiceDiscovered(QBluetoothUuid)));
    connect(m_controller, SIGNAL(discoveryFinished()), this, SLOT(onDiscoveryFinished()));
    connect(m_controller, SIGNAL(connectionUpdated(QLowEnergyConnectionParameters)), this, SLOT(onConnectionUpdated(QLowEnergyConnectionParameters)));
    targetAddress =  QBluetoothAddress(info.address());
    localDevice  =new QBluetoothLocalDevice;
    localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    connect(localDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing)),
               this, SLOT(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));
    m_controller->connectToDevice();
    QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();

    SendMessage( currentDateTime+ "blu_start");
}

void Controller::pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{

    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired)
    {
        emit pair_end(true);
        QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
        SendMessage( currentDateTime+ "配对成功");
        m_controller->discoverServices();
    }
    else
    {
        emit pair_end(false);
        SendMessage("配对失败");
    }
}


void Controller::DisconnectDevice()
{
    if(m_controller)
    {
        m_controller->disconnectFromDevice();
    }
}

QLowEnergyService * Controller::CreateService(QBluetoothUuid serviceUUID)
{
    if(m_controller)
    {
        return m_controller->createServiceObject(serviceUUID);
    }
    else
    {
        return NULL;
    }
}

void Controller::SendMessage(QString str)
{
    emit message(str);

}


void Controller::onConnected()
{
    if(m_controller)
    {
        QString currentDateTime = DateTimeUtil::getCurrentFormattedTime();
        SendMessage( currentDateTime+ "blu_connected_pass");
        emit connect_State("device connected");
        SendMessage("device connected");
        localDevice->requestPairing(targetAddress,QBluetoothLocalDevice::AuthorizedPaired);
    }
}

void Controller::onDisconnected()
{
    emit connect_State("device disconnected");
    SendMessage("device disconnected");
}

void Controller::onStateChanged(QLowEnergyController::ControllerState state)
{
    const QString stateString[] = {
        "UnconnectedState",
        "ConnectingState",
        "ConnectedStatez",
        "DiscoveringState",
        "DiscoveredState",
        "ClosingState",
        "AdvertisingState",
    };

    if(state < stateString->size())
    {
        SendMessage("-----"+stateString[state]);
        if (stateString[state] == "UnconnectedState")
        {
            emit connect_err_info("UnconnectedState");
        }
        else if (stateString[state] == "ClosingState") {
            emit connect_err_info("ClosingState");
        }
    }
}

void Controller::onError(QLowEnergyController::Error newError)
{
    if(m_controller)
    {
        QString str;
        str = QString("Controller Error(%1):").arg(newError);
        str += m_controller->errorString();
        SendMessage(str);
    }
}

void Controller::onServiceDiscovered(QBluetoothUuid serviceUUID)
{

    emit serviceDiscovered(serviceUUID);

}

void Controller::onDiscoveryFinished()
{

    SendMessage("service discovery finished");
    emit service_uuid_end(true);

}

void Controller::onConnectionUpdated(const QLowEnergyConnectionParameters &parameters)
{

    SendMessage("controller connect updated");
}


