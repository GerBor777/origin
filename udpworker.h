
#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QObject>
#include <QUdpSocket>

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void sendDatagram(const QString &message);
    void getLastMessageInfo(QString &sender, QString &data, int &size) const;

signals:
    void datagramReceived();

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    QString lastSender;
    QString lastData;
    int lastSize;
};

#endif // UDPWORKER_H
