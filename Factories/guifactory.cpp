#include "guifactory.h"
#include "GSL/vector2d.h"
#include <array>

GUIFactory* GUIFactory::instance_ = nullptr;

GUIFactory::GUIFactory() {}

GUIFactory *GUIFactory::get()
{
    if(!instance_)
        instance_ = new GUIFactory();
    return instance_;
}

GUI GUIFactory::createGUI()
{
    GUI gui;
    gui.VAO_ = openGLVertexBuffers();
    gui.scale_.x = 0.5;
    gui.scale_.y = 0.5;
    return gui;

}

unsigned int GUIFactory::openGLVertexBuffers()
{
    initializeOpenGLFunctions();
    unsigned int VAO;
    glGenVertexArrays( 1, &VAO);
    glBindVertexArray(VAO);

    std::array<gsl::Vector2D, 4> vertices_ = {{
                                       {-1,1},
                                       {-1,-1},
                                       {1,1},
                                       {1,-1}
                                   }};
    GLuint VBO;

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, static_cast<int>(vertices_.size()*sizeof(gsl::Vector2D)), vertices_.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, sizeof(gsl::Vector2D), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    return VAO;
}
