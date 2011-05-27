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
        unsigned long addr; // stores the mem addr
        int len;
        int act; // stores an eADD or eREMOVE
    };

    Ui::MainWindow *ui;

    unsigned long startAddr;
    int w_height;
    int w_width;
    int curLine;
    QGraphicsScene *scene;

    QMap<unsigned long, QList<QGraphicsRectItem*> > addrToItemMap;

    void addNode(unsigned long addr, int len);
    void removeNode(unsigned long addr);

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
    void firstStep();
};

#endif // MAINWINDOW_H
