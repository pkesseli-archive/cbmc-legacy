#include <ansi-c/c_types.h>

#include <cegis/jsa/value/jsa_types.h>

typet jsa_word_type()
{
  return unsigned_char_type();
}

#define PRED_INSTR_TYPE "tag-__CPROVER_jsa_pred_instruction"
symbol_typet jsa_predicate_instruction_type()
{
  return symbol_typet(PRED_INSTR_TYPE);
}

array_typet jsa_predicate_type(const exprt &size)
{
  return array_typet(jsa_predicate_instruction_type(), size);
}

#define QUERY_INSTR_TYPE "tag-__CPROVER_jsa_query_instruction"
symbol_typet jsa_query_instruction_type()
{
  return symbol_typet(QUERY_INSTR_TYPE);
}

array_typet jsa_query_type(const exprt &size)
{
  return array_typet(jsa_query_instruction_type(), size);
}
