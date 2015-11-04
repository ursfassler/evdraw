#ifndef MODELFROMTYPE
#define MODELFROMTYPE

#include <qt/model/QtList.hpp>
#include <qt/model/QtNameTypeItem.hpp>

#include <QAbstractListModel>

template<class T>
QAbstractListModel* modelFromTypeIndex(const QModelIndex &index)
{
  const QtList<T> *list = dynamic_cast<const QtList<T>*>(index.model());
  precondition(list != nullptr);

  const IQtItem<T>  *item = list->getItemModel();

  const QtNameTypeItem<T> *nti = dynamic_cast<const QtNameTypeItem<T>*>(item);
  precondition(nti != nullptr);

  const INameTypeItem<T> *ntm = nti->getModel();

  return ntm->getTypeModel();
}


#endif // MODELFROMTYPE

