#ifndef TRIETREE_H
#define TRIETREE_H

class QString;
class TrieTreePrivate;
class TrieTree {
public:
  TrieTree();
  ~TrieTree();
  //增丶删丶查
  bool addString(const QString &str);
  void delString(const QString &str);
  bool findString(const QString &str);

private:
  TrieTreePrivate *d;
};

#endif // TRIETREE_H
