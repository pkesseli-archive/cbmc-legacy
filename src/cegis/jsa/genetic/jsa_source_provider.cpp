#include <util/options.h>
#include <util/substitute.h>
#include <goto-programs/remove_returns.h>
#include <goto-instrument/dump_c.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/instrument/literals.h>
#include <cegis/jsa/options/jsa_program_info.h>
#include <cegis/jsa/learn/jsa_symex_learn.h>
#include <cegis/jsa/genetic/jsa_source_provider.h>

jsa_source_providert::jsa_source_providert(const optionst &options,
    jsa_symex_learnt &lcfg) :
    options(options), lcfg(lcfg)
{
}

// XXX: Debug
#include <iostream>
#include <cegis/jsa/value/jsa_genetic_solution.h>
// XXX: Debug

#define START_METHOD_PREFIX "void _start"
#define RETURN_VALUE_ASSIGNMENT RETURN_VALUE_SUFFIX" ="
#define JUMP_BUFFER "__CPROVER_jsa_jump_buffer"

namespace
{
void add_jsa_defines(std::string &result, const jsa_symex_learnt &lcfg)
{
  // TODO: Implement!
  result+="#define __CPROVER_assume(c) __CPROVER_jsa_assume(c)\n";
  result+="// TODO: Implement!";
}

void add_includes_and_globals(std::string &result)
{
  result+="#include <cegis/jsa/value/jsa_genetic_solution.h>\n\n";
  result+="jmp_buf " JUMP_BUFFER";\n\n";
}

void add_main_body(std::string &result, const jsa_symex_learnt &lcfg)
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
  const std::string main_body(oss.str());
  result+=main_body.substr(main_body.find(START_METHOD_PREFIX));
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
  pos=result.find(RETURN_VALUE_SUFFIX);
  while (std::string::npos != pos)
  {
    const std::string::size_type end=result.rfind("= ", pos);
    const std::string::size_type start=result.rfind(' ', end - 2);
    std::string var_name=result.substr(start + 1, end - start);
    var_name+=' ';
    const std::string::size_type prev_end=result.rfind('\n', start);
    const std::string::size_type prev_start=result.rfind("  ", prev_end);
    const std::string::size_type line_end=result.find('\n', prev_end + 1);
    result.erase(prev_end, line_end - prev_end);
    result.insert(prev_start + 2, var_name);
    pos=result.find(RETURN_VALUE_SUFFIX, prev_start);
  }
}

void add_facade_function(std::string &result)
{
  substitute(result, "void _start(void)",
      "int " CEGIS_FITNESS_TEST_FUNC"(const jsa_genetic_solutiont &solution)");
  const std::string::size_type pos=result.find("  __CPROVER_initialize();");
  result.insert(pos, "  if (!setjmp(" JUMP_BUFFER")) return EXIT_FAILURE;\n");
}

void remove_line_with(std::string &result, const std::string &value)
{
  const std::string::size_type pos=result.find(value);
  const std::string::size_type start=result.rfind('\n', pos);
  const std::string::size_type end=result.find('\n', pos);
  result.erase(start, end - start);
}

void remove_predicates(std::string &result, const size_t num_preds)
{
  for (size_t i=0; i < num_preds; ++i)
  {
    std::string base_name="__CPROVER_jsa_predicate_";
    base_name+=std::to_string(i);
    std::string size_var_name(base_name);
    size_var_name+="_size;";
    remove_line_with(result, size_var_name);
    std::string var_name(base_name);
    var_name+='[';
    remove_line_with(result, var_name);
  }
}

void declare_predicate_sizes(std::string &result, const size_t num_preds,
    const std::string::size_type pos)
{
  std::string source;
  for (size_t i=0; i < num_preds; ++i)
  {
    source+="  unsigned char __CPROVER_jsa_predicate_";
    source+=std::to_string(i);
    source+="_size;\n";
  }
  source+=
      "  __CPROVER_jsa_tmp_index=0;\n"
          "  for (const jsa_genetic_solutiont::predicatet &__CPROVER_jsa_predicate : solution.predicates)\n"
          "  {\n"
          "    "
          "  }\n";
}

void add_predicate(std::string &result, const size_t index,
    const std::string::size_type pos)
{
  std::string base_name("__CPROVER_jsa_predicate_");
  base_name+=std::to_string(index);
  std::string size_var_name(base_name);
  size_var_name+="_size";
  std::string source("  jsa_genetic_solutiont::predicatet::value_type ");
  source+=base_name;
  source+="[__CPROVER_jsa_predicate_";
  source+=std::to_string(index);
  source+="_size];\n";
  source+="  __CPROVER_jsa_instr_index=0;\n";
  source+=
      "  for (const jsa_genetic_solutiont::predicatet::value_type &__CPROVER_jsa_instr : ";
  source+=base_name;
  source+=")\n  {\n    ";
  source+=size_var_name;
  source+="=__CPROVER_jsa_instr.size()\n    ";
  source+=base_name;
  source+="[__CPROVER_jsa_instr_index++]=__CPROVER_jsa_instr;\n";
  source+="  }\n";
  result.insert(pos, source);
}

void insert_solution(std::string &result, const jsa_symex_learnt &lcfg)
{
  const std::string::size_type pos=result.find("__CPROVER_initialize();\n");
  const size_t num_preds=get_num_jsa_preds(lcfg.get_symbol_table());
  remove_predicates(result, num_preds);
  declare_predicate_sizes(result, num_preds, pos);
  for (size_t i=0; i < num_preds; ++i)
  {
//    add_predicate(result, i, pos);
  }
  remove_line_with(result, "__CPROVER_jsa_query_size;");
  remove_line_with(result, "__CPROVER_jsa_query[");
  remove_line_with(result, "__CPROVER_jsa_invariant_size;");
  remove_line_with(result, "__CPROVER_jsa_invariant[");
  result.insert(pos,
      "  const __CPROVER_jsa_word_t __CPROVER_jsa_query_size=__CPROVER_jsa_solution.query.size();\n"
          "  jsa_genetic_solutiont::queryt::value_type __CPROVER_jsa_query[__CPROVER_jsa_query_size];\n"
          "  size_t __CPROVER_jsa_tmp_index=0;\n"
          "  for (const jsa_genetic_solutiont::queryt::value_type &__CPROVER_jsa_query_instr : __CPROVER_jsa_solution.query)\n"
          "    __CPROVER_jsa_query[__CPROVER_jsa_tmp_index++]=__CPROVER_jsa_query_instr;\n"
          "  const __CPROVER_jsa_word_t __CPROVER_jsa_invariant_size=__CPROVER_jsa_solution.invariant.size();\n"
          "  jsa_genetic_solutiont::invariantt::value_type __CPROVER_jsa_invariant[__CPROVER_jsa_invariant_size];\n"
          "  __CPROVER_jsa_tmp_index=0;\n"
          "  for (const jsa_genetic_solutiont::invariantt::value_type &__CPROVER_jsa_inv_instr : __CPROVER_jsa_solution.invariant)\n"
          "    __CPROVER_jsa_invariant[__CPROVER_jsa_tmp_index++]=__CPROVER_jsa_inv_instr;\n");
// TODO: Substitute
}
}

const std::string &jsa_source_providert::operator ()()
{
  if (!source.empty()) return source;
  add_jsa_defines(source, lcfg);
  add_includes_and_globals(source);
  add_main_body(source, lcfg);
  fix_return_values(source);
  add_facade_function(source);
  insert_solution(source, lcfg);
// XXX: Debug
  std::cout << source << std::endl;
  assert(!"TODO: Implement");
// XXX: Debug
// TODO: Implement!
  return source;
}
