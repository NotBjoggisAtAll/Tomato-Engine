#include "resourcefactory.h"
#include "octahedronball.h"
#include "fstream"
#include "constants.h"
#include "Components/meshcomponent.h"
#include <sstream>

ResourceFactory* ResourceFactory::instance_ = nullptr;

ResourceFactory *ResourceFactory::instance()
{
    if(!instance_)
        instance_ = new ResourceFactory();

    return instance_;
}

std::pair<Mesh,Collision> ResourceFactory::loadMesh(const std::string& filePath)
{
    currentIt = mMeshMap.end();

    auto meshIt = mMeshMap.find(filePath);
    if (meshIt != mMeshMap.end())
        return meshIt->second;

    mMeshMap.insert({filePath, {Mesh(),Collision()}});
    currentIt = mMeshMap.find(filePath);

    if(filePath == "axis")
        createAxis();
    if(filePath.find(".obj") != std::string::npos)
        createObject(filePath);
    if(filePath.find(".txt") != std::string::npos)
        createObject(filePath);
    if(filePath.find(".terrain") != std::string::npos)
        createObject(filePath);
    if(filePath == "skybox")
        createSkybox();
    if(filePath == "sphere")
        createSphere();
    if(filePath == "plane")
        createPlane();

    currentIt->second.first.filepath_ = filePath;

    return currentIt->second;
}

Mesh ResourceFactory::createLine(const std::string& filePath, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    auto meshIt = mMeshMap.find(filePath);
    if (meshIt != mMeshMap.end())
    {
        currentIt = meshIt;
    }else
    {
        mMeshMap.insert({filePath, {Mesh(),Collision()}});
        currentIt = mMeshMap.find(filePath);
    }
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();

    mVertices = std::move(vertices);
    mIndices = std::move(indices);

    openGLVertexBuffers();
    openGLIndexBuffer();

    currentIt->second.first.mVerticeCount = static_cast<unsigned int>(mVertices.size());
    currentIt->second.first.mIndiceCount = static_cast<unsigned int>(mIndices.size());
    currentIt->second.first.mDrawType = GL_LINES;
    return currentIt->second.first;
}

void ResourceFactory::createCollision(CollisionType Type = CollisionType::NONE)
{
    gsl::Vector3D minVector = mVertices.at(0).mXYZ;
    gsl::Vector3D maxVector = mVertices.at(0).mXYZ;

    for(auto const& vertex : mVertices)
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
    qDebug() << "Min og Max vector " << minVector << "\n" << maxVector;
    currentIt->second.second = Collision(Type,minVector,maxVector);
}


void ResourceFactory::openGLVertexBuffers()
{
    glGenVertexArrays( 1, &currentIt->second.first.mVAO );
    glBindVertexArray( currentIt->second.first.mVAO );

    GLuint mVBO;

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER, static_cast<int>(mVertices.size()*sizeof(Vertex)), mVertices.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    // 3rd attribute buffer : uvs
    glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)( 6 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(2);
}

void ResourceFactory::openGLIndexBuffer()
{
    GLuint mEAB;
    glGenBuffers(1, &mEAB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEAB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<int>(mIndices.size() * sizeof(GLuint)), mIndices.data(), GL_STATIC_DRAW);
}

void ResourceFactory::createPlane()
{
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();

    Vertex v;
    v.set_xyz(0,0,0); v.set_rgb(1,0,0);
    mVertices.push_back(v);
    v.set_xyz(1,0,1); v.set_rgb(0,0,1);
    mVertices.push_back(v);
    v.set_xyz(1,0,0); v.set_rgb(0,1,0);
    mVertices.push_back(v);
    v.set_xyz(0,0,0); v.set_rgb(0,1,0);
    mVertices.push_back(v);
    v.set_xyz(0,0,1); v.set_rgb(0,0,1);
    mVertices.push_back(v);
    v.set_xyz(1,0,1); v.set_rgb(1,0,0);
    mVertices.push_back(v);

    openGLVertexBuffers();

    currentIt->second.first.mVerticeCount = static_cast<unsigned int>(mVertices.size());
    currentIt->second.first.mIndiceCount = static_cast<unsigned int>(mIndices.size());
    currentIt->second.first.mDrawType = GL_TRIANGLES;
    glBindVertexArray(0);
}


void ResourceFactory::createSphere()
{
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();

    OctahedronBall ball(3);
    mVertices = ball.mVertices;
    mIndices = ball.mIndices;

    //set up buffers
    openGLVertexBuffers();
    openGLIndexBuffer();

    currentIt->second.first.mVerticeCount = static_cast<unsigned int>(mVertices.size());
    currentIt->second.first.mIndiceCount = static_cast<unsigned int>(mIndices.size());
    currentIt->second.first.mDrawType = GL_TRIANGLES;
    glBindVertexArray(0);

}


void ResourceFactory::createSkybox()
{
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();


    mVertices.insert( mVertices.end(),
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
                      });

    mIndices.insert( mIndices.end(),
    { 0,  2,  1,  1,  2,  3,      //Face 0 - triangle strip (v0,  v1,  v2,  v3)
      4,  6,  5,  5,  6,  7,      //Face 1 - triangle strip (v4,  v5,  v6,  v7)
      8,  10,  9, 9, 10, 11,      //Face 2 - triangle strip (v8,  v9, v10,  v11)
      12, 14, 13, 13, 14, 15,     //Face 3 - triangle strip (v12, v13, v14, v15)
      16, 18, 17, 17, 18, 19,     //Face 4 - triangle strip (v16, v17, v18, v19)
      20, 22, 21, 21, 22, 23      //Face 5 - triangle strip (v20, v21, v22, v23)
                     });

    openGLVertexBuffers();
    openGLIndexBuffer();

    currentIt->second.first.mVerticeCount = static_cast<unsigned int>(mVertices.size());
    currentIt->second.first.mIndiceCount = static_cast<unsigned int>(mIndices.size());
    currentIt->second.first.mDrawType = GL_TRIANGLES;

    glBindVertexArray(0);
}
void ResourceFactory::createAxis()
{
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();


    mVertices.push_back(Vertex{0.f, 0.f, 0.f, 1.f, 0.f, 0.f});
    mVertices.push_back(Vertex{1000.f, 0.f, 0.f, 1.f, 0.f, 0.f});
    mVertices.push_back(Vertex{0.f, 0.f, 0.f, 0.f, 1.f, 0.f});
    mVertices.push_back(Vertex{0.f, 1000.f, 0.f, 0.f, 1.f, 0.f});
    mVertices.push_back(Vertex{0.f, 0.f, 0.f, 0.f, 0.f, 1.f});
    mVertices.push_back(Vertex{0.f, 0.f, 1000.f, 0.f, 0.f, 1.f});

    //set up buffers
    openGLVertexBuffers();

    currentIt->second.first.mVerticeCount = static_cast<unsigned int>(mVertices.size());
    currentIt->second.first.mIndiceCount = 0;
    currentIt->second.first.mDrawType = GL_LINES;

    glBindVertexArray(0);
}


void ResourceFactory::createObject(std::string filePath)
{
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();

    if(filePath.find(".obj") != std::string::npos)
    {
        readOBJFile(filePath);
    }
    else if(filePath.find(".txt") != std::string::npos)
    {
        readTXTFile(filePath);
    }
    else if(filePath.find(".terrain") != std::string::npos)
    {
        readTerrainFile(filePath);
    }
    createCollision();

    //set up buffers
    openGLVertexBuffers();
    openGLIndexBuffer();

    currentIt->second.first.mVerticeCount = static_cast<unsigned int>(mVertices.size());
    currentIt->second.first.mIndiceCount = static_cast<unsigned int>(mIndices.size());
    currentIt->second.first.mDrawType = GL_TRIANGLES;
    glBindVertexArray(0);
}

void ResourceFactory::readTXTFile(std::string filename)
{
    std::ifstream inn;
    // std::string fileWithPath = gsl::assetFilePath + "Meshes/" + filename;

    inn.open(filename);

    if (inn.is_open()) {
        unsigned int n;
        Vertex vertex;
        inn >> n;
        mVertices.reserve(n);
        for (unsigned int i=0; i<n; i++) {
            inn >> vertex;
            mVertices.push_back(vertex);
        }
        inn.close();
        qDebug() << "File read: " << QString::fromStdString(filename);
    }
    else
    {
        qDebug() << "Could not open file for reading: " << QString::fromStdString(filename);
    }

}

void ResourceFactory::readTerrainFile(std::string filename)
{
    std::ifstream inn;
    inn.open(filename);

    int TilesX = 0;
    int TilesZ = 0;

    if (inn.is_open()) {
        unsigned int n;
        Vertex vertex;
        inn >> n;
        mVertices.reserve(n);
        inn >> TilesX >> TilesZ;
        for (unsigned int i=0; i<n; i++) {
            inn >> vertex;
            mVertices.push_back(vertex);
        }

        inn.close();
        qDebug() << "File read: " << QString::fromStdString(filename);
    }
    else
    {
        qDebug() << "Could not open file for reading: " << QString::fromStdString(filename);
    }

    calculateIndices(TilesX, TilesZ);
    calculateNormals();
}

void ResourceFactory::calculateIndices(int TilesX, int TilesZ)
{
    mIndices.clear();
    for(int i = 0; i < TilesZ*TilesX; ++i)
    {
        if(i == (TilesX*TilesZ)-TilesZ) break;
        if(i > 1 && (i+1) % TilesX == 0)  continue;

        mIndices.emplace_back(i);
        mIndices.emplace_back(i+1);
        mIndices.emplace_back(i+TilesZ+1);

        mIndices.emplace_back(i);
        mIndices.emplace_back(i+TilesZ+1);
        mIndices.emplace_back(i+TilesZ);
    }
}

void ResourceFactory::calculateNormals()
{
    for (unsigned int i = 0; i < mIndices.size(); i+=3)
    {
        auto pos1 = mVertices[mIndices[i+0]].mXYZ;
        auto pos2 = mVertices[mIndices[i+1]].mXYZ;
        auto pos3 = mVertices[mIndices[i+2]].mXYZ;

        auto normal = gsl::Vector3D::cross(pos3-pos1,pos2-pos1);
        normal.normalize();

        mVertices[mIndices[i+0]].set_normal(normal);
        mVertices[mIndices[i+1]].set_normal(normal);
        mVertices[mIndices[i+2]].set_normal(normal);
    }
}


void ResourceFactory::readOBJFile(std::string filename)
{
    //Open File
    //  std::string fileWithPath = gsl::assetFilePath + "Meshes/" + filename;
    std::ifstream fileIn;
    fileIn.open (filename, std::ifstream::in);
    if(!fileIn)
        qDebug() << "Could not open file for reading: " << QString::fromStdString(filename);

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
                    mVertices.push_back(tempVert);
                }
                else            //no uv in mesh data, use 0, 0 as uv
                {
                    Vertex tempVert(tempVertecies[static_cast<unsigned int>(index)],
                            tempNormals[static_cast<unsigned int>(normal)],
                            gsl::Vector2D(0.0f, 0.0f));
                    mVertices.push_back(tempVert);
                }
                mIndices.push_back(temp_index++);
            }
            continue;
        }
    }
    fileIn.close();
    qDebug() << "Obj file read: " << QString::fromStdString(filename);
}
