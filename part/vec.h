#ifndef VEC_H
#define VEC_H

#include "part.h"

#ifndef IS_VEC_C
#define INLINE extern inline
#else
#define INLINE inline
#endif

#define VECSIZE ((NODES + 7) >> 3)

typedef struct vec_s {
	uchar v[VECSIZE];
} vec_t;

typedef unsigned int vech;

typedef enum {
	VECH_GROW = -1,		/* insert ok, tree depth has grown */
	VECH_OK = 0,		/* insert ok, tree depth has not grown */
	VECH_EXISTS = 1		/* no insert, element already exists */
} vech_insert_t;

typedef struct vech_s {
	vech left;
	vech right;
	int balance;
	uint ref;
} vech_t;

typedef struct vech_tree_s {
	vech_t* vecharena;
	vech vha_size;
	vech vha_used;
	vech vha_root;
	vec_t* vecarena;
	uint va_size;
	uint va_used;
} vech_tree;

vech_tree* vech_new(void);
void vech_delete(vech_tree* tree);
vech_tree* vech_dup(vech_tree* source);
vech_insert_t vech_seen(vech_tree* tree, vec_t* v);

INLINE void vec_zero(vec_t* v) {
	memset(v, 0, sizeof(vec_t));
}

INLINE void vec_copy(vec_t* src, vec_t* dest) {
	memcpy(dest, src, sizeof(vec_t));
}

INLINE void vec_setbit(vec_t* v, uint i) {
	v->v[i >> 3] |= 1 << (i & 7);
}

INLINE void vec_clearbit(vec_t* v, uint i) {
	v->v[i >> 3] &= ~(1 << (i & 7));
}

INLINE uint vec_testbit(vec_t* v, uint i) {
	return (v->v[i >> 3] & (1 << (i & 7))) ? 1 : 0;
}

#define DO_VEC(state) { \
	uint i; \
	for (i = 0; i < VECSIZE; ++i) { \
		state; \
	} \
}

INLINE void vec_or(vec_t* src, vec_t* dest)
	DO_VEC(dest->v[i] |= src->v[i])
INLINE void vec_and(vec_t* src, vec_t* dest)
	DO_VEC(dest->v[i] &= src->v[i])
INLINE void vec_xor(vec_t* src, vec_t* dest)
	DO_VEC(dest->v[i] ^= src->v[i])
INLINE void vec_or3(vec_t* s1, vec_t* s2, vec_t* dest)
	DO_VEC(dest->v[i] = s1->v[i] | s2->v[i])
INLINE void vec_and3(vec_t* s1, vec_t* s2, vec_t* dest)
	DO_VEC(dest->v[i] = s1->v[i] & s2->v[i])
INLINE void vec_xor3(vec_t* s1, vec_t* s2, vec_t* dest)
	DO_VEC(dest->v[i] = s1->v[i] ^ s2->v[i])

INLINE int vec_empty(vec_t* v) {
	uint i;
	for (i = 0; i < VECSIZE; ++i) {
		if (v->v[i])
			return 0;
	}
	return 1;
}

extern uchar transform[];
INLINE int vec_cmp(vec_t* s1, vec_t* s2) {
	uint i;
	signed int c;
	for (i = 0; i < VECSIZE; ++i) {
		c = transform[s1->v[i]] - transform[s2->v[i]];
		if (c > 0)
			return 1;
		if (c < 0)
			return -1;
	}
	return 0;
}

/* temporary, used only by canonical_set() */
extern uint bit_count[];
INLINE uint vec_bitcount(vec_t* v) {
	uint c = 0, i;
	for (i = 0; i < VECSIZE; ++i)
		c += bit_count[v->v[i]];
	return c;
}

extern vec_t connections[];
INLINE vec_t* connect_vec(uint i) {
	return &connections[i];
}

#endif
