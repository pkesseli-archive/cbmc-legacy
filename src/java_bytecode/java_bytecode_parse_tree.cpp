/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <ostream>

#include <langapi/language_util.h>

#include "java_bytecode_parse_tree.h"

/*******************************************************************\

Function: java_bytecode_parse_treet::swap

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void java_bytecode_parse_treet::classt::swap(
  classt &other)
{
}

/*******************************************************************\

Function: java_bytecode_parse_treet::classt::output

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void java_bytecode_parse_treet::classt::output(std::ostream &out) const
{
  out << "class " << name;
  if(!extends.empty()) out << " extends " << extends;
  out << " {" << '\n';

  for(memberst::const_iterator
      it=members.begin();
      it!=members.end();
      it++)
  {
    it->output(out);
  }
  
  out << '}' << '\n';
  out << '\n';
}

/*******************************************************************\

Function: java_bytecode_parse_treet::membert::output

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void java_bytecode_parse_treet::membert::output(std::ostream &out) const
{
  out << "  ";

  if(is_public)
    out << "public ";
  
  if(is_static)
    out << "static ";
  
  if(is_native)
    out << "native ";
  
  out << name;
  out << " : " << signature;

  if(is_method)
  {
    out << '\n';

    out << "  {" << '\n';

    for(instructionst::const_iterator
        i_it=instructions.begin();
        i_it!=instructions.end();
        i_it++)
    {
      if(i_it->source_location.get_line()!=irep_idt())
        out << "    // " << i_it->source_location << '\n';

      out << "    " << i_it->address << ": ";
      out << i_it->statement;
      
      for(std::vector<exprt>::const_iterator
          a_it=i_it->args.begin(); a_it!=i_it->args.end(); a_it++)
      {
        if(a_it!=i_it->args.begin()) out << ',';
        #if 0
        out << ' ' << from_expr(*a_it);
        #else
        out << ' ' << *a_it;
        #endif
      }

      out << '\n';
    }

    out << "  }" << '\n';
  }
  else
  {
    out << ';';
  }

  out << '\n';
}
