#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "calc_algorithm.h"

#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculateButton_clicked()
{
    QString qs = ui->textInput->toPlainText();
    std::string input = qs.toStdString();

    if (!input.empty() && input.length() < 20) {
        double answ = cstm::calcExpr(input);
        std::string _output = std::to_string(answ);
        QString output = QString::fromUtf8(_output.c_str());
        ui->outputLabel->setText(output);
    }else if (input.length() > 19){
        ui->outputLabel->setText("number too large and we \nare too stupid too figure out\nhow to fix it(");
    }
}
