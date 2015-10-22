// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef QTITEMINTMOCK_HPP
#define QTITEMINTMOCK_HPP

#include <qtmodel/IQtItem.hpp>

class QtItemIntMock :
    public IQtItem<int>
{
  public:
    int columnCount() const override;
    mutable unsigned columnCount_called{0};
    int columnCount_return{};

    bool editable(int column) const override;
    mutable int editable_column{};
    bool editable_return{};

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    mutable unsigned headerData_called{0};
    QVariant headerData_return{};

    QVariant data(const int *item, int column, int role) const override;
    mutable unsigned data_called{0};
    QVariant data_return{};

    bool setData(int *item, int column, const QVariant &value) override;
    unsigned setData_called{0};
    bool setData_return{};



};

#endif // QTITEMINTMOCK_HPP
