#ifndef CLASS_H
#define CLASS_H

typedef struct {
  const char *name;
} Class;

/**
 * Gets the class name.
 *
 * @param c the class to get the name of.
 * @return the name of the class.
 */
const char *class_name(const Class *c);

#endif /* CLASS_H */
