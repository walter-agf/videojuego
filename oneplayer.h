#ifndef ONEPLAYER_H
#define ONEPLAYER_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
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

    QList<muros *> contras;

    QList<QString *> ubicaciones;

public slots:
    void actualizar();

private slots:
    void on_actionVolver_triggered();

private:
    Ui::oneplayer *ui;

    QTimer *timer;
    QGraphicsScene *scene;
    float dt;
    int h_limit;
    int v_limit;

    void borderCollision(elemento *b);
    void keyPressEvent(QKeyEvent *event);

    QList<grafica *> bars;
};

#endif // ONEPLAYER_H
