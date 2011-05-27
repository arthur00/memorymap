#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QGraphicsRectItem>
#include <QTcpSocket>

#include "connecttoport.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    struct Action {
        int addr; // stores the mem addr
        int act; // stores an eADD or eREMOVE
    };

    Ui::MainWindow *ui;

    int startAddr;
    QGraphicsScene *scene;
    QMap<int, QGraphicsRectItem *> addrToItemMap;

    void addNode(int addr, int len);
    void removeNode(int addr);

    QList<Action> actionList;

    QTcpSocket *sock;
    int blockSize;

    ConnectToPort *connectDialog;

    enum {
        eADD, eREMOVE,
    };

    QString loadFile(const QString &fileName);

private slots:
    void on_actionOpen_triggered();
    void on_pushButton_Listen_clicked();

    void zoomFactorChanged(int factor);

    void readSocket();

    void processData(QString data);

    void startListeningOnPort(QStringList list);
};

#endif // MAINWINDOW_H
