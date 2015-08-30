// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONEDITOR_HPP
#define COMPOSITIONEDITOR_HPP

#include "CompositionDraw.hpp"
#include "InstanceListModel.hpp"
#include "ConnectionListModel.hpp"

#include <QWidget>
#include <QTreeView>

class CompositionEditor : public QWidget
{
    Q_OBJECT
  public:
    explicit CompositionEditor(Composition &composition, QWidget *parent = 0);

  signals:
    void addInstance(Point position, Composition &composition);

  public slots:

  private:
    CompositionDraw draw;

    InstanceListModel   instances;
    QTreeView       instanceView;
    ConnectionListModel connections;
    QTreeView       connectionView;

};

#endif // COMPOSITIONEDITOR_HPP
