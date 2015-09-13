#include <iostream>

// Version 1
// =================================
template <typename... Bases>
class A : public Bases...{
public:
  template <typename... Args>
    A(const std::string &name = "Deriv", Args&&... args)
    : Bases{std::forward<Args>(args)...}..., class_name(name)
  {
    dtor_msg();
  }
  A(const std::string &name = "Deriv") : class_name{name}
  {
    ctor_msg();
  }
  virtual ~A()
  {
    dtor_msg();
  }
 private:
  const std::string class_name;

  void ctor_msg() const {  std::cout << "in constructor of " << class_name << std::endl; }
  void dtor_msg() const {  std::cout << "in destructor  of " << class_name << std::endl; }
};

template <>
class A<>{
public:
  A(const std::string &name = "Deriv") : class_name{name}
  {
    ctor_msg();
  }
  virtual ~A()
  {
    dtor_msg();
  }
  
 private:
  const std::string class_name;

  void ctor_msg() const {  std::cout << "in constructor of " << class_name << std::endl; }
  void dtor_msg() const {  std::cout << "in destructor  of " << class_name << std::endl; }
};



// Version 2 (rather than duplicate all the printing stuff in a specialization (as is done above),
//            use a member that does all the printing!)
// ========================================================================
class PrintMember {
public:
  PrintMember(const std::string &name = "PrintMember") : class_name{name}
  {
    ctor_msg();
  }
  virtual ~PrintMember()
  {
    dtor_msg();
  }
  
 private:
  const std::string class_name;

  void ctor_msg() const {  std::cout << "in constructor of " << class_name << std::endl; }
  void dtor_msg() const {  std::cout << "in destructor  of " << class_name << std::endl; }
};

template <typename... Bases>
class BB : public Bases...{
public:
  template <typename... Args>
    BB(const std::string &name = "Deriv", Args&&... args)
    : Bases{std::forward<Args>(args)...}..., member{name}
  {
  }
  BB(const std::string &name = "Deriv")
    : member{name}
  {
  }
  
 private:
  PrintMember member;
};

template <>
class BB<>{
public:
  BB(const std::string &name = "Deriv") : member{name}
  {
  }
  virtual ~BB()
  {
  }
  
private:
  PrintMember member;
};


int main()
{
  {
    A<A<>> b{"inner", "outer"};
  }

  std::cout << std::endl;

  {
    BB<BB<>> x{"inner", "outer"};
  }
  return 0;
}
