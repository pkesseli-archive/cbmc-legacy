/*******************************************************************\

Module: Variable Numbering

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_PATH_SYMEX_VAR_MAP_H
#define CPROVER_PATH_SYMEX_VAR_MAP_H

#include <map>

#include <util/namespace.h>
#include <util/type.h>

class var_mapt
{
public:
  explicit var_mapt(const namespacet &_ns):
    ns(_ns), shared_count(0), local_count(0), nondet_count(0), dynamic_count(0)
  {
  }

  struct var_infot
  {
    enum { SHARED, THREAD_LOCAL, PROCEDURE_LOCAL } kind;
    
    inline bool is_shared() const
    {
      return kind==SHARED;
    }

    // the variables are numbered
    unsigned number;

    // identifier=symbol+suffix
    irep_idt identifier, symbol, suffix;

    // the type of the identifier (struct member or array)
    typet type;
    
    unsigned ssa_counter;
    
    var_infot():kind(SHARED), number(0), ssa_counter(0)
    {
    }
    
    irep_idt ssa_identifier() const;

    inline void increment_ssa_counter() 
    {
      ++ssa_counter;
    }
    
    void output(std::ostream &out) const;
  };
  
  typedef std::map<irep_idt, var_infot> id_mapt;
  id_mapt id_map;

  inline var_infot &operator()(
    const irep_idt &symbol,
    const irep_idt &suffix,
    const typet &type)
  {
    std::string identifier=
      id2string(symbol)+id2string(suffix);

    std::pair<id_mapt::iterator, bool> result;

    result=id_map.insert(std::pair<irep_idt, var_infot>(
      identifier, var_infot()));      
  
    if(result.second) // inserted?
    {
      result.first->second.identifier=identifier;
      result.first->second.symbol=symbol;
      result.first->second.suffix=suffix;
      result.first->second.type=type;
      init(result.first->second);
    }
    
    return result.first->second;
  }
  
  void init(var_infot &var_info);

  const namespacet &ns;

protected:
  unsigned shared_count, local_count;

public:
  unsigned nondet_count;  // free inputs
  unsigned dynamic_count; // memory allocation  
};

#endif
