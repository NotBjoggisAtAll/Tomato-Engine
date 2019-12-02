#include "resourcefactory.h"
#include "octahedronball.h"
#include "fstream"
#include "constants.h"
#include <sstream>
#include <string>

ResourceFactory* ResourceFactory::instance_ = nullptr;

ResourceFactory *ResourceFactory::get()
{
    if(!instance_)
        instance_ = new ResourceFactory();
    return instance_;
}

Mesh ResourceFactory::loadMesh(std::string file)
{
    if(file == "")
    {
        qDebug() << "Tried to run loadMesh without passing a file";
        return {};
    }
    //Sett file_ til ny filepath, sånn at andre funksjoner kan lage den
    file_ = file;
    //Let etter mesh i map, hvis man finner den returner en kopi av den
    auto meshIterator = meshUMap_.find(file);
    if(meshIterator != meshUMap_.end())
        return meshIterator->second;

    //Hvis man ikke finner den lag en ny mesh
    Mesh mesh = createMesh();
    mesh.filepath_ = file;
    //Til slutt legg den til og returner
    meshUMap_.insert({file,mesh});
    return mesh;
}

Collision ResourceFactory::getCollision(std::string file)
{
    if(file == "")
    {
        qDebug() << "Tried to run getCollision without passing a file";
        return {};
    }
    // Sjekker om den finner en eksisterende collision  i mappet
    auto collisionIterator = collisionUMap_.find(file);
    if(collisionIterator == collisionUMap_.end())
    {
        qDebug() << "Couldn't find the collision for mesh:" + QString::fromStdString(file);
        return {};
    }
    return collisionIterator->second;
}

Mesh ResourceFactory::getCameraFrustum()
{
    vertices_.clear();
    indices_.clear();
    vertices_.reserve(12);
    indices_.reserve(32);

    float d = 1.f; //set to 1 to have it accurately
    float p = 0.95f; //set to 1 to have it accurately
    vertices_.push_back(Vertex(gsl::Vector3D(-d,-d,-d),gsl::Vector3D(-1,0,0),gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(d,-d,-d), gsl::Vector3D(1,0,0), gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(d,-d,d),  gsl::Vector3D(1,0,0), gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(-d,-d,d), gsl::Vector3D(-1,0,0),gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(-d,d,-d), gsl::Vector3D(-1,0,0),gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(d,d,-d),  gsl::Vector3D(1,0,0), gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(d,d,d),   gsl::Vector3D(1,0,0), gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(-d,d,d),  gsl::Vector3D(-1,0,0),gsl::Vector2D(0,0)));

    //middle thing
    vertices_.push_back(Vertex(gsl::Vector3D(d,d,d*p),   gsl::Vector3D(1,0,0), gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(d,-d,d*p),  gsl::Vector3D(1,0,0), gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(-d,-d,d*p), gsl::Vector3D(-1,0,0),gsl::Vector2D(0,0)));
    vertices_.push_back(Vertex(gsl::Vector3D(-d,d,d*p),  gsl::Vector3D(-1,0,0),gsl::Vector2D(0,0)));

    indices_ = {
        0,1,
        1,2,
        2,3,
        3,0,
        0,4,
        1,5,
        2,6,
        3,7,
        7,6,
        6,5,
        5,4,
        4,7,
        8,9,
        9,10,
        10,11,
        11,8
    };
    Mesh frustum;
    initializeOpenGLFunctions();

    frustum.VAO_ = openGLVertexBuffers();
    openGLIndexBuffer();

    frustum.verticeCount_ = static_cast<unsigned int>(vertices_.size());
    frustum.indiceCount_ = static_cast<unsigned int>(indices_.size());
    frustum.drawType_ = GL_LINES;
    glBindVertexArray(0);

    frustum.filepath_ = "frustum";
    frustum.isAffectedByFrustum_ = false;
    return frustum;
}

Mesh ResourceFactory::createLines(std::pair<std::vector<Vertex>, std::vector<unsigned int> > verticesAndIndices)
{
    return createLines(verticesAndIndices.first, verticesAndIndices.second);
}

Mesh ResourceFactory::createLines(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    Mesh box;

    vertices_ = vertices;
    indices_ = indices;
    initializeOpenGLFunctions();

    box.VAO_ = openGLVertexBuffers();
    if(indices_.size() != 0)
        openGLIndexBuffer();
    box.verticeCount_ = static_cast<unsigned int>(vertices_.size());
    box.indiceCount_ = static_cast<unsigned int>(indices_.size());
    box.drawType_ = GL_LINES;
    glBindVertexArray(0);

    box.filepath_ = "line";
    box.isAffectedByFrustum_ = false;

    return box;
}

Mesh ResourceFactory::createMesh()
{
    Mesh mesh;

    vertices_.clear();
    indices_.clear();
    initializeOpenGLFunctions();

    if(file_.find(".obj") != std::string::npos || file_.find(".txt") != std::string::npos)
        mesh = createObject();
    else if(file_.find("axis") != std::string::npos)
        mesh = createAxis();
    else if(file_ == "skybox")
        mesh = createSkybox();
    else if(file_ == "sphere")
        mesh =  createSphere();
    else if(file_ == "plane")
        mesh = createPlane();
    else if(file_ == "frustum")
        mesh = getCameraFrustum();


    glBindVertexArray(0);

    return mesh;
}

Mesh ResourceFactory::createAxis() //Kom tilbake her og gjør om til indices
{
    Mesh mesh;

    vertices_.push_back({0.f, 0.f, 0.f, 1.f, 0.f, 0.f});
    vertices_.push_back({1000.f, 0.f, 0.f, 1.f, 0.f, 0.f});
    vertices_.push_back({0.f, 0.f, 0.f, 0.f, 1.f, 0.f});
    vertices_.push_back({0.f, 1000.f, 0.f, 0.f, 1.f, 0.f});
    vertices_.push_back({0.f, 0.f, 0.f, 0.f, 0.f, 1.f});
    vertices_.push_back({0.f, 0.f, 1000.f, 0.f, 0.f, 1.f});

    mesh.VAO_ = openGLVertexBuffers();
    mesh.verticeCount_ = static_cast<unsigned int>(vertices_.size());
    mesh.indiceCount_ = static_cast<unsigned int>(indices_.size());
    mesh.drawType_ = GL_LINES;
    mesh.isAffectedByFrustum_ = false;

    return mesh;
}

Mesh ResourceFactory::createObject()
{

    Mesh mesh;

    if(file_.find(".obj") != std::string::npos)
    {
        readOBJFile();
    }
    else
    {
        readTXTFile();
    }
    createCollision();

    mesh.VAO_ = openGLVertexBuffers();
    openGLIndexBuffer();
    mesh.verticeCount_ = static_cast<unsigned int>(vertices_.size());
    mesh.indiceCount_ = static_cast<unsigned int>(indices_.size());
    mesh.drawType_ = GL_TRIANGLES;

    return mesh;
}

Mesh ResourceFactory::createSkybox()
{
    Mesh mesh;

    vertices_ =
    {//Vertex data for front
     Vertex{gsl::Vector3D(-1.f, -1.f, 1.f),    gsl::Vector3D(0.f, 0.f, 1.0f),  gsl::Vector2D(0.25f, 0.333f)},  //v0
     Vertex{gsl::Vector3D( 1.f, -1.f, 1.f),    gsl::Vector3D(0.f, 0.f, 1.0f),  gsl::Vector2D(0.5f,  0.333f)},  //v1
     Vertex{gsl::Vector3D(-1.f,  1.f, 1.f),    gsl::Vector3D(0.f, 0.f, 1.0f),  gsl::Vector2D(0.25f, 0.666f)},    //v2
     Vertex{gsl::Vector3D( 1.f,  1.f, 1.f),    gsl::Vector3D(0.f, 0.f, 1.0f),  gsl::Vector2D(0.5f,  0.666f)},    //v3

     //Vertex data for right
     Vertex{gsl::Vector3D(1.f, -1.f,  1.f),    gsl::Vector3D(1.f, 0.f, 0.f),   gsl::Vector2D(0.5f,  0.333f)},  //v4
     Vertex{gsl::Vector3D(1.f, -1.f, -1.f),    gsl::Vector3D(1.f, 0.f, 0.f),   gsl::Vector2D(0.75f, 0.333f)},  //v5
     Vertex{gsl::Vector3D(1.f,  1.f,  1.f),    gsl::Vector3D(1.f, 0.f, 0.f),   gsl::Vector2D(0.5f,  0.666f)},    //v6
     Vertex{gsl::Vector3D(1.f,  1.f, -1.f),    gsl::Vector3D(1.f, 0.f, 0.f),   gsl::Vector2D(0.75f, 0.666f)},    //v7

     //Vertex data for back
     Vertex{gsl::Vector3D( 1.f, -1.f, -1.f),   gsl::Vector3D(0.f, 0.f, -1.f),  gsl::Vector2D(0.75f, 0.333f)},  //v8
     Vertex{gsl::Vector3D(-1.f, -1.f, -1.f),   gsl::Vector3D(0.f, 0.f, -1.f),  gsl::Vector2D(1.f,   0.333f)},  //v9
     Vertex{gsl::Vector3D( 1.f,  1.f, -1.f),   gsl::Vector3D(0.f, 0.f, -1.f),  gsl::Vector2D(0.75f, 0.666f)},    //v10
     Vertex{gsl::Vector3D(-1.f,  1.f, -1.f),   gsl::Vector3D(0.f, 0.f, -1.f),  gsl::Vector2D(1.f,   0.666f)},    //v11

     //Vertex data for left
     Vertex{gsl::Vector3D(-1.f, -1.f, -1.f),   gsl::Vector3D(-1.f, 0.f, 0.f),  gsl::Vector2D(0.f, 0.333f)},    //v12
     Vertex{gsl::Vector3D(-1.f, -1.f,  1.f),   gsl::Vector3D(-1.f, 0.f, 0.f),  gsl::Vector2D(0.25f, 0.333f)},  //v13
     Vertex{gsl::Vector3D(-1.f,  1.f, -1.f),   gsl::Vector3D(-1.f, 0.f, 0.f),  gsl::Vector2D(0.f, 0.666f)},      //v14
     Vertex{gsl::Vector3D(-1.f,  1.f,  1.f),   gsl::Vector3D(-1.f, 0.f, 0.f),  gsl::Vector2D(0.25f,   0.666f)},  //v15

     //Vertex data for bottom
     Vertex{gsl::Vector3D(-1.f, -1.f, -1.f),   gsl::Vector3D(0.f, -1.f, 0.f),  gsl::Vector2D(0.25f, 0.f)},      //v16
     Vertex{gsl::Vector3D( 1.f, -1.f, -1.f),   gsl::Vector3D(0.f, -1.f, 0.f),  gsl::Vector2D(0.5f,  0.f)},      //v17
     Vertex{gsl::Vector3D(-1.f, -1.f,  1.f),   gsl::Vector3D(0.f, -1.f, 0.f),  gsl::Vector2D(0.25f, 0.333f)},   //v18
     Vertex{gsl::Vector3D( 1.f, -1.f,  1.f),   gsl::Vector3D(0.f, -1.f, 0.f),  gsl::Vector2D(0.5f,  0.333f)},   //v19

     //Vertex data for top
     Vertex{gsl::Vector3D(-1.f, 1.f,  1.f),    gsl::Vector3D(0.f, 1.f, 0.f),   gsl::Vector2D(0.25f, 0.666f)},    //v20
     Vertex{gsl::Vector3D( 1.f, 1.f,  1.f),    gsl::Vector3D(0.f, 1.f, 0.f),   gsl::Vector2D(0.5f,  0.666f)},    //v21
     Vertex{gsl::Vector3D(-1.f, 1.f, -1.f),    gsl::Vector3D(0.f, 1.f, 0.f),   gsl::Vector2D(0.25f, 0.999f)},      //v22
     Vertex{gsl::Vector3D( 1.f, 1.f, -1.f),    gsl::Vector3D(0.f, 1.f, 0.f),   gsl::Vector2D(0.5f,  0.999f)}       //v23
    };

    indices_.insert( indices_.end(),
    { 0,  2,  1,  1,  2,  3,      //Face 0 - triangle strip (v0,  v1,  v2,  v3)
      4,  6,  5,  5,  6,  7,      //Face 1 - triangle strip (v4,  v5,  v6,  v7)
      8,  10,  9, 9, 10, 11,      //Face 2 - triangle strip (v8,  v9, v10,  v11)
      12, 14, 13, 13, 14, 15,     //Face 3 - triangle strip (v12, v13, v14, v15)
      16, 18, 17, 17, 18, 19,     //Face 4 - triangle strip (v16, v17, v18, v19)
      20, 22, 21, 21, 22, 23      //Face 5 - triangle strip (v20, v21, v22, v23)
                     });

    mesh.VAO_ = openGLVertexBuffers();
    openGLIndexBuffer();
    mesh.verticeCount_ = static_cast<unsigned int>(vertices_.size());
    mesh.indiceCount_ = static_cast<unsigned int>(indices_.size());
    mesh.drawType_ = GL_TRIANGLES;
    mesh.isAffectedByFrustum_ = false;

    return mesh;
}

Mesh ResourceFactory::createSphere()
{
    Mesh mesh;
    vertices_.clear();
    indices_.clear();
    initializeOpenGLFunctions();

    OctahedronBall ball(3);
    vertices_ = ball.mVertices;
    indices_ = ball.mIndices;

    mesh.VAO_ = openGLVertexBuffers();
    openGLIndexBuffer();
    mesh.verticeCount_ = static_cast<unsigned int>(vertices_.size());
    mesh.indiceCount_ = static_cast<unsigned int>(indices_.size());
    mesh.drawType_ = GL_TRIANGLES;

    return mesh;
}

Mesh ResourceFactory::createPlane()
{
    Mesh mesh;
    Vertex v;
    v.set_xyz(-1,0,1); v.set_rgb(0,0,1); v.set_uv(1,1);
    vertices_.push_back(v);
    v.set_xyz(1,0,1); v.set_rgb(0,1,0); v.set_uv(0,1);
    vertices_.push_back(v);
    v.set_xyz(-1,0,-1); v.set_rgb(0,0,1); v.set_uv(1,0);
    vertices_.push_back(v);
    v.set_xyz(1,0,-1); v.set_rgb(1,0,0); v.set_uv(0,0);
    vertices_.push_back(v);

    createCollision();

    mesh.VAO_ = openGLVertexBuffers();
    mesh.verticeCount_ = static_cast<unsigned int>(vertices_.size());
    mesh.indiceCount_ = static_cast<unsigned int>(indices_.size());
    mesh.drawType_ = GL_TRIANGLE_STRIP;

    return mesh;
}

unsigned int ResourceFactory::openGLVertexBuffers()
{
    unsigned int VAO;
    glGenVertexArrays( 1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, static_cast<int>(vertices_.size()*sizeof(Vertex)), vertices_.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    // 3rd attribute buffer : uvs
    glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)( 6 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(2);

    return VAO;
}

void ResourceFactory::openGLIndexBuffer()
{
    GLuint EAB;
    glGenBuffers(1, &EAB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int>(indices_.size() * sizeof(GLuint)), indices_.data(), GL_STATIC_DRAW);
}

void ResourceFactory::createCollision()
{

    Collision collision;

    gsl::Vector3D minVector = vertices_.at(0).mXYZ;
    gsl::Vector3D maxVector = vertices_.at(0).mXYZ;

    for(auto const& vertex : vertices_)
    {
        if(vertex.mXYZ.x < minVector.x)
            minVector.x = vertex.mXYZ.x;
        if(vertex.mXYZ.y < minVector.y)
            minVector.y = vertex.mXYZ.y;
        if(vertex.mXYZ.z < minVector.z)
            minVector.z = vertex.mXYZ.z;

        if(vertex.mXYZ.x > maxVector.x)
            maxVector.x = vertex.mXYZ.x;
        if(vertex.mXYZ.y > maxVector.y)
            maxVector.y = vertex.mXYZ.y;
        if(vertex.mXYZ.z > maxVector.z)
            maxVector.z = vertex.mXYZ.z;
    }
    collision.minVector_ = minVector;
    collision.maxVector_ = maxVector;
    collision.filepath_ = file_;

    collisionUMap_[file_] = collision;
}

void ResourceFactory::readTXTFile()
{
    std::string fileWithPath = gsl::meshFilePath + file_;
    std::ifstream inn;
    inn.open(fileWithPath);
    if (inn.is_open()) {
        unsigned int n;
        Vertex vertex;
        inn >> n;
        vertices_.reserve(n);
        for (unsigned int i=0; i<n; i++) {
            inn >> vertex;
            vertices_.push_back(vertex);
        }
        inn.close();
        qDebug() << "File read: " << QString::fromStdString(fileWithPath);
    }
    else
    {
        qDebug() << "Could not open file for reading: " << QString::fromStdString(fileWithPath);
    }
}

void ResourceFactory::readOBJFile()
{
    //Open File
    std::string fileWithPath = gsl::meshFilePath + file_;
    std::ifstream fileIn;
    fileIn.open (fileWithPath, std::ifstream::in);
    if(!fileIn)
        qDebug() << "Could not open file for reading: " << QString::fromStdString(fileWithPath);

    //One line at a time-variable
    std::string oneLine;
    //One word at a time-variable
    std::string oneWord;

    std::vector<gsl::Vector3D> tempVertecies;
    std::vector<gsl::Vector3D> tempNormals;
    std::vector<gsl::Vector2D> tempUVs;

    // Varible for constructing the indices vector
    unsigned int temp_index = 0;

    //Reading one line at a time from file to oneLine
    while(std::getline(fileIn, oneLine))
    {
        //Doing a trick to get one word at a time
        std::stringstream sStream;
        //Pushing line into stream
        sStream << oneLine;
        //Streaming one word out of line
        oneWord = ""; //resetting the value or else the last value might survive!
        sStream >> oneWord;

        if (oneWord == "#")
        {
            //Ignore this line
            //            qDebug() << "Line is comment "  << QString::fromStdString(oneWord);
            continue;
        }
        if (oneWord == "")
        {
            //Ignore this line
            //            qDebug() << "Line is blank ";
            continue;
        }
        if (oneWord == "v")
        {
            //            qDebug() << "Line is vertex "  << QString::fromStdString(oneWord) << " ";
            gsl::Vector3D tempVertex;
            sStream >> oneWord;
            tempVertex.x = std::stof(oneWord);
            sStream >> oneWord;
            tempVertex.y = std::stof(oneWord);
            sStream >> oneWord;
            tempVertex.z = std::stof(oneWord);

            //Vertex made - pushing it into vertex-vector
            tempVertecies.push_back(tempVertex);

            continue;
        }
        if (oneWord == "vt")
        {
            //            qDebug() << "Line is UV-coordinate "  << QString::fromStdString(oneWord) << " ";
            gsl::Vector2D tempUV;
            sStream >> oneWord;
            tempUV.x = std::stof(oneWord);
            sStream >> oneWord;
            tempUV.y = std::stof(oneWord);

            //UV made - pushing it into UV-vector
            tempUVs.push_back(tempUV);

            continue;
        }
        if (oneWord == "vn")
        {
            //            qDebug() << "Line is normal "  << QString::fromStdString(oneWord) << " ";
            gsl::Vector3D tempNormal;
            sStream >> oneWord;
            tempNormal.x = std::stof(oneWord);
            sStream >> oneWord;
            tempNormal.y = std::stof(oneWord);
            sStream >> oneWord;
            tempNormal.z = std::stof(oneWord);

            //Vertex made - pushing it into vertex-vector
            tempNormals.push_back(tempNormal);
            continue;
        }
        if (oneWord == "f")
        {
            //            qDebug() << "Line is a face "  << QString::fromStdString(oneWord) << " ";
            //int slash; //used to get the / from the v/t/n - format
            int index, normal, uv;
            for(int i = 0; i < 3; i++)
            {
                sStream >> oneWord;     //one word read
                std::stringstream tempWord(oneWord);    //to use getline on this one word
                std::string segment;    //the numbers in the f-line
                std::vector<std::string> segmentArray;  //temp array of the numbers
                while(std::getline(tempWord, segment, '/')) //splitting word in segments
                {
                    segmentArray.push_back(segment);
                }
                index = std::stoi(segmentArray[0]);     //first is vertex
                if (segmentArray[1] != "")              //second is uv
                    uv = std::stoi(segmentArray[1]);
                else
                {
                    //qDebug() << "No uvs in mesh";       //uv not present
                    uv = 0;                             //this will become -1 in a couple of lines
                }
                normal = std::stoi(segmentArray[2]);    //third is normal

                //Fixing the indexes
                //because obj f-lines starts with 1, not 0
                --index;
                --uv;
                --normal;

                if (uv > -1)    //uv present!
                {
                    Vertex tempVert(tempVertecies[static_cast<unsigned int>(index)],
                            tempNormals[static_cast<unsigned int>(normal)],
                            tempUVs[static_cast<unsigned int>(uv)]);
                    vertices_.push_back(tempVert);
                }
                else            //no uv in mesh data, use 0, 0 as uv
                {
                    Vertex tempVert(tempVertecies[static_cast<unsigned int>(index)],
                            tempNormals[static_cast<unsigned int>(normal)],
                            gsl::Vector2D(0.0f, 0.0f));
                    vertices_.push_back(tempVert);
                }
                indices_.push_back(temp_index++);
            }
            continue;
        }
    }
    fileIn.close();
    qDebug() << "Obj file read: " << QString::fromStdString(fileWithPath);
}
