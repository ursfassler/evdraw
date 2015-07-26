#ifndef COMPONENTLIST_HPP
#define COMPONENTLIST_HPP

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>

#include <QAbstractListModel>

class ComponentList : public QAbstractListModel, public LibraryObserver
{
    Q_OBJECT
  public:

    explicit ComponentList(Library *library, QObject *parent = 0);
    ~ComponentList();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void addComponent(const QString &name);
    Component *getComponent(const QModelIndex &index) const;
    void deleteComponent(const QModelIndex &index);

    Library *getLibrary() const;

    void componentAdded(Component *component);
    void componentDeleted(Component *component);

  signals:

  public slots:

  private:
    Library * const library;

};

#endif // COMPONENTLIST_HPP
