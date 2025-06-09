#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbdialog.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnOpenDialog, &QPushButton::clicked, this, [this]() {
        DbDialog dlg(this);
        dlg.exec();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
