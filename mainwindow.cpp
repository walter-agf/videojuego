#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    h_limit = 1280;
    v_limit = 720;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);
    ui->graphicsView->setScene(scene);

    personaje = new inicio();

    scene->addItem(personaje);

    personaje->setPos(640,360);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    one = new oneplayer(this);
    one->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}

void MainWindow::on_pushButton_2_clicked()
{
    two = new multiplayer(this);
    two->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    puntuacion = new score(this);
    puntuacion->show();
}

void MainWindow::on_pushButton_pressed()
{
    if (b0 == 0){
        ui->pushButton->setStyleSheet("color: rgb(255, 220, 44);background-color: rgb(103, 68, 42);");
        b0=1;
    }
    else {
        ui->pushButton->setStyleSheet("color: rgb(103, 68, 42);background-color: rgb(255, 220, 44);");
        b0=0;
    }

}

void MainWindow::on_pushButton_2_pressed()
{
    if (b2 == 0){
        ui->pushButton_2->setStyleSheet("color: rgb(255, 220, 44);background-color: rgb(103, 68, 42);");
        b2=1;
    }
    else {
        ui->pushButton_2->setStyleSheet("color: rgb(103, 68, 42);background-color: rgb(255, 220, 44);");
        b2=0;
    }
}

void MainWindow::on_pushButton_3_pressed()
{
    if (b3 == 0){
        ui->pushButton_3->setStyleSheet("color: rgb(255, 220, 44);background-color: rgb(103, 68, 42);");
        b3=1;
    }
    else {
        ui->pushButton_3->setStyleSheet("color: rgb(103, 68, 42);background-color: rgb(255, 220, 44);");
        b3=0;
    }
}

void MainWindow::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(198, 0, 0);");
}

void MainWindow::on_pushButton_5_pressed()
{
    if (b5 == 0){
        ui->pushButton_5->setStyleSheet("background-color: rgb(10, 2, 70);");
        b5=1;
    }
    else {
        ui->pushButton_5->setStyleSheet("background-color: rgb(103, 68, 42);");
        b5=0;
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if (personaje->musica->isMuted() == false){
        personaje->musica->setMuted(true);
    }
    else {
        personaje->musica->setMuted(false);
    }
}
