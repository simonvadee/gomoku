#ifndef EXCEPTIONS_H_
# define EXCEPTIONS_H_

# include <exception>
# include <string>
# include <string.h>
# include <errno.h>

namespace Exceptions
{
  class FactoryExcept : public std::exception
  {
  public:
    FactoryExcept(std::string const& msg) throw()
      : _msg(msg) {}
    FactoryExcept(const FactoryExcept& other) throw()
      : _msg(other._msg) {}
    virtual ~FactoryExcept() throw() {}
    virtual const char* what() const throw()
    {
      return _msg.c_str();
    }
    
  private:
    std::string         _msg;
    FactoryExcept	&operator=(const FactoryExcept &) throw();
  };

  class ObjectExcept : public std::exception
  {
  public:
    ObjectExcept(std::string const &msg) throw()
      :_msg(msg) {}

    ObjectExcept(const ObjectExcept & other) throw()
      :_msg(other._msg){}

    virtual ~ObjectExcept() throw() {}

    virtual const char*     what() const throw()
    {
      return _msg.c_str();
    }

  private:
    std::string			_msg;
    ObjectExcept		&operator=(const ObjectExcept &) throw();
  };
};


#endif /* !EXCEPTIONS_H_ */
