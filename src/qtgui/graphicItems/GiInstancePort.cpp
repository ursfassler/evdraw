// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "GiInstancePort.hpp"

#include "GiConnectionCreation.hpp"

#include <core/component/InstanceAppearance.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/connection/DrawPort.hpp>
#include "convert.hpp"

#include <QBrush>

GiInstancePort::GiInstancePort(InstancePort *aModel, Composition *aSheet, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  model(aModel),
  sheet(aSheet),
  label(this)
{
  model->ObserverCollection<PositionObserver>::registerObserver(this);
  model->ObserverCollection<InstancePortObserver>::registerObserver(this);

  setBrush(QBrush(QColor::fromRgb(0xff, 0xfa, 0x99)));

  Point topLeft     = -InstanceAppearance::portDimension() / 2;
  Point bottomRight =  InstanceAppearance::portDimension() / 2;

  setRect(QRectF(puToScene(topLeft), puToScene(bottomRight)));
  setPos(puToScene(model->getOffset()));

  setDisplayName(QString::fromStdString(model->getName()));
}

GiInstancePort::~GiInstancePort()
{
  model->ObserverCollection<InstancePortObserver>::unregisterObserver(this);
  model->ObserverCollection<PositionObserver>::unregisterObserver(this);
}

InstancePort *GiInstancePort::getModel() const
{
  return model;
}

void GiInstancePort::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void GiInstancePort::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  event->accept();
  DrawPort *end = new DrawPort(sceneToPu(event->scenePos()));
  sheet->startConnectionConstruction(model, end);
}

void GiInstancePort::absolutePositionChanged(const RelativePosition *)
{

}

void GiInstancePort::offsetChanged(const RelativePosition *)
{
  setPos(puToScene(model->getOffset()));
}

void GiInstancePort::nameChanged(const std::string &name)
{
  setDisplayName(QString::fromStdString(name));
}

void GiInstancePort::setDisplayName(QString name)
{
  label.setText(name);
  label.setPos(-label.boundingRect().width()/2, -label.boundingRect().height()/2);
}
