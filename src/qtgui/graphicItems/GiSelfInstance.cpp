// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "GiSelfInstance.hpp"

#include "convert.hpp"
#include "GiInstancePort.hpp"

#include <core/component/InstanceAppearance.hpp>

GiSelfInstance::GiSelfInstance(ICompositionInstance &instance, Composition &aComposition) :
  type{this},
  composition{aComposition}
{
  const qreal width = puToScene(instance.getWidth());
  setRect(-width/2, 0, width, puToScene(instance.getHeight()));

  addPorts(instance.getPorts());

  const auto text = QString::fromStdString(instance.getComponent()->getName());
  type.setText(text);
  type.setPos(0, 0.5 * puToScene(InstanceAppearance::textHeight()) - type.boundingRect().height()/2);

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

