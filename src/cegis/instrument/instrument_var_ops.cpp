#include <util/arith_tools.h>
#include <ansi-c/c_types.h>

#include <goto-programs/goto_functions.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/instrument/literals.h>
#include <cegis/instrument/instrument_var_ops.h>

namespace
{
void link_user_symbols(const symbol_tablet &st,
    invariant_variable_idst &var_ids, size_t &variable_id, bool consts,
    const is_op_variablet is_op_variable)
{
  typedef symbol_tablet::symbolst symbolst;
  const symbolst &symbols=st.symbols;
  for (symbolst::const_iterator it=symbols.begin(); it != symbols.end(); ++it)
  {
    const symbolt &symbol=it->second;
    if (!is_op_variable(symbol.name, symbol.type)) continue;
    const bool is_const=is_global_const(symbol.name, symbol.type);
    if (is_const == consts)
      var_ids.insert(std::make_pair(symbol.name, variable_id++));
  }
}
}

size_t get_variable_op_ids(const symbol_tablet &st,
    invariant_variable_idst &ids, const is_op_variablet is_op_variable)
{
  size_t variable_id=0;
  link_user_symbols(st, ids, variable_id, true, is_op_variable);
  const size_t num_consts=ids.size();
  link_user_symbols(st, ids, variable_id, false, is_op_variable);
  return num_consts;
}

namespace
{
bool default_variable_filter(const irep_idt &id, const typet &type)
{
  // TODO: Implement
  return false;
}
}

size_t get_variable_op_ids(const symbol_tablet &st,
    invariant_variable_idst &ids)
{
  return get_variable_op_ids(st, ids, &default_variable_filter);
}

namespace
{
null_pointer_exprt get_null()
{
  const pointer_typet void_pointer_type=pointer_typet(void_typet());
  return null_pointer_exprt(void_pointer_type);
}
}

void link_user_program_variable_ops(const symbol_tablet &st,
    class goto_functionst &gf, const invariant_variable_idst &var_ids,
    const is_op_variablet is_op_variable, goto_programt::targett begin,
    goto_programt::targett end)
{
  invariant_variable_idst to_instrument(var_ids);
  goto_programt &body=get_entry_body(gf);
  goto_programt::instructionst &instrs=body.instructions;
  for (goto_programt::targett it=instrs.begin(); it != end; ++it)
  {
    goto_programt::instructiont &instr=*it;
    const goto_program_instruction_typet type=instr.type;
    if (DECL != type && DEAD != type) continue;
    const irep_idt &name=get_affected_variable(instr);
    if (!is_op_variable(name, typet())) continue;
    const invariant_variable_idst::const_iterator id=var_ids.find(name);
    if (DEAD == type) set_ops_reference(st, body, it, get_null(), id->second);
    else
    {
      set_ops_reference(st, body, it, name, id->second);
      to_instrument.erase(id->first);
    }
  }
  goto_programt::targett pos=begin;
  if (pos != instrs.begin()) --pos;
  typedef invariant_variable_idst::const_iterator itt;
  const itt first=to_instrument.begin();
  for (itt it=first; it != to_instrument.end(); ++it)
  {
    pos=set_ops_reference(st, body, pos, it->first, it->second);
    if (first == it) move_labels(body, begin, pos);
  }
}

goto_programt::targett set_ops_reference(const symbol_tablet &st,
    goto_programt &body, const goto_programt::targett &pos,
    const char * const ops_array, const exprt &rhs, const unsigned int id)
{
  const goto_programt::targett target=body.insert_after(pos);
  goto_programt::instructiont &set_op=*target;
  set_op.type=ASSIGN;
  set_op.source_location=default_cegis_source_location();
  const constant_exprt index(from_integer(id, unsigned_int_type()));
  const symbol_exprt ops(st.lookup(ops_array).symbol_expr());
  const index_exprt op(ops, index);
  set_op.code=code_assignt(op, rhs);
  return target;
}

goto_programt::targett set_ops_reference(const symbol_tablet &st,
    goto_programt &body, const goto_programt::targett &pos,
    const char * const ops_array, const irep_idt &name, const unsigned int id)
{
  const symbol_exprt rhs(st.lookup(name).symbol_expr());
  return set_ops_reference(st, body, pos, ops_array, address_of_exprt(rhs), id);
}

goto_programt::targett set_ops_reference(const symbol_tablet &st,
    goto_programt &body, const goto_programt::targett &pos, const exprt &rhs,
    const unsigned int id)
{
  return set_ops_reference(st, body, pos, CEGIS_OPS, rhs, id);
}

goto_programt::targett set_ops_reference(const symbol_tablet &st,
    goto_programt &body, const goto_programt::targett &pos,
    const irep_idt &name, const unsigned int id)
{
  return set_ops_reference(st, body, pos, CEGIS_OPS, name, id);
}

source_locationt default_cegis_source_location()
{
  source_locationt loc;
  loc.set_file(CEGIS_MODULE);
  loc.set_function(goto_functionst::entry_point());
  return loc;
}
