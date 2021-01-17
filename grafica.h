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

    void actualizar_grafica();
    elemento *getEsf();

    float posx = 50; //Posicion en X
    float posy = 300;  //Posicion en Y
    float r = 20; //Radio de la imagen
    float mass = 50; //Masa del personaje
    float velx = 0; //Velocidad en X
    float vely = 0; //Velocidad en Y
    float K = 0.2; //Resistencias con el aire
    float e = 0.4; //Rebote
    float ancho = 44; //Ancho de la figura
    float alto = 40; // Alto de la figura


public slots:
    void actualizacion_sprites();

private:
    elemento *esf;
};

#endif // GRAFICA_H
