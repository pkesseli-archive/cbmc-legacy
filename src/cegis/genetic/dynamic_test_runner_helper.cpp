#if !defined(_WIN32) || defined(_HAVE_DLFCN)
#include <dlfcn.h>
#endif

#include <cassert>
#include <fstream>

#include <util/tempfile.h>
#include <cegis/genetic/dynamic_test_runner_helper.h>

void close_fitness_tester_library(fitness_lib_handlet &handle,
    fitness_testert &fitness_tester)
{
  if (fitness_tester && handle)
  {
    #ifndef _WIN32
    dlclose(handle);
    handle=0;
    fitness_tester=0;
    #endif
  }
}

namespace
{
void write_file(const char * const path, const std::string &content)
{
  std::ofstream ofs(path);
  ofs << content;
}

#define SOURCE_FILE_PREFIX "concrete_test"
#define SOURCE_FILE_SUFFIX ".c"
#ifndef _WIN32
#define COMPILE_COMMAND "gcc -std=c99 -g0 -O2 -shared -rdynamic -fPIC "
//#define COMPILE_COMMAND "gcc -std=c99 -g3 -O0 -shared -rdynamic -fPIC "
#else
#define COMPILE_COMMAND "gcc -std=c99 -g0 -O2 -shared "
#endif
#define ARTIFACT_SEPARATOR " -o "
#define COMPLING_FAILED "Compiling test runner failed."
#define OPEN_LIB_FAILED "Opening fitness test library failed."
#define LOAD_FUNC_FAILED "Loading fitness test function failed."
}

void prepare_fitness_tester_library(fitness_lib_handlet &handle,
    fitness_testert &fitness_tester,
    const std::function<std::string(void)> &source_code_provider,
    const std::string &library_file_path, const bool danger)
{
  if (fitness_tester) return;
  const temporary_filet source_file(SOURCE_FILE_PREFIX, SOURCE_FILE_SUFFIX);
  const std::string source_file_name(source_file());
  write_file(source_file_name.c_str(), source_code_provider());
  std::string compile_command(COMPILE_COMMAND);
  compile_command+=source_file_name;
  compile_command+=ARTIFACT_SEPARATOR;
  compile_command+=library_file_path;
  const int result=system(compile_command.c_str());
  if (result) throw std::runtime_error(COMPLING_FAILED);
  
  #if !defined(_WIN32) || defined(_HAVE_DLFCN)
  handle=dlopen(library_file_path.c_str(), RTLD_NOW);
  if (!handle)
  {
    perror(OPEN_LIB_FAILED);
    throw std::runtime_error(OPEN_LIB_FAILED);
  }
  fitness_tester=(fitness_testert) dlsym(handle, FUNC);
  char *error=0;
  if ((error=dlerror()))
  {
    perror(error);
    throw std::runtime_error(LOAD_FUNC_FAILED);
  }
  #else
  assert(!"Dynamic library loading currently not supported on Windows.");
  #endif
}
