#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <fstream>

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

std::string string_toupper(std::string input) {
    std::string output = "";
    for (std::string::size_type i = 0; i < input.length(); ++i) {
        // append the to lower converted letter to output string
        output += toupper(input.at(i));
    }
    // return lowercase string
    return output;
}


void MainWindow::on_findPushButton_clicked()
{


    // check if file exists
      std::ifstream fileToSearch(fileName);
      QString result = "";

      if (not fileToSearch) {
          result = "File not found";
      } else {
          result = "File found";

          // check if word is not empty
          if (wordToFind != "") {
              result = "Word not found";

              // search file for word
              if (matchCase == 2) {
                  wordToFind = string_toupper(wordToFind);
              }

              // set to lowercase if matchCase
              std::string row;
              while (std::getline(fileToSearch, row)) {
                  if (matchCase == 2) {
                      row = string_toupper(row);
                  }

                  if (row.find(wordToFind) != std::string::npos) {
                      result = "Word found";
                      break;
                  }
              }
          }
      }
      // set textBrowser status
      ui->textBrowser->clear();
      ui->textBrowser->setText(result);
}

void MainWindow::on_fileLineEdit_textChanged(const QString &arg1)
{
    // update filename
    fileName = arg1.toStdString();
}


void MainWindow::on_keyLineEdit_textChanged(const QString &arg1)
{
    // update word to find
    wordToFind = arg1.toStdString();
}


void MainWindow::on_matchCheckBox_stateChanged(int arg1)
{
    // update checkbox status
    matchCase = arg1;
}
