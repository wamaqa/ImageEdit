#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/mat.hpp>

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

    void on_BtnOpenFile_clicked();

    void on_SliderExposure_sliderReleased();

    void on_SliderLighting_sliderReleased();

    void on_SliderContras_sliderReleased();

private:
    Ui::MainWindow *ui;
    cv::Mat srcImage;
    void on_SliderValueChanged();
};
#endif // MAINWINDOW_H
