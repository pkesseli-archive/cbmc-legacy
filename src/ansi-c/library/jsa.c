/* FUNCTION: __CPROVER_jsa_create_heap */

#if !defined(JSA_TRANSFORMERS_H_) || defined(JSA_SYNTHESIS_H_)
#ifdef JSA_SYNTHESIS_H_
#define JSA_TRANSFORMERS_H_
#endif

#ifndef __CPROVER_JSA_MAX_NODES
#define __CPROVER_JSA_MAX_NODES 100u
#endif
#ifndef __CPROVER_JSA_MAX_ABSTRACT_RANGES
#define __CPROVER_JSA_MAX_ABSTRACT_RANGES __CPROVER_JSA_MAX_NODES
#endif

typedef unsigned char word_t;
typedef word_t data_t;
typedef word_t index_t;
typedef word_t list_t;

typedef struct abstract_heap
{
  struct concrete_nodet
  {
    data_t value;
    index_t index;
  } concrete_nodes[__CPROVER_JSA_MAX_NODES ];
  struct abstract_ranget
  {
    index_t id;
    data_t min;
    data_t max;
    index_t size;
  } abstract_nodes[__CPROVER_JSA_MAX_ABSTRACT_RANGES ];
} abstract_heapt;
#endif

#if !defined(JSA_TRANSFORMERS_H_)
#define JSA_TRANSFORMERS_H_

#ifdef __CPROVER
#define __CPROVER_jsa_inline
#else
#define __CPROVER_jsa_inline inline
#endif

abstract_heapt __CPROVER_jsa_heap;

__CPROVER_jsa_inline abstract_heapt *__CPROVER_jsa_create_heap(void)
{
#ifdef __CPROVER
  abstract_heapt new_heap;
  __CPROVER_jsa_heap=new_heap;
#endif
  return &__CPROVER_jsa_heap;
}

#endif /* CEGIS_JSA_TRANSFORMERS_H_ */

/* FUNCTION: __CPROVER_jsa_create_nondet_list */

__CPROVER_jsa_inline list_t __CPROVER_jsa_create_nondet_list(
    abstract_heapt * const heap)
{

}
