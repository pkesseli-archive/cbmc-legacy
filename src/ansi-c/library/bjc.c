/* FUNCTION: __CPROVER_bjc_run_query */

#ifndef __CPROVER_cegis_max_query_instruction
//#define __CPROVER_cegis_max_query_instruction __CPROVER_cegis_max_instruction + 5u
#define __CPROVER_cegis_max_query_instruction __CPROVER_cegis_max_instruction + 1u
#endif
#ifndef __CPROVER_cegis_max_query_base_opcode
#define __CPROVER_cegis_max_query_base_opcode 27u
#endif
#ifndef __CPROVER_cegis_max_predicate_length
#define __CPROVER_cegis_max_predicate_length 5u
#endif

// Query instructions
void filter(abstract_heapt *heap, ptr_t list, const struct __CPROVER_cegis_instructiont *pred, unsigned char pred_sz);
_Bool equal(const abstract_heapt *heap, ptr_t lhs, ptr_t rhs);
void map(abstract_heapt *heap, ptr_t list, const struct __CPROVER_cegis_instructiont *pred, unsigned char pred_sz);

// B := distinct | filter | forEach | forEachOrdered | peek | sorted
// N := map | flatMap | limit | skip
/* T := allMatch | anyMatch | count | empty | findAny | findFirst
 | max | min | noneMatch | reduce
 */

_Bool __CPROVER_bjc_run_query(
    abstract_heapt *heap,
    const ptr_t original_list, const ptr_t new_list,
    const struct __CPROVER_cegis_instructiont * const query,
    const unsigned char size)
{
  // B
  // N
  // Predicate execution
  _Bool filtered = (_Bool) 0;
  _Bool distinct = (_Bool) 0;
  _Bool sorted = (_Bool) 0;
  for (unsigned char i=0; i < size; ++i)
  {
#define opcode query[i].opcode
    __CPROVER_assume(opcode > __CPROVER_cegis_max_instruction && opcode <= __CPROVER_cegis_max_query_instruction);
    __CPROVER_assume(query[i].op1 == 0 && query[i].op2 == 0);
    const unsigned int predicate_length=program[i].op0;
    __CPROVER_assume(predicate_length <= __CPROVER_cegis_max_predicate_length);
    const struct __CPROVER_cegis_instructiont * const predicate=&query[i + 1];

    if (opcode > __CPROVER_cegis_max_query_base_opcode)
    {
      filtered=(_Bool) 0;
      distinct=(_Bool) 0;
      sorted=(_Bool) 0;
    }
    switch(opcode)
    {
    case 25:
      __CPROVER_assume(!filtered);
      __CPROVER_cegis_opcode_25: filter(heap, new_list, predicate, predicate_length);
      break;
    case 26:
      __CPROVER_assume(!distinct);
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
      //limit(heap, new_list, );
    default:
    __CPROVER_assume((_Bool) 0);
    }
  }
  return equal(heap, original_list, new_list);
}

/* FUNCTION: __CPROVER_bjc_filter */

void __CPROVER_bjc_filter(
    abstract_heapt *heap, ptr_t list,
    const __CPROVER_cegis_instructiont * const predicate,
    const unsigned char predicate_length)
{
  __CPROVER_assume(predicate_length <= __CPROVER_cegis_max_predicate_length);
  const index_t size=heap->lists[list].size;
  const data_t * const data=heap->lists[list].content;
  __CPROVER_assume(size <= MAX_LIST_SIZE);
  for (index_t i=0; i < size; ++i)
  {
    __CPROVER_cegis_OPS[0]=&data[i]; // We assume 0 is the lambda operator.
    // Evaluate predicate
    data_t tmp[predicate_length];
    for (unsigned char tmp = 0; tmp < predicate_length; ++tmp)
    {
      __CPROVER_cegis_ROPS[tmp]=&tmp[tmp];
      __CPROVER_cegis_OPS[__CPROVER_cegis_number_of_vars + tmp]=&tmp[tmp];
    }
    __CPROVER_danger_execute(predicate, predicate_length);

    // Remove based on predicate
    if (tmp[predicate_length - 1] != 0)
      for (unsigned char j = 0; j < predicate_length; ++j)
        if (j >= i && j < predicate_length - 1) data[j]=data[j + 1];
  }
}

/* FUNCTION: __CPROVER_bjc_equal */

_Bool __CPROVER_bjc_equal(const abstract_heapt *heap, ptr_t lhs, ptr_t rhs)
{
  const index_t lhs_size=heap->lists[lhs].size;
  if (lhs_size != heap->lists[rhs].size) return (_Bool) 0;
  const data_t * const lhs_data=heap->lists[lhs].content;
  const data_t * const rhs_data=heap->lists[rhs].content;
  __CPROVER_assume(size <= MAX_LIST_SIZE);
  for (index_t i=0; i < lhs_size; ++i)
    if (lhs_data[i] != rhs_data[i]) return (_Bool) 0;
  return (_Bool) 1;
}

/* FUNCTION: __CPROVER_bjc_new_list */

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

ptr_t __CPROVER_bjc_new_list(abstract_heapt * const heap)
{
  ptr_t new_list;
  for (new_list=0; new_list < NPROG; ++new_list)
    if (!heap->iterators[new_list].is_valid && !heap->lists[new_list].is_valid) break;
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
    if (!heap->iterators[new_iterator].is_valid && !heap->lists[new_iterator].is_valid) break;
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
    if (i >= index && i < size - 1)
      heap->lists[list].content[i]=heap->lists[list].content[i+1];
}

/* FUNCTION: __CPROVER_bjc_clone */

ptr_t __CPROVER_bjc_clone(abstract_heapt *heap, ptr_t list)
{
  const index_t size=heap->lists[list].size;
  __CPROVER_assume(size <= MAX_LIST_SIZE);
  const data_t * const data=heap->lists[list].data;
  const ptr_t new_list=__CPROVER_bjc_new_list(heap);
  heap->lists[new_list].size=size;
  for (index_t i=0; i < size; ++i)
    heap->lists[new_list].content[i]=heap->lists[list].content[i];
  return new_list;
}

/* FUNCTION: __CPROVER_bjc_size */

ptr_t __CPROVER_bjc_size(const abstract_heapt *heap, ptr_t list)
{
  return heap->lists[list].size;
}
