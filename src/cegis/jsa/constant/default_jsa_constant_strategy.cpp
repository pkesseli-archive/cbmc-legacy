#include <util/arith_tools.h>

#include <cegis/constant/literals_collector.h>
#include <cegis/instrument/meta_variables.h>
#include <cegis/cegis-util/program_helper.h>
#include <cegis/jsa/value/jsa_types.h>
#include <cegis/jsa/constant/default_jsa_constant_strategy.h>

namespace
{
const char CONSTANT_PREFIX[]="JSA_CONSTANT_";
std::string get_name(size_t index)
{
  std::string name(CONSTANT_PREFIX);
  return name+=integer2string(index);
}
}

void default_jsa_constant_strategy(symbol_tablet &st, goto_functionst &gf)
{
  const std::vector<constant_exprt> literals(collect_integer_literals(st, gf));
  const typet word_type(jsa_word_type());
  size_t const_index=0u;
  goto_programt::targett pos=get_entry_body(gf).instructions.begin();
  for (const constant_exprt &expr : literals)
  {
    mp_integer value;
    to_integer(expr, value);
    const constant_exprt expr_value(from_integer(value, word_type));
    const std::string base_name(get_name(const_index++));
    pos=declare_cegis_meta_variable(st, gf, pos, base_name, expr_value.type());
    pos=assign_cegis_meta_variable(st, gf, pos, base_name, expr_value);
  }
}
