/* FUNCTION: __CPROVER_jsa_create_heap */

#ifndef JSA_TRANSFORMERS_H_

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

typedef unsigned char __CPROVER_jsa_word_t;
typedef __CPROVER_jsa_word_t  __CPROVER_jsa_data_t;
typedef __CPROVER_jsa_word_t  __CPROVER_jsa_index_t;
typedef __CPROVER_jsa_word_t  __CPROVER_jsa_id_t;
typedef __CPROVER_jsa_id_t  __CPROVER_jsa_node_id_t;
typedef __CPROVER_jsa_id_t  __CPROVER_jsa_list_id_t;
typedef __CPROVER_jsa_id_t  __CPROVER_jsa_iterator_id_t;
#define __CPROVER_jsa_null 0xFF
typedef
struct abstract_heap
{
  /**
   * Concrete node with explicit value.
   */
  struct concrete_nodet
  {
    __CPROVER_jsa_node_id_t next;
    __CPROVER_jsa_node_id_t previous;
    __CPROVER_jsa_list_id_t list;
    __CPROVER_jsa_data_t value;
  } concrete_nodes[__CPROVER_JSA_MAX_CONCRETE_NODES ];
  /**
   * Abstract nodes may assume any of a set of pre-defined values
   * (value_ref to abstract_ranget).
   */
  struct abstract_nodet
  {
    __CPROVER_jsa_node_id_t next;
    __CPROVER_jsa_node_id_t previous;
    __CPROVER_jsa_list_id_t list;
    __CPROVER_jsa_id_t value_ref;
#if __CPROVER_JSA_MAX_ABSTRACT_NODES > 0
  } abstract_nodes[__CPROVER_JSA_MAX_ABSTRACT_NODES ];
#else
}*abstract_nodes;
#endif
  /**
   * Set of pre-defined, possible values for abstract nodes.
   */
  struct abstract_ranget
  {
    __CPROVER_jsa_data_t min;
    __CPROVER_jsa_data_t max;
    __CPROVER_jsa_index_t size;
#if __CPROVER_JSA_MAX_ABSTRACT_NODES > 0
  } abstract_ranges[__CPROVER_JSA_MAX_ABSTRACT_RANGES ];
#else
}*abstract_ranges;
#endif
  /**
   * Iterators point to a node and give the relative index
   * within that node.
   */
  struct iteratort
  {
    __CPROVER_jsa_node_id_t node_id;
    __CPROVER_jsa_node_id_t previous_node_id;
    __CPROVER_jsa_index_t index;
    __CPROVER_jsa_index_t previous_index;
    __CPROVER_jsa_list_id_t list;
  } iterators[__CPROVER_JSA_MAX_ITERATORS ];
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

// Node utility functions
__CPROVER_jsa_node_id_t __CPROVER_jsa__internal_get_head_node(const abstract_heapt * const heap,
    const __CPROVER_jsa_list_id_t list)
{
  return heap->list_head_nodes[list];
}

_Bool __CPROVER_jsa__internal_is_concrete_node(
    const __CPROVER_jsa_node_id_t node)
{
  return node < __CPROVER_JSA_MAX_CONCRETE_NODES;
}

_Bool __CPROVER_jsa__internal_is_abstract_node(
    const __CPROVER_jsa_node_id_t node)
{
  return !__CPROVER_jsa__internal_is_concrete_node(node);
}

unsigned int __CPROVER_jsa__internal_get_abstract_node_index(
    const __CPROVER_jsa_node_id_t node)
{
  return node - __CPROVER_JSA_MAX_CONCRETE_NODES;
}

__CPROVER_jsa_id_t  __CPROVER_jsa__internal_get_abstract_node_id(const unsigned int node_index)

{
  return __CPROVER_JSA_MAX_CONCRETE_NODES + node_index;
}

__CPROVER_jsa_list_id_t  __CPROVER_jsa__internal_get_list(const abstract_heapt * const heap,
const __CPROVER_jsa_node_id_t node)

{
  if (__CPROVER_jsa_null == node) return __CPROVER_jsa_null;
  if (__CPROVER_jsa__internal_is_concrete_node(node))
    return heap->concrete_nodes[node].list;
  return heap->abstract_nodes[node].list;
}

void __CPROVER_jsa__internal_set_next(abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node, const __CPROVER_jsa_node_id_t next_node)
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

__CPROVER_jsa_node_id_t  __CPROVER_jsa__internal_get_next(const abstract_heapt * const heap,
const __CPROVER_jsa_node_id_t node)

{
  if (__CPROVER_jsa__internal_is_concrete_node(node))
    return heap->concrete_nodes[node].next;
  const __CPROVER_jsa_index_t index=
      __CPROVER_jsa__internal_get_abstract_node_index(node);
  return heap->abstract_nodes[index].next;
}

void __CPROVER_jsa__internal_set_previous(abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t node, const __CPROVER_jsa_node_id_t previous_node)
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

__CPROVER_jsa_node_id_t  __CPROVER_jsa__internal_get_previous(const abstract_heapt * const heap,
const __CPROVER_jsa_node_id_t node)

{
  if (__CPROVER_jsa__internal_is_concrete_node(node))
    return heap->concrete_nodes[node].previous;
  const __CPROVER_jsa_index_t index=
      __CPROVER_jsa__internal_get_abstract_node_index(node);
  return heap->abstract_nodes[index].previous;
}

// Heap sanity functions
_Bool __CPROVER_jsa__internal_is_valid_node_id(const __CPROVER_jsa_node_id_t node_id)
{
  return __CPROVER_jsa_null == node_id || node_id < __CPROVER_JSA_MAX_NODES;
}

_Bool __CPROVER_jsa__internal_is_in_valid_list(
    const abstract_heapt * const heap, const __CPROVER_jsa_node_id_t node_id)
{
  const __CPROVER_jsa_list_id_t list=__CPROVER_jsa__internal_get_list(heap,
      node_id);
  return __CPROVER_jsa_null == list || list < heap->list_count;
}

_Bool __CPROVER_jsa__internal_is_linking_correct(
    const abstract_heapt * const heap, const __CPROVER_jsa_node_id_t node_id,
    const __CPROVER_jsa_node_id_t prev, const __CPROVER_jsa_node_id_t next)
{
  return __CPROVER_jsa__internal_is_in_valid_list(heap, node_id)
      && (__CPROVER_jsa_null == prev
          || (node_id == __CPROVER_jsa__internal_get_next(heap, prev)
              && prev < node_id))
      && (__CPROVER_jsa_null == next
          || (node_id == __CPROVER_jsa__internal_get_previous(heap, next)
              && node_id < next));
}

_Bool __CPROVER_jsa__internal_is_valid_iterator_linking(
    const abstract_heapt * const h, const __CPROVER_jsa_list_id_t list,
    const __CPROVER_jsa_node_id_t node_id, const __CPROVER_jsa_index_t index)
{
  if (!__CPROVER_jsa__internal_is_valid_node_id(node_id)) return false;
  if (__CPROVER_jsa_null != node_id
      && list != __CPROVER_jsa__internal_get_list(h, node_id)) return false;
  if (__CPROVER_jsa_null == node_id
      || __CPROVER_jsa__internal_is_concrete_node(node_id)) return index == 0;
  const unsigned int idx=__CPROVER_jsa__internal_get_abstract_node_index(
      node_id);
  const __CPROVER_jsa_id_t value_ref=h->abstract_nodes[idx].value_ref;
  return index < h->abstract_ranges[value_ref].size;
}

__CPROVER_jsa_index_t  __CPROVER_jsa__internal_get_max_index(const abstract_heapt * const heap,
const __CPROVER_jsa_node_id_t node_id)

{
  if (__CPROVER_jsa__internal_is_concrete_node(node_id)) return 0;
  const unsigned int idx=__CPROVER_jsa__internal_get_abstract_node_index(
      node_id);
  const __CPROVER_jsa_id_t value_ref=heap->abstract_nodes[idx].value_ref;
  return heap->abstract_ranges[value_ref].size - 1;
}

_Bool __CPROVER_jsa__internal_is_neighbour(const abstract_heapt * const heap,
    const __CPROVER_jsa_node_id_t lhs_node_id, const __CPROVER_jsa_index_t lhs_index,
    const __CPROVER_jsa_node_id_t rhs_node_id, const __CPROVER_jsa_index_t rhs_index)
{
  if (__CPROVER_jsa__internal_is_concrete_node(lhs_node_id))
  {
    if (lhs_index != 0 || rhs_index != 0) return false;
    return heap->concrete_nodes[lhs_node_id].next == rhs_node_id
        || heap->concrete_nodes[lhs_node_id].previous == rhs_node_id;
  }
  if (lhs_node_id == rhs_node_id)
  {
    if (lhs_index < rhs_index) return lhs_index - rhs_index == 1;
    return rhs_index - lhs_index == 1;
  }
  const struct abstract_nodet node=heap->abstract_nodes[lhs_node_id];
  if (node.next == rhs_node_id)
    return rhs_index == 0
        && lhs_index == __CPROVER_jsa__internal_get_max_index(heap, lhs_node_id);
  if (node.previous == rhs_node_id)
    return lhs_index == 0
        && rhs_index == __CPROVER_jsa__internal_get_max_index(heap, rhs_node_id);
  return false;
}

void __CPROVER_jsa__internal_unused(void)
{
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
  __CPROVER_jsa_id_t max_head_node=h->list_head_nodes[0];
  __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(max_head_node));
  __CPROVER_jsa_list_id_t list_count=0;
  if (max_head_node != __CPROVER_jsa_null)
  {
    __CPROVER_jsa_assume(
        0 == __CPROVER_jsa__internal_get_list(h, max_head_node));
    list_count=1;
  }
  for (__CPROVER_jsa_list_id_t list=1; list < __CPROVER_JSA_MAX_LISTS; ++list)
  {
    const __CPROVER_jsa_id_t head_node=h->list_head_nodes[list];
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(head_node));
    if (head_node != __CPROVER_jsa_null)
    {
      __CPROVER_jsa_assume(head_node > max_head_node);
      __CPROVER_jsa_assume(
          list == __CPROVER_jsa__internal_get_list(h, head_node));
      max_head_node=head_node;
      ++list_count;
    }
  }
  __CPROVER_jsa_assume(h->list_count == list_count);
// Next matches previous && prev < id < next. (Node is part of only one list, no cycles)
  for (__CPROVER_jsa_id_t cnode=0; cnode < __CPROVER_JSA_MAX_CONCRETE_NODES;
      ++cnode)
  {
    const __CPROVER_jsa_id_t nxt=h->concrete_nodes[cnode].next;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(nxt));
    const __CPROVER_jsa_id_t prev=h->concrete_nodes[cnode].previous;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(prev));
    __CPROVER_jsa_assume(
        __CPROVER_jsa__internal_is_linking_correct(h, cnode, prev, nxt));
  }
  for (unsigned int anode=0; anode < __CPROVER_JSA_MAX_ABSTRACT_NODES; ++anode)
  {
    const __CPROVER_jsa_id_t nxt=h->abstract_nodes[anode].next;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(nxt));
    const __CPROVER_jsa_id_t prev=h->abstract_nodes[anode].previous;
    __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_valid_node_id(prev));
    const __CPROVER_jsa_id_t nid=__CPROVER_jsa__internal_get_abstract_node_id(
        anode);
    __CPROVER_jsa_assume(
        __CPROVER_jsa__internal_is_linking_correct(h, nid, prev, nxt));
  }
  for (unsigned int range=0; range < __CPROVER_JSA_MAX_ABSTRACT_RANGES; ++range)
  {
    const struct abstract_ranget r=h->abstract_ranges[range];
    __CPROVER_jsa_assume(r.size >= 1);
    __CPROVER_jsa_assume(r.min <= r.max);
  }
// Iterators point to valid nodes
  __CPROVER_jsa_iterator_id_t iterator_count=0;
  for (__CPROVER_jsa_iterator_id_t it=0; it < __CPROVER_JSA_MAX_ITERATORS; ++it)
  {
    struct iteratort val=h->iterators[it];
    const __CPROVER_jsa_id_t next_node=val.node_id;
    const __CPROVER_jsa_index_t next_index=val.index;
    const __CPROVER_jsa_index_t prev_index=val.previous_index;
    const __CPROVER_jsa_id_t prev_node=val.previous_node_id;
    const __CPROVER_jsa_list_id_t list=val.list;
    if (__CPROVER_jsa_null == list)
    {
      __CPROVER_jsa_assume(
          __CPROVER_jsa_null == next_node && 0 == next_index && __CPROVER_jsa_null == prev_node && 0 == prev_index);
    } else
    {
      ++iterator_count;
      __CPROVER_jsa_assume(list < __CPROVER_JSA_MAX_LISTS);
      __CPROVER_jsa_assume(
          __CPROVER_jsa__internal_is_valid_iterator_linking(h, list, next_node,
              next_index));
      __CPROVER_jsa_assume(
          __CPROVER_jsa__internal_is_valid_iterator_linking(h, list, prev_node,
              prev_index));
      __CPROVER_jsa_assume(
          __CPROVER_jsa_null == next_node || __CPROVER_jsa_null == prev_node || __CPROVER_jsa__internal_is_neighbour(h, next_node, next_index, prev_node, prev_index));
    }
  }
  __CPROVER_jsa_assume(h->iterator_count == iterator_count);
  return &__CPROVER_jsa_heap;
}

#endif /* CEGIS_JSA_TRANSFORMERS_H_ */

/* FUNCTION: __CPROVER_jsa_create_nondet_list */
__CPROVER_jsa_inline __CPROVER_jsa_list_id_t __CPROVER_jsa_create_list(
    const abstract_heapt * const heap)
{
  const __CPROVER_jsa_index_t new_list=heap->list_count;
  __CPROVER_jsa_assume(new_list < __CPROVER_JSA_MAX_LISTS);
  heap->list_head_nodes[new_list]=__CPROVER_jsa_null;
  ++heap->list_count;
  return new_list;
}

/* FUNCTION: __CPROVER_jsa_iterator */
__CPROVER_jsa_inline __CPROVER_jsa_iterator_id_t __CPROVER_jsa_iterator(
    abstract_heapt * const heap, const __CPROVER_jsa_list_id_t list)
{
  const __CPROVER_jsa_index_t new_iterator=heap->iterator_count;
  __CPROVER_jsa_assume(new_iterator < __CPROVER_JSA_MAX_ITERATORS);
  ++heap->iterator_count;
  const struct iteratort tmp={ .node_id=__CPROVER_jsa__internal_get_head_node(
      heap, list), .previous_node_id=
  __CPROVER_jsa_null, .index=0, .previous_index=0 };
  heap->iterators[new_iterator]=tmp;
  return new_iterator;
}

/* FUNCTION: __CPROVER_jsa_hasNext */
__CPROVER_jsa_inline _Bool __CPROVER_jsa_hasNext(
    const abstract_heapt * const heap, const __CPROVER_jsa_iterator_id_t it)
{
  return __CPROVER_jsa_null != heap->iterators[it].node_id;
}

/* FUNCTION: __CPROVER_jsa_next */
__CPROVER_jsa_inline __CPROVER_jsa_data_t __CPROVER_jsa_next(
    abstract_heapt * const heap, const __CPROVER_jsa_iterator_id_t it)
{
  const __CPROVER_jsa_id_t node_id=heap->iterators[it].node_id;
  __CPROVER_jsa_assume(__CPROVER_jsa__internal_is_concrete_node(node_id));
  const __CPROVER_jsa_data_t result=heap->concrete_nodes[node_id].value;
  heap->iterators[it].node_id=heap->concrete_nodes[node_id].next;
  heap->iterators[it].previous_node_id=node_id;
  return result;
}

/* FUNCTION: __CPROVER_jsa_remove */
__CPROVER_jsa_inline void __CPROVER_jsa_remove(abstract_heapt * const heap,
    const __CPROVER_jsa_iterator_id_t it)
{
  const __CPROVER_jsa_id_t node_id_to_remove=
      heap->iterators[it].previous_node_id;
  __CPROVER_jsa_assume(
      __CPROVER_jsa__internal_is_concrete_node(node_id_to_remove));
  const __CPROVER_jsa_id_t previous_node_id=
      heap->concrete_nodes[node_id_to_remove].previous;
  const __CPROVER_jsa_id_t next_node_id=
      heap->concrete_nodes[node_id_to_remove].next;
  __CPROVER_jsa__internal_set_next(heap, previous_node_id, next_node_id);
  __CPROVER_jsa__internal_set_previous(heap, next_node_id, previous_node_id);
  heap->iterators[it].previous_node_id=__CPROVER_jsa_null;
}

/* FUNCTION: __CPROVER_jsa_query_execute */
#ifdef JSA_SYNTHESIS_H_
typedef unsigned char __CPROVER_jsa_opcodet;
typedef unsigned char __CPROVER_jsa_opt;
typedef struct __CPROVER_jsa_instruction
{
  __CPROVER_jsa_opcodet opcode;
  __CPROVER_jsa_opt op0;
  __CPROVER_jsa_opt op1;
  __CPROVER_jsa_opt op2;
} __CPROVER_jsa_instructiont;

__CPROVER_jsa_inline _Bool __CPROVER_jsa_query_compare(
    const abstract_heapt * const heap, const __CPROVER_jsa_list_id_t list,
    const __CPROVER_jsa_iterator_id_t it,
    const __CPROVER_jsa_list_id_t candidate_list,
    const __CPROVER_jsa_instructiont * const query)
{
  __CPROVER_jsa_node_id_t lhs_node=__CPROVER_jsa__internal_get_head_node(heap, list);
  const struct iteratort iterator=heap->iterators[it];
  const __CPROVER_jsa_node_id_t it_node=iterator.node_id;
  __CPROVER_jsa_node_id_t rhs_node=__CPROVER_jsa__internal_get_head_node(heap, candidate_list);
  for (unsigned int i = 0; i < __CPROVER_JSA_MAX_NODES_PER_LIST; ++i)
  {
    if (lhs_node == it_node) break;
    if (__CPROVER_jsa__internal_is_conrete_node(lhs_node))
    {
      heap->concrete_nodes[lhs_node].value;
    }
    else
    {

    }
  }
  return __CPROVER_jsa_null == rhs_node;
}

__CPROVER_jsa_inline void __CPROVER_jsa_query_execute(
    abstract_heapt * const heap, const __CPROVER_jsa_list_id_t list,
    const __CPROVER_jsa_instructiont * const query)
{
}
#endif
