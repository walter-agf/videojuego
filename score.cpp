#include "score.h"
#include "ui_score.h"

score::score(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::score)
{
    ui->setupUi(this);
}

score::~score()
{
    delete ui;
}

void score::on_actionVolver_triggered()
{
    close();
}
