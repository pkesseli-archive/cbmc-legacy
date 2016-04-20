#include <ansi-c/c_types.h>
#include <util/arith_tools.h>
#include <util/type_eq.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/jsa/value/jsa_types.h>
#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/preprocessing/add_constraint_meta_variables.h>
#include <cegis/jsa/learn/instrument_pred_ops.h>

namespace
{
bool contains(const std::string &haystack, const char * const needle)
{
  return std::string::npos != haystack.find(needle);
}

bool is_pred_op_decl(const symbol_tablet &st, const goto_programt::targett &pos)
{
  if (goto_program_instruction_typet::DECL != pos->type) return false;
  const std::string &id=id2string(get_affected_variable(*pos));
  if (contains(id, JSA_TMP_PREFIX) || contains(id, JSA_LAMBDA_OP)) return true;
  if (contains(id, CPROVER_PREFIX)) return false;
  const namespacet ns(st);
  const typet lhs(jsa_word_type());
  return type_eq(lhs, st.lookup(id).type, ns);
}
}

goto_programt::targetst collect_pred_ops(jsa_programt &prog)
{
  const symbol_tablet &st=prog.st;
  goto_programt::instructionst &body=get_entry_body(prog.gf).instructions;
  const goto_programt::targett end(prog.body.first);
  goto_programt::targetst pred_ops;
  for (goto_programt::targett it=body.begin(); it != end; ++it)
    if (is_pred_op_decl(st, it)) pred_ops.push_back(it);
  return pred_ops;
}

#define PRED_OPS "__CPROVER_JSA_PRED_OPS"
#define PRED_RES_OPS "__CPROVER_JSA_PRED_RESULT_OPS"

namespace
{
bool is_const(const symbol_exprt &symbol)
{
  const std::string &id=id2string(symbol.get_identifier());
  if (std::string::npos != id.find(JSA_CONSTANT_PREFIX)) return true;
  return symbol.type().get_bool(ID_C_constant);
}
}

std::map<size_t, symbol_exprt> instrument_pred_ops(jsa_programt &prog,
    const goto_programt::targetst &ops)
{
  const symbol_tablet &st=prog.st;
  goto_functionst &gf=prog.gf;
  const symbol_exprt pred_ops(st.lookup(PRED_OPS).symbol_expr());
  const symbol_exprt pred_res_ops(st.lookup(PRED_RES_OPS).symbol_expr());
  const typet sz_type(signed_int_type());
  size_t op_index=0;
  size_t res_op_idx=0;
  std::map<size_t, symbol_exprt> result;
  for (goto_programt::targett op : ops)
  {
    const bool is_synth_begin=op == prog.synthetic_variables;
    const symbol_exprt var(st.lookup(get_affected_variable(*op)).symbol_expr());
    const constant_exprt op_index_expr(from_integer(op_index++, sz_type));
    const index_exprt op_elem(pred_ops, op_index_expr);
    op=jsa_assign(st, gf, op, op_elem, address_of_exprt(var));
    if (!is_const(var))
    {
      const constant_exprt res_op_idx_expr(from_integer(res_op_idx++, sz_type));
      const index_exprt res_op_elem(pred_res_ops, res_op_idx_expr);
      op=jsa_assign(st, gf, op, res_op_elem, address_of_exprt(var));
    }
    if (is_synth_begin) prog.synthetic_variables=op;
  }
  return result;
}
