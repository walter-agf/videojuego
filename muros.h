#ifndef MUROS_H
#define MUROS_H

#include <QGraphicsItem>
#include <QPainter>


class muros: public QGraphicsItem
{
public:

    int w,h;
    int posx, posy;

    muros(int posx_, int posy_, int w_, int h_);

    int getw();
    int geth();
    int getposx();
    int getposy();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MUROS_H
