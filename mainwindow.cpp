#include "mainwindow.hpp"

#include "ui_mainwindow.h"

#include <QThread>
#include <iostream>
#include <lo/lo.h>

#define MUTY_HAS_SMOOTH_SWTICHING 0

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    address = ui->hostTxt->text().toStdString();
    port = ui->portTxt->text().toStdString();
    path = ui->pathCB->currentText().toStdString();
    minVal = (float) ui->minSB->value() / 100;
    maxVal = (float) ui->maxSB->value() / 100;
    ui->settingsWidget->setVisible(false);
    adjustSize();
    on_invertBtn_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendData(float value)
{
    const auto addr = lo_address_new(address.c_str(), port.c_str());
    const auto SendMessageImpl = [&](float val)
    {
        const auto msg = lo_message_new();
        lo_message_add_float(msg, val);
        lo_send_message(addr, path.c_str(), msg);
        lo_message_free(msg);
        ui->statusLabel->setText(QString("C=%0 MIN=%1 MAX=%2").arg(currentValue).arg(minVal).arg(maxVal));
    };
#if MUTY_HAS_SMOOTH_SWTICHING
    auto val = currentValue;
    while (std::abs(val - value) >= 0.06)
    {
        SendMessageImpl(val);
        QThread::msleep(10);
        val += ((val >= value ? -1 : +1) * 0.05);
    }
#endif
    currentValue = value;
    SendMessageImpl(value);
    lo_address_free(addr);
}

void MainWindow::on_muteButton_pressed()
{
    SendData(minVal);
}

void MainWindow::on_muteButton_released()
{
    SendData(maxVal);
    ui->stickyMuteButton->setChecked(false);
}

void MainWindow::on_minSlider_valueChanged(int value)
{
    ui->minSB->setValue(value);
    minVal = (float) value / 100;
}

void MainWindow::on_maxSlider_valueChanged(int value)
{
    ui->maxSB->setValue(value);
    maxVal = (float) value / 100;
}

void MainWindow::on_minSB_valueChanged(int arg1)
{
    ui->minSlider->setValue(arg1);
    minVal = (float) arg1 / 100;
}

void MainWindow::on_maxSB_valueChanged(int arg1)
{
    ui->maxSlider->setValue(arg1);
    maxVal = (float) arg1 / 100;
}

void MainWindow::on_hostTxt_textEdited(const QString &arg1)
{
    address = arg1.toStdString();
}

void MainWindow::on_portTxt_textEdited(const QString &arg1)
{
    port = arg1.toStdString();
}

void MainWindow::on_pathCB_currentTextChanged(const QString &arg1)
{
    path = arg1.toStdString();
}

void MainWindow::on_settingsBtn_clicked()
{
    const auto currentSize = this->size();
    ui->settingsWidget->setVisible(!ui->settingsWidget->isVisible());
    this->adjustSize();
    this->resize(originalSize);
    this->adjustSize();
    originalSize = currentSize;
}

void MainWindow::on_invertBtn_clicked()
{
    {
        const float _min = minVal * 100;
        const float _max = maxVal * 100;
        // Switch MIN and MAX
        ui->minSB->setValue(_max);
        ui->minSlider->setValue(_max);
        ui->maxSB->setValue(_min);
        ui->maxSlider->setValue(_min);
    }
    // minVal and maxVal have been updated (Exchanged)
    // If current is min, set to max (which is now exchanged into "minVal")
    SendData((currentValue == maxVal) ? minVal : maxVal);
    ui->stickyMuteButton->setChecked(currentValue == minVal);
}

void MainWindow::on_stickyMuteButton_clicked(bool checked)
{
    SendData(checked ? minVal : maxVal);
}
