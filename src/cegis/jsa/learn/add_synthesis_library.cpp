#include <ansi-c/cprover_library.h>
#include <ansi-c/c_types.h>

#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/learn/add_synthesis_library.h>

// XXX: Debug
#include <util/ui_message.h>
#include <iostream>
// XXX: Debug

namespace
{
void add_placenholder(symbol_tablet &st, const irep_idt &id)
{
  if (st.has_symbol(id)) return;
  symbolt symbol;
  symbol.name=id;
  symbol.base_name=symbol.name;
  symbol.pretty_name=symbol.base_name;
  symbol.type=signed_int_type();
  symbol.is_lvalue=true;
  symbol.mode=ID_C;
  symbol.module=JSA_MODULE;
  st.add(symbol);
}
}

void add_jsa_synthesis_library(jsa_programt &prog, const size_t max_sz)
{
  symbol_tablet &st=prog.st;
  std::string library_text("#define JSA_SYNTHESIS_H_");
  library_text+="\n#define __CPROVER_JSA_MAX_QUERY_SIZE ";
  library_text+=std::to_string(max_sz);
  library_text+='\n';
  // TODO: Detect from st?
  library_text+="#define __CPROVER_JSA_MAX_CONCRETE_NODES 1u\n"
"#define __CPROVER_JSA_MAX_ABSTRACT_NODES 0u\n"
"#define __CPROVER_JSA_MAX_ITERATORS 1u\n"
"#define __CPROVER_JSA_MAX_LISTS 1u\n";
  // TODO: Detect from st?
  std::set<irep_idt> functions={ "__CPROVER_jsa_assume_valid_heap",
      "__CPROVER_jsa_query_execute_up_to" };
  symbol_tablet dummy_st;
  add_placenholder(dummy_st, "__CPROVER_jsa_assume_valid_heap");
  add_placenholder(dummy_st, "__CPROVER_jsa_query_execute_up_to");
  library_text+=get_cprover_library_text(functions, dummy_st);
  // XXX: Debug
  ui_message_handlert msg(ui_message_handlert::PLAIN, "");
  std::cout << "<lib_text>" << library_text << "</lib_text>" << std::endl;
  // XXX: Debug
  add_library(library_text, st, msg);
}
