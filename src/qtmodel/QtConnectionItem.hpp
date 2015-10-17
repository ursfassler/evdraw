// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTCONNECTIONITEM_HPP
#define QTCONNECTIONITEM_HPP

#include "IQtItem.hpp"
#include "QtList.hpp"

#include <core/connection/Connection.hpp>

//TODO make instances/ports editable
//TODO update view when names changed

class QtConnectionItem final :
    public IQtItem<Connection>
{
  public:
    int columnCount() const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const Connection *connection, int column, int role) const override;

  private:
    static const uint SRC_INST_INDEX = 0;
    static const uint SRC_PORT_INDEX = 1;
    static const uint DST_INST_INDEX = 2;
    static const uint DST_PORT_INDEX = 3;
    static const uint COLUMN_COUNT = 4;

    QString instanceName(const IPort &port) const;
};

//TODO remove
class ConnectionListModel :
    public QtList<Connection>
{
  public:
    ConnectionListModel(List<Connection> &aModel, QObject *parent = 0);

    static QtConnectionItem &item();

};

#endif
