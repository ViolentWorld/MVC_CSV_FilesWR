#include "checkboxdelegate.h"

#include <QCheckBox>
#include <QApplication>

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    :QStyledItemDelegate (parent)
{

}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QCheckBox *editor = new QCheckBox(parent);
    return editor;
}

void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
    checkBox->setChecked(index.data().toBool());
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QStyleOptionButton checkBoxStyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkBoxStyle);

    checkBoxStyle.rect = option.rect;
    checkBoxStyle.rect.setLeft(option.rect.x() +
                               option.rect.width()/2 - checkbox_rect.width()/2);

    editor->setGeometry(checkBoxStyle.rect);
}


void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool data = index.model()->data(index, Qt::DisplayRole).toBool();

    QStyleOptionButton checkBoxStyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkBoxStyle);

    checkBoxStyle.rect = option.rect;
    checkBoxStyle.rect.setLeft(option.rect.x() +
                               option.rect.width()/2 - checkbox_rect.width()/2);

    if(data)
        checkBoxStyle.state = QStyle::State_On|QStyle::State_Enabled;
    else
        checkBoxStyle.state = QStyle::State_Off|QStyle::State_Enabled;

    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkBoxStyle, painter);
}
