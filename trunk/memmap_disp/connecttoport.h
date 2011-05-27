#ifndef CONNECTTOPORT_H
#define CONNECTTOPORT_H

#include <QDialog>
#include <QRegExpValidator>

namespace Ui {
    class ConnectToPort;
}

class ConnectToPort : public QDialog {
    Q_OBJECT
public:
    ConnectToPort(QWidget *parent = 0);
    ~ConnectToPort();

    void setName(QString name);

    QStringList previousInfo; // Public list to store previous names; addresses; ports

private:
    Ui::ConnectToPort *ui;

    QRegExpValidator* addressValidator;
    QRegExpValidator* portValidator;

private slots:
    void dialogAccepted();

signals:
    void connectToPortClicked(QStringList list);

};

#endif // CONNECTTOPORT_H
