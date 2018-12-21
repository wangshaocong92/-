#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&Widget::onPushButtonClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onPushButtonClicked()
{
    std::string fileName=QFileDialog::getOpenFileName().toStdString();
    mat=cv::imread(fileName,cv::IMREAD_COLOR);
    qDebug()<<mat.size;

    cv::imshow("aaa",mat);
}
