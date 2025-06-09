
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);

    connect(ui->pb_sendDatagram, &QPushButton::clicked, this, &MainWindow::on_pb_sendDatagram_clicked);
    connect(udpWorker, &UDPworker::datagramReceived, this, &MainWindow::onDatagramReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_sendDatagram_clicked()
{
    QString message = ui->le_message->text();
    udpWorker->sendDatagram(message);
}

void MainWindow::onDatagramReceived()
{
    QString sender, data;
    int size;
    udpWorker->getLastMessageInfo(sender, data, size);

    QString output = QString("Принято сообщение от %1, размер сообщения (байт): %2\n%3\n")
                     .arg(sender).arg(size).arg(data);
    ui->te_receivedData->append(output);
}
