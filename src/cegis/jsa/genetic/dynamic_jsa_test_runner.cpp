#include <cegis/genetic/dynamic_test_runner_helper.h>
#include <cegis/jsa/genetic/dynamic_jsa_test_runner.h>

dynamic_jsa_test_runnert::dynamic_jsa_test_runnert(
    const std::function<std::string(void)> &source_code_provider) :
    source_code_provider(source_code_provider), shared_library(LIBRARY_PREFIX,
    LIBRARY_SUFFIX), handle(0), fitness_tester(0)
{
}

dynamic_jsa_test_runnert::~dynamic_jsa_test_runnert()
{
  close_fitness_tester_library(handle, fitness_tester);
}

void dynamic_jsa_test_runnert::run_test(individualt &individual,
    const counterexamplet &counterexample,
    const std::function<void(bool)> on_complete)
{
  prepare_fitness_tester_library(handle, fitness_tester, source_code_provider,
      shared_library());
  on_complete(EXIT_SUCCESS == fitness_tester(individual));
}

void dynamic_jsa_test_runnert::join()
{
}
