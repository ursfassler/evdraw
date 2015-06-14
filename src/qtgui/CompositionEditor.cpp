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

  updater.init();
}
