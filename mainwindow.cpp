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

    QMediaPlayer *musica = new QMediaPlayer();
    musica->setMedia(QUrl("qrc:/sonidos/2020_01.mp3"));
    musica->play();

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
