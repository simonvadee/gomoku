#ifndef EXCEPTIONS_H_
# define EXCEPTIONS_H_

# include <exception>
# include <string>
# include <string.h>
# include <errno.h>

namespace Exceptions
{
  class EndGameExcept : public std::exception
  {
  public:
    EndGameExcept(std::string const& msg) throw()
      : _msg(msg) {}
    EndGameExcept(const EndGameExcept& other) throw()
      : _msg(other._msg) {}
    virtual ~EndGameExcept() throw() {}
    virtual const char* what() const throw()
    {
      return _msg.c_str();
    }
    
  private:
    std::string         _msg;
    EndGameExcept	&operator=(const EndGameExcept &) throw();
  };

  class ErrorExcept : public std::exception
  {
  public:
    ErrorExcept(std::string const &msg) throw()
      :_msg(msg) {}

    ErrorExcept(const ErrorExcept & other) throw()
      :_msg(other._msg){}

    virtual ~ErrorExcept() throw() {}

    virtual const char*     what() const throw()
    {
      return _msg.c_str();
    }

  private:
    std::string			_msg;
    ErrorExcept		&operator=(const ErrorExcept &) throw();
  };
};


#endif /* !EXCEPTIONS_H_ */
