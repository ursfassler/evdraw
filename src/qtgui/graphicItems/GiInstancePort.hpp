#ifndef GIINSTANCEPORT_HPP
#define GIINSTANCEPORT_HPP

#include <core/instance/InstancePort.hpp>
#include <core/implementation/Composition.hpp>

#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>

class GiInstancePort :
    public QGraphicsRectItem,
    protected PositionObserver,
    protected InstancePortObserver
{
  public:
    explicit GiInstancePort(InstancePort *model, Composition *sheet, QGraphicsItem *parent);
    ~GiInstancePort();

    InstancePort *getModel() const;

  signals:

  public slots:

  protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    virtual void absolutePositionChanged(const RelativePosition *sender);
    virtual void offsetChanged(const RelativePosition *sender);

    virtual void nameChanged(const std::string &name);

  private:
    InstancePort *model;
    Composition *sheet;
    QGraphicsSimpleTextItem label;

    void setDisplayName(QString name);

};

#endif // GIINSTANCEPORT_HPP
