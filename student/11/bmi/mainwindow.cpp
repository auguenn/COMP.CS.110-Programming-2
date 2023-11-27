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
    QString weight = ui->weightLineEdit->text();
      QString height = ui->heightLineEdit->text();

      double w = weight.toDouble();
      double h = height.toDouble();
    if ( h > 0)
      {
      double bmi = w/(h*h*0.0001);

      ui->resultLabel->setText(QString::number(bmi));

      if (bmi >= 25){
          ui->infoTextBrowser->setText("Overweight");
        }

      else if (bmi <= 18.5){
          ui->infoTextBrowser->setText("Underweight");
        }
      else{
          ui->infoTextBrowser->setText("Normal range");
        }
      }
    else{
        ui->resultLabel->setText("Cannot count");
        ui->infoTextBrowser->setText("");
      }
}
