#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("青年大学习自动录入工具v0.2");

    QImage img;
    img.load("./background.jpg");
    ui->label->setPixmap(QPixmap::fromImage(img));

    filemanager = new DXXTL::FileManagement();
    excleops = NULL;

    connect(ui->openfolderButton, &QPushButton::clicked, this, &MainWindow::openfolderSlot);
    connect(ui->openfileButton, &QPushButton::clicked, this, &MainWindow::openfileSlot);
    connect(ui->startOpenxlsxButton, &QPushButton::clicked, this, &MainWindow::startOpenxlsxSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete filemanager;
    delete excleops;
}

void MainWindow::openfolderSlot()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("选择一个文件夹"), QCoreApplication::applicationFilePath());

    if (folderName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件夹！");
    }
    else{
        ui->textBrowser->insertPlainText("待检索的文件夹为：\n" + folderName + "\n");
        filemanager->searchFiles(folderName.toStdString());
        filemanager->printFiles();
    }
}

void MainWindow::openfileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择一个文件"), QCoreApplication::applicationFilePath(), "*.xlsx *.cpp");

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件！");
    }
    else
    {
        ui->textBrowser->insertPlainText("选择的总文件为：\n" + fileName + "\n");
        filemanager->settFilepath(fileName.toStdString());
        std::cout << filemanager->gettFilepath();
        // DXXTL::FileManagement* f = new DXXTL::FileManagement();
        // f->searchFiles("./temp/21/2");
        // f->printFiles();
        // std::cout << f->getFiles()[19] << std::endl;
        // DXXTL::Excelops* item = new DXXTL::Excelops(f->getFiles()[19], 2, 3);    // 数据从第几行开始
        // item->fillWriteValues(0, 2);    // 需要检查的姓名分别在两个文件中所在的列数
        // item->loadData();       // 从第三行开始记录数据
        // item->~Excelops();

        // // QFile file(fileName);
        // // file.open(QIODevice::ReadOnly);
        // // QByteArray ba = file.readAll();
        // // ui->textEdit->setText(QString(ba));
        // // file.close();
    }
}

void MainWindow::startOpenxlsxSlot()
{
    if (filemanager->gettFilepath().empty() || filemanager->getFiles().empty())
    {
        QMessageBox::warning(this, "警告", "请先选择待检索的文件夹以及总文件！");
    }
    else
    {
        // excleops = new DXXTL::Excelops()
    }
}