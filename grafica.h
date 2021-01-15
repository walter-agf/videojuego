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

    float posx = 50;
    float posy = 300;
    float r = 20;
    float mass = 50;
    float velx = 0;
    float vely = 0;
    float K = 0.1;
    float e = 0.2;
    float ancho = 44;
    float alto = 40;


public slots:
    void actualizacion_sprites();

private:
    elemento *esf;
};

#endif // GRAFICA_H
