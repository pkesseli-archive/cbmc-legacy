#include <cegis/bjc/symex/verify/bjc_symex_verify.h>

bjc_symex_verifyt::bjc_symex_verifyt(const bjc_programt &program) :
    original_program(program)
{
}

bjc_symex_verifyt::~bjc_symex_verifyt()
{
}

void bjc_symex_verifyt::process(const candidatet &candidate)
{
}

const symbol_tablet &bjc_symex_verifyt::get_symbol_table() const
{
  return program.st;
}

const goto_functionst &bjc_symex_verifyt::get_goto_functions() const
{
  return program.gf;
}

void bjc_symex_verifyt::convert(counterexamplest &counterexamples,
    const goto_tracet &trace)
{
}
