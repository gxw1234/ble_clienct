#include "service.h"

Service::Service(QObject *parent) : QObject(parent)
{
    m_service = NULL;
    mapping["4c53010000000000000000000000000000000000"] = "语音按下";
    mapping["4c53000000000000000000000000000000000000"] = "语音抬起";

}

void Service::ConnectService(QLowEnergyService * service)
{
    m_service = service;
    if(m_service)
    {
        if(m_service->state() == QLowEnergyService::ServiceDiscovered)
        {
            onStateChanged(QLowEnergyService::ServiceDiscovered);
        }
        else
        {
            connect(m_service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)), this, SLOT(onStateChanged(QLowEnergyService::ServiceState)));
            connect(m_service, SIGNAL(characteristicChanged(QLowEnergyCharacteristic, QByteArray)), this, SLOT(onCharacteristicChanged(QLowEnergyCharacteristic, QByteArray)));
            connect(m_service, SIGNAL(characteristicRead(QLowEnergyCharacteristic, QByteArray)), this, SLOT(onCharacteristicRead(QLowEnergyCharacteristic, QByteArray)));
            connect(m_service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic, QByteArray)), this, SLOT(onCharacteristicWritten(QLowEnergyCharacteristic, QByteArray)));
//            connect(m_service, SIGNAL(descriptorRead(QLowEnergyCharacteristic, QByteArray)), this, SLOT(onDescriptorRead(QLowEnergyCharacteristic, QByteArray)));
//            connect(m_service, SIGNAL(descriptorWritten(QLowEnergyCharacteristic, QByteArray)), this, SLOT(onDescriptorWritten(QLowEnergyCharacteristic, QByteArray)));
            connect(m_service, SIGNAL(error(QLowEnergyService::ServiceError)), this, SLOT(onError(QLowEnergyService::ServiceError)));
            m_service->discoverDetails();
        }
    }
}

void Service::SendMessage(QString msg)
{
    emit message(msg);
}

void Service::OpenNotify(QLowEnergyCharacteristic ch, bool flag)
{

    if(m_service)
    {
        if(ch.isValid())
        {
            if(ch.properties() & QLowEnergyCharacteristic::Notify)
            {
                QLowEnergyDescriptor d = ch.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
                if(d.isValid())
                {
                    if(true == flag)
                    {
                        // 获取特征的handle值
                        quint16 handleValue = ch.handle();
                        QString handleStr = QString::number(handleValue,16);
                        QString notifyMessage;
                        SendMessage("监听......."+notifyMessage  +"......handleValue:  "+handleStr);
                        m_service->writeDescriptor(d, QByteArray::fromHex("0100"));

                    }
                    else
                    {
                        m_service->writeDescriptor(d, QByteArray::fromHex("0000"));
                    }
                }
            }
        }
    }
}

void Service::ReadCharacteristic(QLowEnergyCharacteristic ch)
{
    if(m_service)
    {
        if(ch.isValid())
        {
            if(ch.properties() & QLowEnergyCharacteristic::Read)
            {
                for (int i = 1; i <= 20; i++) {
                    m_service->readCharacteristic(ch);
                }
            }
        }
    }
}


void Service::WriteCharacteristic(QLowEnergyCharacteristic ch, QByteArray arr)
{
    if(m_service)
    {
        if(ch.isValid())
        {
            if(ch.properties() & QLowEnergyCharacteristic::Write)
            {
                m_service->writeCharacteristic(ch, arr, QLowEnergyService::WriteWithResponse);
            }
            else if(ch.properties() & QLowEnergyCharacteristic::WriteNoResponse)
            {
                m_service->writeCharacteristic(ch, arr, QLowEnergyService::WriteWithoutResponse);
            }
            else if(ch.properties() & QLowEnergyCharacteristic::WriteSigned)
            {
                m_service->writeCharacteristic(ch, arr, QLowEnergyService::WriteSigned);
            }
        }

    }
}


void Service::onStateChanged(QLowEnergyService::ServiceState newState)
{
    if(m_service)
    {
        switch(newState)
        {
            case QLowEnergyService::DiscoveringServices:
            {
                SendMessage("Discovering services...");
            }
            break;

            case QLowEnergyService::DiscoveryRequired:
            {
                SendMessage("require discover services...");
            }
            break;

            case QLowEnergyService::ServiceDiscovered:
            {

                SendMessage("Discovered services");

                QList<QLowEnergyCharacteristic> characteristics = m_service->characteristics();

                foreach(QLowEnergyCharacteristic ch, characteristics)
                {
                    if(ch.isValid())
                    {
                        if(ch.properties() & QLowEnergyCharacteristic::Notify)
                        {
                            QLowEnergyDescriptor d = ch.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
                            if(d.isValid())
                            {
                                if(true)
                                {
                                    quint16 handleValue = ch.handle();
                                    QString handleStr = QString::number(handleValue);
                                    QString notifyMessage;
//                                    notifyMessage = QString("监听.......... UUID: %1").arg(ch.uuid().toString() +"征的handle" +handleStr);
//                                    SendMessage("监听....................uuid"+notifyMessage  );
                                    m_service->writeDescriptor(d, QByteArray::fromHex("0200"));
                                }
                                else
                                {
                                    m_service->writeDescriptor(d, QByteArray::fromHex("0000"));
                                }
                            }
                        }
                    }

                    emit discoveryCharacteristic(ch);
                }
                emit onStateChanged_end();

        }
            break;

            default:
            break;
        }
    }
}

void Service::onCharacteristicChanged(const QLowEnergyCharacteristic &info, const QByteArray &value)
{



    if(info.uuid().toString() ==uuid1 )
    {
        if (mapping.contains(value.toHex())) {
            emit onKeyresult(mapping[value.toHex()]);
        }
    }
    else if (info.uuid().toString() ==uuid2) {
        if (value.toHex() != service_value)
        {
            emit onaudio(value.toHex());
        }

    }

}

void Service::onCharacteristicRead(const QLowEnergyCharacteristic &info, const QByteArray &value)
{

//    QString ch = info.uuid().toString() + " - Characteristic read:" + QString(value);
    QString ch = info.uuid().toString() + " - Characteristic read:" + value.toHex();
    qDebug() << "value" <<value;
    SendMessage(ch);
}

void Service::onCharacteristicWritten(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
//    QString ch = info.uuid().toString() + " - Characteristic written:" + QString(value);
    QString ch = info.uuid().toString() + " - Characteristic written:" + value.toHex();
    SendMessage(ch);
}

void Service::onDescriptorRead(const QLowEnergyDescriptor &info, const QByteArray &value)
{
    QString ch = info.uuid().toString() + " - descriptor read:" + value.toHex();
    SendMessage(ch);
}

void Service::onDescriptorWritten(const QLowEnergyDescriptor &info, const QByteArray &value)
{
    QString ch = info.uuid().toString() + " - descriptor written:" + value.toHex();
    SendMessage(ch);
}

void Service::onError(QLowEnergyService::ServiceError error)
{

    const QString ServiceError[] {
        "NoError",
        "OperationError",
        "CharacteristicWriteError",
        "DescriptorWriteError",
        "UnknownError",
        "CharacteristicReadError",
        "DescriptorReadError"
    };


    if(error < ServiceError->size())
    {
        QString str;
        str = QString("service Error(%1):").arg(error);
        str += ServiceError[error];
        SendMessage(str);
    }
}
