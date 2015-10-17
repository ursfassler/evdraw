// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "GiInstance.hpp"

#include <core/component/InstanceAppearance.hpp>

#include "convert.hpp"

#include <QBrush>
#include <QFont>
#include <QRectF>

GiInstance::GiInstance(Instance *aModel, QGraphicsItem *parent) :
  QGraphicsRectItem(parent),
  model(aModel),
  instanceText(this),
  componentText(this)
{
  model->ObserverCollection<PositionObserver>::registerObserver(this);
  model->ObserverCollection<InstanceObserver>::registerObserver(this);
  model->getPorts().registerObserver(this);
  setBrush(QBrush(QColor::fromRgb(0xf2, 0xf2, 0xff)));

  resize();
  updatePosition();

  updateText();
  addPorts();
}

GiInstance::~GiInstance()
{
  model->getPorts().unregisterObserver(this);
  model->ObserverCollection<InstanceObserver>::unregisterObserver(this);
  model->ObserverCollection<PositionObserver>::unregisterObserver(this);
}

void GiInstance::resize()
{
  qreal x = puToScene(-model->getWidth() / 2);
  qreal w = puToScene(model->getWidth());
  qreal y = puToScene(0);
  qreal h = puToScene(model->getHeight());

  setRect(x, y, w, h);
}

void GiInstance::updatePosition()
{
  setPos(puToScene(model->getOffset()));
}

void GiInstance::updateText()
{
  instanceText.setText(QString::fromStdString(model->getName()));
  instanceText.setPos(calcTextPos(0, instanceText.boundingRect()));

  componentText.setText(QString::fromStdString(model->getComponent()->getName()));
  componentText.setPos(calcTextPos(1, componentText.boundingRect()));
}

void GiInstance::absolutePositionChanged(const RelativePosition *)
{
}

void GiInstance::offsetChanged(const RelativePosition *)
{
  updatePosition();
}

void GiInstance::added(InstancePort *port)
{
  addPort(port);
}

void GiInstance::removed(InstancePort *port)
{
  precondition(ports.contains(port));

  GiInstancePort *inst = ports.take(port);
  delete inst;

  postcondition(!childItems().contains(inst));
}

void GiInstance::nameChanged(const IInstance *)
{
  updateText();
}

void GiInstance::componentNameChanged(const IInstance *)
{
  updateText();
}

void GiInstance::heightChanged()
{
  resize();
}

QPointF GiInstance::calcTextPos(unsigned index, const QRectF &boundingRect) const
{
  const qreal x = -boundingRect.width()/2;
  const qreal offset = (0.5 + index) * puToScene(InstanceAppearance::textHeight());
  const qreal y = offset - boundingRect.height()/2;
  return QPointF(x,y);
}

void GiInstance::addPorts()
{
  for (InstancePort *port : model->getPorts()) {
    addPort(port);
  }
}

void GiInstance::addPort(IPort *port)
{
  InstancePort *ip = dynamic_cast<InstancePort*>(port);
  GiInstancePort *gipo = new GiInstancePort(ip, this);
  ports[ip] = gipo;

  connect(gipo, SIGNAL(startConnection(InstancePort*,Point)), this, SIGNAL(startConnection(InstancePort*,Point)));
}

void GiInstance::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  model->setOffset(sceneToPu(event->scenePos() - event->lastPos()));
  event->accept();
}

void GiInstance::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  grabMouse();
  event->accept();
}

void GiInstance::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  ungrabMouse();
  event->accept();
}
