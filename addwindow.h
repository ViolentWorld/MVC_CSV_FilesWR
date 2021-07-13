#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class AddWindow;
}

class AddWindow : public QWidget
{
    Q_OBJECT

public:

    AddWindow(QWidget *parent = nullptr);

    void ClearText();

    void setFirstColumn(QString text);
    void setSecondColumn(QString text);
    void setThirdColumn(QString text);

    ~AddWindow();

signals:

    void LineAdded(const QString& firstColumn, const QString& secondColumn, const QString& thirdColumn);
    void HeaderAdded(const QString& firstColumn, const QString& secondColumn, const QString& thirdColumn);

private slots:

    void on_Button_line_clicked();

    void on_Button_header_clicked();

private:

    Ui::AddWindow *ui;
};

#endif // ADDWINDOW_H
