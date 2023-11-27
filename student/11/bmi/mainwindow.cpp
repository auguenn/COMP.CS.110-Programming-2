#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countButton_clicked()
{
    int weight = std::stoi(ui->weightLineEdit->text().toStdString());
    int height = std::stoi(ui->heightLineEdit->text().toStdString());
    if (height == 0) {
        ui->resultLabel->setText(QString("Cannot count."));
        return;
    }
    double result = weight/((height/100.0)*(height/100.0));

    ui->resultLabel->setNum(result);

    if (result < 18.5)
    {
        ui->infoTextBrowser->setText(QString("Underweight"));
    }
    else if (result > 25.0)
    {
        ui->infoTextBrowser->setText(QString("Overweight"));
    }
    else
    {
        ui->infoTextBrowser->setText(QString("Normal range"));
    }
}
