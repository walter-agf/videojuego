#ifndef JEFE_UNO_H
#define JEFE_UNO_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "elemento.h"
#include <stdlib.h>
#include <time.h>

class jefe_uno: public QObject, public QGraphicsItem
{
public:
    explicit jefe_uno(QObject *parent = nullptr);

    QTimer *timer;
    QPixmap *pixmap;

    float filas, columnas;
    int moment = 0;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    void actualizar_jefe_uno();

    float posx = 0; //Posicion en X
    float posy = 0;  //Posicion en Y
    float ancho = 320; //Ancho de la figura
    float alto = 320; // Alto de la figura
    float rango = 300; //rango de ataque

public slots:
    void actualizacion_sprites_jefe_uno();
};

#endif // JEFE_UNO_H
