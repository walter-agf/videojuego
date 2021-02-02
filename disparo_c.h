#ifndef DISPARO_C_H
#define DISPARO_C_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "elemento.h"
#include <stdlib.h>
#include <time.h>

class disparo_c: public QObject, public QGraphicsItem
{
public:
    explicit disparo_c(QObject *parent = nullptr);

    QTimer *timer;
    QPixmap *pixmap;

    float filas, columnas;
    int moment = 0, rango = 500;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    void disparo_caballero();

    float posx = 0; //Posicion en X
    float posy = 0;  //Posicion en Y
    float ancho = 25; //Ancho de la figura
    float alto = 24; // Alto de la figura

public slots:
    void actualizar_disparo_caballero();
};

#endif // DISPARO_C_H
