#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "elemento.h"
#include "grafica.h"

namespace Ui {
class multiplayer;
}

class multiplayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit multiplayer(QWidget *parent = nullptr);
    ~multiplayer();

public slots:
    void actualizar();

private slots:
    void on_actionVolver_triggered();

private:
    Ui::multiplayer *ui;

    QTimer *timer;
    QGraphicsScene *scene;
    float dt;
    int h_limit;
    int v_limit;

    void borderCollision(elemento *b);
    void keyPressEvent(QKeyEvent *event);

    QList<grafica *> bars;
};

#endif // MULTIPLAYER_H
