#ifndef COMPIFACEMODEL_HPP
#define COMPIFACEMODEL_HPP

#include <core/component/Component.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include <QAbstractListModel>

class CompifaceModel : public QAbstractListModel, protected ComponentObserver
{
    Q_OBJECT
  public:
    explicit CompifaceModel(Component &component, QObject *parent = 0);
    ~CompifaceModel();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void delPort(const QModelIndex &index);
    void addPort(const QString &name);

    const Component *getComponent() const;

  protected:
    void portAdded(ComponentPort *port);
    void portDeleted(ComponentPort *port);

  private:
    enum class ColumnType
    {
      Name = 0,
      Type = 1
    };

    Component &component;

    QString getColumnString(const ComponentPort *port, ColumnType type) const;
    QString getPortTypeName(const ComponentPort *port) const;
};

class PortTypeNameVisitor : public NullConstVisitor
{
  public:
    void visit(const Slot &port);
    void visit(const Signal &port);

    QString name;

};

#endif // COMPIFACEMODEL_HPP
