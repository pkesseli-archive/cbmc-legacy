/* FUNCTION: __CPROVER_bjc_run_query */

// cegis.h
typedef unsigned char opcodet;
typedef unsigned char opt;
struct __CPROVER_cegis_instructiont
{
  opcodet opcode;
  opt op0;
  opt op1;
  opt op2;
};
#define __CPROVER_cegis_max_instruction 24u
// cegis.h

// bjc.h
typedef unsigned int word_t;
typedef word_t ptr_t;
typedef word_t index_t;
typedef word_t data_t;

#define MAX_LIST_SIZE 5
#ifndef NPROG
#define NPROG 4
#endif

typedef struct abstract_iterator
{
  _Bool is_valid;
  ptr_t list;
  index_t index;
} abstract_iteratort;

typedef struct abstract_list
{
  _Bool is_valid;
  index_t size;
  data_t content[MAX_LIST_SIZE];
} abstract_listt;

typedef struct abstract_heap
{
  abstract_listt lists[NPROG];
  abstract_iteratort iterators[NPROG];
} abstract_heapt;
// bjc.h

#ifndef __CPROVER_cegis_max_query_instruction
//#define __CPROVER_cegis_max_query_instruction __CPROVER_cegis_max_instruction + 5u
#define __CPROVER_cegis_max_query_instruction __CPROVER_cegis_max_instruction + 1u
#endif
#ifndef __CPROVER_cegis_max_query_base_opcode
#define __CPROVER_cegis_max_query_base_opcode 27u
#endif
#ifndef __CPROVER_cegis_max_predicate_length
//#define __CPROVER_cegis_max_predicate_length 5u
#define __CPROVER_cegis_max_predicate_length 2u
#endif

void __CPROVER_bjc_filter(abstract_heapt * heap, ptr_t list, const struct __CPROVER_cegis_instructiont * predicate, unsigned char predicate_length);
_Bool __CPROVER_bjc_equal(const abstract_heapt * heap, ptr_t lhs, ptr_t rhs);

// B := distinct | filter | forEach | forEachOrdered | peek | sorted
// N := map | flatMap | limit | skip
/* T := allMatch | anyMatch | count | empty | findAny | findFirst
 | max | min | noneMatch | reduce
 */

_Bool __CPROVER_bjc_run_query(abstract_heapt *heap, const ptr_t original_list,
    const ptr_t new_list,
    const struct __CPROVER_cegis_instructiont * const query,
    const unsigned char size)
{
  __CPROVER_assert(0 == 1, "__CPROVER_bjc_run_query");
  // B
  // N
  // Predicate execution
  _Bool filtered=(_Bool) 0;
  _Bool distincted=(_Bool) 0;
  _Bool sorted=(_Bool) 0;
  for (unsigned char i=0; i < size; ++i)
  {
#define opcode query[i].opcode
    __CPROVER_assume(opcode> __CPROVER_cegis_max_instruction && opcode <= __CPROVER_cegis_max_query_instruction);
    __CPROVER_assume(query[i].op1 == 0 && query[i].op2 == 0);
    const unsigned int predicate_length=query[i].op0;
    __CPROVER_assume(predicate_length <= __CPROVER_cegis_max_predicate_length);
    const struct __CPROVER_cegis_instructiont * const predicate=&query[i + 1];

    if (opcode > __CPROVER_cegis_max_query_base_opcode)
    {
      filtered=(_Bool) 0;
      distincted=(_Bool) 0;
      sorted=(_Bool) 0;
    }
    switch(opcode)
    {
      case 25:
      __CPROVER_assume(!filtered);
      __CPROVER_cegis_opcode_25: __CPROVER_bjc_filter(heap, new_list, predicate, predicate_length);
      break;
      /*case 26:
       __CPROVER_assume(!distincted);
       __CPROVER_cegis_opcode_26: distinct(heap, new_list);
       break;
       case 27:
       __CPROVER_assume(!sorted);
       __CPROVER_cegis_opcode_27: sort(heap, new_list);
       break;
       case 28:
       map(heap, new_list, predicate, predicate_length);
       break;
       case 29:
       break;
       //limit(heap, new_list, );*/
      default:
      __CPROVER_assume((_Bool) 0);
    }
  }
  return __CPROVER_bjc_equal(heap, original_list, new_list);
}

/* FUNCTION: __CPROVER_bjc_filter */

void __CPROVER_danger_execute(struct __CPROVER_cegis_instructiont *program, unsigned char size);
extern const void *__CPROVER_cegis_OPS[__CPROVER_cegis_number_of_ops];
extern void *__CPROVER_cegis_RESULT_OPS[__CPROVER_cegis_max_solution_size];

void __CPROVER_bjc_filter(abstract_heapt * const heap, const ptr_t list,
    const struct __CPROVER_cegis_instructiont * const predicate,
    const unsigned char predicate_length)
{
  __CPROVER_assume(predicate_length <= __CPROVER_cegis_max_predicate_length);
  const index_t size=heap->lists[list].size;
  __CPROVER_assume(size <= MAX_LIST_SIZE);
  data_t * const data=heap->lists[list].content;
  data_t tmp[predicate_length];
  for (unsigned char tmp_id=0; tmp_id < __CPROVER_cegis_max_predicate_length; ++tmp_id)
  {
    if (tmp_id >= predicate_length) break;
    __CPROVER_cegis_RESULT_OPS[tmp_id]=&tmp[tmp_id];
    __CPROVER_cegis_OPS[__CPROVER_cegis_number_of_vars + tmp_id]=&tmp[tmp_id];
  }
  for (index_t i=0; i < MAX_LIST_SIZE; ++i)
  {
    if (i >= size) break;
    __CPROVER_cegis_OPS[0]=&data[i]; // We assume 0 is the lambda operator.
    // Evaluate predicate
    __CPROVER_danger_execute(predicate, predicate_length);

    // Remove based on predicate
    if (tmp[predicate_length - 1] != 0)
      for (unsigned char j=0; j < MAX_LIST_SIZE; ++j)
        if (j >= i && j < size - 1) data[j]=data[j + 1];
  }
}

/* FUNCTION: __CPROVER_bjc_equal */

_Bool __CPROVER_bjc_equal(const abstract_heapt * const heap, const ptr_t lhs,
    const ptr_t rhs)
{
  const index_t lhs_size=heap->lists[lhs].size;
  __CPROVER_assume(lhs_size <= MAX_LIST_SIZE);
  if (lhs_size != heap->lists[rhs].size) return (_Bool) 0;
  const data_t * const lhs_data=heap->lists[lhs].content;
  const data_t * const rhs_data=heap->lists[rhs].content;
  for (index_t i=0; i < MAX_LIST_SIZE; ++i)
  {
    if (i >= lhs_size) break;
    if (lhs_data[i] != rhs_data[i]) return (_Bool) 0;
  }
  return (_Bool) 1;
}

/* FUNCTION: __CPROVER_bjc_nondet_list */

// bjc.h
typedef unsigned int word_t;
typedef word_t ptr_t;
typedef word_t index_t;
typedef word_t data_t;

#define MAX_LIST_SIZE 5
#ifndef NPROG
#define NPROG 4
#endif

typedef struct abstract_iterator
{
  _Bool is_valid;
  ptr_t list;
  index_t index;
} abstract_iteratort;

typedef struct abstract_list
{
  _Bool is_valid;
  index_t size;
  data_t content[MAX_LIST_SIZE];
} abstract_listt;

typedef struct abstract_heap
{
  abstract_listt lists[NPROG];
  abstract_iteratort iterators[NPROG];
} abstract_heapt;
// bjc.h

ptr_t __CPROVER_bjc_nondet_list(abstract_heapt * const heap)
{
  ptr_t new_list;
  for (new_list=0; new_list < NPROG; ++new_list)
    if (!heap->iterators[new_list].is_valid && !heap->lists[new_list].is_valid)
      break;
  __CPROVER_assert(new_list < NPROG, "Increase NPROG");
  heap->lists[new_list].is_valid=(_Bool) 1;
  __CPROVER_assume(heap->lists[new_list].size <= MAX_LIST_SIZE);
  return new_list;
}

/* FUNCTION: __CPROVER_bjc_new_list */

ptr_t __CPROVER_bjc_new_list(abstract_heapt * const heap)
{
  ptr_t new_list;
  for (new_list=0; new_list < NPROG; ++new_list)
    if (!heap->iterators[new_list].is_valid && !heap->lists[new_list].is_valid)
      break;
  __CPROVER_assert(new_list < NPROG, "Increase NPROG");
  heap->lists[new_list].is_valid=(_Bool) 1;
  heap->lists[new_list].size=0;
  return new_list;
}

/* FUNCTION: __CPROVER_bjc_iterator */

ptr_t __CPROVER_bjc_iterator(abstract_heapt * const heap, const ptr_t list)
{
  ptr_t new_iterator;
  for (new_iterator=0; new_iterator < NPROG; ++new_iterator)
    if (!heap->iterators[new_iterator].is_valid
        && !heap->lists[new_iterator].is_valid) break;
  __CPROVER_assert(new_iterator < NPROG, "Increase NPROG");
  heap->iterators[new_iterator].is_valid=(_Bool) 1;
  heap->iterators[new_iterator].list=list;
  heap->iterators[new_iterator].index=0;
  return new_iterator;
}

/* FUNCTION: __CPROVER_bjc_hasNext */

_Bool __CPROVER_bjc_hasNext(const abstract_heapt * const heap, const ptr_t it)
{
  const ptr_t list=heap->iterators[it].list;
  return heap->iterators[it].index < heap->lists[list].size;
}

/* FUNCTION: __CPROVER_bjc_next */

data_t __CPROVER_bjc_next(abstract_heapt * const heap, const ptr_t it)
{
  const ptr_t list=heap->iterators[it].list;
  const index_t index=heap->iterators[it].index;
  const data_t result=heap->lists[list].content[index];
  ++heap->iterators[it].index;
  return result;
}

/* FUNCTION: __CPROVER_bjc_it_remove */

void __CPROVER_bjc_it_remove(abstract_heapt * const heap, const ptr_t it)
{
  const ptr_t list=heap->iterators[it].list;
  const index_t size=heap->lists[list].size;
  const index_t index=heap->iterators[it].index;
  for (index_t i=0; i < MAX_LIST_SIZE; ++i)
    if (i >= index && i < size - 1) heap->lists[list].content[i]=
        heap->lists[list].content[i + 1];
}

/* FUNCTION: __CPROVER_bjc_clone */

ptr_t __CPROVER_bjc_clone(abstract_heapt * const heap, const ptr_t list)
{
  const index_t size=heap->lists[list].size;
  __CPROVER_assume(size <= MAX_LIST_SIZE);
  const data_t * const data=heap->lists[list].content;
  const ptr_t new_list=__CPROVER_bjc_nondet_list(heap);
  heap->lists[new_list].size=size;
  for (index_t i=0; i < MAX_LIST_SIZE && i < size; ++i)
    heap->lists[new_list].content[i]=heap->lists[list].content[i];
  return new_list;
}

/* FUNCTION: __CPROVER_bjc_size */

ptr_t __CPROVER_bjc_size(const abstract_heapt * const heap, const ptr_t list)
{
  return heap->lists[list].size;
}
