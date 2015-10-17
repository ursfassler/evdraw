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

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    mutable unsigned headerData_called{0};
    QVariant headerData_return{};

    QVariant data(const int *item, int column, int role) const override;
    mutable unsigned data_called{0};
    QVariant data_return{};


};

#endif // QTITEMINTMOCK_HPP
