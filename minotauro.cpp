#include "minotauro.h"

minotauro::minotauro(QObject *parent) : QObject(parent)
{
    Tauro = new elemento(posx,posy,velx,vely,mass,r,K,e,ancho,alto);

    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/personaje_1_1.png");

    timer->start(48);
    connect(timer,&QTimer::timeout,this,&minotauro::actualizacion_sprites_minotauro);
}

minotauro::~minotauro()
{
    delete Tauro;
}


QRectF minotauro::boundingRect() const
{
    return QRectF(-Tauro->getAncho()/2,-Tauro->getAlto()/2,Tauro->getAncho(),Tauro->getAlto());
}

void minotauro::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-Tauro->getAncho()/2,-Tauro->getAlto()/2,*pixmap,columnas,filas,Tauro->getAncho(),Tauro->getAlto());
}

void minotauro::actualizar_minotauro()
{
    Tauro->actualizar_elemento();
    setPos(Tauro->getPX(),720-Tauro->getPY());
}

elemento *minotauro::getTauro()
{
    return Tauro;
}

void minotauro::actualizacion_sprites_minotauro()
{
    if (moment == 0){

        filas = 0;
        columnas += 44;
        if(columnas >= 352){
            columnas =0;
        }

    }

    else if (moment == 1){

        filas = 40;
        columnas += 44;
        if(columnas >= 352){
            columnas =0;
        }

    }

    else if (moment == 2){

        filas = 80;
        columnas += 44;
        if(columnas >= 440){
            columnas =0;
        }

    }

    else if (moment == 3){

        filas = 120;
        columnas += 44;
        if(columnas >= 440){
            columnas =0;
        }

    }

    else if (moment == 4){

        filas = 160;
        columnas += 44;
        if(columnas >= 132){
            columnas =0;
        }

    }

    else if (moment == 5){

        filas = 200;
        columnas += 44;
        if(columnas >= 132){
            columnas =0;
        }

    }

    this->update(-Tauro->getAncho()/2,-Tauro->getAlto()/2,Tauro->getAncho(),Tauro->getAlto());


    if (moment == 2)moment = 0;
    else if (moment == 3)moment = 1;

    if (Tauro->getVY() <= 1 && Tauro->getVY() >= -1){
        if (moment == 4)moment = 0;
        else if (moment == 5)moment = 1;
    }
}
