#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "component.h"
#include <vector>
#include "vertex.h"
#include "gltypes.h"
#include "Managers/filemanager.h"
struct MeshComponent : public Component
{
    MeshComponent(std::string FileName)
    {
        readFile(FileName);
//        auto[vertices,indices] = FileManager::GetInstance()->ReadFile(QString::fromStdString(FileName));
//        mVertices = vertices;
//        mIndices = indices;
    }
    std::vector<Vertex> mVertices;   //This is usually not needed after object is made
    std::vector<GLuint> mIndices;    //This is usually not needed after object is made

    void readFile(std::string filename)
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

        //    std::vector<Vertex> mVertices;    //made in VisualObject
        //    std::vector<GLushort> mIndices;   //made in VisualObject

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
};

#endif // MESHCOMPONENT_H
