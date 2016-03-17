#include <goto-programs/goto_functions.h>

#include <cegis/cegis-util/program_helper.h>

goto_programt &get_entry_body(goto_functionst &gf)
{
  const irep_idt id(goto_functionst::entry_point());
  goto_functionst::function_mapt &function_map=gf.function_map;
  const goto_functionst::function_mapt::iterator it=function_map.find(id);
  assert(function_map.end() != it && "Danger program function missing.");
  goto_function_templatet<goto_programt> &f=it->second;
  assert(f.body_available() && "Danger program function body missing.");
  return f.body;
}

const goto_programt &get_entry_body(const goto_functionst &gf)
{
  const irep_idt id(goto_functionst::entry_point());
  const goto_functionst::function_mapt &function_map=gf.function_map;
  const goto_functionst::function_mapt::const_iterator it=function_map.find(id);
  assert(function_map.end() != it && "Danger program function missing.");
  const goto_function_templatet<goto_programt> &f=it->second;
  assert(f.body_available() && "Danger program function body missing.");
  return f.body;
}
