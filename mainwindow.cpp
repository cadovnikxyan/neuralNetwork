#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    if(!files.isEmpty()){
        for(QString filepath : files){
            src_images.push_back(imageToneuro_line(filepath));
            Neuro net;
            net.LearnNeuroNet(src_images);
        }

    }else{
        QMessageBox* box = new QMessageBox(this);
        box->setWindowTitle(tr("Ошибка"));
        box->setInformativeText(tr("Файлы не выбраны!"));
        if(box->exec()==QMessageBox::Ok){
        }
        delete box;
    }
}

void MainWindow::on_fileDialog_clicked()
{
    QStringList file= QFileDialog::getOpenFileNames(this,tr("Открыть изображения"), "/home/",tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<file;
    ui->filepath->setText(file[0]+" ...");
    files=file;
}

Neuro::neurons_line MainWindow::imageToneuro_line(const QString& filepath)
{
    QImage img(filepath);
    int width = img.width();
    int height = img.height();
    vector<uint> pixels;

    for(int j = 0; j < height; j++)
    {
      for(int i = 0; i < width; i++)
      {
          if(qGray(img.pixel(i,j))>1){
              pixels.push_back(1);
          }else{
              pixels.push_back(0);
          }
      }
    }
    Neuro::neurons_line result;
    result.reserve(pixels.size());
    for(uint pix__ : pixels){
        Neuro::neuron_state state = pix__ ? Neuro::UPPER_STATE : Neuro::LOWER_STATE;
        result.push_back(state);
    }
   return result;
}

void MainWindow::on_recognize_clicked()
{

}
