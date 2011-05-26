#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QGraphicsRectItem>

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
    Ui::MainWindow *ui;

    int startAddr;
    QMap<int, QGraphicsRectItem> addrMap;

    void addNode(int addr, int len);
    void removeNode(int addr);

private slots:
    void on_actionOpen_triggered();

    void zoomFactorChanged(int factor);
};

#endif // MAINWINDOW_H
