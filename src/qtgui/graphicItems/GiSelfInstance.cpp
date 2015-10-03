// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "GiSelfInstance.hpp"

#include "convert.hpp"
#include "GiInstancePort.hpp"

#include <core/component/InstanceAppearance.hpp>

#include <QCursor>

VerticalLine::VerticalLine(ICompositionInstance &aInstance, QGraphicsItem *parent) :
  MoveableLine{parent},
  instance{aInstance}
{
}

void VerticalLine::moveTo(const Point &pos)
{
  const auto width = 2 * std::fabs(pos.x);
  instance.setWidth(width);
}



HorizontallLine::HorizontallLine(ICompositionInstance &aInstance, QGraphicsItem *parent) :
  MoveableLine{parent},
  instance{aInstance}
{
}

void HorizontallLine::moveTo(const Point &pos)
{
  const auto height = pos.y;
  instance.setHeight(height);
}



GiSelfInstance::GiSelfInstance(ICompositionInstance &aInstance, Composition &aComposition) :
  type{this},
  leftLine{aInstance, this},
  rightLine{aInstance, this},
  bottomLine{aInstance, this},
  instance{aInstance},
  composition{aComposition}
{
  instance.registerObserver(this);

  updateSize();

  leftLine.setCursor(QCursor(Qt::SizeHorCursor));
  rightLine.setCursor(QCursor(Qt::SizeHorCursor));
  bottomLine.setCursor(QCursor(Qt::SizeVerCursor));

  addPorts(instance.getPorts());

  const auto text = QString::fromStdString(instance.getComponent()->getName());
  type.setText(text);
  type.setPos(0, 0.5 * puToScene(InstanceAppearance::textHeight()) - type.boundingRect().height()/2);
}

GiSelfInstance::~GiSelfInstance()
{
  instance.unregisterObserver(this);
}

void GiSelfInstance::addPorts(const std::vector<InstancePort *> &ports)
{
  for (InstancePort *port : ports) {
    addPort(port);
  }
}

void GiSelfInstance::addPort(InstancePort *port)
{
  InstancePort *ip = dynamic_cast<InstancePort*>(port);
  GiInstancePort *gipo = new GiInstancePort(ip, &composition, this);
  //  ports[ip] = gipo;
}

void GiSelfInstance::widthChanged()
{
  updateSize();
}

void GiSelfInstance::heightChanged()
{
  updateSize();
}

void GiSelfInstance::updateSize()
{
  const auto width = puToScene(instance.getWidth());
  const auto height = puToScene(instance.getHeight());
  const auto newRect = QRectF{-width/2, 0, width, height};

  prepareGeometryChange();

  setRect(newRect);

  leftLine.setLine(-width/2, 0, -width/2, height);
  rightLine.setLine(width/2, 0, width/2, height);
  bottomLine.setLine(-width/2, height, width/2, height);

  update();
}


