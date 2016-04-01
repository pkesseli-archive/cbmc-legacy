#include <cegis/jsa/options/jsa_program.h>

jsa_programt::jsa_programt()
{
}

jsa_programt::jsa_programt(const jsa_programt &other) :
    safety(other.safety)
{
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
  return *this;
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
