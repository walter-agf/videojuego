#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "elemento.h"
#include "grafica.h"
#include "score.h"
#include "inicio.h"
#include "dificultad.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int b0=0;
    int b2=0;
    int b3=0;
    int b4=0;
    int b5=0;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;

    score *puntuacion;

    dificultad *dif;

    QGraphicsScene *scene;

    int h_limit;
    int v_limit;

    inicio *personaje;
    float x,y,ancho,alto;

};


#endif // MAINWINDOW_H
