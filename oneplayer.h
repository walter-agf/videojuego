#ifndef ONEPLAYER_H
#define ONEPLAYER_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>

#include <math.h>
#include <fstream>
#include <string>
using namespace std;

#include "elemento.h"
#include "grafica.h"
#include "muros.h"


namespace Ui {
class oneplayer;
}

class oneplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit oneplayer(QWidget *parent = nullptr);
    ~oneplayer();

    string dato, x_pix, y_pix, x_tam, y_tam;
    int numero_x,numero_y, largo;
    int cantidad_x, cantidad_y;

    void nivel1();

    QList<muros *> contras;

public slots:
    void actualizar();

private slots:
    void on_actionVolver_triggered();

private:
    Ui::oneplayer *ui;

    QTimer *timer;
    QGraphicsScene *scene;

    void borderCollision(elemento *b);
    void keyPressEvent(QKeyEvent *event);

    QList<grafica *> bars;
};

#endif // ONEPLAYER_H
