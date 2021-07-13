#include "newmodel.h"
#include "mainwindow.h"

NewModel::NewModel(QObject* parent) : QAbstractTableModel(parent)
{
}

int NewModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return lines.count();
}

int NewModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return lastColumn;
}

QVariant NewModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
        return section;

    addWindow->setFirstColumn(header[firstColumn]);
    addWindow->setSecondColumn(header[secondColumn]);
    addWindow->setThirdColumn(header[thirdColumn]);

    switch(section) {
    case firstColumn: return header[firstColumn];
    case secondColumn: return header[secondColumn];
    case thirdColumn: return header[thirdColumn];
    case checkBox: return "Tick";
    }

    return QVariant();
}

QVariant NewModel::data(const QModelIndex& index, int role) const {
    if(!index.isValid() || lines.count() <= index.row() ||
       (role != Qt::DisplayRole && role != Qt::EditRole))
            return QVariant();

    switch(index.column()) {
        case firstColumn: return lines[index.row()].firstColumn;
        case secondColumn: return lines[index.row()].secondColumn;
        case thirdColumn: return lines[index.row()].thirdColumn;
        case checkBox: return lines[index.row()].state;
    }

    return QVariant();
}

void NewModel::appendLine(const QString& firstColumn_, const QString& secondColumn_, const QString& thirdColumn_) {

    LineInfo person;
    person.firstColumn = firstColumn_;
    person.secondColumn = secondColumn_;
    person.thirdColumn = thirdColumn_;
    person.state = false;

    int row = lines.count();
    beginInsertRows(QModelIndex(), row, row);
    lines.append(person);
    endInsertRows();
}

void NewModel::changeHeader(const QString &firstColumn_, const QString &secondColumn_, const QString &thirdColumn_)
{
    header[firstColumn] = firstColumn_;
    header[secondColumn] = secondColumn_;
    header[thirdColumn] = thirdColumn_;

    setHeaderData(firstColumn, Qt::Horizontal, firstColumn, Qt::EditRole);
    setHeaderData(secondColumn, Qt::Horizontal, secondColumn, Qt::EditRole);
    setHeaderData(thirdColumn, Qt::Horizontal, thirdColumn, Qt::EditRole);

    emit headerDataChanged(Qt::Horizontal, firstColumn, thirdColumn);
}

Qt::ItemFlags NewModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if(index.isValid())
        flags |= Qt::ItemIsEditable;

    return flags;
}

void NewModel::removeSelected() {
    int index = 0;
    auto iterator = lines.begin();

    while(iterator != lines.end()){
        if(iterator->state){
            beginRemoveRows(QModelIndex(), index, index);
            iterator = lines.erase(iterator);
            endRemoveRows();
        }
        else{
            iterator++;
            index++;
        }
    }
}

void NewModel::removeAll()
{
    auto iterator = lines.begin();

    while(iterator != lines.end()){
        beginRemoveRows(QModelIndex(), 0, 0);
        iterator = lines.erase(iterator);
        endRemoveRows();
    }
}

int NewModel::getFirstColumn()
{
    return firstColumn;
}

int NewModel::getSecondColumn()
{
    return secondColumn;
}

int NewModel::getThirdColumn()
{
    return thirdColumn;
}

int NewModel::getCheckBoxColumn()
{
    return checkBox;
}

int NewModel::getLastLine()
{
    return lines.count() - 1;
}

QString NewModel::setHeader(QString row)
{
    QStringList temp = row.split(QRegularExpression(R"((?<!\\);)"));

    if(temp.count() != 3){
        return "Bad csv format!";
    }

    header = temp;
    return QString();
}

void NewModel::setDefaultHeader()
{
    header[firstColumn] = "FirstColumn";
    header[secondColumn] = "SecondColumn";
    header[thirdColumn] = "ThirdColumn";
}

void NewModel::setAddWindow(AddWindow* addWindow)
{
    this->addWindow = addWindow;
}

bool NewModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if(!index.isValid() || role != Qt::EditRole||
            lines.count() <= index.row())
                return false;

    switch(index.column()) {
        case firstColumn: lines[index.row()].firstColumn = value.toString(); break;
        case secondColumn: lines[index.row()].secondColumn = value.toString(); break;
        case thirdColumn: lines[index.row()].thirdColumn = value.toString(); break;
        case checkBox: lines[index.row()].state = value.toBool(); break;
    }

    emit dataChanged(index, index);

    return true;
}
