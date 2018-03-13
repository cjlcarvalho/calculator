#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

    ui->resultado->setText("0");

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

    connect(ui->opSoma, &QPushButton::clicked, this, &MainWindow::executarSoma);
    connect(ui->opSub, &QPushButton::clicked, this, &MainWindow::executarSubtracao);
    connect(ui->opDiv, &QPushButton::clicked, this, &MainWindow::executarDivisao);
    connect(ui->opMult, &QPushButton::clicked, this, &MainWindow::executarMultiplicacao);
}

void MainWindow::adicionarValor()
{
    QPushButton *button = dynamic_cast<QPushButton *>(sender());

    if (button)
        ui->valorAtual->setText(ui->valorAtual->toPlainText() + button->text());
}

void MainWindow::executarSoma()
{
    if(!checarValorAtual())
        return;

    int numValorAtual = ui->valorAtual->toPlainText().toInt();
    int numResultado = ui->resultado->toPlainText().toInt();

    ui->valorAtual->setText(QStringLiteral());

    ui->resultado->setText(QString::number(numValorAtual + numResultado));

    // guardar no command
}

void MainWindow::executarSubtracao()
{
    if(!checarValorAtual())
        return;

    int numValorAtual = ui->valorAtual->toPlainText().toInt();
    int numResultado = ui->resultado->toPlainText().toInt();

    ui->valorAtual->setText(QStringLiteral());

    ui->resultado->setText(QString::number(numResultado - numValorAtual));

    // guardar no command
}

void MainWindow::executarDivisao()
{
    if(!checarValorAtual())
        return;

    int numValorAtual = ui->valorAtual->toPlainText().toInt();

    if (!numValorAtual) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Divisão por zero!");
        messageBox.setText("Não é possível dividir por zero!!!");
        messageBox.exec();
        return;
    }

    int numResultado = ui->resultado->toPlainText().toInt();

    ui->valorAtual->setText(QStringLiteral());

    ui->resultado->setText(QString::number(numResultado / numValorAtual));

    // guardar no command
}

void MainWindow::executarMultiplicacao()
{
    if(!checarValorAtual())
        return;

    int numValorAtual = ui->valorAtual->toPlainText().toInt();
    int numResultado = ui->resultado->toPlainText().toInt();

    ui->valorAtual->setText(QStringLiteral());

    ui->resultado->setText(QString::number(numResultado * numValorAtual));

    // guardar no command
}

bool MainWindow::checarValorAtual()
{
    if (ui->valorAtual->toPlainText() == "") {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Erro!");
        messageBox.setText("Por favor, preencha o seu valor atual antes de realizar uma operação.");
        messageBox.exec();
        return false;
    }
    return true;
}
