#include <util/options.h>
#include <goto-programs/goto_inline.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/instrument/literals.h>
#include <cegis/instrument/cegis_library.h>
#include <cegis/instrument/instrument_var_ops.h>
#include <cegis/constant/default_cegis_constant_strategy.h>
#include <cegis/bjc/preprocessing/bjc_query_factory.h>
#include <cegis/bjc/preprocessing/bjc_preprocessing.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

bjc_preprocessingt::bjc_preprocessingt(optionst &options,
    const symbol_tablet &st, const goto_functionst &gf) :
    options(options), original_program(st, gf), num_consts(0)
{
}

bjc_preprocessingt::~bjc_preprocessingt()
{
}

namespace
{
const char LAMBDA_OPERATOR_NAME[]="__CPROVER_cegis_lambda_op";
const size_t LAMBDA_OPERATOR_ID=0u;

bool int_list_filter(const irep_idt &id, const typet &type)
{
  if (!is_instrumentable_user_variable(id, type)) return false;
  const irep_idt &type_id=type.id();
  return ID_signedbv == type_id || ID_unsignedbv == type_id;
}

std::string find_refactored_loop_id(goto_programt &body)
{
  body.compute_loop_numbers();
  std::string loop_id("main.");
  for (const goto_programt::instructiont instr : body.instructions)
    if (instr.is_backwards_goto()
        && instr.source_location.get_function() == "main") return loop_id+=
        std::to_string(instr.loop_number);
  assert(!"Refactored loop not found.");
}
}

void bjc_preprocessingt::operator ()()
{
  symbol_tablet &st=original_program.st;
  const namespacet ns(st);
  null_message_handlert msg;
  goto_functionst &gf=original_program.gf;
  goto_inline(gf, ns, msg);
  goto_programt &body=get_entry_body(gf);

  default_cegis_constant_strategy(st, gf);
  original_program.ce_targets=find_nondet_instructions(body);
  var_ids.insert(std::make_pair(LAMBDA_OPERATOR_NAME, LAMBDA_OPERATOR_ID));
  num_consts=get_variable_op_ids(st, var_ids, &int_list_filter);
  original_program.refactored_loop_id=find_refactored_loop_id(body);
}

void bjc_preprocessingt::operator ()(const size_t max_length)
{
  current_program=original_program;
  symbol_tablet &st=current_program.st;
  goto_functionst &gf=current_program.gf;
  null_message_handlert msg;
  const std::string name(CEGIS_EXECUTE);
  const size_t num_vars=var_ids.size();
  add_cegis_library(st, gf, msg, num_vars, num_consts, max_length, name);
  operand_idst instr(var_ids);
  instr.erase(LAMBDA_OPERATOR_NAME);

  goto_programt::instructionst &instrs=get_entry_body(gf).instructions;
  link_user_program_variable_ops(st, gf, instr, &int_list_filter,
      instrs.begin(), instrs.end());
  add_bjc_query(current_program, num_vars, num_consts, max_length);
  const size_t max_list_size=5u;
  std::string unwind_set(current_program.refactored_loop_id);
  unwind_set+=':';
  unwind_set+=std::to_string(max_list_size);
  unwind_set+=",__CPROVER_danger_execute.0";
  unwind_set+=':';
  unwind_set+=std::to_string(max_length);
  // XXX: Debug
  std::cout << "<unwindset>" << unwind_set << "</unwindset>" << std::endl;
  options.set_option("unwinding-assertions", true);
  // XXX: Debug
  options.set_option("unwindset", unwind_set);
}

size_t bjc_preprocessingt::get_min_solution_size() const
{
// XXX: Allow empty queries?
  return 2;
}

const bjc_programt &bjc_preprocessingt::get_bjc_program() const
{
  return current_program;
}
