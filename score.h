#ifndef SCORE_H
#define SCORE_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

namespace Ui {
class score;
}

class score : public QMainWindow
{
    Q_OBJECT

public:
    explicit score(QWidget *parent = nullptr);
    ~score();

private slots:
    void on_actionVolver_triggered();

private:
    Ui::score *ui;
};

#endif // SCORE_H
