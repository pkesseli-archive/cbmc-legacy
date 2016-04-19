#include <ansi-c/c_types.h>
#include <util/arith_tools.h>
#include <util/bv_arithmetic.h>

#include <cegis/cegis-util/program_helper.h>

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
  const bv_arithmetict bv(to_array_type(st.lookup(PREDS).type).size());
  const mp_integer::ullong_t num_preds=bv.to_integer().to_ulong();
  goto_programt &body=get_entry_body(gf);
  for (mp_integer::ullong_t i=0; i < num_preds; ++i)
  {
    goto_programt::targett &pos=prog.synthetic_variables;
    pos=body.insert_after(pos);
    std::string base_name(LOCAL_PRED);
    base_name+=std::to_string(i);
    const std::string size_name(base_name + LOCAL_SIZE_SUFFIX);
    declare_jsa_meta_variable(st, pos, size_name, signed_int_type());
    const irep_idt &size_id=get_affected_variable(*pos);
    const symbol_exprt sz_expr(st.lookup(size_id).symbol_expr());
    pos=body.insert_after(pos);
    pos->source_location=jsa_builtin_source_location();
    pos->type=goto_program_instruction_typet::ASSUME;
    const binary_relation_exprt size_limit(sz_expr, ID_le, max_expr);
    pos->guard=size_limit;
    pos=body.insert_after(pos);
    declare_jsa_meta_variable(st, pos, base_name, jsa_predicate_type(sz_expr));
  }
  //declare_jsa_meta_variable(st, pos, )

  // XXX: Debug
  std::cout << "<jsa_symex_verifyt>" << std::endl;
  const namespacet ns(prog.st);
  prog.gf.output(ns, std::cout);
  std::cout << "</jsa_symex_verifyt>" << std::endl;
  assert(false);
  // XXX: Debug
}
