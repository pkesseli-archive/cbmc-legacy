#include <ansi-c/c_types.h>
#include <util/expr_util.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/instrument/meta_variables.h>
#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/preprocessing/clone_heap.h>
#include <cegis/jsa/learn/execute_jsa_programs.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

namespace
{
goto_programt::targett make_constraint_call(const symbol_tablet &st,
    goto_functionst &gf, goto_programt::targett pos,
    const char * const exec_name, const code_function_callt::argumentst &args)
{
  goto_programt &body=get_entry_body(gf);
  const symbol_exprt lhs(st.lookup(get_affected_variable(*pos)).symbol_expr());
  pos=body.insert_after(pos);
  pos->type=goto_program_instruction_typet::FUNCTION_CALL;
  pos->source_location=jsa_builtin_source_location();
  code_function_callt call;
  call.lhs()=lhs;
  call.function()=st.lookup(exec_name).symbol_expr();
  call.arguments()=args;
  pos->code=call;
  return pos;
}

address_of_exprt get_prog_param(const symbol_tablet &st,
    const char * const name)
{
  const symbol_exprt p(st.lookup(get_cegis_meta_name(name)).symbol_expr());
  return address_of_exprt(index_exprt(p, gen_zero(signed_int_type())));
}

goto_programt::targett make_constraint_call(const symbol_tablet &st,
    goto_functionst &gf, goto_programt::targett pos,
    const char * const exec_name, const char * const prog_name,
    const char * const sz_name, const bool use_clone=true)
{
  code_function_callt::argumentst args;
  if (use_clone) args.push_back(address_of_exprt(get_cloned_heap_variable(st)));
  else args.push_back(address_of_exprt(get_user_heap_variable(gf)));
  args.push_back(address_of_exprt(get_user_heap_variable(gf)));
  args.push_back(get_prog_param(st, prog_name));
  args.push_back(st.lookup(get_cegis_meta_name(sz_name)).symbol_expr());
  args.push_back(get_prog_param(st, JSA_QUERY));
  args.push_back(st.lookup(get_cegis_meta_name(JSA_QUERY_SZ)).symbol_expr());
  return make_constraint_call(st, gf, pos, exec_name, args);
}
}

#define EXEC_INV "__CPROVER_jsa_invariant_execute"
#define JSA_EXEC_POST "__CPROVER_jsa_postcondition_execute"
#define JSA_EXEC_QUERY "__CPROVER_jsa_query_execute"

void execute_jsa_learn_programs(jsa_programt &prog)
{
  const symbol_tablet &st=prog.st;
  goto_functionst &gf=prog.gf;
  goto_programt::targett pos=prog.base_case;
  pos=make_constraint_call(st, gf, pos, EXEC_INV, JSA_INV, JSA_INV_SZ, false);
  pos=prog.inductive_assumption;
  pos=make_constraint_call(st, gf, pos, EXEC_INV, JSA_INV, JSA_INV_SZ);
  pos=prog.inductive_step;
  pos=make_constraint_call(st, gf, pos, EXEC_INV, JSA_INV, JSA_INV_SZ);
  pos=prog.property_entailment;
  pos=make_constraint_call(st, gf, pos, JSA_EXEC_POST, JSA_POST, JSA_POST_SZ);

  // XXX: Debug
  std::cout << "<jsa_symex_verifyt>" << std::endl;
  const namespacet ns(prog.st);
  prog.gf.output(ns, std::cout);
  std::cout << "</jsa_symex_verifyt>" << std::endl;
  assert(false);
  // XXX: Debug
}
