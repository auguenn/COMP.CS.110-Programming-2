#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_findPushButton_clicked();

    void on_fileLineEdit_textChanged(const QString &arg1);

    void on_keyLineEdit_textChanged(const QString &arg1);

    void on_matchCheckBox_stateChanged(int arg1);


private:
    Ui::MainWindow *ui;

    std::string fileName = "";
    std::string wordToFind = "";
    int matchCase = 0;
};
#endif // MAINWINDOW_HH
