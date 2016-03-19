#include <goto-programs/goto_inline.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/instrument/cegis_library.h>
#include <cegis/bjc/preprocessing/bjc_preprocessing.h>

bjc_preprocessingt::bjc_preprocessingt(const optionst &options,
    const symbol_tablet &st, const goto_functionst &gf) :
    options(options), original_program(st, gf)
{
}

bjc_preprocessingt::~bjc_preprocessingt()
{
}

void bjc_preprocessingt::operator ()()
{
  symbol_tablet &st=original_program.st;
  const namespacet ns(st);
  null_message_handlert msg;
  goto_functionst &gf=original_program.gf;
  goto_inline(gf, ns, msg);
  goto_programt &body=get_entry_body(gf);
  original_program.ce_targets=find_nondet_instructions(body);
  // TODO: Instrument vars (OPS, ROPS)
  // TODO: add_cegis_library(st, gf, msg, )
}

void bjc_preprocessingt::operator ()(const size_t max_length)
{
  current_program=original_program;
  // TODO: Add query declaration
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
