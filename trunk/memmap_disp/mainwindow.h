#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QGraphicsRectItem>
#include <QTcpSocket>
#include <QTcpServer>


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
        long addr; // stores the mem addr
        int len;
        int act; // stores an eADD or eREMOVE
    };

    Ui::MainWindow *ui;

    int startAddr;
    QGraphicsScene *scene;
    QMap<int, QGraphicsRectItem *> addrToItemMap;

    void addNode(int addr, int len);
    void removeNode(int addr);

    QList<Action> actionList;

    QTcpServer *server;
    QTcpSocket *sock;
    int blockSize;

    int currStep;

    enum {
        eADD, eREMOVE,
    };

    QString loadFile(const QString &fileName);

private slots:
    void on_actionOpen_triggered();

    void zoomFactorChanged(int factor);

    void readSocket();

    void processData(QString data);

    void newConnection();

    void nextStep();
    void prevStep();
};

#endif // MAINWINDOW_H
