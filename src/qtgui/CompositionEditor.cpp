#include "CompositionEditor.hpp"

#include "graphicItems/convert.hpp"

#include <core/component/InstanceAppearance.hpp>

CompositionEditor::CompositionEditor(Composition &aComposition, QWidget *parent) :
  QGraphicsView(parent),
  scene(this),
  updater(scene, aComposition),
  composition(aComposition)
{
  setScene(&scene);

  QFont font("Sans", 0.6 * puToScene(InstanceAppearance::textHeight()));
  scene.setFont(font);

  connect(&scene, SIGNAL(removeFromModel(QGraphicsItem*)), this, SLOT(removeFromModel(QGraphicsItem*)));

  updater.init();
}

void CompositionEditor::removeFromModel(QGraphicsItem *item)
{
  updater.removeFromModel(item);
}
