#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "result.h"
#include "sessionloader.h"
#include "commands/command.h"
#include "commands/commandstack.h"
#include "commands/sumcommand.h"
#include "commands/divisioncommand.h"
#include "commands/multiplicationcommand.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_result(new Result(0.0)),
    m_commandStack(new CommandStack),
    m_sessionLoader(new SessionLoader("session.json"))
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    setWindowTitle("Calculadora");

    ui->resultado->setText(m_result->toString());
    ui->valorAtual->setText("");

    connect(ui->botao1, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao2, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao3, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao4, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao5, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao6, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao7, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao8, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao9, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botao0, &QPushButton::clicked, this, &MainWindow::adicionarValor);
    connect(ui->botaoDot, &QPushButton::clicked, this, &MainWindow::adicionarValor);

    connect(ui->opSoma, &QPushButton::clicked, this, &MainWindow::executarSoma);
    connect(ui->opSub, &QPushButton::clicked, this, &MainWindow::executarSubtracao);
    connect(ui->opDiv, &QPushButton::clicked, this, &MainWindow::executarDivisao);
    connect(ui->opMult, &QPushButton::clicked, this, &MainWindow::executarMultiplicacao);

    connect(ui->botaoUndo, &QPushButton::clicked, this, &MainWindow::undoOperation);
    connect(ui->botaoRedo, &QPushButton::clicked, this, &MainWindow::redoOperation);

    connect(ui->botaoSession, &QPushButton::clicked, this, &MainWindow::loadSession);

    ui->botaoSession->setEnabled(m_sessionLoader->isSessionAvailable());
}

void MainWindow::adicionarValor()
{
    QPushButton *button = dynamic_cast<QPushButton *>(sender());

    if (button) {
        QString buttonName = button->objectName().mid(5, button->objectName().size() - 5);
        if (buttonName == "Dot")
            ui->valorAtual->setText(ui->valorAtual->toPlainText() + ".");
        else
            ui->valorAtual->setText(ui->valorAtual->toPlainText() + buttonName);
    }
}

void MainWindow::executarSoma()
{
    if(!checarValorAtual())
        return;

    double numValorAtual = ui->valorAtual->toPlainText().toDouble();

    m_result->add(numValorAtual);

    ui->valorAtual->setText(QString());

    ui->resultado->setText(m_result->toString());

    m_commandStack->addCommand(new SumCommand(m_result, numValorAtual));
}

void MainWindow::executarSubtracao()
{
    if(!checarValorAtual())
        return;

    double numValorAtual = ui->valorAtual->toPlainText().toDouble();

    m_result->add(-numValorAtual);

    ui->valorAtual->setText(QString());

    ui->resultado->setText(m_result->toString());

    m_commandStack->addCommand(new SumCommand(m_result, -numValorAtual));
}

void MainWindow::executarDivisao()
{
    if(!checarValorAtual())
        return;

    double numValorAtual = ui->valorAtual->toPlainText().toDouble();

    if (!numValorAtual) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Divisão por zero!");
        messageBox.setText("Não é possível dividir por zero!!!");
        messageBox.exec();
        return;
    }

    m_result->divide(numValorAtual);

    ui->valorAtual->setText(QString());

    ui->resultado->setText(m_result->toString());

    m_commandStack->addCommand(new DivisionCommand(m_result, numValorAtual));
}

void MainWindow::executarMultiplicacao()
{
    if(!checarValorAtual())
        return;

    double numValorAtual = ui->valorAtual->toPlainText().toDouble();

    m_result->multiply(numValorAtual);

    ui->valorAtual->setText(QString());

    ui->resultado->setText(m_result->toString());

    m_commandStack->addCommand(new MultiplicationCommand(m_result, numValorAtual));
}

bool MainWindow::checarValorAtual()
{
    if (ui->valorAtual->toPlainText() == QString()) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Erro!");
        messageBox.setText("Por favor, preencha o seu valor atual antes de realizar uma operação.");
        messageBox.exec();
        return false;
    }

    return true;
}

void MainWindow::undoOperation()
{
    if (!m_commandStack->undoCommand()) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Fim da pilha!");
        messageBox.setText("Você chegou no fim da sua pilha de comandos!");
        messageBox.exec();
    }

    ui->resultado->setText(m_result->toString());
}

void MainWindow::redoOperation()
{
    if (!m_commandStack->redoCommand()) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Não há mais comandos!");
        messageBox.setText("Não existem mais comandos para serem refeitos!");
        messageBox.exec();
    }

    ui->resultado->setText(m_result->toString());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_sessionLoader->saveSession(m_commandStack);

    QWidget::closeEvent(event);
}

void MainWindow::loadSession()
{
    m_sessionLoader->loadSession(m_result, m_commandStack);

    // m_commandStack top is set to 0
    // so, do redoCommand until the end of m_commandStack
    while (m_commandStack->redoCommand()) { }

    ui->resultado->setText(m_result->toString());

    ui->botaoSession->setEnabled(false);
}
