#include "trietree.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <QtMath>

QVector<QString> str;
int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  TrieTree tree;
  qDebug() << QTime::currentTime();
  for (auto i = 0; i < 10000000; i++) {
    tree.addString(QString("%1%2%3")
                       .arg(qrand() / 100000)
                       .arg(QChar(qrand() / 10000))
                       .arg(QChar(qrand() / 65535)));
    str.append(QString("%1%2%3")
                   .arg(qrand() / 100000)
                   .arg(QChar(qrand() / 10000))
                   .arg(QChar(qrand() / 65535)));
  }
  tree.addString("124578asuygdqywdiksdf");
  str.append("124578asuygdqywdiksdf");
  qDebug() << QTime::currentTime();

  qDebug() << tree.findString("1245asuygdqywdiksdf");
  qDebug() << QTime::currentTime();

  qDebug() << str.contains("1278asuygdqywdiksdf");
  qDebug() << QTime::currentTime();

  return a.exec();
}
