#include "muros.h"

muros::muros(int posx_, int posy_, int w_, int h_)
{
    posx = posx_;
    posy = posy_;
    w = w_;
    h = h_;
}

int muros::getw()
{
    return w;
}

int muros::geth()
{
    return h;
}

int muros::getposx()
{
    return posx;
}

int muros::getposy()
{
    return posy;
}

QRectF muros::boundingRect() const
{
    return QRectF(posx,posy,w,h);
}

void muros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setBrush(Qt::red);
//    painter->drawRect(boundingRect());
}
