/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <ostream>

#include "c_qualifiers.h"

/*******************************************************************\

Function: c_qualifierst::as_string

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

std::string c_qualifierst::as_string() const
{
  std::string qualifiers;
  
  if(is_constant)
    qualifiers+="const ";

  if(is_volatile)
    qualifiers+="volatile ";

  if(is_restricted)
    qualifiers+="restrict ";
    
  if(is_atomic)
    qualifiers+="_Atomic ";
    
  if(is_ptr32)
    qualifiers+="__ptr32 ";
    
  if(is_ptr64)
    qualifiers+="__ptr64 ";

  if(is_noreturn)
    qualifiers+="_Noreturn ";
    
  return qualifiers;
}

/*******************************************************************\

Function: c_qualifierst::read

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void c_qualifierst::read(const typet &src)
{
  if(src.get_bool(ID_C_constant))
    is_constant=true;

  if(src.get_bool(ID_C_volatile))
    is_volatile=true;

  if(src.get_bool(ID_C_restricted))
    is_restricted=true;

  if(src.get_bool(ID_C_atomic))
    is_atomic=true;

  if(src.get_bool(ID_C_ptr32))
    is_ptr32=true;

  if(src.get_bool(ID_C_ptr64))
    is_ptr64=true;

  if(src.get_bool(ID_C_transparent_union))
    is_transparent_union=true;

  if(src.get_bool(ID_C_noreturn))
    is_noreturn=true;
}

/*******************************************************************\

Function: c_qualifierst::write

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void c_qualifierst::write(typet &dest) const
{
  if(is_constant)
    dest.set(ID_C_constant, true);
  else
    dest.remove(ID_C_constant);

  if(is_volatile)
    dest.set(ID_C_volatile, true);
  else
    dest.remove(ID_C_volatile);

  if(is_restricted)
    dest.set(ID_C_restricted, true);
  else
    dest.remove(ID_C_restricted);

  if(is_atomic)
    dest.set(ID_C_atomic, true);
  else
    dest.remove(ID_C_atomic);

  if(is_ptr32)
    dest.set(ID_C_ptr32, true);
  else
    dest.remove(ID_C_ptr32);

  if(is_ptr64)
    dest.set(ID_C_ptr64, true);
  else
    dest.remove(ID_C_ptr64);

  if(is_transparent_union)
    dest.set(ID_C_transparent_union, true);
  else
    dest.remove(ID_C_transparent_union);

  if(is_noreturn)
    dest.set(ID_C_noreturn, true);
  else
    dest.remove(ID_C_noreturn);
}

/*******************************************************************\

Function: c_qualifierst::clear

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void c_qualifierst::clear(typet &dest)
{
  dest.remove(ID_C_constant);
  dest.remove(ID_C_volatile);
  dest.remove(ID_C_restricted);
  dest.remove(ID_C_ptr32);
  dest.remove(ID_C_ptr64);
  dest.remove(ID_C_transparent_union);
  dest.remove(ID_C_noreturn);
}

/*******************************************************************\

Function: operator <<

  Inputs:

 Outputs:

 Purpose: pretty-print the qualifiers

\*******************************************************************/

std::ostream &operator << (
  std::ostream &out,
  const c_qualifierst &c_qualifiers)
{
  return out << c_qualifiers.as_string();
}

