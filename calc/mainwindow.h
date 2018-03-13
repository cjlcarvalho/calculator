#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Result;
class CommandStack;
class SessionLoader;

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
    void loadSession();

private:
    void init();
    bool checarValorAtual();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Result *m_result;
    CommandStack *m_commandStack;
    SessionLoader *m_sessionLoader;

};

#endif // MAINWINDOW_H
