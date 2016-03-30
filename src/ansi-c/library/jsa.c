/* FUNCTION: __CPROVER_jsa_create_heap */

#if !defined(JSA_TRANSFORMERS_H_) || defined(JSA_SYNTHESIS_H_)
#ifdef JSA_SYNTHESIS_H_
#define JSA_TRANSFORMERS_H_
#endif

#include <stdbool.h>

#ifndef __CPROVER_JSA_MAX_CONCRETE_NODES
#define __CPROVER_JSA_MAX_CONCRETE_NODES 100u
#endif
#ifndef __CPROVER_JSA_MAX_ABSTRACT_NODES
#define __CPROVER_JSA_MAX_ABSTRACT_NODES __CPROVER_JSA_MAX_CONCRETE_NODES
#endif
#ifndef __CPROVER_JSA_MAX_NODES
#define __CPROVER_JSA_MAX_NODES __CPROVER_JSA_MAX_CONCRETE_NODES + __CPROVER_JSA_MAX_ABSTRACT_NODES
#endif
#ifndef __CPROVER_JSA_MAX_ABSTRACT_RANGES
#define __CPROVER_JSA_MAX_ABSTRACT_RANGES __CPROVER_JSA_MAX_ABSTRACT_NODES
#endif
#ifndef __CPROVER_JSA_MAX_ITERATORS
#define __CPROVER_JSA_MAX_ITERATORS 100u
#endif
#ifndef __CPROVER_JSA_MAX_LISTS
#define __CPROVER_JSA_MAX_LISTS __CPROVER_JSA_MAX_ITERATORS
#endif

typedef unsigned char word_t;
typedef word_t data_t;
typedef word_t index_t;
typedef word_t id_t;
typedef id_t list_t;
typedef id_t iterator_t;

typedef struct abstract_heap
{
  /**
   * Concrete node with explicit value.
   */
  struct concrete_nodet
  {
    id_t next;
    id_t previous;
    data_t value;
  } concrete_nodes[__CPROVER_JSA_MAX_CONCRETE_NODES ];
  /**
   * Abstract nodes may assume any of a set of pre-defined values
   * (value_ref to abstract_ranget).
   */
  struct abstract_nodet
  {
    id_t next;
    id_t previous;
    id_t value_ref;
  } abstract_nodes[__CPROVER_JSA_MAX_ABSTRACT_NODES ];
  /**
   * Set of pre-defined, possible values for abstract nodes.
   */
  struct abstract_ranget
  {
    data_t min;
    data_t max;
    index_t size;
  } abstract_ranges[__CPROVER_JSA_MAX_ABSTRACT_RANGES ];
  /**
   * Iterators point to a node and give the relative index
   * within that node.
   */
  struct iteratort
  {
    id_t node_id;
    id_t previous;
    index_t index;
    list_t list;
  } iterators[__CPROVER_JSA_MAX_ITERATORS ];
  /**
   * Number of iterators on the heap.
   */
  index_t iterator_count;
  /**
   * Set of node ids which are list heads.
   */
  list_t list_head_nodes[__CPROVER_JSA_MAX_LISTS ];
  /**
   * Number of lists on the heap.
   */
  index_t list_count;
} abstract_heapt;
#endif

#if !defined(JSA_TRANSFORMERS_H_)
#define JSA_TRANSFORMERS_H_

#ifdef __CPROVER
#define __CPROVER_jsa_inline
#else
#define __CPROVER_jsa_inline inline
#endif

#ifdef __CPROVER
#define __CPROVER_jsa_assume(c) __CPROVER_assume(c)
#else
_Bool __CPROVER_jsa_assume_violated;
#define __CPROVER_jsa_assume(c) if (!(c)) __CPROVER_jsa_assume_violated=true
#endif
#define __CPROVER_jsa_null 0

id_t __CPROVER_jsa_get_head_node(const abstract_heapt * const heap,
    const list_t list)
{
  return heap->list_head_nodes[list];
}

_Bool __CPROVER_jsa_is_concrete_node(const id_t node)
{
  return node < __CPROVER_JSA_MAX_CONCRETE_NODES;
}

_Bool __CPROVER_jsa_is_abstract_node(const id_t node)
{
  return !__CPROVER_jsa_is_concrete_node(node);
}

unsigned int __CPROVER_jsa_get_abstract_node_index(const id_t node)
{
  return node - __CPROVER_JSA_MAX_CONCRETE_NODES;
}

void __CPROVER_jsa_set_next(abstract_heapt * const heap, const id_t node,
    const id_t next_node)
{
  if (__CPROVER_jsa_is_concrete_node(lhs))
  {
    heap->concrete_nodes[node].next=next_node;
  } else
  {
    const index_t index=__CPROVER_jsa_get_abstract_node_index(lhs);
    heap->abstract_nodes[index].next=next_node;
  }
}

void __CPROVER_jsa_set_previous(abstract_heapt * const heap, const id_t node,
    const id_t previous_node)
{
  if (__CPROVER_jsa_is_concrete_node(lhs))
  {
    heap->concrete_nodes[node].previous=previous_node;
  } else
  {
    const index_t index=__CPROVER_jsa_get_abstract_node_index(lhs);
    heap->abstract_nodes[index].previous=previous_node;
  }
}

abstract_heapt __CPROVER_jsa_heap;
#ifdef __CPROVER
abstract_heapt nondet_heap();
#endif

__CPROVER_jsa_inline abstract_heapt *__CPROVER_jsa_create_heap(void)
{
#ifdef __CPROVER
  __CPROVER_jsa_heap=nondet_heap();
#endif
  const abstract_heapt * const h=&__CPROVER_jsa_heap;
  // Lists point to valid head nodes.
  // Enforce strictly ascending head node ids (unless null).
  id_t max_head_node=__CPROVER_jsa_null;
  for (list_t list=0; list < __CPROVER_JSA_MAX_LISTS; ++list)
  {
    const id_t head_node=h->list_head_nodes[list];
    __CPROVER_jsa_assume(head_node < __CPROVER_JSA_MAX_NODES);
    if (head_node != __CPROVER_jsa_null)
    {
      __CPROVER_jsa_assume(head_node > max_head_node);
      max_head_node=head_node;
    }
  }
  // Iterators point to valid nodes
  // Node is part of only one list.
  // No cycles
  return &__CPROVER_jsa_heap;
}

#endif /* CEGIS_JSA_TRANSFORMERS_H_ */

/* FUNCTION: __CPROVER_jsa_create_nondet_list */

__CPROVER_jsa_inline list_t __CPROVER_jsa_create_nondet_list(
    const abstract_heapt * const heap)
{
  const index_t new_list=heap->list_count;
  __CPROVER_jsa_assume(new_list < __CPROVER_JSA_MAX_LISTS);
  ++heap->list_count;
  return heap->list_head_nodes[new_list];
}

/* FUNCTION: __CPROVER_jsa_iterator */
__CPROVER_jsa_inline iterator_t __CPROVER_jsa_iterator(
    abstract_heapt * const heap, const list_t list)
{
  const index_t new_iterator=heap->iterator_count;
  __CPROVER_jsa_assume(new_iterator < __CPROVER_JSA_MAX_ITERATORS);
  ++heap->iterator_count;
  heap->iterators[new_iterator].node_id=__CPROVER_jsa_get_head_node(heap, list);
  heap->iterators[new_iterator].previous=__CPROVER_jsa_null;
  heap->iterators[new_iterator].index=0;
  heap->iterators[new_iterator].list=list;
  return new_iterator;
}

/* FUNCTION: __CPROVER_jsa_hasNext */
__CPROVER_jsa_inline _Bool __CPROVER_jsa_hasNext(
    const abstract_heapt * const heap, const iterator_t it)
{
  return __CPROVER_jsa_null != heap->iterators[it].node_id;
}

/* FUNCTION: __CPROVER_jsa_next */
__CPROVER_jsa_inline data_t __CPROVER_jsa_next(abstract_heapt * const heap,
    const iterator_t it)
{
  const id_t node_id=heap->iterators[it].node_id;
  __CPROVER_jsa_assume(__CPROVER_jsa_is_concrete_node(node_id));
  const data_t result=heap->concrete_nodes[node_id].value;
  heap->iterators[it].node_id=heap->concrete_nodes[node_id].next;
  heap->iterators[it].previous=node_id;
  return result;
}

/* FUNCTION: __CPROVER_jsa_remove */
__CPROVER_jsa_inline void __CPROVER_jsa_remove(abstract_heapt * const heap,
    const iterator_t it)
{
  const id_t node_id_to_remove=heap->iterators[it].previous;
  __CPROVER_jsa_assume(__CPROVER_jsa_is_concrete_node(node_id_to_remove));
  const id_t previous_node_id=heap->concrete_nodes[node_id_to_remove].previous;
  const id_t next_node_id=heap->concrete_nodes[node_id_to_remove].next;
  __CPROVER_jsa_set_next(heap, previous_node_id, next_node_id);
  __CPROVER_jsa_set_previous(heap, next_node_id, previous_node_id);
  heap->iterators[it].previous=__CPROVER_jsa_null;
}
