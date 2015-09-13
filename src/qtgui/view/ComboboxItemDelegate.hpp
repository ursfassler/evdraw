// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMBOBOXITEMDELEGATE_HPP
#define COMBOBOXITEMDELEGATE_HPP

#include <QStyledItemDelegate>

typedef QAbstractListModel* (*ModelFromIndex)(const QModelIndex &index);

class ComboboxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
  public:
    ComboboxItemDelegate(ModelFromIndex modelFromIndex, QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

  private:
    ModelFromIndex modelFromIndex;
};

#endif // COMBOBOXITEMDELEGATE_HPP
