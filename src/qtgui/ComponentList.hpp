#ifndef COMPONENTLIST_HPP
#define COMPONENTLIST_HPP

#include <core/component/Library.hpp>

#include <QAbstractListModel>

class ComponentList : public QAbstractListModel
{
    Q_OBJECT
  public:
    typedef enum
    {
      ComponentRole = Qt::UserRole
    } Roles;

    explicit ComponentList(Library *library, QObject *parent = 0);
    ~ComponentList();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Component *getComponent(const QModelIndex &index) const;

    Library *getLibrary() const;

  signals:

  public slots:

  private:
    Library * const library;

};

#endif // COMPONENTLIST_HPP
