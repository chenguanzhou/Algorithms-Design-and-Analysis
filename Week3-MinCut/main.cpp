#include <iostream>
#include <QtCore>
#include <ctime>
class Graph
{
public:
    Graph(){

    }
    ~Graph()
    {
        clear();
    }

    void clear()
    {
        vertex.clear();
        edges.clear();
    }

    bool readFromFile(QString path)
    {
        clear();

        QFile file(path);
        try{
            if (file.open(QFile::ReadOnly)==false)
                throw QString("Read file %1 failed!").arg(path);
            QTextStream in(&file);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList ids = line.split(QRegExp("\\W+"), QString::SkipEmptyParts);
                if (ids.count()<1)
                    continue;
                bool ret;
                int vertexID = ids[0].toInt(&ret);
                if (ret==false)
                    continue;

                insertVertex(vertexID);
                for (int i=1;i<ids.count();++i)
                {
                    int anotherID = ids[i].toInt();
                    if (vertexID<anotherID)
                        insertEdge(vertexID,anotherID);
                }
            }
        }
        catch (const QString &msg)
        {
            qDebug()<<msg;
            return false;
        }
        return true;
    }

    void insertVertex(int id)
    {
        vertex.insert(id);
    }
    void insertEdge(int id1,int id2)
    {
        edges<<qMakePair(id1,id2);
    }

    void printGraph()
    {
        qDebug()<<"Graph";
        QStringList vertexList;
        foreach (int id, vertex) {
            vertexList<<QString::number(id);
        }

        qDebug()<<"Vertex:["<<vertexList.join(",")<<"]";
        qDebug()<<"Edges count:"<<edges.size();
    }

    int RandomContraction() const
    {
        if (vertex.count()<=1)
            return 0;

        qsrand(std::clock());
        QSet<int> remainVertex(vertex);
        QList<QPair<int,int> > edgesCopy(edges);

        while(remainVertex.count()>2)
        {
            int edgeToContract = qrand()%edgesCopy.size();
            int id1 = edgesCopy.value(edgeToContract).first;
            int id2 = edgesCopy.value(edgeToContract).second;

            edgesCopy.removeAll(qMakePair(id1,id2));
            for (QList<QPair<int,int> >::iterator iter = edgesCopy.begin();iter!=edgesCopy.end();++iter)
            {
                if (iter->first==id1)iter->first=id2;
                if (iter->second==id1)iter->second=id2;
            }

            remainVertex.remove(id1);
        }
        return edgesCopy.count();
    }

private:
    QSet<int> vertex;//vertex
    QList<QPair<int,int> > edges;
};

int main(int argc,char**argv)
{
    if (argc<1)
        qCritical()<<"Params erroe!";

    Graph g;
    if (g.readFromFile(QString::fromLocal8Bit(argv[1]))==false)
    {
        qDebug()<<"Read file failed";
        return 0;
    }

    g.printGraph();
    int minVal = std::numeric_limits<int>::max();
    for (int i=0;i<1000000;++i)
    {
        int val = g.RandomContraction();
        minVal = minVal>val?val:minVal;
    }
    qDebug()<<minVal;
    return 0;
}
