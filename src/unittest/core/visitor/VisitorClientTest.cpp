#include "VisitorClientTest.hpp"

#include <core/visitor/VisitorClient.hpp>
#include <core/visitor/NullVisitor.hpp>
#include <core/visitor/NullConstVisitor.hpp>
#include <core/base/Base.hpp>

class TestVisitorClient : public VisitorClient
{
  public:
    void accept(Visitor &)
    {
    }

    void accept(ConstVisitor &) const
    {
    }

};

void VisitorClientTest::inheritsBase()
{
  TestVisitorClient tvc;
  CPPUNIT_ASSERT(dynamic_cast<Base*>(&tvc) != nullptr);
}

void VisitorClientTest::acceptsVisitor()
{
  VisitorClient *tvc = new TestVisitorClient();
  NullVisitor visitor;
  tvc->accept(visitor);
  delete tvc;
}

void VisitorClientTest::acceptsConstVisitor()
{
  VisitorClient *tvc = new TestVisitorClient();
  NullConstVisitor visitor;
  tvc->accept(visitor);
  delete tvc;
}
