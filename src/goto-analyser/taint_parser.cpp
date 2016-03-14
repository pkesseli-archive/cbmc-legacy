/*******************************************************************\

Module: Taint Parser

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <ostream>

#include <json/json_parser.h>

#include "taint_parser.h"

/*******************************************************************\

Function: taint_parser

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

bool taint_parser(
  const std::string &file_name,
  taint_parse_treet &dest,
  message_handlert &message_handler)
{
  jsont json;

  if(parse_json(file_name, message_handler, json))
  {
    messaget message(message_handler);
    message.error() << "taint file is not a valid json file"
                    << messaget::eom;
    return true;
  }

  if(!json.is_array())
  {
    messaget message(message_handler);
    message.error() << "expecting an array in the taint file, but got "
                    << json << messaget::eom;
    return true;
  }
  
  for(jsont::arrayt::const_iterator
      it=json.array.begin();
      it!=json.array.end();
      it++)
  {
    if(!it->is_object())
    {
      messaget message(message_handler);
      message.error() << "expecting an array of objects in the taint file, but got "
                      << *it << messaget::eom;
      return true;
    }
    
    taint_parse_treet::entryt entry;
    
    const std::string kind=(*it)["kind"].value;
    const std::string function=(*it)["function"].value;
    const std::string where=(*it)["where"].value;
    const std::string taint=(*it)["taint"].value;
    const std::string message=(*it)["message"].value;
    
    if(kind=="source")
      entry.kind=taint_parse_treet::entryt::SOURCE;
    else if(kind=="sink")
      entry.kind=taint_parse_treet::entryt::SINK;
    else
    {
      messaget message(message_handler);
      message.error() << "taint entry must have \"kind\" which is \"source\" or \"sink\""
                      << messaget::eom;
      return true;
    }
    
    if(function.empty())
    {
      messaget message(message_handler);
      message.error() << "taint entry must have 'function'"
                      << messaget::eom;
      return true;
    }
    else
      entry.function_identifier=function;

    if(where=="return_value")
    {
      entry.where=taint_parse_treet::entryt::RETURN_VALUE;
    }
    else if(where=="this")
    {
      entry.where=taint_parse_treet::entryt::THIS;
    }
    else if(std::string(where, 0, 9)=="parameter")
    {
      entry.where=taint_parse_treet::entryt::PARAMETER;
    }
    else
    {
      messaget message(message_handler);
      message.error() << "taint entry must have \"where\""
                      << " which is \"return_value\" or \"this\" or \"parameter1\"..."
                      << messaget::eom;
      return true;
    }
    
    entry.taint=taint;
    entry.message=message;
    
    dest.entries.push_back(entry);
  }
  
  return false;
}

/*******************************************************************\

Function: taint_parse_treet::entryt::output

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void taint_parse_treet::entryt::output(std::ostream &out) const
{
  switch(kind)
  {
  case SOURCE: out << "SOURCE "; break;
  case SINK: out << "SINK "; break;
  }
  
  out << taint << " on ";
  
  switch(where)
  {
  case THIS: out << "this in " << function_identifier; break;
  case PARAMETER: out << "parameter " << parameter_number << " of " << function_identifier; break;
  case RETURN_VALUE: out << "return value of " << function_identifier; break;
  }
  
  out << '\n';
}

/*******************************************************************\

Function: taint_parse_treet::output

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void taint_parse_treet::output(std::ostream &out) const
{
  for(const auto & entry : entries)
    entry.output(out);
}

