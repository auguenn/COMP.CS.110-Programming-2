#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calculatePushButton, &QPushButton::clicked, this, &MainWindow::result);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::result()
{
    n = ui->spinBoxN->value();
    g = ui->spinBoxG->value();
    p = ui->spinBoxP->value();
    e = ui->spinBoxE->value();

    int score = calculate_total_grade(n, g, p, e);
    int w = score_from_weekly_exercises(n,g);
    int ps = score_from_projects(p);

    ui->textBrowser->setText(QString::fromStdString("W-Score: " + std::to_string(w) + "\nP-Score: " +std::to_string(ps) + "\nTotal grade: " + std::to_string(score)));
}
