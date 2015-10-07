// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NAMETYPEMODEL_HPP
#define NAMETYPEMODEL_HPP

#include <QObject>
#include <QAbstractListModel>
#include <QStringListModel>

//TODO add tests

class NameTypeModel : public QAbstractListModel
{
  public:
    explicit NameTypeModel(QObject *parent);

    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual QAbstractListModel *getTypes() const = 0;

    static const uint NAME_INDEX = 0;
    static const uint TYPE_INDEX = 1;
    static const uint COLUMN_COUNT = 2;

  protected:

    void setNameEditable(bool editable);
    void setTypeEditable(bool editable);

    virtual QString getName(uint row) const = 0;
    virtual bool setName(uint row, QString name);
    virtual QModelIndex getType(uint row) const = 0;
    virtual bool setType(uint row, const QVariant &value);

  private:
    bool editable[COLUMN_COUNT] = { false, false };

};

auto modelFromTypeIndex = [](const QModelIndex &index) -> QAbstractListModel*
{
  const NameTypeModel *model = dynamic_cast<const NameTypeModel*>(index.model());
  return model->getTypes();
};

#endif // NAMETYPEMODEL_HPP
