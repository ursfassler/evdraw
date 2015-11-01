#ifndef INAMETYPEITEM
#define INAMETYPEITEM

#include "../core/util/contract.hpp"

#include <QAbstractListModel>
#include <functional>
#include <vector>

template <typename T>
using ChangeNameTypeListener = typename std::function<void(T *item)>;
//TODO make item const

template<class T>
class INameTypeItem
{
  public:
    virtual ~INameTypeItem() = default;

    virtual bool isNameEditable() const = 0;
    virtual bool isTypeEditable() const = 0;

    virtual QAbstractListModel *getTypeModel() const = 0;

    virtual std::string getName(const T* item) const = 0;
    virtual void setName(T* item, const std::string &value) = 0;
    virtual unsigned getType(const T* item) const = 0;
    virtual void setType(T* item, unsigned value) = 0;

    virtual void added(T *item) = 0;
    virtual void removed(T *item) = 0;
    virtual void addNameListener(ChangeNameTypeListener<T> listener) = 0;
    virtual void addTypeListener(ChangeNameTypeListener<T> listener) = 0;
};

template<class T>
class ANameTypeItem :
    public INameTypeItem<T>
{
  public:
    void addNameListener(ChangeNameTypeListener<T> listener) override final
    {
      nameListener.push_back(listener);
    }

    void addTypeListener(ChangeNameTypeListener<T> listener) override final
    {
      typeListener.push_back(listener);
    }

  protected:
    void notifyNameChange(T *item)
    {
      notify(nameListener, item);
    }

    void notifyTypeChange(T *item)
    {
      notify(typeListener, item);
    }

  private:
    std::vector<ChangeNameTypeListener<T>> nameListener{};
    std::vector<ChangeNameTypeListener<T>> typeListener{};

    void notify(const std::vector<ChangeNameTypeListener<T>> &listeners, T *item) const
    {
      for (const auto& listener : listeners) {
        listener(item);
      }
    }
};




#endif // INAMETYPEITEM

