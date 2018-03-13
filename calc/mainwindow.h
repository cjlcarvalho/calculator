#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Result;
class CommandStack;

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
    void undoOperation();
    void redoOperation();

private:
    void init();
    bool checarValorAtual();

private:
    Ui::MainWindow *ui;
    Result *m_result;
    CommandStack *m_commandStack;

};

#endif // MAINWINDOW_H
