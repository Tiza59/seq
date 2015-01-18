#ifndef PP_H
#define PP_H

#include <string.h>
#include "walker.h"

typedef struct pp_s_n {
	int n;
	int p;
	int pp;
	int d;
	int usable;
} pp_n;

typedef struct pp_s_value {
	int value;
	int parent;
	int inv;
} pp_value;

typedef struct pp_s_pp {
	int p;
	int pp;
	int depend;
	int valsize;
	int valmax;
	pp_value* value;
	int min_discard;
	int invtotal;
	int total;
	int denominator;
	int invdenom;
	struct s_walk_result* wr;
	struct s_walker* w;
	int need_num;
	int need_den;
	int spare_num;
	int spare_den;
} pp_pp;

extern pp_n* ppn;
extern pp_pp* pppp;
extern pp_pp** pplist;
extern int pplistsize;
extern int pplistmax;
#define MINPPSET 10

extern void setup_pp(int k);
extern void teardown_pp(void);
extern void pp_study(int target);
extern int pp_find(int target);
extern void pp_save_r(pp_n* ppi);

#endif /* PP_H */
