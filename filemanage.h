#ifndef FILEMANAGE_H
#define FILEMANAGE_H

#include "newmodel.h"

#include <QFile>
#include <QFileDialog>
#include <QObject>

class FileManage
{

private:

    QString FilePath;

    NewModel* model;

public:

    FileManage(NewModel* model);

    QString OpenFile(QWidget* parent);
    QString SaveFile();
    QString SaveFileAs(QWidget* parent);

    void replaseBackSlashes(QStringList& list);
    void putBackSlashes(QString& line);

    void writeHeaderData(QFile* file);
};

#endif // FILEMANAGE_H
