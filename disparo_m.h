#ifndef DISPARO_M_H
#define DISPARO_M_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "elemento.h"
#include <stdlib.h>
#include <time.h>

class disparo_m: public QObject, public QGraphicsItem
{
public:
    explicit disparo_m(QObject *parent = nullptr);

    QTimer *timer;
    QPixmap *pixmap;

    float filas, columnas;
    int moment = 0;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    void disparo_mago();

    float posx = 0; //Posicion en X
    float posy = 0;  //Posicion en Y
    float ancho = 68; //Ancho de la figura
    float alto = 68; // Alto de la figura

public slots:
    void actualizar_disparo_mago();
};

#endif // DISPARO_M_H
