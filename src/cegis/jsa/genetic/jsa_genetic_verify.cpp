#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/converters/counterexample.h>
#include <cegis/jsa/converters/solution.h>
#include <cegis/jsa/verify/jsa_symex_verify.h>
#include <cegis/jsa/genetic/jsa_genetic_verify.h>

jsa_genetic_verifyt::jsa_genetic_verifyt(jsa_symex_verifyt &verify) :
    verify(verify)
{
}

void jsa_genetic_verifyt::process(const candidatet &candidate)
{
  verify.process(candidate);
}

const symbol_tablet &jsa_genetic_verifyt::get_symbol_table() const
{
  return verify.get_symbol_table();
}

const goto_functionst &jsa_genetic_verifyt::get_goto_functions() const
{
  return verify.get_goto_functions();
}

void jsa_genetic_verifyt::convert(counterexamplest &counterexamples,
    const goto_tracet &trace)
{
  jsa_symex_verifyt::counterexamplest ces;
  verify.convert(ces, trace);
  assert(!ces.empty());
  counterexamples.push_back(::convert(ces.front()));
}

void jsa_genetic_verifyt::show_counterexample(messaget::mstreamt &os,
    const counterexamplet &counterexample) const
{
  verify.show_counterexample(os, ::convert(get_symbol_table(), counterexample));
}
