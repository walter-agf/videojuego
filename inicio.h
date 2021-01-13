#ifndef INICIO_H
#define INICIO_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class inicio : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit inicio(QObject *parent = nullptr);

    QTimer *timer_inicio;
    QPixmap *pixmap_inicio;

    float filas, columnas;
    float ancho, alto;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:
    void Actualizacion_Inicio();

};

#endif // INICIO_H
