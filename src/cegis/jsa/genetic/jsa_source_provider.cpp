#include <util/options.h>
#include <goto-programs/remove_returns.h>
#include <goto-instrument/dump_c.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/jsa/learn/jsa_symex_learn.h>
#include <cegis/jsa/genetic/jsa_source_provider.h>

jsa_source_providert::jsa_source_providert(const optionst &options,
    jsa_symex_learnt &lcfg) :
    options(options), lcfg(lcfg)
{
}

#include <iostream> // XXX: Debug

#define START_METHOD_PREFIX "void _start"
#define RETURN_VALUE_ASSIGNMENT "#return_value ="

namespace
{
std::string generate_main_body(const jsa_symex_learnt &lcfg)
{
  const goto_functionst &gf=lcfg.get_goto_functions();
  const goto_functionst::function_mapt &fm=gf.function_map;
  goto_functionst entry_only;
  const irep_idt entry_id(goto_functionst::entry_point());
  const goto_functionst::function_mapt::const_iterator it=fm.find(entry_id);
  entry_only.function_map[entry_id].copy_from(it->second);
  const namespacet ns(lcfg.get_symbol_table());
  std::ostringstream oss;
  dump_c(entry_only, false, ns, oss);
  std::string main_body(oss.str());
  main_body=main_body.substr(main_body.find(START_METHOD_PREFIX));
  return main_body;
}

void fix_return_values(std::string &result)
{
  std::string::size_type pos=result.find(RETURN_VALUE_ASSIGNMENT);
  while (std::string::npos != pos)
  {
    const std::string::size_type start=result.rfind(' ', pos);
    const std::string::size_type value=result.find('=', pos);
    const std::string::size_type end=result.find(';', pos);
    std::string return_statement=" return";
    return_statement+=result.substr(value + 1, end - value);
    result.replace(start, end, return_statement);
    pos=result.find(RETURN_VALUE_ASSIGNMENT, start);
  }
}
}

const std::string &jsa_source_providert::operator ()()
{
  if (!source.empty()) return source;
  const std::string main_body(generate_main_body(lcfg));
  source="#include \"jsa.h\"\n\n";
  source+=main_body;
  fix_return_values(source);
// XXX: Debug
  std::cout << source << std::endl;
  assert(!"TODO: Implement");
// XXX: Debug
// TODO: Implement!
  return source;
}
