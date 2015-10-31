// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONEDITOR_HPP
#define COMPOSITIONEDITOR_HPP

#include "CompositionDraw.hpp"
#include <qtmodel/InstanceItem.hpp>
#include <qtmodel/QtConnectionItem.hpp>
#include <qtmodel/ComponentItem.hpp>

#include <core/component/Library.hpp>

#include <QWidget>
#include <QTreeView>
#include <QSplitter>

class CompositionEditor : public QSplitter
{
    Q_OBJECT
  public:
    explicit CompositionEditor(Composition &composition, Library &library, QWidget *parent = 0);
    ~CompositionEditor();

  signals:
    void addInstance(Point position, Composition &composition);

  public slots:

  private:
    CompositionDraw draw;

    ComponentListModel  componentModel;
    InstanceListModel   instances;
    QTreeView           instanceView;
    ConnectionListModel connections;
    QTreeView           connectionView;

};

#endif // COMPOSITIONEDITOR_HPP
