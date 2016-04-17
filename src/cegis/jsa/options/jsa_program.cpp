#include <cegis/invariant/options/target_copy_helper.h>
#include <cegis/cegis-util/program_helper.h>
#include <cegis/jsa/options/jsa_program.h>

jsa_programt::jsa_programt()
{
}

namespace
{
jsa_programt &assign(jsa_programt &lhs, const jsa_programt &rhs)
{
  goto_programt &new_body=get_entry_body(lhs.get_gf());
  const goto_programt &old_body=get_entry_body(rhs.get_gf());
  const target_copy_helpert copy(old_body, new_body);
  copy(lhs.input_locations, rhs.input_locations);
  return lhs;
}
}

jsa_programt::jsa_programt(const jsa_programt &other) :
    safety(other.safety)
{
  assign(*this, other);
}

jsa_programt::jsa_programt(const symbol_tablet &st, const goto_functionst &gf) :
    safety(st, gf)
{
}

jsa_programt::~jsa_programt()
{
}

jsa_programt &jsa_programt::operator =(const jsa_programt &other)
{
  safety=other.safety;
  return assign(*this, other);
}

symbol_tablet &jsa_programt::get_st()
{
  return safety.st;
}

const symbol_tablet &jsa_programt::get_st() const
{
  return safety.st;
}

goto_functionst &jsa_programt::get_gf()
{
  return safety.gf;
}

const goto_functionst &jsa_programt::get_gf() const
{
  return safety.gf;
}
