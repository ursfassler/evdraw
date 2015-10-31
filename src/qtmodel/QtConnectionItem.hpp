// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTCONNECTIONITEM_HPP
#define QTCONNECTIONITEM_HPP

#include "IQtItem.hpp"

#include <core/connection/Connection.hpp>

//TODO make instances/ports editable
//TODO update view when names changed

class QtConnectionItem final :
    public AQtItem<Connection>
{
  public:
    int columnCount() const override;
    bool editable(int column) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const Connection *connection, int column, int role) const override;
    bool setData(Connection *item, int column, const QVariant &value) override final;

    void added(Connection *item) override final;
    void removed(Connection *item) override final;

  private:
    static const uint SRC_INST_INDEX = 0;
    static const uint SRC_PORT_INDEX = 1;
    static const uint DST_INST_INDEX = 2;
    static const uint DST_PORT_INDEX = 3;
    static const uint COLUMN_COUNT = 4;

    QString instanceName(const IPort &port) const;
};

#include "QtList.hpp"

//TODO remove
class ConnectionListModel :
    public QtList<Connection>
{
  public:
    ConnectionListModel(List<Connection> &aModel, QObject *parent = 0);

    static QtConnectionItem *item();

};

#endif
