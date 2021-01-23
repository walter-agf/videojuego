#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

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


namespace Ui {
class multiplayer;
}

class multiplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit multiplayer(QWidget *parent = nullptr);
    ~multiplayer();

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
    Ui::multiplayer *ui;
    multiplayer *one;
    bool conti = true;

    QTimer *timer;
    QGraphicsScene *scene;

    void borderCollision(elemento *b);
    void keyPressEvent(QKeyEvent *event);

    QList<grafica*> bars;
    QList<mago*> magos;
};

#endif // MULTIPLAYER_H
