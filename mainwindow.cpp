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
    delete net;
    delete ui;
}
template <typename Ch, typename Tr>
basic_ostream<Ch, Tr>& operator<< (basic_ostream<Ch, Tr>&stm, const neurons_line_print_descriptor &line) {
    Neuro::neurons_line::const_iterator it = begin(line._line), it_end = end(line._line);

    for (size_t i = 0; i < line._height; ++i) {
        for (size_t j = 0; j < line._width; ++j) {
            if (*it > 0)
                cout << " ";
            else
                cout << "0";
            ++it;
        }
        cout << endl;
    }

    return stm;
}

void MainWindow::on_start_clicked()
{
    if(!files.isEmpty()){
        Neuro::neurons_line line = imageToneuro_line(ui->filepath->text());
        QImage img(ui->filepath->text());
        int width = img.width();
        int height = img.height();
        Neuro::link_koefs koef=neuro.LearnNeuroNet(src_images);
        net= new neuro_net_system(koef);
        std::cout<<neurons_line_print_descriptor(line,width,height);
        Neuro::neurons_line* tmp= net->recognize(&line);
        std::cout<<neurons_line_print_descriptor(line,width,height);


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
    QStringList files__= QFileDialog::getOpenFileNames(this,tr("Открыть изображения"), "/home/ahotchenkov/neuro/",tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<files__;
    files=files__;
    for(QString filepath : files){
        src_images.push_back(imageToneuro_line(filepath));
    }
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
    QString file = QFileDialog::getOpenFileName(this,tr("Открыть изображение"), "/home/ahotchenkov/neuro/",tr("Image Files (*.png *.jpg *.bmp)"));
    ui->filepath->setText(file);

}
