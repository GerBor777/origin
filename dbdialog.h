#ifndef DBDIALOG_H
#define DBDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DbDialog; }
QT_END_NAMESPACE

class DbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DbDialog(QWidget *parent = nullptr);
    ~DbDialog();

    QString host() const;
    QString databaseName() const;
    QString login() const;
    QString password() const;
    quint16 port() const;

private:
    Ui::DbDialog *ui;
};

#endif // DBDIALOG_H
