#include <algorithm>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/instrument/meta_variables.h>
#include <cegis/invariant/util/invariant_program_helper.h>
#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/value/jsa_types.h>
#include <cegis/jsa/preprocessing/add_constraint_meta_variables.h>
#include <cegis/jsa/preprocessing/clone_heap.h>

namespace
{
bool is_heap_type(const typet &type)
{
  if (ID_symbol != type.id()) return false;
  return to_symbol_type(type).get_identifier() == JSA_HEAP_TAG;
}

bool is_heap(const goto_programt::instructiont &instr)
{
  if (goto_program_instruction_typet::DECL != instr.type) return false;
  return is_heap_type(to_code_decl(instr.code).symbol().type());
}
}

const symbol_exprt &get_user_heap(const goto_functionst &gf)
{
  const goto_programt::instructionst &i=get_entry_body(gf).instructions;
  const goto_programt::const_targett end(i.end());
  const goto_programt::const_targett p=std::find_if(i.begin(), end, is_heap);
  assert(end != p);
  return to_symbol_expr(to_code_decl(p->code).symbol());
}

symbol_exprt get_queried_heap(const symbol_tablet &st)
{
  return st.lookup(get_cegis_meta_name(JSA_QUERIED_HEAP)).symbol_expr();
}

symbol_exprt get_org_heap(const symbol_tablet &st)
{
  return st.lookup(get_cegis_meta_name(JSA_ORG_HEAP)).symbol_expr();
}

void clone_heap(jsa_programt &prog)
{
  symbol_tablet &st=prog.st;
  goto_functionst &gf=prog.gf;
  goto_programt &body=get_entry_body(gf);
  goto_programt::targett pos=prog.base_case;
  pos=insert_before_preserve_labels(body, pos);
  const symbol_typet heap_type(jsa_heap_type());
  declare_jsa_meta_variable(st, pos, JSA_QUERIED_HEAP, heap_type);
  jsa_assign(st, gf, pos, get_queried_heap(st), get_user_heap(gf));
  pos=insert_before_preserve_labels(body, prog.inductive_assumption);
  declare_jsa_meta_variable(st, pos, JSA_ORG_HEAP, heap_type);
  pos=jsa_assign(st, gf, pos, get_org_heap(st), get_user_heap(gf));
  jsa_assign(st, gf, pos, get_queried_heap(st), get_org_heap(st));
  pos=std::prev(prog.inductive_step);
  pos=jsa_assign(st, gf, pos, get_queried_heap(st), get_org_heap(st));
  move_labels(body, prog.inductive_step, pos);
}
