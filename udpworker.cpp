
#include "udpworker.h"

UDPworker::UDPworker(QObject *parent)
    : QObject(parent),
      udpSocket(new QUdpSocket(this))
{
    udpSocket->bind(QHostAddress::LocalHost, 12345);
    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPworker::processPendingDatagrams);
}

void UDPworker::sendDatagram(const QString &message)
{
    QByteArray data = message.toUtf8();
    udpSocket->writeDatagram(data, QHostAddress::LocalHost, 12345);
}

void UDPworker::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QHostAddress sender;
        quint16 port;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &port);

        lastSender = sender.toString();
        lastData = QString::fromUtf8(datagram);
        lastSize = datagram.size();

        emit datagramReceived();
    }
}

void UDPworker::getLastMessageInfo(QString &sender, QString &data, int &size) const
{
    sender = lastSender;
    data = lastData;
    size = lastSize;
}
