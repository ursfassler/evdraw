// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTIONLISTMODEL_HPP
#define CONNECTIONLISTMODEL_HPP

#include <core/implementation/Composition.hpp>
#include <core/visitor/NullConstVisitor.hpp>

#include <QObject>
#include <QAbstractListModel>

//TODO make instances/ports editable
//TODO update view when names changed
class ConnectionListModel :
    public QAbstractListModel,
    private CompositionObserver
{
    Q_OBJECT

  public:
    explicit ConnectionListModel(Composition &composition, QObject *parent);
    ~ConnectionListModel();

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  private:
    static const uint SRC_INST_INDEX = 0;
    static const uint SRC_PORT_INDEX = 1;
    static const uint DST_INST_INDEX = 2;
    static const uint DST_PORT_INDEX = 3;
    static const uint COLUMN_COUNT = 4;

    Composition &composition;

    Connection *getConnection(uint row) const;
    QPair<QString,QString> endpointName(const IPort &port) const;

    void connectionAdded(Connection *connection);
    void connectionRemoved(Connection *connection);

};

class ConnectionEndpointNameVisitor : public NullConstVisitor
{
  public:
    void visit(const Instance &instance);
    void visit(const CompositionInstance &instance);
    void visit(const InstancePort &port);

    QString instance;
    QString port;
};

#endif // CONNECTIONLISTMODEL_HPP
