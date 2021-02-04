#include "score.h"
#include "ui_score.h"

score::score(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::score)
{
    ui->setupUi(this);
    QFile pun;
    //_______________
    QTextStream io;
    QString valor;
    //_______________
    pun.setFileName(":/documentos/score.txt");
    pun.open(QIODevice::Text | QIODevice::ReadOnly);
    io.setDevice(&pun);
    valor = io.readAll();
    pun.close();

    ui->texto->setText(valor);
}

score::~score()
{
    delete ui;
}

void score::on_actionVolver_triggered()
{
    close();
}
