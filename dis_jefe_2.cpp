#include "dis_jefe_2.h"

dis_jefe_2::dis_jefe_2(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/disparo_jefe_caida.png");

    timer->start(20);
    connect(timer,&QTimer::timeout,this,&dis_jefe_2::actualizar_dis_jefe);
}
QRectF dis_jefe_2::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void dis_jefe_2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,filas,ancho,alto);
}

void dis_jefe_2::dis_jefe()
{
    setPos(posx,posy);
    actualizar_dis_jefe();
}

void dis_jefe_2::actualizar_dis_jefe()
{
    columnas += 21;
    if(columnas >= 1281){
        columnas =0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}
