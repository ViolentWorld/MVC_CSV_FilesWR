#include "addwindow.h"
#include "ui_addwindow.h"
#include "mainwindow.h"

AddWindow::AddWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWindow)
{
    ui->setupUi(this);

    setWindowTitle("New Line");
}

void AddWindow::on_Button_line_clicked()
{
   LineAdded(ui->FirstColumnText->text(), ui->SecondColumnText->text(), ui->ThirdColumnText->text());

   ClearText();

   close();
}


void AddWindow::on_Button_header_clicked()
{
    HeaderAdded(ui->FirstColumnText->text(), ui->SecondColumnText->text(), ui->ThirdColumnText->text());

    ClearText();

    close();
}

void AddWindow::ClearText()
{
    ui->FirstColumnText->clear();
    ui->SecondColumnText->clear();
    ui->ThirdColumnText->clear();
    ui->FirstColumnText->setFocus();
}

void AddWindow::setFirstColumn(QString text)
{
    ui->FirstColumn->setText(text);
}

void AddWindow::setSecondColumn(QString text)
{
    ui->SecondColumn->setText(text);
}

void AddWindow::setThirdColumn(QString text)
{
    ui->ThirdColumn->setText(text);
}

AddWindow::~AddWindow()
{
    delete ui;
}
