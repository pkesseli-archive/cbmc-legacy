#include <cegis/jsa/converters/solution.h>
#include <cegis/jsa/genetic/jsa_serialiser.h>

jsa_serialisert::jsa_serialisert(const jsa_programt &prog) :
    prog(prog)
{
}

void jsa_serialisert::operator()(irept &sdu, const jsa_solutiont &entity) const
{
  // TODO: Implement
  assert(false);
}

void jsa_serialisert::operator()(jsa_solutiont &entity, const irept &sdu) const
{
  // TODO: Implement
  assert(false);
}

void jsa_serialisert::operator()(jsa_genetic_solutiont &entity,
    const irept &sdu) const
{
  // TODO: Implement
  assert(false);
}

jsa_serialisert::operator std::function<void(irept &, const jsa_solutiont &)>() const
{
  return [this](irept &sdu, const jsa_solutiont &entity)
  { this->operator ()(sdu, entity);};
}

jsa_serialisert::operator std::function<void(jsa_solutiont &, const irept &)>() const
{
  return [this](jsa_solutiont &entity, const irept &sdu)
  { this->operator ()(entity, sdu);};
}

jsa_serialisert::operator std::function<void(jsa_genetic_solutiont &, const irept &)>() const
{
  return [this](jsa_genetic_solutiont &entity, const irept &sdu)
  { this->operator ()(entity, sdu);};
}
