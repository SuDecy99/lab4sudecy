#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QVector>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);
    void processTile(int pos, QVector<int>& bricks, QVector<bool>& lights);
    void generateMaze(int pos, QVector<int>& bricks);


signals:

public slots:
    QVector<int> newGame();
    QVector<bool> light(QVector<int> bricks);


};

#endif // HELPER_H
