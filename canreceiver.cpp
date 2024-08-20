#include "canreceiver.h"
#include <QCanBus>
#include <QDebug>
#include <QProcess>

CanReceiver::CanReceiver(QObject *parent)
    : QObject(parent),
    canDevice(nullptr),
    expectedId(0x100)
{
}

CanReceiver::~CanReceiver()
{
    if (this->canDevice)
    {
        this->canDevice->disconnectDevice();
        delete this->canDevice;
    }
}

void CanReceiver::startReceiving(const QString &interfaceName)
{
    QProcess process;
    process.start("sudo ip link set " + interfaceName + " down");
    process.waitForFinished();
    process.start("sudo ip link set " + interfaceName + " up type can bitrate 500000");
    process.waitForFinished();

    qDebug() << "CanReceiver startReceiving()";

    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
    {
        qDebug() << "device: socketcan  " << "interface: " << interfaceName;
        this->canDevice = QCanBus::instance()->createDevice("socketcan", interfaceName);
        if (this->canDevice)
        {
            qDebug() << "Successfully created CAN device";
            connect(this->canDevice, &QCanBusDevice::framesReceived, this, &CanReceiver::processReceivedFrames);
            if (!this->canDevice->connectDevice())
            {
                qDebug() << "Failed to connect CAN device";
                delete this->canDevice;
                this->canDevice = nullptr;
            }
        }
    }
}

void CanReceiver::processReceivedFrames()
{
    if (!this->canDevice)
    {
        qDebug() << "canDevice is NULL";
        return;
    }

    while (this->canDevice->framesAvailable())
    {
        qDebug() << "Message received";
        const QCanBusFrame frame = this->canDevice->readFrame();

        if (!frame.isValid())
        {
            qDebug() << "Invalid CAN frame received";
            qDebug() << "Frame: " << frame.toString();
            continue;
        }

        const int messageId = frame.frameId();
        qDebug() << "Message ID: " << messageId;

        if (messageId != this->expectedId)
        {
            continue;
        }

        QByteArray payload = frame.payload();

        if (payload.size() == sizeof(float))
        {
            unsigned int scaledSpeed = 0;
            memcpy(&scaledSpeed, payload.constData(), sizeof(unsigned int));
            int rawSpeed = static_cast<int>(scaledSpeed / this->SCALE);

            float filteredSpeed = static_cast<float>(rawSpeed);

            // В зависимости от выбранного фильтра, фильтрация будет происходить в MainWindow
            // Фильтр будет применяться в MainWindow перед вызовом updateSpeed

            qDebug() << "Speed (cm/s): " << filteredSpeed;
            emit speedUpdated(filteredSpeed);
        }
    }
}
