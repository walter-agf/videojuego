#ifndef ONEPLAYER_H
#define ONEPLAYER_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFile>

#include <math.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "elemento.h"
#include "grafica.h"
#include "muros.h"
#include "niveles.h"
#include "mago.h"
#include "minotauro.h"


namespace Ui {
class oneplayer;
}

class oneplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit oneplayer(QWidget *parent = nullptr);
    ~oneplayer();

    int h_limit,w_limit;

    string dato, x_pix, y_pix, x_tam, y_tam,num;
    int numero_x,numero_y, largo;
    int cantidad_x, cantidad_y;

    void nivel(string num_);

    QList<muros*> contras;

public slots:
    void actualizar();

private slots:
    void on_actionVolver_triggered();

    void on_actionReiniciar_triggered();

private:
    Ui::oneplayer *ui;
    oneplayer *one;
    bool conti = true;
    int enemigo = 1;

    QTimer *timer;
    QGraphicsScene *scene;

    void borderCollision(elemento *b);
    void keyPressEvent(QKeyEvent *event);

    QList<grafica*> bars;
    QList<mago*> magos;
    QList<minotauro*> tauros;
};

#endif // ONEPLAYER_H
