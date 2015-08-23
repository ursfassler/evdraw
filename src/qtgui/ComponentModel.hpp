#ifndef COMPONENTLIST_HPP
#define COMPONENTLIST_HPP

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include <QAbstractListModel>

class ComponentModel : public QAbstractListModel, public LibraryObserver
{
    Q_OBJECT
  public:

    explicit ComponentModel(Library *library, QObject *parent = 0);
    ~ComponentModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
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

    static const uint NAME_INDEX = 0;
    static const uint TYPE_INDEX = 1;
    static const uint COLUMN_COUNT = 2;

    QString getImplementationName(const Component *component) const;
};

class ImplementationNameVisitor : public NullConstVisitor
{
  public:
    void visit(const Composition &composition);
    void visit(const NullImplementation &nullImplementation) ;

    QString name;
};


#endif // COMPONENTLIST_HPP
