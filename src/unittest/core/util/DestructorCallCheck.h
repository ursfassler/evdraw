#ifndef DESTRUCTORCALLCHECK_H
#define DESTRUCTORCALLCHECK_H

class DestructorCallCheck
{
  public:
    DestructorCallCheck(const DestructorCallCheck&) = delete;
    DestructorCallCheck operator=(const DestructorCallCheck&) = delete;


    DestructorCallCheck(bool *aDestructorCalled = nullptr) :
      destructorCalled(aDestructorCalled)
    {
    }

    ~DestructorCallCheck()
    {
      if (destructorCalled != nullptr) {
        *destructorCalled = true;
      }
    }

  private:
    bool *destructorCalled;
};

#endif // DESTRUCTORCALLCHECK_H
