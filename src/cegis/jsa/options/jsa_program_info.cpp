#include <util/bv_arithmetic.h>
#include <util/symbol_table.h>
#include <util/std_types.h>

#include <cegis/jsa/value/jsa_genetic_synthesis.h>
#include <cegis/jsa/options/jsa_program_info.h>

size_t get_size(const symbol_tablet &st, const char * const id)
{
  const bv_arithmetict bv(to_array_type(st.lookup(id).type).size());
  return bv.to_integer().to_long();
}

#define PRED_RELAY "__CPROVER_JSA_MAX_PRED_SIZE_RELAY"

size_t get_max_pred_size(const symbol_tablet &st)
{
  return get_size(st, PRED_RELAY);
}

#define QUERY_RELAY "__CPROVER_JSA_MAX_QUERY_SIZE_RELAY"

size_t get_max_query_size(const symbol_tablet &st)
{
  return get_size(st, QUERY_RELAY);
}

size_t get_pred_instruction_set_size()
{
  return __CPROVER_JSA_NUM_PRED_INSTRUCTIONS;
}

size_t get_query_instruction_set_size()
{
  return __CPROVER_JSA_NUM_QUERY_INSTRUCTIONS;
}

size_t get_num_jsa_preds(const symbol_tablet &st)
{
  return get_size(st, JSA_PREDS);
}
