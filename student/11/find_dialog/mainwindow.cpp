#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <string>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect signals to slots
        connect(ui->closePushButton, &QPushButton::clicked, this, &MainWindow::close);
        connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::on_findPushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_findPushButton_clicked()
{
    if(!QFile::exists(ui->fileLineEdit->text())){
        ui->textBrowser->setText(FILE_NOT_FOUND);
    }
    else if (QFile::exists(ui->fileLineEdit->text())){
        QFile file(ui->fileLineEdit->text());
        file.open(QIODevice::ReadWrite);
        if (ui->matchCheckBox->isChecked()){
            if(ui->keyLineEdit->text().isEmpty()){
                ui->textBrowser->setText(FILE_FOUND);
            }else{
                QTextStream in(&file);
                QString searchString(ui->keyLineEdit->text());
                while (!in.atEnd()) {
                        QString line = in.readLine();
                        if (line.contains(searchString, Qt::CaseSensitive)){
                            ui->textBrowser->setText(WORD_FOUND);
                            return;
                        }
                }
                ui->textBrowser->setText(WORD_NOT_FOUND);
            }
        }else{
            if(ui->keyLineEdit->text().isEmpty()){
                ui->textBrowser->setText(FILE_FOUND);
            }else{
                QTextStream in(&file);
                QString searchString(ui->keyLineEdit->text());
                while (!in.atEnd()) {
                        QString line = in.readLine();
                        if (line.contains(searchString, Qt::CaseInsensitive)){
                            ui->textBrowser->setText(WORD_FOUND);
                            return;
                        }
                }
            ui->textBrowser->setText(WORD_NOT_FOUND);
            }
        }
    file.close();
    }
}

