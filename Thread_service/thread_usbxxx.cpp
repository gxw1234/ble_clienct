#include "thread_usbxxx.h"


Thread_usbxxx::Thread_usbxxx()
{

}



void Thread_usbxxx::scan_start()
{
    if(m_agent)
    {
        m_agent->setLowEnergyDiscoveryTimeout(1000);

        m_agent->start();
        if(m_agent->isActive())
        {
            qDebug() <<("scanning...");
        }
    }
}

void Thread_usbxxx::init()
{
    m_agent = new QBluetoothDeviceDiscoveryAgent(nullptr);

    if(m_agent)
    {
        connect(m_agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(onDeviceDiscovered(QBluetoothDeviceInfo)));
//        connect(m_agent,  &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &Thread_usbxxx::onDeviceDiscovered);
        connect(m_agent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)), this, SLOT(onError(QBluetoothDeviceDiscoveryAgent::Error)));
        connect(m_agent, SIGNAL(finished()), this, SLOT(onFinished()));
        connect(m_agent, SIGNAL(canceled()), this, SLOT(onCanceled()));
    }
}

void Thread_usbxxx::start()
{
    if(m_agent)
    {
        m_agent->setLowEnergyDiscoveryTimeout(1000);

        m_agent->start();
        if(m_agent->isActive())
        {
            qDebug() <<("scanning...");
        }
    }

}

void Thread_usbxxx::onDeviceDiscovered(const QBluetoothDeviceInfo &info)
{

}

void Thread_usbxxx::onError(QBluetoothDeviceDiscoveryAgent::Error err)
{

}

void Thread_usbxxx::onFinished()
{
    qDebug()<<("Agent scan finished");

}

void Thread_usbxxx::onCanceled()
{

    qDebug()<<("Agent scan canceled...");
}
