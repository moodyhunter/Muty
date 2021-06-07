#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
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
    void on_hostTxt_textEdited(const QString &arg1);
    void on_invertBtn_clicked();
    void on_maxSB_valueChanged(int arg1);
    void on_maxSlider_valueChanged(int value);
    void on_minSB_valueChanged(int arg1);
    void on_minSlider_valueChanged(int value);
    void on_muteButton_pressed();
    void on_muteButton_released();
    void on_pathCB_currentTextChanged(const QString &arg1);
    void on_portTxt_textEdited(const QString &arg1);
    void on_settingsBtn_clicked();
    void on_stickyMuteButton_clicked(bool checked);

  private:
    Ui::MainWindow *ui;

  private:
    void SendData(float value);
    float minVal;
    float maxVal;
    std::string address;
    std::string port;
    std::string path;
    QSize originalSize;
    float currentValue = 0;
};
