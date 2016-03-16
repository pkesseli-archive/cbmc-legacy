#ifndef CEGIS_BJC_H_
#define CEGIS_BJC_H_

typedef struct abstract_heap abstract_heapt;

typedef unsigned int word_t;
typedef word_t ptr_t;
typedef word_t data_t;

ptr_t __CPROVER_bjc_new_list(abstract_heapt *heap);
ptr_t __CPROVER_bjc_iterator(abstract_heapt *heap, ptr_t list);
data_t __CPROVER_bjc_next(abstract_heapt * heap, ptr_t it);
_Bool __CPROVER_bjc_hasNext(const abstract_heapt * heap, ptr_t it);
void __CPROVER_bjc_it_remove(abstract_heapt *heap, ptr_t it);

#endif /* CEGIS_BJC_H_ */
