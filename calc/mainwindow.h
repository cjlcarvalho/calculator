#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void adicionarValor();
    void executarSoma();
    void executarSubtracao();
    void executarDivisao();
    void executarMultiplicacao();

private:
    void init();
    bool checarValorAtual();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
