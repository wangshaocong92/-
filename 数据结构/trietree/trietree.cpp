#include "trietree.h"
#include <QString>
#include <QVector>

class TrieTreeNode {
public:
  TrieTreeNode(QChar ch, bool endChar, int useTime = 1,
               QVector<TrieTreeNode *> nodeVector = QVector<TrieTreeNode *>())
      : ch(ch), nodeVector(nodeVector), endChar(endChar), useTime(useTime) {}
  ~TrieTreeNode() {
    for (auto i : nodeVector) {
      if (i != nullptr) {
        delete i;
        i = nullptr;
      }
    }
  }
  QChar ch;
  QVector<TrieTreeNode *> nodeVector;
  bool endChar;
  int useTime;

  inline void addNodePtr(TrieTreeNode *nodePtr) { nodeVector.append(nodePtr); }
  inline void setEndChar(bool end) { endChar = end; }
  inline void addUseTime(bool add) { add ? useTime++ : useTime--; }
};
class TrieTreePrivate {
public:
  TrieTreePrivate();
  ~TrieTreePrivate();
  bool add(const QString &str);
  void del(const QString &str);
  bool find(const QString &str);

private:
  TrieTreeNode *hand;
  TrieTreeNode *currentChar(const TrieTreeNode *node, QChar ch);
  TrieTreeNode *newNode(TrieTreeNode *parentNode, QChar ch, bool end);
};

TrieTree::TrieTree() : d(new TrieTreePrivate) {}

TrieTree::~TrieTree() { delete d; }

bool TrieTree::addString(const QString &str) { return d->add(str); }

void TrieTree::delString(const QString &str) { d->del(str); }

bool TrieTree::findString(const QString &str) { return d->find(str); }

TrieTreePrivate::TrieTreePrivate() : hand(new TrieTreeNode(' ', false, 0)) {}

TrieTreePrivate::~TrieTreePrivate() { delete hand; }

bool TrieTreePrivate::add(const QString &str) {
  if (str.isEmpty())
    return true;

  TrieTreeNode *node = hand;
  hand->addUseTime(true);
  TrieTreeNode *parentNode = nullptr;
  auto i = str.begin();

  for (; i != str.end(); i++) {
    auto n = currentChar(node, *i);
    if (n == nullptr) {
      parentNode = node;
      break;
    } else {
      node = n;
      n->addUseTime(true);
    }
  }
  if (parentNode == nullptr) {
    if (node->endChar)
      return true;
    else
      node->setEndChar(true);
    return true;
  }

  for (; i != str.end(); i++)
    parentNode = newNode(parentNode, *i, (i == str.end() - 1) ? true : false);
  return true;
}

void TrieTreePrivate::del(const QString &str) {
  QVector<TrieTreeNode *> nodeVector;
  auto node = hand;
  nodeVector.append(hand);
  for (auto i : str) {
    auto n = currentChar(node, i);
    if (n != nullptr) {
      node = n;
      nodeVector.append(node);
    } else {
      return;
    }
  }
  if (node->endChar) {
    for (auto i : nodeVector) {
      i->addUseTime(false);
      if (i->useTime == 0) {
        delete i;
        break;
      }
    }
  }
  if (node != nullptr) {
    node->setEndChar(false);
  }
  return;
}

bool TrieTreePrivate::find(const QString &str) {
  auto node = hand;
  for (auto i : str) {
    auto n = currentChar(node, i);
    if (n != nullptr) {
      node = n;
    } else {
      return false;
    }
  }
  return node->endChar;
}

TrieTreeNode *TrieTreePrivate::currentChar(const TrieTreeNode *node, QChar ch) {
  for (auto i : node->nodeVector) {
    if (i->ch == ch)
      return i;
  }
  return nullptr;
}

TrieTreeNode *TrieTreePrivate::newNode(TrieTreeNode *parentNode, QChar ch,
                                       bool end) {
  TrieTreeNode *node = new TrieTreeNode(ch, end, 1);
  parentNode->addNodePtr(node);
  return node;
}
