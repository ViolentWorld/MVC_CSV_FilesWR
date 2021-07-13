#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"newmodel.h"
#include "addwindow.h"
#include "filemanage.h"

#include <QMainWindow>
#include "checkboxdelegate.h"

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

    void on_Button_Add_clicked();

    void on_Button_Remove_clicked();

    void OnItemClicked(const QModelIndex&);

    void on_Open_triggered();

    void on_Save_triggered();

    void on_SaveAs_triggered();

private:

    NewModel model;

    AddWindow addWindow;

    FileManage fileManage;

    CheckBoxDelegate delegate;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
