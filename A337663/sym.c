#include <stdlib.h>

#include "sym.h"
#include "group.h"

void init_sym(void) {
    return;
}

bool is_transpose(sym_t s) {
    return (s & 4) ? 1 : 0;
}

bool sym_check(sym_t s, int x, int y, int *v) {
    int xm = x - 1, ym = y - 1;

    if (x != y && is_transpose(s))
        return 0;

    switch (s) {
        case xy:
            return 1;
        case xY:
            for (int i = 0; i <= xm; ++i)
                for (int j = 0; j + j < ym; ++j)
                    if (v[i * y + j] != v[i * y + ym - j])
                        return 0;
            return 1;
        case Xy:
            for (int i = 0; i + i < xm; ++i)
                for (int j = 0; j <= ym; ++j)
                    if (v[i * y + j] != v[(xm - i) * y + j]) 
                        return 0;
            return 1;
        case XY:
            for (int i = 0; i <= xm; ++i)
                for (int j = 0; j <= ym; ++j)
                    if (v[i * y + j] != v[(xm - i) * y + ym - j])
                        return 0;
            return 1;
        case yx:
            for (int i = 0; i <= xm; ++i)
                for (int j = i; j <= ym; ++j)
                    if (v[i * y + j] != v[j * y + i])
                        return 0;
            return 1;
        case yX:
            for (int i = 0; i <= xm; ++i)
                for (int j = 0; j <= ym; ++j) 
                    if (v[i * y + j] != v[j * y + ym - i])
                        return 0;
            return 1;
        case Yx:
            for (int i = 0; i <= xm; ++i)
                for (int j = 0; j <= ym; ++j) 
                    if (v[i * y + j] != v[(xm - j) * y + i])
                        return 0;
            return 1;
        case YX:            for (int i = 0; i <= xm; ++i)
                for (int j = 0; j <= ym; ++j) 
                    if (v[i * y + j] != v[(xm - j) * y + ym - i])
                        return 0;
            return 1;
    }
}

int *sym_transform(sym_t s, int x, int y, int *vals) {
    int *v = malloc(sizeof(int *) * x * y);
    int xm = x - 1, ym = y - 1;

    switch (s) {
        case xy:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j) 
                    v[i * y + j] = vals[i * y + j];
            break;
        case xY:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j)
                    v[i * y + ym - j] = vals[i * y + j];
            break;
        case Xy:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j) 
                    v[(xm - i) * y + j] = vals[i * y + j];
            break;
        case XY:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j) 
                    v[(xm - i) * y + ym - j] = vals[i * y + j];
            break;
        case yx:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j) 
                    v[j * y + i] = vals[i * y + j];
            break;
        case yX:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j)
                    v[j * y + ym - i] = vals[i * y + j];
            break;
        case Yx:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j) 
                    v[(xm - j) * y + i] = vals[i * y + j];
            break;
        case YX:
            for (int i = 0; i < x; ++i)
                for (int j = 0; j < y; ++j) 
                    v[(xm - j) * y + ym - i] = vals[i * y + j];
            break;
    }
    return v;
}

loc_t sym_transloc(sym_t s, group_t *g, loc_t l) {
    int xm = g->x - 1, ym = g->y - 1;

    switch (s) {
        case xy:
            return (loc_t){ l.x, l.y };
        case xY:
            return (loc_t){ l.x, ym - l.y };
        case Xy:
            return (loc_t){ xm - l.x, l.y };
        case XY:
            return (loc_t){ xm - l.x, ym - l.y };
        case yx:
            return (loc_t){ l.y, l.x };
        case yX:
            return (loc_t){ l.y, xm - l.x };
        case Yx:
            return (loc_t){ ym - l.y, l.x };
        case YX:
            return (loc_t){ ym - l.y, xm - l.x };
    }
}
