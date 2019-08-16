#include "bittree.h"
#include <QtMath>

quint64 pow(quint32 cardinalNumber, quint32 secondPower) {
  quint64 tem = cardinalNumber;
  for (auto i = 0; i < secondPower; i++)
    tem *= cardinalNumber;
  return tem;
}

class BitTreePrivate {
public:
  explicit BitTreePrivate();
  char *bitmap;
  BitTree::State state;
  quint64 max;
  void setBitmap(quint64 m, char n);
  bool peekBitmap(quint64 m, char n);
  bool repeat(quint64 m, char n);
};

BitTree::BitTree(quint64 capacity, BitTree::State state)
    : d(new BitTreePrivate) {
  d->bitmap =
      new char[state == Repeat ? (capacity / 8 * 2 + 1) : (capacity / 8 + 1)];
  memset(d->bitmap, 0,
         state == Repeat ? (capacity / 8 * 2 + 1) : (capacity / 8 + 1));
  d->state = state;
  d->max = capacity;
}

BitTree::~BitTree() {
  delete[] d->bitmap;
  delete d;
}

void BitTree::write(quint64 digital) {
  if (digital > (d->max - 1))
    return;
  if (d->state == Repeat) {
    quint64 m = digital / 4;
    quint64 n = digital % 4;
    d->setBitmap(m, char(pow(2, (6 - n * 2))));
  } else {
    quint64 m = digital / 8;
    quint64 n = digital % 8;
    d->setBitmap(m, char(pow(2, (7 - n))));
  }
}

bool BitTree::find(quint64 digital) {
  if (digital > (d->max - 1))
    return false;
  if (d->state == Repeat) {
    quint64 m = digital / 4;
    quint64 n = digital % 4;
    return d->peekBitmap(m, char(pow(2, (6 - n * 2))));
  } else {
    quint64 m = digital / 8;
    quint64 n = digital % 8;
    return d->peekBitmap(m, char(pow(2, (7 - n))));
  }
}

bool BitTree::repeat(quint64 digital) {
  if (d->state == NoRepeat)
    return false;
  if (digital > (d->max - 1))
    return false;
  quint64 m = digital / 4;
  quint64 n = digital % 4;
  return d->repeat(m, char(pow(2, (6 - n * 2))));
}

BitTreePrivate::BitTreePrivate() {}

void BitTreePrivate::setBitmap(quint64 m, char n) {
  if (state == BitTree::Repeat) {
    char tem = bitmap[m] & (3 * n);
    if (tem == (3 * n))
      return;
    bitmap[m] = bitmap[m] + n;
  } else {
    bitmap[m] = bitmap[m] | n;
  }
}

bool BitTreePrivate::peekBitmap(quint64 m, char n) {
  if (state == BitTree::Repeat) {
    return quint8(bitmap[m] & (3 * n)) == 0 ? false : true;
  } else {
    return quint8(bitmap[m] & n) == 0 ? false : true;
  }
}

bool BitTreePrivate::repeat(quint64 m, char n) {
  return quint8(bitmap[m] & (3 * n)) <= n ? false : true;
}
