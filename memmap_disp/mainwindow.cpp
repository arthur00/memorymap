#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMatrix>
#include <QTime>
#include <QDebug>

#include "connecttoport.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->hide();
    ui->statusBar->hide();

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(zoomFactorChanged(int)));

    connectDialog = new ConnectToPort(this);
    connect(connectDialog, SIGNAL(connectToPortClicked(QStringList)), this, SLOT(startListeningOnPort(QStringList)));

    startAddr = 0;

    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNode(int addr, int len)
{
    if (startAddr = 0) {
        startAddr = addr;
    }

    double width = len / 8;
    int height = 200 / 8;

    // calculate offset:
    double offset = (addr - startAddr) / 8;

    QBrush brush(QColor(qrand() % 256, qrand() % 256, qrand() % 256));

    QGraphicsRectItem* item = new QGraphicsRectItem(offset, 0, static_cast<qreal>(width), static_cast<qreal>(height));
    item->setBrush(brush);
    item->setToolTip(QString("0x") + QString("%1, ").arg(addr, 9, 16, QLatin1Char('0')).toUpper() + QString("%2 bytes").arg(len));
    ui->graphicsView->scene()->addItem(item);

    addrToItemMap.insert(addr, item);

}

void MainWindow::removeNode(int addr)
{
    if (addrToItemMap.contains(addr)) {
        QGraphicsRectItem* item = addrToItemMap.value(addr);

        ui->graphicsView->scene()->removeItem(item);

        addrToItemMap.remove(addr);

        delete item;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    // parse a log

    // dummy code for now:

//    [MALLOC]: [0x1002CE030] : 88 bytes
//    [MALLOC]: [0x1002CE0B0] : 4096 bytes
//    [MALLOC]: [0x1002CF0D0] : 2160 bytes



    addNode(0x1002CE030, 88);
    addNode(0x1002CE0B0, 4096);
    addNode(0x1002CF0D0, 2160);

    //    [FREE]: 0x1002CE0B0
    //    [MALLOC]: [0x1002CE0B0] : 3312 bytes
    //    [MALLOC]: [0x1002CF960] : 4096 bytes
    //    [REALLOC]: [0x1002D0980] : 90596 bytes
    //    [FREE]: 0x1002CF960
    //    [MALLOC]: [0x1002CE0B0] : 192 bytes
    //    [MALLOC]: [0x1002CE190] : 46 bytes
    //    [MALLOC]: [0x1002CE1E0] : 48 bytes
    //    [MALLOC]: [0x1002CE230] : 20 bytes
    //    [MALLOC]: [0x1002CE270] : 488 bytes
    //    [MALLOC]: [0x1002CE480] : 389 bytes
    //    [MALLOC]: [0x1002CE630] : 56 bytes
    //    [MALLOC]: [0x1002CE690] : 30 bytes
    //    [MALLOC]: [0x1002CE6D0] : 72 bytes
    //    [MALLOC]: [0x1002CE740] : 1280 bytes
    //    [MALLOC]: [0x1002CEC60] : 112 bytes
    //    [MALLOC]: [0x1002CECF0] : 113 bytes
    //    [MALLOC]: [0x1002CED90] : 112 bytes
    //    [FREE]: 0x1002CED90

    removeNode(0x1002CE0B0);

    addNode(0x1002CE0B0, 3312);
    addNode(0x1002CF960, 4096);

    removeNode(0x1002CE0B0);

//    removeNode(0x1002D0980);
//    addNode(0x1002D0980, 90596);

    removeNode(0x1002CF960);

    addNode(0x1002CE0B0, 192);
    addNode(0x1002CE190, 46);
    addNode(0x1002CE1E0, 48);
    addNode(0x1002CE230, 20);
    addNode(0x1002CE270, 488);
    addNode(0x1002CE480, 389);
    addNode(0x1002CE630, 56);
    addNode(0x1002CE690, 30);
    addNode(0x1002CE6D0, 72);
    addNode(0x1002CE740, 1280);
    addNode(0x1002CEC60, 112);
    addNode(0x1002CECF0, 113);
    addNode(0x1002CED90, 112);

    removeNode(0x1002CED90);



}

void MainWindow::on_pushButton_Listen_clicked()
{
    connectDialog->show();
}

void MainWindow::zoomFactorChanged(int factor)
{
    QMatrix matrix;
    matrix.scale(factor * .01, factor * .01);
    ui->graphicsView->setMatrix(matrix);
}


void MainWindow::readSocket()
{
    int addr;
    int act;

    // finished parsing the line:
    Action action;
    action.addr = addr;
    action.act = eADD;

    actionList.append(action);

}

void MainWindow::startListeningOnPort(QStringList list)
{
    sock = new QTcpSocket(this);
    sock->connectToHost(list.at(0), QString(list.at(1)).toInt(), QTcpSocket::ReadOnly);
    qDebug() << "Listening...";

    connect(sock, SIGNAL(readyRead()), this, SLOT(readSocket()));
}
