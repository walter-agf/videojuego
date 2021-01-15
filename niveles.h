#ifndef NIVELES_H
#define NIVELES_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "elemento.h"
#include "grafica.h"
#include "muros.h"

class niveles : public QMainWindow
{
    Q_OBJECT

public:
    explicit niveles(QWidget *parent = nullptr);
    ~niveles();

    bool avanzar;

    QList<muros *> contras;

private:
    QGraphicsScene *scene;
    QList<grafica *> bars;
};

#endif // NIVELES_H
