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
    w_width= 1920;
    w_height = 1080;
    curLine = 0;
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
    connect(ui->pushButton_First, SIGNAL(clicked()),this, SLOT(firstStep()));

    startAddr = 0;
    blockSize = 0;
    currStep = -1;

    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNode(unsigned long addr, int len)
{
    if (startAddr == 0) {
        startAddr = addr;
    }

    double real_offset;
    double totallen = len;
    int height = 30;

    // calculate offset:
    double offset = ((addr - startAddr));
    unsigned long line = offset / w_width;
    if (line == 0)
        real_offset = offset;
    else
        real_offset = (unsigned long)offset % (unsigned long)w_width;
    QList<QGraphicsRectItem*> t_list;

    if (real_offset + len < w_width)
    {
        QBrush brush(QColor(qrand() % 256, qrand() % 256, qrand() % 256));

        QGraphicsRectItem* item = new QGraphicsRectItem(real_offset, (line * height), static_cast<qreal>(totallen), static_cast<qreal>(height));
        item->setBrush(brush);
        item->setToolTip(QString("0x") + QString("%1, ").arg(addr, 9, 16, QLatin1Char('0')).toUpper() + QString("%2 bytes").arg(totallen));
        ui->graphicsView->scene()->addItem(item);
        t_list.append(item);
    }
    else
    {
        QBrush brush(QColor(qrand() % 256, qrand() % 256, qrand() % 256));

        QGraphicsRectItem* item = new QGraphicsRectItem(real_offset, (line * height), static_cast<qreal>(w_width - real_offset), static_cast<qreal>(height));
        item->setBrush(brush);
        item->setToolTip(QString("0x") + QString("%1, ").arg(addr, 9, 16, QLatin1Char('0')).toUpper() + QString("%2 bytes").arg(totallen));
        ui->graphicsView->scene()->addItem(item);

        line++;
        t_list.append(item);
        len = len - (w_width - real_offset);
        while ((len / w_width) > 0)
        {
            item = new QGraphicsRectItem(0, (line * height), static_cast<qreal>(w_width), static_cast<qreal>(height));
            item->setBrush(brush);
            item->setToolTip(QString("0x") + QString("%1, ").arg(addr, 9, 16, QLatin1Char('0')).toUpper() + QString("%2 bytes").arg(totallen));
            ui->graphicsView->scene()->addItem(item);

            line++;
            t_list.append(item);
            len = len - w_width;
        }

        item = new QGraphicsRectItem(0, (line * height), static_cast<qreal>(len), static_cast<qreal>(height));
        item->setBrush(brush);
        item->setToolTip(QString("0x") + QString("%1, ").arg(addr, 9, 16, QLatin1Char('0')).toUpper() + QString("%2 bytes").arg(totallen));
        ui->graphicsView->scene()->addItem(item);

        t_list.append(item);
    }
    addrToItemMap.insert(addr,t_list);
}

void MainWindow::removeNode(unsigned long addr)
{
    if (addrToItemMap.contains(addr)) {
        QList<QGraphicsRectItem*> list = addrToItemMap.value(addr);
        int i = 0;
        int len = list.size();
        while (i < len)
        {
            QGraphicsRectItem* item = list[i];
            ui->graphicsView->scene()->removeItem(item);
            i++;
            delete item;
        }
        addrToItemMap.remove(addr);
    }
    else
    {
        qDebug() << "Could not find address.";
        qDebug() << addr;
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


void MainWindow::zoomFactorChanged(int factor)
{
    QMatrix matrix;
    matrix.scale(factor * .01, factor * .01);
    ui->graphicsView->setMatrix(matrix);
}


void MainWindow::readSocket()
{
    char data[1024];
    while(sock->bytesAvailable() > 0) {
        sock->readLine(data,sizeof(data));
        processData(data);

    }
}

void MainWindow::processData(QString data)
{
    QStringList cmds = data.split(":");
    Action action;

    bool ok = false;

    if (cmds[0] == "[MALLOC]")
    {
        currStep++;
        /*
        qDebug() << "Its a malloc";
        qDebug() << "Address: " + cmds[1];
        qDebug() << "Size: " + cmds[2];*/

        action.addr = QString(cmds[1]).toULong(&ok, 16);
        action.act = eADD;
        action.len = QString(cmds[2]).toInt(&ok, 10);
        actionList.append(action);

        addNode(action.addr, QString(cmds[2]).toInt(&ok, 10));


    }
    else if (cmds[0] == "[FREE]")
    {/*
        qDebug() << "Its a free";
        qDebug() << "Address: " + cmds[1];*/
        currStep++;
        action.addr = QString(cmds[1]).toULong(&ok, 16);
        action.act = eREMOVE;
        action.len = findMallocForAddr(action.addr);

        actionList.append(action);

        removeNode(action.addr);
    }
    else if (cmds[0] == "[REALLOC]")
    {/*
        qDebug() << "Its a realloc";
        qDebug() << "Old Address: " + cmds[1];
        qDebug() << "New Address: " + cmds[2];
        qDebug() << "Size of newly allocated block: " + cmds[3];
    */
        currStep++;
        action.addr = QString(cmds[1]).toULong(&ok, 16);
        action.act = eREMOVE;
        action.len = findMallocForAddr(action.addr);

        actionList.append(action);

        removeNode(action.addr);

        currStep++;
        Action action2;

        action2.addr = QString(cmds[2]).toULong(&ok, 16);
        action2.act = eADD;
        action2.len = QString(cmds[3]).toInt(&ok, 10);

        actionList.append(action2);

        addNode(action2.addr, QString(cmds[3]).toInt(&ok, 10));
    }
}

int MainWindow::findMallocForAddr(unsigned long addr)
{
    int i = currStep - 1;
    while (i > 0)
    {
        Action act = actionList.at(i);
        if (act.act == eADD)
        {
            if (act.addr == addr)
                return act.len;
        }
        i--;
    }
    // Should not get to here, if so, there is a memory leak \o/
    qDebug() << "Could not find add for address ";
    qDebug() <<  addr;
    return -1;
}

void MainWindow::newConnection()
{
    sock = server->nextPendingConnection();
    qDebug() << "New connection incoming";
    connect(sock, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void MainWindow::nextStep()
{
    if (currStep < actionList.size() - 1 && currStep >= 0) {
        currStep++;
        // won't buffer overflow
        Action action = actionList.at(currStep);
        if (action.act == eADD) {
            addNode(action.addr, action.len);
        }
        else if (action.act == eREMOVE){
            removeNode(action.addr);
        }
    }
}

void MainWindow::prevStep()
{
    if (currStep > 0 && currStep < actionList.size()) {
        // won't buffer overflow
        Action action = actionList.at(currStep);

        if (action.act == eREMOVE) {
            addNode(action.addr, action.len);
        }
        else if (action.act == eADD){
            removeNode(action.addr);
        }
        currStep--;
    }
}

void MainWindow::firstStep()
{
    // clear view

    QList<unsigned long> keys = addrToItemMap.keys();
    for (int i = 0; i < keys.size(); i++) {
        removeNode(keys.at(i));
    }

    currStep = 0;
    Action action = actionList.at(0);
    if (action.act == eADD) {
        addNode(action.addr, action.len);
    }

}



