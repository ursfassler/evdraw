// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IDATAABSTRACTION
#define IDATAABSTRACTION

#include <QVariant>
#include <functional>

template <typename T>
using ChangeListener = typename std::function<void(T *item, int column)>;


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

    virtual void added(T *item) = 0;
    virtual void removed(T *item) = 0;
    virtual void addListener(ChangeListener<T> listener) = 0;
};

template<class T>
class AQtItem :
    public IQtItem<T>
{
  public:
    void addListener(ChangeListener<T> listener) override final
    {
      listeners.push_back(listener);
    }

  protected:
    void notify(T *item, int column)
    {
      for (const auto& listener : listeners) {
        listener(item, column);
      }
    }

  private:
    std::vector<ChangeListener<T>> listeners{};
};

#endif // IDATAABSTRACTION

