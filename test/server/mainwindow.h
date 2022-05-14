#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "memory.h"
#include <thread>
#include <string>
#include <stdio.h>
#include <string.h>
#include <QDebug>

using std::this_thread::sleep_for;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeMemoryUsage();
    void changeMemoryUsageHelper();
    void inMemoryCardsInfo();
    void changePointsInfo();
    void changePagesInfo();
    void logInfo();
    void getNames();

private slots:
    void on_startServerBtn_clicked();

private:
    Ui::MainWindow *ui;
    Server *server;
    Memory memoryManager;
    int tableIteration = 0;
    int tablei = 0;
};
#endif // MAINWINDOW_H
