#include <goto-programs/goto_inline.h>
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
  const namespacet ns(original_program.st);
  null_message_handlert msg;
  goto_functionst &gf=original_program.gf;
  goto_inline(gf, ns, msg);
}

void bjc_preprocessingt::operator ()(const size_t max_length)
{
}

size_t bjc_preprocessingt::get_min_solution_size() const
{
  // XXX: Allow empty queries?
  return 0;
}

const bjc_programt &bjc_preprocessingt::get_bjc_program() const
{
  return current_program;
}
