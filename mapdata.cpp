#include "mapdata.h"
#include <qDebug>

MapData::MapData(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"MapData::MapData(QObject *parent)";
    int arr1[12][24]={
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
                    {0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,0,0,0,0},
                    {0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,3,1,0,0,1,1,0,4,0},
                    {0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,1,1,1},
                    {0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        };
    QVector<QVector<int>> all1;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr1[i][j]);
        }
        all1.push_back(row);
    }
    m_map.insert(1,all1);

    int arr2[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,0,0,0,1,1,1,7,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,4,0},
                        {0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3},
                        {0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,6,3,6,1,1,1,0,1},
                        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all2;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr2[i][j]);
        }
        all2.push_back(row);
    }
    m_map.insert(2,all2);

    int arr3[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {3,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},
                        {0,1,0,0,0,0,0,0,3,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0},
                        {0,1,0,0,0,0,0,0,1,7,0,0,0,0,7,0,0,1,0,0,1,1,0,0},
                        {0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,4,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,1,0,0},
                        {0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,1,0},
                        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all3;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr3[i][j]);
        }
        all3.push_back(row);
    }
    m_map.insert(3,all3);

    int arr4[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,3,0,0,0},
                        {0,0,0,0,6,1,0,0,1,0,0,7,0,1,0,0,1,0,1,0,1,0,0,0},
                        {0,0,0,0,1,0,0,0,7,1,0,0,0,0,0,7,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,3,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,6,0,0},
                        {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0},
                        {0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,3,0,0,0,0,0,0,0},
                        {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all4;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr4[i][j]);
        }
        all4.push_back(row);
    }
    m_map.insert(4,all4);

    int arr5[12][24]={
                        {0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {1,1,1,0,1,1,7,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,1,3,1,0,1,6,1,0,1,0,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0},
                        {0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
                        {0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
                        {0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,0,1,1,1,7,1,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
                        {0,0,0,0,1,1,1,1,3,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
                        {1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all5;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr5[i][j]);
        }
        all5.push_back(row);
    }
    m_map.insert(5,all5);

    int arr6[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,3,0,0,1,1,1,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,6,6,0,0,0,0},
                        {0,0,0,0,0,0,1,0,3,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
                        {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,7,0,3,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0},
                        {1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
                        };
    QVector<QVector<int>> all6;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr6[i][j]);
        }
        all6.push_back(row);
    }
    m_map.insert(6,all6);

    int arr7[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {1,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,3,6,0,0,0,0},
                        {0,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
                        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,7},
                        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all7;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr7[i][j]);
        }
        all7.push_back(row);
    }
    m_map.insert(7,all7);

    int arr8[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
                        {0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1},
                        {0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0},
                        {0,3,0,0,0,1,0,0,0,0,0,0,0,0,0,6,0,0,6,0,0,0,0,0},
                        {0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0},
                        {0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,6,0,4},
                        {0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1},
                        {0,0,0,1,1,1,7,1,7,7,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {1,1,1,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all8;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr8[i][j]);
        }
        all8.push_back(row);
    }
    m_map.insert(8,all8);

    int arr9[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0},
                        {0,7,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0},
                        {0,7,0,1,1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {3,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0},
                        {1,0,0,1,1,1,0,0,0,0,0,0,6,0,0,0,0,0,0,7,0,0,4,0},
                        {1,0,0,0,0,0,0,0,0,0,1,1,1,1,7,1,1,0,0,0,0,1,1,1},
                        {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all9;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr9[i][j]);
        }
        all9.push_back(row);
    }
    m_map.insert(9,all9);

    int arr10[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {7,1,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
                        {0,0,1,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
                        {0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,3,1,0},
                        {0,0,0,0,0,0,0,0,7,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0},
                        {0,0,0,0,0,3,6,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,1,1,1,7,0,0,0,0,7,0,7,0,0,0,0,0,1,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,3,1,0},
                        {1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,7,7,1,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,7,0,0,0,0,0,0,0},
                        };
    QVector<QVector<int>> all10;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr10[i][j]);
        }
        all10.push_back(row);
    }
    m_map.insert(10,all10);

    int arr11[12][24]={
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,6,0,0,0},
                        {0,0,0,0,0,0,0,0,1,1,1,0,0,0,7,0,0,1,7,0,1,0,0,0},
                        {3,0,0,0,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,3,0,0},
                        {1,0,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0},
                        {7,6,0,6,0,0,0,0,6,6,3,6,6,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0},
                        {0,7,7,7,7,7,7,7,7,7,7,7,7,7,0,1,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,1,0,0,0,3,6,0,0,0},
                        {1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,1,1,0,1,4},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        };
    QVector<QVector<int>> all11;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr11[i][j]);
        }
        all11.push_back(row);
    }
    m_map.insert(11,all11);

    int arr12[12][24]={
                         {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,4},
                         {0,0,0,3,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,1},
                         {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,7,0,1,1},
                         {0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,7,0,7,0,0,7,0,0,1},
                         {0,0,1,0,0,1,1,7,1,7,0,0,0,0,0,0,0,0,0,0,7,0,1,1},
                         {3,0,6,0,0,7,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,1,1,1,0,0,0,0,6,0,0,0,0,0,1,7,1,7,1,0,0,1,1,0},
                         {0,0,0,0,1,1,1,1,1,1,0,7,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,6,0,6,0,0,0,7,0,0,0,0,0,0,0,0,6,0,3,0},
                         {1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         };
    QVector<QVector<int>> all12;
    for(int i = 0; i < 12; i++)
    {
        QVector<int>row;
        for(int j = 0 ; j < 24; j++)
        {
            row.push_back(arr12[i][j]);
        }
        all12.push_back(row);
    }
    m_map.insert(12,all12);
}
