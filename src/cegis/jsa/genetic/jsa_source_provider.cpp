#include <util/options.h>

#include <cegis/jsa/learn/jsa_symex_learn.h>
#include <cegis/jsa/genetic/jsa_source_provider.h>

jsa_source_providert::jsa_source_providert(const optionst &options,
    jsa_symex_learnt &lcfg) :
    options(options), lcfg(lcfg)
{
}

const std::string &jsa_source_providert::operator ()()
{
  if (!source.empty()) return source;
  assert(!"TODO: Implement");
  // TODO: Implement!
  return source;
}
