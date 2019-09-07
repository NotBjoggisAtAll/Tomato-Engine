#include "resourcefactory.h"
#include "vertex.h"

ResourceFactory* ResourceFactory::mInstance = nullptr;

ResourceFactory::ResourceFactory()
{

}

ResourceFactory *ResourceFactory::instance()
{
    if(!mInstance)
        mInstance = new ResourceFactory();

    return mInstance;
}

MeshComponent* ResourceFactory::createMeshComponent(unsigned int EntityID, std::string filePath)
{
    auto search = mMeshComponentMap.find(filePath);
    if (search != mMeshComponentMap.end())
    {
        mMeshComponents.push_back(mMeshComponents[search->second]);
        mMeshComponents.back().EntityID = EntityID;
        return &mMeshComponents.back();
    }

    if(filePath == "axis")
        createAxis();
    if(filePath.find(".obj") != std::string::npos)
        createObject(filePath);
    if(filePath.find(".txt") != std::string::npos)
        createObject(filePath);

    mMeshComponents.back().EntityID = EntityID;
    return &mMeshComponents.back();
}

TransformComponent *ResourceFactory::createTransformComponent(unsigned int EntityID)
{
    mTransformComponents.push_back(TransformComponent());
    mTransformComponents.back().EntityID = EntityID;
    return &mTransformComponents.back();
}

MaterialComponent *ResourceFactory::createMaterialComponent(unsigned int EntityID, Shader* Shader)
{
    mMaterialComponents.push_back(MaterialComponent());
    mMaterialComponents.back().EntityID = EntityID;
    mMaterialComponents.back().mShader = Shader;
    return &mMaterialComponents.back();
}

std::vector<MeshComponent>& ResourceFactory::getMeshComponents()
{
    return mMeshComponents;
}

std::vector<TransformComponent> &ResourceFactory::getTransformComponents()
{
    return mTransformComponents;
}

std::vector<MaterialComponent> &ResourceFactory::getMaterialComponents()
{
    return mMaterialComponents;
}

void ResourceFactory::openGLVertexBuffers()
{
    glGenVertexArrays( 1, &mMeshComponents.back().mVAO );
    glBindVertexArray( mMeshComponents.back().mVAO );

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mMeshComponents.back().mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mMeshComponents.back().mVBO );

    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mMeshComponents.back().mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
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
    glGenBuffers(1, &mMeshComponents.back().mEAB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mMeshComponents.back().mEAB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), mIndices.data(), GL_STATIC_DRAW);
}

void ResourceFactory::createAxis()
{
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();

    mMeshComponents.push_back(MeshComponent());

    mVertices.push_back(Vertex{0.f, 0.f, 0.f, 1.f, 0.f, 0.f});
    mVertices.push_back(Vertex{1000.f, 0.f, 0.f, 1.f, 0.f, 0.f});
    mVertices.push_back(Vertex{0.f, 0.f, 0.f, 0.f, 1.f, 0.f});
    mVertices.push_back(Vertex{0.f, 1000.f, 0.f, 0.f, 1.f, 0.f});
    mVertices.push_back(Vertex{0.f, 0.f, 0.f, 0.f, 0.f, 1.f});
    mVertices.push_back(Vertex{0.f, 0.f, 1000.f, 0.f, 0.f, 1.f});

    //set up buffers
    openGLVertexBuffers();

    mMeshComponents.back().mVerticeCount = static_cast<unsigned int>(mVertices.size());
    mMeshComponents.back().mIndiceCount = 0;
    mMeshComponents.back().mDrawType = GL_LINES;

    glBindVertexArray(0);

}


void ResourceFactory::createObject(std::string filePath)
{
    mVertices.clear();
    mIndices.clear();
    initializeOpenGLFunctions();

    mMeshComponents.push_back(MeshComponent());

    mMeshComponentMap[filePath] = static_cast<unsigned int>(mMeshComponents.size()) - 1;

    if(filePath.find(".obj") != std::string::npos)
        readOBJFile(filePath);
    else if(filePath.find(".txt") != std::string::npos)
        readTXTFile(filePath);

    //set up buffers
    openGLVertexBuffers();
    openGLIndexBuffer();

    mMeshComponents.back().mVerticeCount = static_cast<unsigned int>(mVertices.size());
    mMeshComponents.back().mIndiceCount = static_cast<unsigned int>(mIndices.size());
    mMeshComponents.back().mDrawType = GL_TRIANGLES;
    glBindVertexArray(0);
}

void ResourceFactory::readTXTFile(std::string filename)
{
    std::ifstream inn;
    std::string fileWithPath = gsl::assetFilePath + "Meshes/" + filename;

    inn.open(fileWithPath);

    if (inn.is_open()) {
        int n;
        Vertex vertex;
        inn >> n;
        mVertices.reserve(n);
        for (int i=0; i<n; i++) {
            inn >> vertex;
            mVertices.push_back(vertex);
        }
        inn.close();
        qDebug() << "TriangleSurface file read: " << QString::fromStdString(filename);
    }
    else
    {
        qDebug() << "Could not open file for reading: " << QString::fromStdString(filename);
    }
}

void ResourceFactory::readOBJFile(std::string filename)
{
    //Open File
    std::string fileWithPath = gsl::assetFilePath + "Meshes/" + filename;
    std::ifstream fileIn;
    fileIn.open (fileWithPath, std::ifstream::in);
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
                    Vertex tempVert(tempVertecies[index], tempNormals[normal], tempUVs[uv]);
                    mVertices.push_back(tempVert);
                }
                else            //no uv in mesh data, use 0, 0 as uv
                {
                    Vertex tempVert(tempVertecies[index], tempNormals[normal], gsl::Vector2D(0.0f, 0.0f));
                    mVertices.push_back(tempVert);
                }
                mIndices.push_back(temp_index++);
            }

            //For some reason the winding order is backwards so fixing this by swapping the last two indices
            //Update: this was because the matrix library was wrong - now it is corrected so this is no longer needed.
            //            unsigned int back = mIndices.size() - 1;
            //            std::swap(mIndices.at(back), mIndices.at(back-1));
            continue;
        }
    }

    //beeing a nice boy and closing the file after use
    fileIn.close();
    qDebug() << "Obj file read: " << QString::fromStdString(filename);
}
