#include "muros.h"

muros::muros(int w_, int h_, int x, int y)
{
    w = w_;
    h = h_;
    posx = x;
    posy = y;
}

QRectF muros::boundingRect() const
{
    return QRectF(w, h,posx,posy);
}

void muros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::darkBlue);
    painter->drawRect(boundingRect());
}
