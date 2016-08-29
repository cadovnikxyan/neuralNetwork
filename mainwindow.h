#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include "neuro.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_start_clicked();
        void on_fileDialog_clicked();

    private:
        list<Neuro::neurons_line> src_images;
        Neuro::neurons_line imageToneuro_line(const QString& filepath);
        Ui::MainWindow *ui;
        QStringList files;
};

#endif // MAINWINDOW_H
