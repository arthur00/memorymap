#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMatrix>
#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->hide();
//    ui->statusBar->hide();

    server = new QTcpServer(this);
    server->listen();
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    ui->statusBar->showMessage(QString("The app is listening on port %1").arg(server->serverPort()));

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(zoomFactorChanged(int)));

    connect(ui->pushButton_Next, SIGNAL(clicked()), this, SLOT(nextStep()));
    connect(ui->pushButton_Previous, SIGNAL(clicked()), this, SLOT(prevStep()));

    startAddr = 0;
    blockSize = 0;
    currStep = 0;

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

QString MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return "";
    }

    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("ISO 8859-1"));

    return in.readAll();
}


void MainWindow::on_actionOpen_triggered()
{
    // parse a log

    QString fileName = QFileDialog::getOpenFileName(
            this,
            "Open text file",
            0,
            "Text files (*.*)");
    if (!fileName.isEmpty()) {

        QString input = loadFile(fileName);

        QStringList inputList = input.split('\n');

        for (int i = 0; i < inputList.size(); i++) {
            processData(inputList.at(i));
        }
    }
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
    while(sock->bytesAvailable() > 0) {
        QString data;
        QDataStream in(sock);

        in >> data;
        processData(data);
        currStep++;
    }
}

void MainWindow::processData(QString data)
{
    QStringList cmds = data.split(":");
    Action action;

    bool ok = false;

    if (cmds[0] == "[MALLOC]")
    {
        qDebug() << "Its a malloc";
        qDebug() << "Address: " + cmds[1];
        qDebug() << "Size: " + cmds[2];

        action.addr = QString(cmds[1]).toLong(&ok, 16);
        action.act = eADD;
        action.len = QString(cmds[2]).toInt(&ok, 10);
        actionList.append(action);

        addNode(action.addr, QString(cmds[2]).toInt(&ok, 10));

    }
    else if (cmds[0] == "[FREE]")
    {
        qDebug() << "Its a free";
        qDebug() << "Address: " + cmds[1];

        action.addr = QString(cmds[1]).toLong(&ok, 16);
        action.act = eREMOVE;
        actionList.append(action);

        removeNode(action.addr);

    }
    else if (cmds[0] == "[REALLOC]")
    {
        qDebug() << "Its a realloc";
        qDebug() << "Old Address: " + cmds[1];
        qDebug() << "New Address: " + cmds[2];
        qDebug() << "Size of newly allocated block: " + cmds[3];

        action.addr = QString(cmds[1]).toLong(&ok, 16);
        action.act = eREMOVE;

        actionList.append(action);

        removeNode(action.addr);

        action.addr = QString(cmds[2]).toLong(&ok, 16);
        action.act = eADD;
        action.len = QString(cmds[3]).toInt(&ok, 10);

        actionList.append(action);

        addNode(action.addr, QString(cmds[3]).toInt(&ok, 10));

    }

}

void MainWindow::newConnection()
{
    sock = server->nextPendingConnection();
    connect(sock, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void MainWindow::nextStep()
{
    if (actionList.size() > currStep) {
        // won't buffer overflow
        Action action = actionList.at(currStep + 1);
        if (action.act == eADD) {
            addNode(action.addr, action.len);
        }
        else if (action.act = eREMOVE){
            removeNode(action.addr);
        }
        currStep++;
    }

}

void MainWindow::prevStep()
{
    if (currStep > 0) {
        // won't buffer overflow
        Action action = actionList.at(currStep);
        if (action.act == eREMOVE) {
            addNode(action.addr, action.len);
        }
        else if (action.act = eADD){
            removeNode(action.addr);
        }
        currStep--;
    }

}



