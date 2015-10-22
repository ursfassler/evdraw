#ifndef INAMETYPEITEM
#define INAMETYPEITEM

#include <QAbstractListModel>

template<class T>
class INameTypeItem
{
  public:
    virtual ~INameTypeItem(){}

    virtual bool isNameEditable() const = 0;
    virtual bool isTypeEditable() const = 0;

    virtual QAbstractListModel *getTypeModel() = 0;

    virtual std::string getName(const T* item) const = 0;
    virtual void setName(T* item, const std::string &value) = 0;
    virtual unsigned getType(const T* item) const = 0;
    virtual void setType(T* item, unsigned value) = 0;

};

#endif // INAMETYPEITEM

