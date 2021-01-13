#ifndef GRAFICA_H
#define GRAFICA_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "elemento.h"
#include <stdlib.h>
#include <time.h>

class grafica: public QObject, public QGraphicsItem
{
public:
    explicit grafica(QObject *parent = nullptr);
    ~grafica();

    QTimer * timer;
    QPixmap *pixmap;

    float filas, columnas;
    int moment = 0;


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    void actualizar_grafica(float v_lim);
    elemento *getEsf();

public slots:
    void actualizacion_sprites();

private:
    elemento *esf;
};

#endif // GRAFICA_H
