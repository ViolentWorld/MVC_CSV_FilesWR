#include "filemanage.h"

#include <QMessageBox>
#include <QTextCodec>
#include <QRegularExpression>
#include <QTextStream>

FileManage::FileManage(NewModel* model)
{
    this->model = model;
}

QString FileManage::OpenFile(QWidget* parent)
{
    QString data;
    QStringList rows;
    QStringList rowData;

    QString path = QFileDialog::getOpenFileName(parent, ("Open File"),
                                                "/file", ("csv File(*.csv)"));
    QFile file(path);

    if (!file.open(QFile::ReadOnly))
            return "File was not opened!";

    FilePath = path;
    data = file.readAll();
    rows = data.split("\n");
    file.close();

    model->removeAll();

    QString headerMistake = model->setHeader(rows[model->getFirstColumn()]);
    if(headerMistake != QString()){
        model->setDefaultHeader();
        return headerMistake;
    }


    for (int i = 1; i < rows.size(); i++){
        rowData = rows.at(i).split(QRegularExpression(R"((?<!\\);)"));

        if(rowData.count() != model->getCheckBoxColumn()) {
            model->removeAll();
            model->setDefaultHeader();
            return "Bad csv format!";
        }

        replaseBackSlashes(rowData);

        model->appendLine(rowData[model->getFirstColumn()].simplified(),
            rowData[model->getSecondColumn()].simplified(), rowData[model->getThirdColumn()].simplified());
    }

    return QString();
}

QString FileManage::SaveFile()
{
    QString data;
    int rows = model->rowCount(QModelIndex());
    int columns = model->getCheckBoxColumn();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            QString temp;
            if(i == 0)
               temp  = '\n' + model->data(model->index(i,j), Qt::DisplayRole).toString();
            else
               temp = model->data(model->index(i,j), Qt::DisplayRole).toString();
            putBackSlashes(temp);
            data += temp.simplified();
            if(j == model->getThirdColumn() )
                continue;
            data += ";";
        }
        if(i == model->getLastLine() )
            continue;
        data += "\n";
    }

    QFile file(FilePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
         return "File was not saved!";

    writeHeaderData(&file);
    QTextStream toWrite(&file);
    toWrite.setCodec("UTF-8");
    toWrite << data.toUtf8();
    file.close();
    return QString();
}

QString FileManage::SaveFileAs(QWidget* parent)
{
    QString data;
    int rows = model->rowCount(QModelIndex());
    int columns = model->getCheckBoxColumn();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            QString temp;
            if(i == 0)
               temp  = '\n' + model->data(model->index(i,j), Qt::DisplayRole).toString();
            else
               temp = model->data(model->index(i,j), Qt::DisplayRole).toString();
            putBackSlashes(temp);
            data += temp.simplified();
            if(j == model->getThirdColumn() )
                continue;
            data += ";";
        }
        if(i == model->getLastLine() )
            continue;
        data += "\n";
    }

   QString path = QFileDialog::getSaveFileName(parent,
            ("Save Address Book"), "/file", "csv File(*.csv)");

   QFile file(path);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
            return "File was not saved!";

    writeHeaderData(&file);
    FilePath = path;
    QTextStream toWrite(&file);
    toWrite.setCodec("UTF-8");
    toWrite << data;
    file.close();
    return QString();
}

void FileManage::replaseBackSlashes(QStringList& list)
{
    for(int i = 0; i < list.count(); i++){
        list[i].replace("\\;", ";");
    }
}

void FileManage::putBackSlashes(QString& line)
{
    line.replace(';', "\\;");
}

void FileManage::writeHeaderData(QFile* file)
{
    QString data;

    for(int i = 0; i < model->getCheckBoxColumn(); i++){
        QString temp = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        putBackSlashes(temp);
        data += temp.simplified();

        if(i == model->getThirdColumn() )
            continue;

        data += ';';
    }
    data += '\n';

    QTextStream toWrite(file);
    toWrite.setCodec("UTF-8");
    toWrite << data;
}
