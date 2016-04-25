#include <ansi-c/c_types.h>
#include <util/symbol_table.h>

#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/value/jsa_types.h>

typet jsa_word_type()
{
  return unsigned_char_type();
}

typet jsa_internal_index_type()
{
  return jsa_word_type();
}

#define PRED_INSTR_TYPE "tag-__CPROVER_jsa_pred_instruction"
const typet &jsa_predicate_instruction_type(const symbol_tablet &st)
{
  return st.lookup(PRED_INSTR_TYPE).type;
}

array_typet jsa_predicate_type(const symbol_tablet &st, const exprt &size)
{
  return array_typet(jsa_predicate_instruction_type(st), size);
}

#define INV_INSTR_TYPE "tag-__CPROVER_jsa_invariant_instruction"
const typet &jsa_invariant_instruction_type(const symbol_tablet &st)
{
  return st.lookup(INV_INSTR_TYPE).type;
}

array_typet jsa_invariant_type(const symbol_tablet &st, const exprt & size)
{
  return array_typet(jsa_invariant_instruction_type(st), size);
}

#define QUERY_INSTR_TYPE "tag-__CPROVER_jsa_query_instruction"
const typet &jsa_query_instruction_type(const symbol_tablet &st)
{
  return st.lookup(QUERY_INSTR_TYPE).type;
}

array_typet jsa_query_type(const symbol_tablet &st, const exprt &size)
{
  return array_typet(jsa_query_instruction_type(st), size);
}

const typet &jsa_heap_type(const symbol_tablet &st)
{
  return st.lookup(JSA_HEAP_TAG).type;
}
