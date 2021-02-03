#include "dis_jefe_1.h"

dis_jefe_1::dis_jefe_1(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/disparo_jefe_recto.png");

    timer->start(80);
    connect(timer,&QTimer::timeout,this,&dis_jefe_1::actualizar_dis_jefe);
}
QRectF dis_jefe_1::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void dis_jefe_1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,filas,ancho,alto);
}

void dis_jefe_1::dis_jefe()
{
    setPos(posx,posy);
    actualizar_dis_jefe();
}

void dis_jefe_1::actualizar_dis_jefe()
{
    columnas += 47;
    if(columnas >= 188){
        columnas =0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}
