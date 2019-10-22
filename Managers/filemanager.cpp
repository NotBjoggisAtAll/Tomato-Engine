#include "filemanager.h"
#include <fstream>
#include "vertex.h"
#include <QString>
#include <QFile>

FileManager* FileManager::m_Instance = nullptr;

FileManager *FileManager::GetInstance()
{
    if(!m_Instance)
        m_Instance = new FileManager;

    return m_Instance;
}

std::pair<std::vector<Vertex>,std::vector<unsigned int>> FileManager::ReadFile(const QString& File)
{
    if(File.endsWith("txt"))
        return ReadTXTFile(File);
    if(File.endsWith("obj"))
        return ReadOBJFile(File);
    return {};
}

std::pair<std::vector<Vertex>,std::vector<unsigned int>> FileManager::ReadTXTFile(const QString& File) //TODO Write from std to Q syntax
{
    std::string FilePath = m_DirPath.toStdString() + File.toStdString();
    std::ifstream fs;

    std::vector<Vertex> Vertices;
    fs.open(FilePath.c_str());

    if (fs.is_open())
    {
        unsigned int n;
        Vertex vertex;
        fs >> n;
        Vertices.reserve(n);
        for (unsigned int i=0; i<n; i++)
        {
            fs >> vertex;
            Vertices.push_back(vertex);
        }
        fs.close();
    }
    return {Vertices, {}};
}

void FileManager::WriteTXTFile(const QString &File, std::vector<Vertex>& Vertices) //TODO Write from std to Q syntax
{
    std::string FilePath = m_DirPath.toStdString() + File.toStdString();

    std::ofstream os;
    os.open(FilePath.c_str());

    if (os.is_open())
    {
        auto n = Vertices.size();
        Vertex vertex;
        os << n << std::endl;
        for (auto & Verts : Vertices)
        {
            vertex = Verts;
            os << vertex << std::endl;
        }
        os.close();
    }
}

std::pair<std::vector<Vertex>,std::vector<unsigned int>> FileManager::ReadOBJFile(const QString& File)
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<gsl::Vector3D> Position;
    std::vector<gsl::Vector3D> Normals;
    std::vector<gsl::Vector2D> Texture;

    unsigned int index{};
    QFile file(m_DirPath + File);

    if(!file.open(QIODevice::ReadOnly))
        return {};

    while (!file.atEnd())
    {
        QString Line = file.readLine();
        QStringList List = Line.split(" ");
        if(List.first() == "v")
        {
            List.removeFirst();
            gsl::Vector3D TempPosition;
            TempPosition.x = List.takeFirst().toFloat();
            TempPosition.y = List.takeFirst().toFloat();
            TempPosition.z = List.takeFirst().toFloat();

            Position.push_back(TempPosition);
        }
        else if(List.first() == "vt")
        {
            List.removeFirst();
            gsl::Vector2D TempUV;
            TempUV.x = List.takeFirst().toFloat();
            TempUV.y = List.takeFirst().toFloat();
            Texture.push_back(TempUV);
        }
        else if(List.first() == "vn")
        {
            List.removeFirst();
            gsl::Vector3D TempNormal;
            TempNormal.x = List.takeFirst().toFloat();
            TempNormal.y = List.takeFirst().toFloat();
            TempNormal.z = List.takeFirst().toFloat();
            Normals.push_back(TempNormal);
        }
        else if(List.first() == "f")
        {
            List.removeFirst();
            while(!List.isEmpty())
            {
                std::vector<unsigned int> TempIndices;
                QString IndiceString = List.takeFirst();
                QStringList IndiceList = IndiceString.split("/");

                while(!IndiceList.isEmpty())
                    TempIndices.push_back(IndiceList.takeFirst().toUInt());

                if((static_cast<int>(TempIndices.at(1)) - 1) <= 0)
                    Vertices.emplace_back(Position.at(TempIndices.at(0) - 1), Normals.at(TempIndices.at(2) - 1),gsl::Vector2D());
                else
                    Vertices.emplace_back(Position.at(TempIndices.at(0) - 1), Normals.at(TempIndices.at(2) - 1), Texture.at(TempIndices.at(1) - 1));

                Indices.emplace_back(index++);
            }
        }
    }
    file.close();
    return {Vertices, Indices};
}

std::shared_ptr<QOpenGLTexture> FileManager::LoadTexture(const QString &File, bool MirrorHorziontally, bool MirrorVertically)
{
    auto Texture = std::make_shared<QOpenGLTexture>(QImage(m_DirTexturePath + File).mirrored(MirrorHorziontally, MirrorVertically));
    return Texture;
}


FileManager::~FileManager()
{
    delete m_Instance;
    m_Instance = nullptr;
}
