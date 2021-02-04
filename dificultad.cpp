#include "dificultad.h"
#include "ui_dificultad.h"

dificultad::dificultad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dificultad)
{
    ui->setupUi(this);
}

dificultad::~dificultad()
{
    delete ui;
}

void dificultad::on_pushButton_2_clicked()
{
    close();
}

void dificultad::on_pushButton_clicked()
{
    if (v == 1){
        one = new oneplayer(this);
        if (ui->facil->isChecked()){
            one->dificultad = 0.5;
        }
        else if (ui->medio->isChecked()){
            one->dificultad = 1;
        }
        else if (ui->dificil->isChecked()){
            one->dificultad = 1.4;
        }
        one->show();
    }
    else if (v == 2){
        two = new multiplayer(this);
        if (ui->facil->isChecked()){
            two->dificultad = 0.5;
        }
        else if (ui->medio->isChecked()){
            two->dificultad = 1;
        }
        else if (ui->dificil->isChecked()){
            two->dificultad = 1.4;
        }
        two->show();
    }
    close();
}
