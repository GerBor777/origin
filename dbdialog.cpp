#include "dbdialog.h"
#include "ui_dbdialog.h"

DbDialog::DbDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DbDialog)
{
    ui->setupUi(this);
}

DbDialog::~DbDialog()
{
    delete ui;
}

QString DbDialog::host() const { return ui->lineEditHost->text(); }
QString DbDialog::databaseName() const { return ui->lineEditDbName->text(); }
QString DbDialog::login() const { return ui->lineEditLogin->text(); }
QString DbDialog::password() const { return ui->lineEditPassword->text(); }
quint16 DbDialog::port() const { return static_cast<quint16>(ui->spinBoxPort->value()); }
