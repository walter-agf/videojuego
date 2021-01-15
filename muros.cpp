#include "muros.h"

muros::muros(int w_, int h_)
{
    w = w_;
    h = h_;
}

QRectF muros::boundingRect() const
{
    return QRectF(w, h,40,40);
}

void muros::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(boundingRect());
}
