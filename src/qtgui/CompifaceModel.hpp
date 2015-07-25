#ifndef COMPIFACEMODEL_HPP
#define COMPIFACEMODEL_HPP

#include <core/component/Component.hpp>

#include <QAbstractListModel>

class CompifaceModel : public QAbstractListModel
{
    Q_OBJECT
  public:
    explicit CompifaceModel(Component &component, QObject *parent = 0);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void delPort(const QModelIndex &index);

  private:
    Component &component;

};

#endif // COMPIFACEMODEL_HPP
