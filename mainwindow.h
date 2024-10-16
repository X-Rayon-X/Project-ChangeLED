#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_frequencyDoubleSpinBox_valueChanged(double arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_brightnessSpinBox_valueChanged(int arg1);

    void sendCommandToUART(const QString &command);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
