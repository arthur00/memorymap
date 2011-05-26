#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMatrix>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->hide();
    ui->statusBar->hide();

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(zoomFactorChanged(int)));

    startAddr = 0;
    currOffset = 0;

    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNode(int addr, int len)
{
    int width = len / 4;
    int height = 100;
    QGraphicsRectItem* item = new QGraphicsRectItem(currOffset, 0, static_cast<qreal>(width), static_cast<qreal>(height));
    ui->graphicsView->scene()->addItem(item);

    addrMap.insert(addr, item);

}

void MainWindow::removeNode(int addr)
{
    if (addrMap.contains(addr)) {
        QGraphicsRectItem* item = addrMap.value(addr);

        ui->graphicsView->scene()->removeItem(item);

        addrMap.remove(addr);
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

}

void MainWindow::zoomFactorChanged(int factor)
{
    QMatrix matrix;
    matrix.scale(factor * .01, factor * .01);
    ui->graphicsView->setMatrix(matrix);
}
