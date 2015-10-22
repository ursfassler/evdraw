// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IDATAABSTRACTION
#define IDATAABSTRACTION

#include <QVariant>

template<class T>
class IQtItem
{
  public:
    virtual ~IQtItem() = default;

    virtual int columnCount() const = 0;
    virtual bool editable(int column) const = 0;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const = 0;
    virtual QVariant data(const T *item, int column, int role) const = 0;
    virtual bool setData(T *item, int column, const QVariant &value) = 0;
};


#endif // IDATAABSTRACTION

