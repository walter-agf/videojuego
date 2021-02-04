#ifndef DIFICULTAD_H
#define DIFICULTAD_H

#include <QWidget>
#include "oneplayer.h"
#include "multiplayer.h"

namespace Ui {
class dificultad;
}

class dificultad : public QWidget
{
    Q_OBJECT

public:
    explicit dificultad(QWidget *parent = nullptr);
    ~dificultad();

    int v = 0;
    float cam_dif;

    oneplayer *one;
    multiplayer *two;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::dificultad *ui;
};

#endif // DIFICULTAD_H
