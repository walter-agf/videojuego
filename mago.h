#ifndef MAGO_H
#define MAGO_H


#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "elemento.h"
#include <stdlib.h>
#include <time.h>

#include "muros.h"

class mago: public QObject, public QGraphicsItem
{
public:
    explicit mago(QObject *parent = nullptr);

    QTimer *timer;
    QPixmap *pixmap;

    float filas, columnas;
    int moment = 0;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    void actualizar_mago();

    float posx = 0; //Posicion en X
    float posy = 0;  //Posicion en Y
    float ancho = 32; //Ancho de la figura
    float alto = 55; // Alto de la figura


public slots:
    void actualizacion_sprites_mago();
};

#endif // MAGO_H
