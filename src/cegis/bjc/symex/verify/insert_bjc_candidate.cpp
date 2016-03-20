#include <ansi-c/c_types.h>
#include <util/expr_util.h>

#include <cegis/instrument/literals.h>
#include <cegis/cegis-util/program_helper.h>
#include <cegis/bjc/options/bjc_program.h>
#include <cegis/bjc/symex/verify/insert_bjc_candidate.h>

namespace
{
bool is_initialised(const goto_programt::targett &target)
{
  return target != goto_programt::targett();
}

array_exprt empty_candidate()
{
  const exprt sz=gen_zero(unsigned_int_type());
  array_typet type(symbol_typet(CEGIS_INSTRUCTION_TYPE_NAME), sz);
  return array_exprt(type);
}
}

void insert_bjc_candidate(bjc_programt &prog, const candidatet &candidate)
{
  //if (candidate.is_nil()) return insert_bjc_candidate(prog, empty_candidate());
  if (candidate.is_nil()) return;
  const goto_programt::targett &decl=prog.query_decl;
  assert(is_initialised(decl));
  const irep_idt &id=get_affected_variable(*decl);
  cegis_assign_user_variable(prog.st, prog.gf, decl, id, candidate);
}
