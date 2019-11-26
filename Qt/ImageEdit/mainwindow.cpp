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


void MainWindow::on_pushButton_clicked()
{
 auto	fileName = QFileDialog::getOpenFileName(this,
		tr("Open Image"), "D:\\wmq\\Pictures\\person\\2019.11.15", tr("Image Files (*.png *.jpg *.bmp)"));
 Mat srcImage = imread(fileName.toLatin1().data());
 cvtColor(srcImage, srcImage, COLOR_BGR2RGB);
 QImage disImage = QImage((const unsigned char*)(srcImage.data), srcImage.cols, srcImage.rows, QImage::Format_RGB888);

 QGraphicsScene* scene = new QGraphicsScene();
 auto pix = QPixmap::fromImage(disImage);
 scene->addPixmap(pix);
 ui->graphicsView->setScene(scene);
 ui->graphicsView->fitInView(pix.rect(), Qt::KeepAspectRatio);

 ui->graphicsView->show();
}

void MainWindow::on_graphicsView_destroyed()
{

}

void MainWindow::on_MainWindow_tabifiedDockWidgetActivated(QDockWidget *dockWidget)
{

}
