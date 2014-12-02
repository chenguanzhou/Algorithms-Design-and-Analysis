#include <iostream>
#include <QtCore>
#include <ctime>

//QMultiMap<int,int> edges;
QMultiMap<int,int> edges_inverse;


const int VERTEX_COUNT = 875714;// 1<<id<<VERTEX_COUNT

bool ReadFromFile(QString path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly)==false)
        return false;

    edges_inverse.clear();
    QTextStream in(&file);
    while(!in.atEnd())
    {
        int from,to;
        in>>from>>to;
//        edges.insert(from,to);
        edges_inverse.insert(to,from);
    }

//    qDebug()<<"edges:"<<edges;

    return true;
}

void DFS(int i,const QMultiMap<int,int> &edges,int &t,QMap<int,int> &vertexID_FinishTime,QSet<int> &isExplored,QMap<int,int> &leader,int currentNode)
{
//    qDebug()<<-1;
    isExplored.insert(i);
    leader[i] = currentNode;
//    qDebug()<<0;
    foreach (int id, edges.values(i)) {
//        qDebug()<<1;
        if (!isExplored.contains(id))
        {
//            qDebug()<<2;
            DFS(id,edges,t,vertexID_FinishTime,isExplored,leader,currentNode);
        }
//        qDebug()<<3;
    }
    ++t;
//    qDebug()<<"Finished ID:"<<i<<" with "<<t;
    vertexID_FinishTime.insert(i,t);
}

int main(int argc,char**argv)
{
    if (argc<1)
    {
        qCritical()<<"Params error!";
        return 0;
    }


    if (ReadFromFile(QString::fromLocal8Bit(argv[1]))==false)
    {
        qCritical()<<"Read file failed!";
        return 0;
    }

    QCoreApplication app(argc,argv);
    QMap<int,int> vertexID_FinishTime;

    qDebug()<<"Start First Loop";

    //First loop
    int t = 0;
    int s = 0;
    QMap<int,int> leader;
    QSet<int> isExplored;
    for (int i=1;i<=VERTEX_COUNT;++i)
    {
        if (!isExplored.contains(i))
        {
            s = i;
            DFS(i,edges_inverse,t,vertexID_FinishTime,isExplored,leader,s);
        }
    }


//    qDebug()<<"leader:"<<leader;
//    qDebug()<<"vertexID_FinishTime:"<<vertexID_FinishTime;

    qDebug()<<"Start Second Loop";

    //Second loop
    t = 0;
    s = 0;
    leader.clear();
    isExplored.clear();
    QMultiMap<int,int> newGraghEdge;
    foreach (int fromID, edges_inverse.keys().toSet()) {
        QList<int> values = edges_inverse.values(fromID);
//        qDebug()<<fromID<<values;
        foreach (int toID, values) {
            newGraghEdge.insert(VERTEX_COUNT - vertexID_FinishTime[toID] + 1, VERTEX_COUNT - vertexID_FinishTime[fromID] + 1);
        }
    }
    for (int i=1;i<=VERTEX_COUNT;++i)
    {
        if (!isExplored.contains(i))
        {
            s = i;
            DFS(i,newGraghEdge,t,vertexID_FinishTime,isExplored,leader,s);
        }
    }

    QList<int> values = leader.values();
    QMap<int,int> statistic;
    foreach (int value, values) {
        statistic[value]++;
    }
    QList<int> result = statistic.values();
    qSort(result);
    qDebug()<<result;
    return app.exec();
}
