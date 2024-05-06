#ifndef MAPDATA_H
#define MAPDATA_H

#include <QObject>
#include <QVector>
#include <QMap>

class MapData : public QObject
{
    Q_OBJECT
public:
    explicit MapData(QObject *parent = nullptr);

    QMap<int,QVector<QVector<int>>> m_map;

signals:
};

#endif // MAPDATA_H
