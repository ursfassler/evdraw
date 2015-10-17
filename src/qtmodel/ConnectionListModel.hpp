// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTIONLISTMODEL_HPP
#define CONNECTIONLISTMODEL_HPP

#include <core/connection/Connection.hpp>
#include <core/visitor/NullConstVisitor.hpp>
#include <core/util/List.hpp>

#include <QObject>
#include <QAbstractListModel>

//TODO make instances/ports editable
//TODO update view when names changed
class ConnectionListModel :
    public QAbstractListModel,
    private ListObserver<Connection>
{
    Q_OBJECT

  public:
    ConnectionListModel(const ConnectionListModel&) = delete;
    ConnectionListModel &operator =(const ConnectionListModel&) = delete;


    //TODO use connection list interface instead composition
    explicit ConnectionListModel(List<Connection> &connections, QObject *parent = 0);
    ~ConnectionListModel();

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  private:
    static const uint SRC_INST_INDEX = 0;
    static const uint SRC_PORT_INDEX = 1;
    static const uint DST_INST_INDEX = 2;
    static const uint DST_PORT_INDEX = 3;
    static const uint COLUMN_COUNT = 4;

    List<Connection> &connections;

    Connection *getConnection(uint row) const;
    QString instanceName(const IPort &port) const;

    void added(Connection* value) override;
    void removed(Connection* value) override;

};

#endif // CONNECTIONLISTMODEL_HPP
