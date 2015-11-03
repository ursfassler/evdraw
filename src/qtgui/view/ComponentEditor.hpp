// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTEDITOR_H
#define COMPONENTEDITOR_H

#include <qtmodel/QtList.hpp>

#include <core/component/Component.hpp>
#include <core/component/ComponentPort.hpp>

#include <QWidget>
#include <QTreeView>

class ComponentEditor : public QWidget
{
    Q_OBJECT
  public:
    explicit ComponentEditor(QWidget *parent = 0);
    ~ComponentEditor() override;

    void setModel(IComponent *component);
    IComponent *getModel() const;

  signals:

  public slots:
    void addPort();
    void delPort();

  private:
    IComponent *model{nullptr};

    QtList<ComponentPort> *portModel = nullptr;
    QTreeView portView;

};

#endif // COMPONENTEDITOR_H
