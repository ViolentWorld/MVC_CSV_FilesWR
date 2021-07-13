#ifndef NEWMODEL_H
#define NEWMODEL_H

#include "addwindow.h"

#include <QAbstractTableModel>
#include <QList>

class NewModel : public QAbstractTableModel       
{
    Q_OBJECT

private:

    struct LineInfo{

       QString firstColumn;
       QString secondColumn;
       QString thirdColumn;
       bool state;
    };

    enum Column {
           firstColumn = 0,
           secondColumn,
           thirdColumn,
           checkBox,
           lastColumn
       };
    QList<LineInfo> lines;
    QStringList header = {"FirstColumn", "SecondColumn", "ThirdColumn"};
    AddWindow* addWindow;

public:

    NewModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent) const;

    int columnCount(const QModelIndex& parent) const;

    QVariant data(const QModelIndex& index, int role) const;

    bool setData(const QModelIndex& index, const QVariant& value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    Qt::ItemFlags flags (const QModelIndex& index) const;

    void removeAll();

    int getFirstColumn();
    int getSecondColumn();
    int getThirdColumn();
    int getCheckBoxColumn();

    int getLastLine();

    QString setHeader(QString row);
    void setDefaultHeader();
    void setAddWindow(AddWindow* addWindow);

public slots:

    void appendLine(const QString& firstColumn_, const QString& secondColumn_, const QString& thirdColumn_);

    void changeHeader(const QString& firstColumn_, const QString& secondColumn_, const QString& thirdColumn_);

    void removeSelected();
};

#endif // NEWMODEL_H
