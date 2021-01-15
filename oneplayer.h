#ifndef ONEPLAYER_H
#define ONEPLAYER_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>

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

    bool avanzar;
    string dato;
    int valor;


    bool nivel1();

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
