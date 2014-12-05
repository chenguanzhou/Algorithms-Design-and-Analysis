#include <QtCore>

struct Edge{
    Edge(int from,int to,int w):fromID(from),toID(to),weight(w){}
    int fromID;
    int toID;
    int weight;
};

class Graph
{
public:
    void ReadFromFile(QString fileName)
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)==false)
            throw "Read file failed";
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (line.isEmpty())
                continue;
            QStringList lineList = line.split("\t",QString::SkipEmptyParts);
            int vertexID = lineList[0].toInt();
            lineList.pop_front();
//            qDebug()<<vertexID<<":"<<lineList;
            vertexList<<vertexID;
            foreach (QString word, lineList) {
                QStringList list = word.split(",");
                int toID = list[0].toInt();
                int weight = list[1].toDouble();
                Edge e(vertexID,toID,weight);
                edges.push_back(e);
            }
        }

    }


    void Dijkstra(int start)
    {
        if (vertexList.contains(start)==false)
            throw "Start vertex is not exist";

        QMap<int,int> minDis;
        QMap<int,QList<int> > path;

        QSet<int> exploredVertex;
        QSet<int> unexploredVertex = vertexList.toSet();
        exploredVertex.insert(start);
        unexploredVertex.remove(start);

        minDis.insert(start,0);
        path.insert(start,QList<int>());

        while(!unexploredVertex.empty())
        {
            QList<Edge> candidateEdges;
            foreach (Edge e, edges) {
                if (exploredVertex.contains(e.fromID) && unexploredVertex.contains(e.toID))
                {
                    candidateEdges.push_back(e);
                }
            }


            int minScore = std::numeric_limits<int>::max();
            int minScoreIndex = -1;
            for (int i=0;i<candidateEdges.count();++i){
                Edge e = candidateEdges[i];
                int score = minDis[e.fromID] + e.weight;
                if (score<minScore)
                {
                    minScore = score;
                    minScoreIndex = i;
                }
            }

            if (minScoreIndex==-1)
                continue;

            int fromID = candidateEdges[minScoreIndex].fromID;
            int toID = candidateEdges[minScoreIndex].toID;
            minDis[toID] = minScore;
            path[toID] = path.value(fromID);
            path[toID].push_back(toID);
            exploredVertex.insert(toID);
            unexploredVertex.remove(toID);

//            qDebug()<<minScoreIndex<<candidateEdges[minScoreIndex].fromID<<candidateEdges[minScoreIndex].toID;
//            qDebug()<<minDis;
//            qDebug()<<path;
//            qDebug()<<exploredVertex;
//            qDebug()<<unexploredVertex;
//            qDebug()<<"\n";
        }

        qDebug()<<minDis;
        qDebug()<<path;

        QList<int> ids = {7,37,59,82,99,115,133,165,188,197};
        foreach (int id, ids) {
            qDebug()<<id<<minDis[id]<<path[id];
        }
    }
private:
    QList<int> vertexList;
    QList<Edge> edges;
};





int main(int argc,char** argv)
{
    try
    {
        if (argc<=1)
            throw QString("Params error!");

        Graph g;
        g.ReadFromFile(QString::fromLocal8Bit(argv[1]));
        g.Dijkstra(1);
    }
    catch(QString msg)
    {
        qCritical()<<"Error: "<<msg;
    }
    return 0;
}
