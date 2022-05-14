#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "memory.h"
#include "card.h"
#include <string>

/**
 * @brief Construct a new Main Window:: Main Window object
 * 
 * @param parent 
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , server (new Server)
{
    ui->setupUi(this);
    changeMemoryUsageHelper();
    ui->startServerBtn->setToolTip("Iniciar servidor");
}

/**
 * @brief Destroy the Main Window:: Main Window object
 * 
 */
MainWindow::~MainWindow()
{
    delete ui;

}

/**
 * @brief Crea un thread del muestreo de la memoria utilizada.
 * 
 */
void MainWindow::changeMemoryUsageHelper() {
    std::thread tMemory(&MainWindow::changeMemoryUsage, this);
    tMemory.detach();
}

/**
 * @brief Obtiene los nombres de los jugadores para mostrarlos en pantalla.
 */
void MainWindow::getNames() {
    while (!memoryManager.getGame()->getPlaying()) {
        sleep_for(std::chrono::milliseconds(10));
    }
    ui->staticName1->setText(memoryManager.getGame()->getPlayer1name());
    ui->staticName2->setText(memoryManager.getGame()->getPlayer2name());
}

/**
 * @brief Crea un thread del muestreo la información del servidor.
 * 
 */
void MainWindow::logInfo() {
    char* logMessage;
    //QTextStream out(stdout);
    while (1) {
        logMessage = memoryManager.getServer()->getLastMessage();
        qDebug() << logMessage;
        sleep_for(std::chrono::milliseconds(2000));
    }
}

/**
 * @brief Cambia el valor en pantalla de la memoria en uso.
 * 
 */
void MainWindow::changeMemoryUsage() {
    int num;
    QString numS;
    while (1) {
        num = memoryManager.getCurrentMemoryUsage();
        numS = QString::number(num);
        numS.append(" Bytes");
        ui->variableMemoryUsage->setText(numS);
        sleep_for(std::chrono::milliseconds(1000));
    }
}

/**
 * @brief Cambia el valor en pantalla de los page hit y los page fault.
 * 
 */
void MainWindow::changePagesInfo() {
    while (1) {
        ui->pageHit->setText(QString::number(memoryManager.getPageHit()));
        ui->pageFault->setText(QString::number(memoryManager.getPageFault()));
        sleep_for(std::chrono::milliseconds(1000));
    }

}

/**
 * @brief Cambia el valor en pantalla de las tarjetas en memoria y en disco.
 * 
 */
void MainWindow::inMemoryCardsInfo() {
    while (1) {
        memoryManager.createInMemoryCardsInfo();
        memoryManager.createInDiscCardsInfo();
        QTableWidgetItem *item = new QTableWidgetItem(memoryManager.getInMemoryCardsInfo());
        QTableWidgetItem *item1 = new QTableWidgetItem(memoryManager.getInDiscCardsInfo());
        ui->tableWidget->setItem(0, 0, item);
        ui->tableWidget->setItem(0, 1, item1);
        sleep_for(std::chrono::milliseconds(1000));
    }
}

/**
 * @brief Cambia el valor en pantalla de los puntajes de los jugadores.
 * 
 */
void MainWindow::changePointsInfo() {
    int points[2];
    while (1) {
        points[0] = memoryManager.getGame()->getScore(0);
        points[1] = memoryManager.getGame()->getScore(1);
        ui->points1->setText(QString::number(points[0]));
        ui->points2->setText(QString::number(points[1]));
        sleep_for(std::chrono::milliseconds(1000));
    }
}



// Al iniciar el servidor debe iniciar todos los threads de la funciones que deben escuchar y generar las clases puntero de MainWindow.

/**
 * @brief Realiza todos los preparativos para iniciar el servidor y algunas características del juego.
 * 
 */
void MainWindow::on_startServerBtn_clicked()
{
    ui->startServerBtn->setEnabled(false);
    ui->logText->appendPlainText("Iniciando server");
    memoryManager.startGame();
    ui->logText->appendPlainText("Server iniciado");

    // Para tratar la tabla.
    std::thread tMemory(&MainWindow::inMemoryCardsInfo, this);
    tMemory.detach();

    std::thread tPoints(&MainWindow::changePointsInfo, this);
    tPoints.detach();

    std::thread tPages(&MainWindow::changePagesInfo, this);
    tPages.detach();

    std::thread tNames(&MainWindow::getNames, this);
    tNames.detach();
}


