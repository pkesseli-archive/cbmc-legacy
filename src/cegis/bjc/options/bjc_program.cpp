#include <cegis/cegis-util/iterator_helper.h>
#include <cegis/cegis-util/program_helper.h>
#include <cegis/bjc/options/bjc_program.h>

bjc_programt::bjc_programt()
{
}

bjc_programt::bjc_programt(const symbol_tablet &st, const goto_functionst &gf) :
    st(st)
{
  this->gf.copy_from(gf);
}

namespace
{
bjc_programt &assign(bjc_programt &lhs, const bjc_programt &rhs)
{
  lhs.gf.copy_from(rhs.gf);
  goto_programt::instructionst &lbody=get_entry_body(lhs.gf).instructions;
  const goto_programt::instructionst &rbody=get_entry_body(rhs.gf).instructions;
  lhs.query_decl=copy_iterator(rbody, lbody, rhs.query_decl);
  lhs.ce_targets=copy_iterators(rbody, lbody, lhs.ce_targets);
  return lhs;
}
}

bjc_programt::bjc_programt(const bjc_programt &other) :
    st(other.st)
{
  assign(*this, other);
}

bjc_programt::~bjc_programt()
{
}

bjc_programt& bjc_programt::operator =(const bjc_programt &other)
{
  st=other.st;
  return assign(*this, other);
}
