#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Обмеження для frequencyDoubleSpinBox
    ui->frequencyDoubleSpinBox->setRange(0.5, 10.0);

    // Обмеження для brightnessSpinBox
    ui->brightnessSpinBox->setRange(0, 100);

    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::on_comboBox_currentIndexChanged);
    connect(ui->frequencyDoubleSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::on_frequencyDoubleSpinBox_valueChanged);
    connect(ui->brightnessSpinBox, &QSpinBox::valueChanged, this, &MainWindow::on_brightnessSpinBox_valueChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString command;

    if (index == 0) { // "Off"
        command = "SET_MODE:OFF";
        //QMessageBox::information(this, "LED Control", "LED4 is turned OFF.");
    } else if (index == 1) { // "On"
        command = "SET_MODE:ON";
        //QMessageBox::information(this, "LED Control", "LED4 is turned ON.");
    } else if (index == 2) { // "Blink"
        command = "SET_MODE:BLINK";
        //QMessageBox::information(this, "LED Control", "LED4 is blinking.");
    }

    if (!command.isEmpty()) {
        sendCommandToUART(command);
    }
}


void MainWindow::on_brightnessSpinBox_valueChanged(int arg1)
{
    QString command = QString("SET_BRIGHTNESS:%1").arg(arg1);
    sendCommandToUART(command);

    //QMessageBox::information(this, "Brightness Changed", QString("Brightness set to %1%").arg(arg1));
}


void MainWindow::on_frequencyDoubleSpinBox_valueChanged(double arg1)
{
    QString command = QString("SET_FREQUENCY:%1").arg(arg1);
    sendCommandToUART(command);

    //::information(this, "Frequency Changed", QString("Blinking frequency set to %1 Hz").arg(arg1));
}

void MainWindow::sendCommandToUART(const QString &command) {
    QSerialPort serial; // Створення об'єкта для роботи з серійним портом

    serial.setPortName("COM3"); // Порт
    serial.setBaudRate(QSerialPort::Baud115200); // Швидкість передачі
    serial.setDataBits(QSerialPort::Data8); // Кількість біт на дані
    serial.setParity(QSerialPort::NoParity); // Паритет
    serial.setStopBits(QSerialPort::OneStop); // Кількість стоп-біт
    serial.setFlowControl(QSerialPort::NoFlowControl); // Контроль потоку

    if (serial.open(QIODevice::ReadWrite)) { // Відкрити порт для читання та запису
        serial.write(command.toUtf8()); // Відправити команду
        serial.waitForBytesWritten(100);
        serial.close();
    } else {
        // Обробка помилки при відкритті порту
        QMessageBox::warning(this, "UART Error", "Failed to open the UART port.");
    }
}
