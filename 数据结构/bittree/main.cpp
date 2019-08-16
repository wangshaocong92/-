#include "bittree.h"
#include <QCoreApplication>
#include <QDebug>
#include <QtAlgorithms>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  // QMap<int, int> qqq;

  //  BitTree tree(1000, BitTree::NoRepeat);
  //  for (auto i = 0; i < 100; i++) {
  //    qqq[qrand() % 1000] = i;
  //  }
  //  for (auto i : qqq.keys()) {
  //    tree.write(i);
  //  }
  //  for (auto i = 0; i < 300; i++) {
  //    if (tree.find(i))
  //      qDebug() << i << "find " << tree.find(i);
  //  }
  //  qDebug() << qqq.keys();
  QVector<int> qqq;
  BitTree tree(10000, BitTree::Repeat);
  for (auto i = 0; i < 10000 - 1; i++) {
    int t = qrand() % 10000;
    tree.write(t);
    if (t > 1000 && t < 1100) {
      qqq.append(t);
    }
  }
  for (auto i = 1000; i < 1100; i++) {
    if (tree.find(i))
      qDebug() << i << " find " << tree.find(i);
    if (tree.repeat(i))
      qDebug() << i << " repeat " << tree.repeat(i);
  }
  qSort(qqq.begin(), qqq.end());
  qDebug() << qqq;

  return a.exec();
}
