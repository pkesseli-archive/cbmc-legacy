#ifndef CPROVER_PARSER_H
#define CPROVER_PARSER_H

#include <istream>
#include <string>
#include <vector>

#include "expr.h"
#include "message.h"

class parsert:public messaget
{
public:
  std::istream *in;
  locationt location;
  
  std::string last_line;
  
  std::vector<exprt> stack;
  
  virtual void clear()
  {
    line_no=0;
    stack.clear();
    location.clear();
    last_line.clear();
  }
  
  inline parsert() { clear(); }
  
  virtual ~parsert() { }

  inline bool read(char &ch)
  {
    if(!in->read(&ch, 1)) return false;

    if(ch=='\n')
      last_line.clear();
    else
      last_line+=ch;
    
    return true;
  }
   
  virtual bool parse()
  {
    return true;
  }

  inline bool eof()
  {
    return in->eof();
  }
  
  void parse_error(
    const std::string &message,
    const std::string &before);
    
  void inc_line_no()
  {
    ++line_no;
    location.set_line(line_no);
  }
  
  inline void set_line_no(unsigned _line_no)
  {
    line_no=_line_no;
    location.set_line(line_no);
  }
  
  inline void set_file(const irep_idt &file)
  {
    location.set_file(file);
  }
  
  inline unsigned get_line_no() const
  {
    return line_no;
  }

  inline void set_location(exprt &e)
  {
    e.location()=location;
  }

private:
  unsigned line_no;
};
 
exprt &_newstack(parsert &parser, unsigned &x);

#define newstack(x) _newstack(PARSER, (x))

#define stack(x) (PARSER.stack[x])

#define YY_INPUT(buf,result,max_size) \
    do { \
        for(result=0; result<max_size;) \
        { \
          char ch; \
          if(!PARSER.read(ch)) \
          { \
            if(result==0) result=YY_NULL; \
            break; \
          } \
          \
          if(ch!='\r') \
          { \
            buf[result++]=ch; \
            if(ch=='\n') { PARSER.inc_line_no(); break; } \
          } \
        } \
    } while(0)

#endif
