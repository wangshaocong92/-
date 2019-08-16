#ifndef BITTREE_H
#define BITTREE_H
#include <QtGlobal>

class BitTreePrivate;
class BitTree {
public:
  enum State { Repeat, NoRepeat };
  BitTree(quint64 capacity, State state);
  ~BitTree();
  void write(quint64 digital);
  bool find(quint64 digital);
  bool repeat(quint64 digital);

private:
  BitTreePrivate *d;
};

#endif // BITTREE_H
