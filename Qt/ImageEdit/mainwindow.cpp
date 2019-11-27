#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;
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

void MainWindow::on_SliderValueChanged()
{
    double exposure = ui->SliderExposure->value() / 10.0;
    double contras = ui->SliderContras->value()/4.0;
    int lighting = ui->SliderLighting->value();
	cv::Mat g_dstImage = cv::Mat::zeros(srcImage.size(), srcImage.type());
	for (int y = 0; y < srcImage.rows; y++) {
		for (int x = 0; x < srcImage.cols; x++) {
			for (int z = 0; z < srcImage.channels(); z++) {
				auto val1 = cv::saturate_cast<uchar>((contras * srcImage.at<cv::Vec3b>(y, x)[z]) + lighting);
				g_dstImage.at<cv::Vec3b>(y, x)[z] = cv::saturate_cast<uchar>(val1 * pow(2.0, exposure));
			}
		}
	}

    QImage disImage = QImage((const unsigned char*)(g_dstImage.data), g_dstImage.cols, g_dstImage.rows, QImage::Format_RGB888);

    QGraphicsScene* scene = new QGraphicsScene();
    auto pix = QPixmap::fromImage(disImage);
    scene->addPixmap(pix);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(pix.rect(), Qt::KeepAspectRatio);
    ui->graphicsView->show();
}


void MainWindow::on_BtnOpenFile_clicked()
{
    auto	fileName = QFileDialog::getOpenFileName(this,
           tr("Open Image"), "D:\\wmq\\Pictures\\person\\2019.11.15", tr("Image Files (*.png *.jpg *.bmp)"));
    srcImage = imread(fileName.toLatin1().data());
    cvtColor(srcImage, srcImage, COLOR_BGR2RGB);
    QImage disImage = QImage((const unsigned char*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);

    QGraphicsScene* scene = new QGraphicsScene();
    auto pix = QPixmap::fromImage(disImage);
    scene->addPixmap(pix);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(pix.rect(), Qt::KeepAspectRatio);
    ui->graphicsView->show();
}

void MainWindow::on_SliderExposure_sliderReleased()
{
    on_SliderValueChanged();
}

void MainWindow::on_SliderLighting_sliderReleased()
{
    on_SliderValueChanged();
}

void MainWindow::on_SliderContras_sliderReleased()
{
    on_SliderValueChanged();
}
