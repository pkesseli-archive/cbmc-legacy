#ifndef CEGIS_BJC_H_
#define CEGIS_BJC_H_

typedef unsigned int __CPROVER_jsa_word_t;
typedef __CPROVER_jsa_word_t ptr_t;
typedef __CPROVER_jsa_word_t __CPROVER_jsa_data_t;
typedef __CPROVER_jsa_word_t __CPROVER_jsa_index_t;

#define MAX_LIST_SIZE 5
#ifndef NPROG
#define NPROG 4
#endif

typedef struct abstract_iterator
{
  _Bool is_valid;
  ptr_t list;
  __CPROVER_jsa_index_t index;
} abstract_iteratort;

typedef struct abstract_list
{
  _Bool is_valid;
  __CPROVER_jsa_index_t size;
  __CPROVER_jsa_data_t content[MAX_LIST_SIZE];
} abstract_listt;

typedef struct abstract_heap
{
  abstract_listt lists[NPROG];
  abstract_iteratort iterators[NPROG];
} abstract_heapt;


ptr_t __CPROVER_bjc_nondet_list(abstract_heapt * heap);
ptr_t __CPROVER_bjc_new_list(abstract_heapt *heap);
ptr_t __CPROVER_bjc_clone(abstract_heapt *heap, ptr_t list);
ptr_t __CPROVER_bjc_iterator(abstract_heapt *heap, ptr_t list);
__CPROVER_jsa_data_t __CPROVER_bjc_next(abstract_heapt * heap, ptr_t it);
_Bool __CPROVER_bjc_hasNext(const abstract_heapt * heap, ptr_t it);
void __CPROVER_bjc_it_remove(abstract_heapt *heap, ptr_t it);

#endif /* CEGIS_BJC_H_ */
