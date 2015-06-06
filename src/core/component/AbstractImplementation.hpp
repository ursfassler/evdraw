#ifndef ABSTRACTIMPLEMENTATION_HPP
#define ABSTRACTIMPLEMENTATION_HPP

class AbstractImplementation
{
  public:
    virtual ~AbstractImplementation() {}
};

class NullImplementation final : public AbstractImplementation
{
};

#endif // ABSTRACTIMPLEMENTATION_HPP
