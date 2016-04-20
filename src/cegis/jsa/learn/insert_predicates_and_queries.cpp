#include <ansi-c/c_types.h>
#include <util/arith_tools.h>
#include <util/bv_arithmetic.h>
#include <util/expr_util.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/instrument/meta_variables.h>

#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/value/jsa_types.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/preprocessing/add_constraint_meta_variables.h>
#include <cegis/jsa/learn/insert_predicates_and_queries.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

#define PREDS "__CPROVER_JSA_PREDICATES"
#define PRED_SIZES "__CPROVER_JSA_PREDICATE_SIZES"
#define LOCAL_PRED "__CPROVER_jsa_predicate_"
#define LOCAL_SIZE_SUFFIX "_size"

void declare_jsa_predicates(jsa_programt &prog, const size_t max_size)
{
  symbol_tablet &st=prog.st;
  goto_functionst &gf=prog.gf;
  const constant_exprt max_expr(from_integer(max_size, signed_int_type()));
  const symbol_exprt preds(st.lookup(PREDS).symbol_expr());
  const symbol_exprt pred_sizes(st.lookup(PRED_SIZES).symbol_expr());
  const bv_arithmetict bv(to_array_type(preds.type()).size());
  const mp_integer::ullong_t num_preds=bv.to_integer().to_ulong();
  const typet sz_type(signed_int_type());
  const exprt zero(gen_zero(sz_type));
  goto_programt &body=get_entry_body(gf);
  for (mp_integer::ullong_t i=0; i < num_preds; ++i)
  {
    goto_programt::targett &pos=prog.synthetic_variables;
    pos=body.insert_after(pos);
    std::string base_name(LOCAL_PRED);
    base_name+=std::to_string(i);
    const std::string size_name(base_name + LOCAL_SIZE_SUFFIX);
    declare_jsa_meta_variable(st, pos, size_name, jsa_internal_index_type());
    const irep_idt &size_id=get_affected_variable(*pos);
    const symbol_exprt sz_expr(st.lookup(size_id).symbol_expr());
    pos=body.insert_after(pos);
    pos->source_location=jsa_builtin_source_location();
    pos->type=goto_program_instruction_typet::ASSUME;
    const binary_relation_exprt size_limit(sz_expr, ID_le, max_expr);
    pos->guard=size_limit;
    pos=body.insert_after(pos);
    declare_jsa_meta_variable(st, pos, base_name, jsa_predicate_type(sz_expr));
    const constant_exprt index(from_integer(i, sz_type));
    const index_exprt preds_elem(preds, index);
    const std::string local_pred_name(get_cegis_meta_name(base_name));
    const symbol_exprt &local_pred(st.lookup(local_pred_name).symbol_expr());
    const index_exprt local_preds_elem(local_pred, zero);
    pos=jsa_assign(st, gf, pos, preds_elem, address_of_exprt(local_preds_elem));
    const index_exprt pred_sizes_elem(pred_sizes, index);
    pos=jsa_assign(st, gf, pos, pred_sizes_elem, sz_expr);
  }
}

void declare_jsa_queries(jsa_programt &prog, size_t max_size)
{
  // XXX: Debug
  std::cout << "<jsa_symex_verifyt>" << std::endl;
  const namespacet ns(prog.st);
  prog.gf.output(ns, std::cout);
  std::cout << "</jsa_symex_verifyt>" << std::endl;
  assert(false);
  // XXX: Debug
}
