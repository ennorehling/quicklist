/*
Copyright (c) 2010-2011, Enno Rehling <enno@eressea.de>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
**/

#ifndef _QUICKLIST_H
#define _QUICKLIST_H

/* From http://en.wikipedia.org/wiki/Unrolled_linked_list
 * In computer programming, an unrolled linked list is a variation on the
 * linked list which stores multiple elements in each node. It can
 * dramatically increase cache performance, while decreasing the memory
 * overhead associated with storing list metadata such as references. It
 * is related to the B-tree.
*/

#ifdef __cplusplus
extern "C" {
#endif

    typedef int ql_bool;
    typedef struct quicklist quicklist;
    typedef struct ql_iter {
        struct quicklist *l;
        int i;
    } ql_iter;
    
    ql_bool qli_equal(struct ql_iter a, struct ql_iter b);
    ql_iter qli_begin(struct quicklist *ql);
    ql_iter qli_end(struct quicklist *ql);
    void qli_incr(struct ql_iter *iter);
    void * qli_get(const struct ql_iter iter);

    void ql_map_reduce(struct quicklist *ql, void (*mapfunc)(void *entry, void *data), void(*reducefunc)(void *data, void *result), void *data, void *result);
    
    void * ql_get(const struct quicklist *ql, int qi);
    int ql_length(const struct quicklist *ql);
    void ql_free(struct quicklist *ql);
    ql_bool ql_empty(const struct quicklist *ql);

    struct quicklist * ql_push(struct quicklist **qlp, void *data);
    int ql_delete(struct quicklist **qlp, int index);
    int ql_insert(struct quicklist **qlp, int index, void *data);
    void ql_foreach(struct quicklist *ql, void (*cb) (void *));
    void ql_foreachx(struct quicklist *ql, void (*cb) (void *, void *), void *);
    int ql_advance(struct quicklist **iterator, int *index, int stride);
    void *ql_replace(struct quicklist *ql, int index, void *data);
    
    /* you can use it as a set (sorted pointers)*/
    int ql_set_insert(struct quicklist **qlp, void *data);
    ql_bool ql_set_find(struct quicklist **qlp, int *qip, const void *data);
    int ql_set_remove(struct quicklist **qlp, void *data);

#ifdef __cplusplus
}
#endif
#endif
