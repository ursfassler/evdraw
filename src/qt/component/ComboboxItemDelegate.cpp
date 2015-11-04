// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComboboxItemDelegate.hpp"

#include <QComboBox>

ComboboxItemDelegate::ComboboxItemDelegate(ModelFromIndex aModelFromIndex, QObject *parent) :
  QStyledItemDelegate(parent),
  modelFromIndex(aModelFromIndex)
{
}

QWidget *ComboboxItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
  QComboBox *editor = new QComboBox(parent);
  editor->setFrame(false);
  editor->setModel(modelFromIndex(index));
  return editor;
}

void ComboboxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  const QVariant data = index.model()->data(index, Qt::EditRole);
  const int value = data.toUInt();

  QComboBox *box = static_cast<QComboBox*>(editor);
  box->setCurrentIndex(value);
}

void ComboboxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *box = static_cast<QComboBox*>(editor);
  int value = box->currentIndex();

  model->setData(index, value, Qt::EditRole);
}

void ComboboxItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
  editor->setGeometry(option.rect);
}
