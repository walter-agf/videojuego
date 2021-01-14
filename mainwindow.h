#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "elemento.h"
#include "grafica.h"
#include "oneplayer.h"
#include "multiplayer.h"
#include "score.h"
#include "inicio.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    oneplayer *one;
    multiplayer *two;
    score *puntuacion;

    QGraphicsScene *scene;

    int h_limit;
    int v_limit;

    inicio *personaje;
    float x,y,ancho,alto;

};


#endif // MAINWINDOW_H
