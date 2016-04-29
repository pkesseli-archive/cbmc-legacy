/* FUNCTION: __CPROVER_jsa_synthesise */

#ifndef JSA_TRANSFORMERS_H_

#ifdef JSA_GENETIC_SYNTHESIS_H_
#ifndef __CPROVER_jsa_extern
#define __CPROVER_jsa_extern extern
#define JSA_SYNTHESIS_H_
#define __CPROVER_JSA_DEFINE_TRANSFORMERS
#endif
#else
#ifndef __CPROVER_jsa_extern
#define __CPROVER_jsa_extern
#endif
#endif

#ifndef JSA_SYNTHESIS_H_
#define __CPROVER_JSA_DEFINE_TRANSFORMERS
#endif

#ifndef __CPROVER
#include <assert.h>
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
#ifndef __CPROVER_JSA_MAX_NODES_PER_LIST
#define __CPROVER_JSA_MAX_NODES_PER_LIST __CPROVER_JSA_MAX_NODES
#endif
#if __CPROVER_JSA_MAX_LISTS < 1
#error "JSA needs at least one list variable for analysis."
#endif
#if __CPROVER_JSA_MAX_ABSTRACT_NODES != 0
#error "Currently in concrete-mode only."
#endif

typedef unsigned char __CPROVER_jsa_word_t;
typedef __CPROVER_jsa_word_t  __CPROVER_jsa_data_t;
typedef __CPROVER_jsa_word_t  __CPROVER_jsa_index_t;
typedef __CPROVER_jsa_word_t  __CPROVER_jsa__internal_index_t;
typedef __CPROVER_jsa_word_t  __CPROVER_jsa_id_t;
typedef __CPROVER_jsa_id_t  __CPROVER_jsa_node_id_t;
typedef __CPROVER_jsa_id_t  __CPROVER_jsa_list_id_t;
typedef __CPROVER_jsa_id_t  __CPROVER_jsa_iterator_id_t;
#define __CPROVER_jsa_null 0xFF

/**
 * Concrete node with explicit value.
 */
typedef struct __CPROVER_jsa_concrete_node
{
  __CPROVER_jsa_node_id_t next;
  __CPROVER_jsa_node_id_t previous;
  __CPROVER_jsa_list_id_t list;
  __CPROVER_jsa_data_t value;
} __CPROVER_jsa_concrete_nodet;

/**
 * Abstract nodes may assume any of a set of pre-defined values
 * (value_ref to abstract_ranget).
 */
typedef struct __CPROVER_jsa_abstract_node
{
  __CPROVER_jsa_node_id_t next;
  __CPROVER_jsa_node_id_t previous;
  __CPROVER_jsa_list_id_t list;
  __CPROVER_jsa_id_t value_ref;
} __CPROVER_jsa_abstract_nodet;

/**
 * Set of pre-defined, possible values for abstract nodes.
 */
typedef struct __CPROVER_jsa_abstract_range
{
  __CPROVER_jsa_data_t min;
  __CPROVER_jsa_data_t max;
  __CPROVER_jsa_index_t size;
} __CPROVER_jsa_abstract_ranget;

/**
 * Iterators point to a node and give the relative index
 * within that node.
 */
typedef struct __CPROVER_jsa_iterator
{
  __CPROVER_jsa_node_id_t node_id;
  __CPROVER_jsa_node_id_t previous_node_id;
  __CPROVER_jsa_index_t index;
  __CPROVER_jsa_index_t previous_index;
  __CPROVER_jsa_list_id_t list;
} __CPROVER_jsa_iteratort;

typedef struct __CPROVER_jsa_abstract_heap
{
  __CPROVER_jsa_concrete_nodet concrete_nodes[__CPROVER_JSA_MAX_CONCRETE_NODES];

#if __CPROVER_JSA_MAX_ABSTRACT_NODES > 0
    __CPROVER_jsa_abstract_nodet abstract_nodes[__CPROVER_JSA_MAX_ABSTRACT_NODES];
#else
  __CPROVER_jsa_abstract_nodet *abstract_nodes;
#endif

#if __CPROVER_JSA_MAX_ABSTRACT_NODES > 0
  __CPROVER_jsa_abstract_ranget abstract_ranges[__CPROVER_JSA_MAX_ABSTRACT_RANGES];
#else
  __CPROVER_jsa_abstract_ranget *abstract_ranges;
#endif

  __CPROVER_jsa_iteratort iterators[__CPROVER_JSA_MAX_ITERATORS];

  /**
   * Number of iterators on the heap.
   */
  __CPROVER_jsa_index_t iterator_count;

  /**
   * Set of node ids which are list heads.
   */
  __CPROVER_jsa_list_id_t list_head_nodes[__CPROVER_JSA_MAX_LISTS ];

  /**
   * Number of lists on the heap.
   */
  __CPROVER_jsa_index_t list_count;

} __CPROVER_jsa_abstract_heapt;


#ifdef __CPROVER
#define __CPROVER_jsa_inline
#else
#define __CPROVER_jsa_inline static inline
#endif

#ifdef __CPROVER
#define __CPROVER_jsa_assume(c) __CPROVER_assume(c)
#define __CPROVER_jsa_assert(c, str) __CPROVER_assert(c, str)
#else
#define __CPROVER_jsa_assume(c) assert(c)
#define __CPROVER_jsa_assert(c, str) assert(c && str)
#endif

// Heap comparison
#ifdef __CPROVER
#define __CPROVER_jsa__internal_are_heaps_equal(lhs, rhs) (*(lhs) == *(rhs))
#else
__CPROVER_jsa_inline _Bool __CPROVER_jsa__internal_are_heaps_equal(
    const __CPROVER_jsa_abstract_heapt * const lhs,
    const __CPROVER_jsa_abstract_heapt * const rhs)
{
  __CPROVER_jsa__internal_index_t i;
  for (i=0; i < __CPROVER_JSA_MAX_ABSTRACT_NODES; ++i)
  {
    const __CPROVER_jsa_abstract_nodet lhs_node=lhs->abstract_nodes[i];
    const __CPROVER_jsa_abstract_nodet rhs_node=rhs->abstract_nodes[i];
    if (lhs_node.list != rhs_node.list ||
        lhs_node.next != rhs_node.next ||
        lhs_node.previous != rhs_node.previous ||
        lhs_node.value_ref != rhs_node.value_ref) return false;
  }
  for (i=0; i < __CPROVER_JSA_MAX_ABSTRACT_RANGES; ++i)
  {
    const __CPROVER_jsa_abstract_ranget lhs_range=lhs->abstract_ranges[i];
    const __CPROVER_jsa_abstract_ranget rhs_range=rhs->abstract_ranges[i];
    if (lhs_range.max != rhs_range.max ||
        lhs_range.min != rhs_range.min ||
        lhs_range.size != rhs_range.size) return false;
  }
  for (i=0; i < __CPROVER_JSA_MAX_CONCRETE_NODES; ++i)
  {
    const __CPROVER_jsa_concrete_nodet lhs_node=lhs->concrete_nodes[i];
    const __CPROVER_jsa_concrete_nodet rhs_node=rhs->concrete_nodes[i];
    if (lhs_node.list != rhs_node.list ||
        lhs_node.next != rhs_node.next ||
        lhs_node.previous != rhs_node.previous ||
        lhs_node.value != rhs_node.value) return false;
  }
  if (lhs->iterator_count != rhs->iterator_count) return false;
  for (i=0; i < lhs->iterator_count; ++i)
  {
    const __CPROVER_jsa_iteratort lhs_it=lhs->iterators[i];
    const __CPROVER_jsa_iteratort rhs_it=rhs->iterators[i];
    if (lhs_it.index != rhs_it.index ||
        lhs_it.list != rhs_it.list ||
        lhs_it.node_id != rhs_it.node_id ||
        lhs_it.previous_index != rhs_it.previous_index ||
        lhs_it.previous_node_id != rhs_it.previous_node_id) return false;
  }
  if (lhs->list_count != rhs->list_count) return false;
  for (i=0; i < lhs->list_count; ++i)
    if (lhs->list_head_nodes[i] != rhs->list_head_nodes[i]) return false;
  return true;
}
#endif

// Node utility functions
#define __CPROVER_jsa__internal_get_head_node(heap_ptr, list) \
    (heap_ptr)->list_head_nodes[list]

#define __CPROVER_jsa__internal_is_concrete_node(node) \
  (node < __CPROVER_JSA_MAX_CONCRETE_NODES)

#define __CPROVER_jsa__internal_is_abstract_node(node) \
  (!__CPROVER_jsa__internal_is_concrete_node(node))

#define __CPROVER_jsa__internal_get_abstract_node_index(node) \
  (node - __CPROVER_JSA_MAX_CONCRETE_NODES)

#define __CPROVER_jsa__internal_get_abstract_node_id(node_index) \
  (__CPROVER_JSA_MAX_CONCRETE_NODES + node_index)

#define __CPROVER_jsa__internal_get_list(heap_ptr, node) \
  (__CPROVER_jsa_null == node ? __CPROVER_jsa_null : __CPROVER_jsa__internal_is_concrete_node(node) ? (heap_ptr)->concrete_nodes[node].list : (heap_ptr)->abstract_nodes[node].list)

__CPROVER_jsa_inline void __CPROVER_jsa__internal_set_next(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node,
    const __CPROVER_jsa_node_id_t next_node)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  if (__CPROVER_jsa__internal_is_concrete_node(node))
  {
    heap->concrete_nodes[node].next=next_node;
  } else
  {
    const __CPROVER_jsa_index_t index=
        __CPROVER_jsa__internal_get_abstract_node_index(node);
    heap->abstract_nodes[index].next=next_node;
  }
}
#else
;
#endif

#define __CPROVER_jsa__internal_get_next(heap_ptr, node) \
  (__CPROVER_jsa__internal_is_concrete_node(node) ? (heap_ptr)->concrete_nodes[node].next : (heap_ptr)->abstract_nodes[__CPROVER_jsa__internal_get_abstract_node_index(node)].next)

__CPROVER_jsa_inline void __CPROVER_jsa__internal_set_previous(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node,
    const __CPROVER_jsa_node_id_t previous_node)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  if (__CPROVER_jsa__internal_is_concrete_node(node))
  {
    heap->concrete_nodes[node].previous=previous_node;
  } else
  {
    const __CPROVER_jsa_index_t index=
        __CPROVER_jsa__internal_get_abstract_node_index(node);
    heap->abstract_nodes[index].previous=previous_node;
  }
}
#else
;
#endif

#define __CPROVER_jsa__internal_get_previous(heap_ptr, node) \
  (__CPROVER_jsa__internal_is_concrete_node(node) ? (heap_ptr)->concrete_nodes[node].previous : (heap_ptr)->abstract_nodes[__CPROVER_jsa__internal_get_abstract_node_index(node)].previous)

__CPROVER_jsa_inline void __CPROVER_jsa__internal_remove(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node_id_to_remove)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_concrete_node(node_id_to_remove));
  const __CPROVER_jsa_id_t previous_node_id=heap->concrete_nodes[node_id_to_remove].previous;
  const __CPROVER_jsa_id_t next_node_id=heap->concrete_nodes[node_id_to_remove].next;
  if (__CPROVER_jsa_null != previous_node_id)
    __CPROVER_jsa__internal_set_next(heap, previous_node_id, next_node_id);
  else
  {
    const __CPROVER_jsa_list_id_t list=__CPROVER_jsa__internal_get_list(heap, node_id_to_remove);
    heap->list_head_nodes[list]=next_node_id;
  }
  if (__CPROVER_jsa_null != next_node_id)
    __CPROVER_jsa__internal_set_previous(heap, next_node_id, previous_node_id);
}
#else
;
#endif

// Iterator utility functions
__CPROVER_jsa_inline void __CPROVER_jsa__internal_make_null(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_iterator_id_t it)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  heap->iterators[it].index=0;
  heap->iterators[it].previous_index=0;
  heap->iterators[it].node_id=__CPROVER_jsa_null;
  heap->iterators[it].previous_node_id=__CPROVER_jsa_null;
}
#else
;
#endif

// Heap sanity functions
__CPROVER_jsa_inline _Bool __CPROVER_jsa__internal_is_valid_node_id(const __CPROVER_jsa_node_id_t node_id)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  const _Bool __CPROVER_jsa__internal_is_valid_node_id_result=__CPROVER_jsa_null == node_id || node_id < __CPROVER_JSA_MAX_NODES;
  return __CPROVER_jsa__internal_is_valid_node_id_result;
}
#else
;
#endif

__CPROVER_jsa_inline _Bool __CPROVER_jsa__internal_is_in_valid_list(
    const __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node_id)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  const __CPROVER_jsa_list_id_t list=__CPROVER_jsa__internal_get_list(heap, node_id);
  const _Bool __CPROVER_jsa__internal_is_in_valid_list_result=__CPROVER_jsa_null == list || list < heap->list_count;
  return __CPROVER_jsa__internal_is_in_valid_list_result;
}
#else
;
#endif

__CPROVER_jsa_inline _Bool __CPROVER_jsa__internal_is_linking_correct(
    const __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node_id,
    const __CPROVER_jsa_node_id_t prev,
    const __CPROVER_jsa_node_id_t next)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  const _Bool __CPROVER_jsa__internal_is_linking_correct_result_tmp1=__CPROVER_jsa__internal_is_in_valid_list(heap, node_id);
  if (!__CPROVER_jsa__internal_is_linking_correct_result_tmp1) return false;
  if (__CPROVER_jsa_null != prev)
  {
    const _Bool __CPROVER_jsa__internal_is_linking_correct_result_tmp2=(node_id == __CPROVER_jsa__internal_get_next(heap, prev) && prev < node_id);
    if (!__CPROVER_jsa__internal_is_linking_correct_result_tmp2) return false;
  }
  if (__CPROVER_jsa_null != next)
  {
    const _Bool __CPROVER_jsa__internal_is_linking_correct_result_tmp3=(node_id == __CPROVER_jsa__internal_get_previous(heap, next) && node_id < next);
    if (!__CPROVER_jsa__internal_is_linking_correct_result_tmp3) return false;
  }
  return true;
}
#else
;
#endif

__CPROVER_jsa_inline _Bool __CPROVER_jsa__internal_is_valid_iterator_linking(
    const __CPROVER_jsa_abstract_heapt * const h,
    const __CPROVER_jsa_list_id_t list,
    const __CPROVER_jsa_node_id_t node_id,
    const __CPROVER_jsa_index_t index)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  if (!__CPROVER_jsa__internal_is_valid_node_id(node_id)) return false;
  if (__CPROVER_jsa_null != node_id)
      if (list != __CPROVER_jsa__internal_get_list(h, node_id)) return false;
  if (__CPROVER_jsa_null == node_id || __CPROVER_jsa__internal_is_concrete_node(node_id))
  {
    const _Bool __CPROVER_jsa__internal_is_valid_iterator_linking_tmp1=index == 0;
    return __CPROVER_jsa__internal_is_valid_iterator_linking_tmp1;
  }
  const __CPROVER_jsa__internal_index_t idx=__CPROVER_jsa__internal_get_abstract_node_index(node_id);
  const __CPROVER_jsa_id_t value_ref=h->abstract_nodes[idx].value_ref;
  const _Bool __CPROVER_jsa__internal_is_valid_iterator_linking_result=index < h->abstract_ranges[value_ref].size;
  return __CPROVER_jsa__internal_is_valid_iterator_linking_result;
}
#else
;
#endif

__CPROVER_jsa_inline __CPROVER_jsa_index_t  __CPROVER_jsa__internal_get_max_index(
    const __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node_id)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  if (__CPROVER_jsa__internal_is_concrete_node(node_id)) return 0;
  const __CPROVER_jsa__internal_index_t idx=__CPROVER_jsa__internal_get_abstract_node_index(node_id);
  const __CPROVER_jsa_id_t value_ref=heap->abstract_nodes[idx].value_ref;
  const __CPROVER_jsa_index_t __CPROVER_jsa__internal_get_max_index_result=heap->abstract_ranges[value_ref].size - 1;
  return __CPROVER_jsa__internal_get_max_index_result;
}
#else
;
#endif

__CPROVER_jsa_inline _Bool __CPROVER_jsa__internal_is_neighbour(
    const __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t lhs_node_id,
    const __CPROVER_jsa_index_t lhs_index,
    const __CPROVER_jsa_node_id_t rhs_node_id,
    const __CPROVER_jsa_index_t rhs_index)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  if (__CPROVER_jsa__internal_is_concrete_node(lhs_node_id))
  {
    if (lhs_index != 0 || rhs_index != 0) return false;
    const _Bool __CPROVER_jsa__internal_is_neighbour_tmp1=(heap->concrete_nodes[lhs_node_id].next == rhs_node_id || heap->concrete_nodes[lhs_node_id].previous == rhs_node_id);
    return __CPROVER_jsa__internal_is_neighbour_tmp1;
  }
  if (lhs_node_id == rhs_node_id)
  {
    if (lhs_index < rhs_index)
    {
      const _Bool __CPROVER_jsa__internal_is_neighbour_tmp2=lhs_index - rhs_index;
      const _Bool __CPROVER_jsa__internal_is_neighbour_tmp3=__CPROVER_jsa__internal_is_neighbour_tmp2 == 1;
      return __CPROVER_jsa__internal_is_neighbour_tmp3;
    }
    const _Bool __CPROVER_jsa__internal_is_neighbour_tmp4=rhs_index - lhs_index;
    const _Bool __CPROVER_jsa__internal_is_neighbour_tmp5=__CPROVER_jsa__internal_is_neighbour_tmp4 == 1;
    return __CPROVER_jsa__internal_is_neighbour_tmp5;
  }
  const __CPROVER_jsa_abstract_nodet node=heap->abstract_nodes[lhs_node_id];
  if (node.next == rhs_node_id)
  {
    const _Bool __CPROVER_jsa__internal_is_neighbour_tmp6=rhs_index == 0;
    const __CPROVER_jsa_index_t __CPROVER_jsa__internal_is_neighbour_tmp7=__CPROVER_jsa__internal_get_max_index(heap, lhs_node_id);
    const _Bool __CPROVER_jsa__internal_is_neighbour_tmp8=__CPROVER_jsa__internal_is_neighbour_tmp6 && __CPROVER_jsa__internal_is_neighbour_tmp7;
    return __CPROVER_jsa__internal_is_neighbour_tmp8;
  }
  if (node.previous == rhs_node_id)
  {
    const _Bool __CPROVER_jsa__internal_is_neighbour_tmp9=lhs_index == 0;
    const __CPROVER_jsa_index_t __CPROVER_jsa__internal_is_neighbour_tmp10=__CPROVER_jsa__internal_get_max_index(heap, rhs_node_id);
    const _Bool __CPROVER_jsa__internal_is_neighbour_tmp11=__CPROVER_jsa__internal_is_neighbour_tmp9 && __CPROVER_jsa__internal_is_neighbour_tmp10;
    return __CPROVER_jsa__internal_is_neighbour_tmp11;
  }
  return false;
}
#else
;
#endif

__CPROVER_jsa_inline void __CPROVER_jsa_assume_valid_list(
    const __CPROVER_jsa_abstract_heapt * const h,
    const __CPROVER_jsa_list_id_t list)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  __CPROVER_jsa_assume(list < h->list_count);
}
#else
;
#endif

__CPROVER_jsa_inline void __CPROVER_jsa_assume_valid_iterator(
    const __CPROVER_jsa_abstract_heapt * const h,
    const __CPROVER_jsa_iterator_id_t it)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  __CPROVER_jsa_assume(it < h->iterator_count);
}
#else
;
#endif

__CPROVER_jsa_inline void __CPROVER_jsa_assume_valid_heap(const __CPROVER_jsa_abstract_heapt * const h)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  // Lists point to valid head nodes.
  // Enforce strictly ascending head node ids (unless null).
  __CPROVER_jsa_id_t max_head_node=0;
  __CPROVER_jsa_assume(h->list_count <= __CPROVER_JSA_MAX_LISTS);
  for (__CPROVER_jsa_list_id_t list=0; list < __CPROVER_JSA_MAX_LISTS; ++list)
  {
    const __CPROVER_jsa_id_t head_node=h->list_head_nodes[list];
    if (list >= h->list_count)
      __CPROVER_jsa_assume(__CPROVER_jsa_null == head_node);
    else
    {
      __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(head_node));
      if (list != 0)
      {
        __CPROVER_jsa_assume(head_node > max_head_node);
        max_head_node=head_node;
      }
      __CPROVER_jsa_assume(list == __CPROVER_jsa__internal_get_list(h, head_node));
    }
  }
  // Next matches previous && prev < id < next. (Node is part of only one list, no cycles)
  for (__CPROVER_jsa_id_t cnode=0; cnode < __CPROVER_JSA_MAX_CONCRETE_NODES; ++cnode)
  {
    const __CPROVER_jsa_id_t nxt=h->concrete_nodes[cnode].next;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(nxt));
    const __CPROVER_jsa_id_t prev=h->concrete_nodes[cnode].previous;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(prev));
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_linking_correct(h, cnode, prev, nxt));
  }
  for (__CPROVER_jsa__internal_index_t anode=0; anode < __CPROVER_JSA_MAX_ABSTRACT_NODES; ++anode)
  {
    const __CPROVER_jsa_id_t nxt=h->abstract_nodes[anode].next;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(nxt));
    const __CPROVER_jsa_id_t prev=h->abstract_nodes[anode].previous;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(prev));
    const __CPROVER_jsa_id_t nid=__CPROVER_jsa__internal_get_abstract_node_id(anode);
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_linking_correct(h, nid, prev, nxt));
  }
  for (__CPROVER_jsa__internal_index_t range=0; range < __CPROVER_JSA_MAX_ABSTRACT_RANGES; ++range)
  {
    const __CPROVER_jsa_abstract_ranget r=h->abstract_ranges[range];
    __CPROVER_jsa_assume(r.size >= 1);
    __CPROVER_jsa_assume(r.min <= r.max);
  }
  // Iterators point to valid nodes
  __CPROVER_jsa_assume(h->iterator_count <= __CPROVER_JSA_MAX_ITERATORS);
  for (__CPROVER_jsa_iterator_id_t it=0; it < __CPROVER_JSA_MAX_ITERATORS; ++it)
  {
    const __CPROVER_jsa_iteratort val=h->iterators[it];
    const __CPROVER_jsa_id_t next_node=val.node_id;
    const __CPROVER_jsa_index_t next_index=val.index;
    const __CPROVER_jsa_index_t prev_index=val.previous_index;
    const __CPROVER_jsa_id_t prev_node=val.previous_node_id;
    const __CPROVER_jsa_list_id_t list=val.list;
    if (it >= h->iterator_count)
    {
      __CPROVER_jsa_assume(__CPROVER_jsa_null == next_node);
      __CPROVER_jsa_assume(__CPROVER_jsa_null == prev_node);
      __CPROVER_jsa_assume(next_index == 0);
      __CPROVER_jsa_assume(prev_index == 0);
      __CPROVER_jsa_assume(__CPROVER_jsa_null == list);
    }
    else
    {
      __CPROVER_jsa_assume(list < __CPROVER_JSA_MAX_LISTS);
      __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_iterator_linking(h, list, next_node, next_index));
      __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_iterator_linking(h, list, prev_node, prev_index));
      __CPROVER_jsa_assume(__CPROVER_jsa_null == next_node ||
                           __CPROVER_jsa_null == prev_node ||
                           __CPROVER_jsa__internal_is_neighbour(h, next_node, next_index, prev_node, prev_index));
    }
  }
}
#else
;
#endif

__CPROVER_jsa_inline __CPROVER_jsa_list_id_t __CPROVER_jsa_create_list(
    __CPROVER_jsa_abstract_heapt * const heap)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  const __CPROVER_jsa_index_t new_list=heap->list_count;
  __CPROVER_jsa_assume(new_list < __CPROVER_JSA_MAX_LISTS);
  heap->list_head_nodes[new_list]=__CPROVER_jsa_null;
  ++heap->list_count;
  return new_list;
}
#else
;
#endif

__CPROVER_jsa_inline __CPROVER_jsa_iterator_id_t __CPROVER_jsa_iterator(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_list_id_t list)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  const __CPROVER_jsa_index_t new_iterator=heap->iterator_count;
  __CPROVER_jsa_assume(new_iterator < __CPROVER_JSA_MAX_ITERATORS);
  ++heap->iterator_count;
#ifdef __cplusplus
  const __CPROVER_jsa_iteratort tmp = {
      /*.node_id=*/__CPROVER_jsa__internal_get_head_node(heap, list),
      /*.previous_node_id=*/__CPROVER_jsa_null,
      /*.index=*/0,
      /*.previous_index=*/0 };
#else
  const __CPROVER_jsa_iteratort tmp = {
      .node_id=__CPROVER_jsa__internal_get_head_node(heap, list),
      .previous_node_id=__CPROVER_jsa_null,
      .index=0,
      .previous_index=0 };
#endif
  heap->iterators[new_iterator]=tmp;
  return new_iterator;
}
#else
;
#endif

#define __CPROVER_jsa_hasNext(heap, it) __CPROVER_jsa_null != (heap)->iterators[it].node_id

__CPROVER_jsa_inline __CPROVER_jsa_data_t __CPROVER_jsa_next(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_iterator_id_t it)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  const __CPROVER_jsa_id_t node_id=heap->iterators[it].node_id;
  __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_concrete_node(node_id));
  const __CPROVER_jsa_data_t result=heap->concrete_nodes[node_id].value;
  heap->iterators[it].node_id=heap->concrete_nodes[node_id].next;
  heap->iterators[it].previous_node_id=node_id;
  return result;
}
#else
;
#endif

__CPROVER_jsa_inline void __CPROVER_jsa_remove(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_iterator_id_t it)
#ifdef __CPROVER_JSA_DEFINE_TRANSFORMERS
{
  const __CPROVER_jsa_id_t node_id_to_remove=heap->iterators[it].previous_node_id;
  __CPROVER_jsa__internal_remove(heap, node_id_to_remove);
  heap->iterators[it].previous_node_id=__CPROVER_jsa_null;
}
#else
;
#endif

// SYNTHESIS

#ifdef JSA_SYNTHESIS_H_

#ifndef __CPROVER_JSA_NUM_PRED_OPS
#define __CPROVER_JSA_NUM_PRED_OPS 10
#endif
#ifndef __CPROVER_JSA_NUM_PRED_RESULT_OPS
#define __CPROVER_JSA_NUM_PRED_RESULT_OPS __CPROVER_JSA_NUM_PRED_OPS
#endif
#ifndef __CPROVER_JSA_MAX_QUERY_SIZE
#define __CPROVER_JSA_MAX_QUERY_SIZE 10
#endif
#ifndef __CPROVER_JSA_MAX_PRED_SIZE
#define __CPROVER_JSA_MAX_PRED_SIZE (__CPROVER_JSA_MAX_QUERY_SIZE - 1)
#endif
#ifndef __CPROVER_JSA_NUM_PREDS
#define __CPROVER_JSA_NUM_PREDS (__CPROVER_JSA_MAX_QUERY_SIZE - 1)
#endif

__CPROVER_jsa_extern __CPROVER_jsa_word_t *__CPROVER_JSA_PRED_OPS[__CPROVER_JSA_NUM_PRED_OPS];
__CPROVER_jsa_extern __CPROVER_jsa_word_t *__CPROVER_JSA_PRED_RESULT_OPS[__CPROVER_JSA_NUM_PRED_RESULT_OPS];

typedef __CPROVER_jsa_word_t __CPROVER_jsa_opcodet;
typedef __CPROVER_jsa_word_t __CPROVER_jsa_opt;
typedef struct __CPROVER_jsa_pred_instruction
{
  __CPROVER_jsa_opcodet opcode;
  __CPROVER_jsa_opt result_op;
  __CPROVER_jsa_opt op0;
  __CPROVER_jsa_opt op1;
} __CPROVER_jsa_pred_instructiont;

__CPROVER_jsa_extern const __CPROVER_jsa_pred_instructiont *__CPROVER_JSA_PREDICATES[__CPROVER_JSA_NUM_PREDS];
__CPROVER_jsa_extern __CPROVER_jsa__internal_index_t __CPROVER_JSA_PREDICATE_SIZES[__CPROVER_JSA_NUM_PREDS];

#define __CPROVER_JSA_NUM_PRED_INSTRUCTIONS 1u

typedef __CPROVER_jsa_word_t __CPROVER_jsa_pred_id_t;

__CPROVER_jsa_inline __CPROVER_jsa_word_t __CPROVER_jsa_execute_pred(
    const __CPROVER_jsa_pred_id_t pred_id)
{
  __CPROVER_jsa_assume(pred_id < __CPROVER_JSA_NUM_PREDS);
  const __CPROVER_jsa_pred_instructiont * const pred=__CPROVER_JSA_PREDICATES[pred_id];
  const __CPROVER_jsa__internal_index_t pred_sz=__CPROVER_JSA_PREDICATE_SIZES[pred_id];
  __CPROVER_jsa_assert(pred_sz <= __CPROVER_JSA_MAX_PRED_SIZE, "pred_sz <= __CPROVER_JSA_MAX_PRED_SIZE");
  __CPROVER_jsa_word_t result=0;
  for (__CPROVER_jsa__internal_index_t i=0; i < __CPROVER_JSA_MAX_PRED_SIZE; ++i)
  {
    if (i >= pred_sz) break;
    const __CPROVER_jsa_pred_instructiont instr=pred[i];
    __CPROVER_jsa_assume(instr.op0 < __CPROVER_JSA_NUM_PRED_OPS);
    __CPROVER_jsa_assume(instr.op1 < __CPROVER_JSA_NUM_PRED_OPS);
    __CPROVER_jsa_assume(instr.result_op < __CPROVER_JSA_NUM_PRED_RESULT_OPS);
#define __CPROVER_jsa_execute_pred_op0_ptr __CPROVER_JSA_PRED_OPS[instr.op0]
    __CPROVER_jsa_assume(__CPROVER_jsa_execute_pred_op0_ptr);
#define __CPROVER_jsa_execute_pred_op1_ptr __CPROVER_JSA_PRED_OPS[instr.op1]
    __CPROVER_jsa_assume(__CPROVER_jsa_execute_pred_op1_ptr);
#define __CPROVER_jsa_execute_pred_result_op_ptr __CPROVER_JSA_PRED_RESULT_OPS[instr.result_op]
    __CPROVER_jsa_assume(__CPROVER_jsa_execute_pred_result_op_ptr);
#define __CPROVER_jsa_execute_pred_op0 *__CPROVER_jsa_execute_pred_op0_ptr
#define __CPROVER_jsa_execute_pred_op1 *__CPROVER_jsa_execute_pred_op1_ptr
#define __CPROVER_jsa_execute_pred_result *__CPROVER_jsa_execute_pred_result_op_ptr
    switch (instr.opcode)
    {
    case 0:
      __CPROVER_jsa_pred_opcode_0: __CPROVER_jsa_execute_pred_result=__CPROVER_jsa_execute_pred_op0 < __CPROVER_jsa_execute_pred_op1;
      break;
    default:
      __CPROVER_jsa_assume(false); // TODO: Speed-up, slow-down?
    }
    result=__CPROVER_jsa_execute_pred_result;
  }
  return result;
}

// Instrumentation adds a lambda variable at program entry. It'll have id 0.
#define __CPROVER_jsa__internal_lambda_op_id 0

__CPROVER_jsa_inline void __CPROVER_jsa_filter(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_list_id_t list,
    const __CPROVER_jsa_iterator_id_t it,
    const __CPROVER_jsa_pred_id_t pred_id)
{
  __CPROVER_jsa_node_id_t filter_node=__CPROVER_jsa__internal_get_head_node(heap, list);
  const __CPROVER_jsa_node_id_t end=heap->iterators[it].node_id;
  for (__CPROVER_jsa__internal_index_t i=0; i < __CPROVER_JSA_MAX_NODES_PER_LIST; ++i)
  {
    if (end == filter_node || __CPROVER_jsa_null == filter_node) break;
    const _Bool is_concrete=__CPROVER_jsa__internal_is_concrete_node(filter_node);
    if (is_concrete)
    {
      *__CPROVER_JSA_PRED_OPS[__CPROVER_jsa__internal_lambda_op_id]=heap->concrete_nodes[filter_node].value;
      const __CPROVER_jsa_word_t pred_result=__CPROVER_jsa_execute_pred(pred_id);
      if (pred_result == 0)
        __CPROVER_jsa__internal_remove(heap, filter_node);
      else
        filter_node=__CPROVER_jsa__internal_get_next(heap, filter_node);
    }
    else
    {
      // TODO: Implement filtering abstract nodes. (Maybe ignore and handle on whole query level?)
    }
  }
}

typedef struct __CPROVER_jsa_query_instruction
{
  __CPROVER_jsa_opcodet opcode;
  __CPROVER_jsa_opt op;
} __CPROVER_jsa_query_instructiont;

#define __CPROVER_JSA_NUM_QUERY_INSTRUCTIONS 1u

__CPROVER_jsa_inline void __CPROVER_jsa_query_execute(
    __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_query_instructiont * const query,
    const __CPROVER_jsa__internal_index_t query_size)
{
  __CPROVER_jsa_assert(query_size <= __CPROVER_JSA_MAX_QUERY_SIZE, "query_size <= __CPROVER_JSA_MAX_QUERY_SIZE");
  const __CPROVER_jsa_list_id_t list=query[0].opcode;
  __CPROVER_jsa_assume_valid_list(heap, list);
  const __CPROVER_jsa_iterator_id_t it=query[0].op;
  __CPROVER_jsa_assume_valid_iterator(heap, it);
  for (__CPROVER_jsa__internal_index_t i=1; i < __CPROVER_JSA_MAX_QUERY_SIZE; ++i)
  {
    if (i >= query_size) break;
    const __CPROVER_jsa_query_instructiont instr=query[i];
    __CPROVER_jsa_assume(instr.op < __CPROVER_JSA_NUM_PREDS);
    switch (instr.opcode)
    {
    case 0:
      __CPROVER_jsa_query_opcode_0: __CPROVER_jsa_filter(heap, list, it, instr.op);
      break;
    default:
      __CPROVER_jsa_assume(false); // TODO: Speed-up, slow-down?
    }
  }
}

__CPROVER_jsa_inline void __CPROVER_jsa_full_query_execute(
    __CPROVER_jsa_abstract_heapt * const heap,
    __CPROVER_jsa_query_instructiont * const query,
    const __CPROVER_jsa__internal_index_t query_size)
{
  const __CPROVER_jsa_iterator_id_t it=query[0].op;
  __CPROVER_jsa_assume_valid_iterator(heap, it);
  __CPROVER_jsa__internal_make_null(heap, it); // Apply query to full list.
  __CPROVER_jsa_query_execute(heap, query, query_size);
}

__CPROVER_jsa_inline void __CPROVER_jsa_synchronise_iterator(
    const __CPROVER_jsa_abstract_heapt * const heap,
    __CPROVER_jsa_abstract_heapt * const queried_heap,
    const __CPROVER_jsa_query_instructiont * const query,
    const __CPROVER_jsa__internal_index_t query_size)
{
  const __CPROVER_jsa_iterator_id_t it=query[0].op;
  __CPROVER_jsa_assume_valid_iterator(heap, it);
  queried_heap->iterators[it]=heap->iterators[it];
}

__CPROVER_jsa_inline void __CPROVER_jsa_verify_synchronise_iterator(
    const __CPROVER_jsa_abstract_heapt * const heap,
    __CPROVER_jsa_abstract_heapt * const queried_heap,
    const __CPROVER_jsa_iterator_id_t it)
{
  __CPROVER_jsa_assume_valid_iterator(heap, it);
  queried_heap->iterators[it]=heap->iterators[it];
}


typedef struct __CPROVER_jsa_invariant_instruction
{
  __CPROVER_jsa_opcodet opcode;
} __CPROVER_jsa_invariant_instructiont;

#define __CPROVER_JSA_NUM_INV_INSTRUCTIONS 1u

__CPROVER_jsa_inline _Bool __CPROVER_jsa_invariant_execute(
    const __CPROVER_jsa_abstract_heapt * const heap,
    const __CPROVER_jsa_abstract_heapt * const queried_heap,
    const __CPROVER_jsa_invariant_instructiont * const inv,
    const __CPROVER_jsa__internal_index_t inv_size)
{
  __CPROVER_jsa_assume(inv_size == 1u);
  __CPROVER_jsa_assume(inv[0].opcode == 0); // Single instruction
  const _Bool __CPROVER_jsa_invariant_execute_result=__CPROVER_jsa__internal_are_heaps_equal(heap, queried_heap);
  return __CPROVER_jsa_invariant_execute_result;
}

#endif

#endif /* CEGIS_JSA_TRANSFORMERS_H_ */