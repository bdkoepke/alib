#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "container.h"

typedef struct _dictionary_vtable dictionary_vtable;
typedef struct Dictionary {
  dictionary_vtable *vtable;
} Dictionary;
struct _dictionary_vtable {
  container_vtable container;
  void *(*max)(const Dictionary *);
  void *(*min)(const Dictionary *);
  void *(*predecessor)(const Dictionary *, const void *);
  void *(*successor)(const Dictionary *, const void *);
};

void *dictionary_max(const Dictionary *);
void *dictionary_min(const Dictionary *);
void *dictionary_predecessor(const Dictionary *, const void *);
void *dictionary_successor(const Dictionary *, const void *);

#endif /* DICTIONARY_H */
