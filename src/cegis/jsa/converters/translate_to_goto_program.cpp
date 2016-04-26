#include <cegis/invariant/util/copy_instructions.h>
#include <cegis/instructions/instruction_set_factory.h>
#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/converters/replace_operators.h>
#include <cegis/jsa/converters/translate_to_goto_program.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

#define PRED_SINGLE JSA_PREFIX "pred_opcode_"
#define PRED_FIRST JSA_PREFIX "pred_opcode_first_"
#define PRED_LAST JSA_PREFIX "pred_opcode_last_"

namespace
{
instruction_sett get_instruction_set(const goto_functionst &gf,
    const char * const func, const char * const first,
    const char * const last, const char * const single)
{
  const goto_functionst::function_mapt &fm=gf.function_map;
  const goto_functionst::function_mapt::const_iterator it=fm.find(func);
  assert(fm.end() != it);
  const goto_functionst::goto_functiont &function=it->second;
  assert(function.body_available());
  return extract_instruction_set(function.body, first, last, single);
}

instruction_sett get_pred_instruction_set(const goto_functionst &gf)
{
  return get_instruction_set(gf, JSA_PRED_EXEC, PRED_FIRST, PRED_LAST, PRED_SINGLE);
}
}

goto_programt::instructionst convert(const jsa_programt &prog,
    const pred_op_idst &pred_ops, const pred_op_idst &result_pred_ops,
    const std::vector<__CPROVER_jsa_pred_instructiont> &solution)
{
  const instruction_sett instr_set(get_pred_instruction_set(prog.gf));
  goto_programt::instructionst result;
  copy_instructionst copy;
  for (const __CPROVER_jsa_pred_instructiont &instr : solution)
  {
    const instruction_sett::const_iterator it=instr_set.find(instr.opcode);
    assert(instr_set.end() != it);
    copy(result, it->second);
  }
  copy.finalize();
  replace_pred_ops(result, pred_ops, result_pred_ops);

  // XXX: Debug
  const namespacet ns(prog.st);
  goto_programt tmp;
  tmp.instructions=result;
  tmp.compute_incoming_edges();
  tmp.compute_target_numbers();
  tmp.output(ns, "", std::cout);
  assert(false);
  // XXX: Debug
  return result;
}
