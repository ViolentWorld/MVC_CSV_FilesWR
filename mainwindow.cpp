#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addwindow.h"
#include "checkboxdelegate.h"
#include "filemanage.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), fileManage(&model)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("DataBase");

    model.setAddWindow(&addWindow);
    ui->Table->setModel(&model);
    ui->Table->setItemDelegateForColumn(model.getCheckBoxColumn(), &delegate);

    ui->Table->horizontalHeader()->setSectionResizeMode(
           model.getFirstColumn(), QHeaderView::Stretch);
    ui->Table->horizontalHeader()->setSectionResizeMode(
           model.getSecondColumn(), QHeaderView::Stretch);
    ui->Table->horizontalHeader()->setSectionResizeMode(
           model.getThirdColumn(), QHeaderView::Stretch);
    ui->Table->setColumnWidth(model.getCheckBoxColumn(), 10);

    connect(ui->Table, &QTableView::clicked,
            this, &MainWindow::OnItemClicked);

    connect(&addWindow, &AddWindow::LineAdded,
            &model, &NewModel::appendLine);

    connect(&addWindow, &AddWindow::HeaderAdded,
            &model, &NewModel::changeHeader);
}

void MainWindow::OnItemClicked(const QModelIndex& index)
{
    if(index.column() == model.getCheckBoxColumn())
        model.setData(index, !index.data().toBool(), Qt::EditRole);
}

void MainWindow::on_Button_Add_clicked()
{
    addWindow.ClearText();
    addWindow.show();
}

void MainWindow::on_Button_Remove_clicked()
{
    model.removeSelected();
}


void MainWindow::on_Open_triggered()
{
    QString result = fileManage.OpenFile(this);
    if(!result.isEmpty())
        QMessageBox::warning(nullptr, "Warning!",result);
}

void MainWindow::on_Save_triggered()
{
    QString result = fileManage.SaveFile();
    if(!result.isEmpty())
        QMessageBox::warning(nullptr, "Warning!",result);
}

void MainWindow::on_SaveAs_triggered()
{
    QString result = fileManage.SaveFileAs(this);
    if(!result.isEmpty())
        QMessageBox::warning(nullptr, "Warning!",result);
}

MainWindow::~MainWindow()
{
    delete ui;
}
