#include "renderwindow.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>

#include "mainwindow.h"

#include "Managers/entitymanager.h"
#include "Managers/shadermanager.h"
#include "Managers/soundmanager.h"
#include "Components/allcomponents.h"
#include "resourcefactory.h"
#include "World.h"

#include <QJsonDocument>
#include "jsonscene.h"
#include "constants.h"

#include "Systems/rendersystem.h"

RenderWindow::RenderWindow(MainWindow *mainWindow)
    : context_(nullptr), initialized_(false), mMainWindow(mainWindow)
{
    QSurfaceFormat format;

    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setDepthBufferSize(24);
    format.setSamples(8);
    format.setSwapInterval(0); //Turn off VSync

    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    context_ = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    context_->setFormat(requestedFormat());
    if (!context_->create()) {
        delete context_;
        context_ = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

}

RenderWindow::~RenderWindow()
{
    SoundManager::instance()->cleanUp();
}

void RenderWindow::init()
{
    if (!context_->makeCurrent(this)) {
        qDebug() << "makeCurrent() failed";
        return;
    }
    if (!initialized_)
        initialized_ = true;

    initializeOpenGLFunctions();

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

    startOpenGLDebugger();

    glEnable(GL_DEPTH_TEST);    //enables depth sorting - must use GL_DEPTH_BUFFER_BIT in glClear
    glEnable(GL_CULL_FACE);     //draws only front side of models - usually what you want -
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //color used in glClear GL_COLOR_BUFFER_BIT

    //**********************  Texture stuff: **********************

    texture_[0] = new Texture("white.bmp");
    texture_[1] = new Texture("hund.bmp", 1);
    texture_[2] = new Texture("skybox.bmp", 2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_[0]->id());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_[1]->id());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture_[2]->id());

    emit initDone();
}

void RenderWindow::tick()
{
    context_->makeCurrent(this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    getWorld()->getSystem<RenderSystem>()->tick();
    context_->swapBuffers(this);
}

void RenderWindow::updateCamera(Camera *newCamera)
{
    //new system - shader sends uniforms so needs to get the view and projection matrixes from camera
    for(auto& Shader : ShaderManager::instance()->mShaders){
        Shader.second->setCurrentCamera(newCamera);
    }

    getWorld()->setCurrentCamera(newCamera);
}

void RenderWindow::updateCollisionOutline(Entity newEntity){

    if(lastEntityCollision != -1)
    {
        getWorld()->destroyEntity(lastEntityCollision);

        if(newEntity == -1){
            lastEntityCollision = -1;
            return;
        }

    }

    Collision* collision = getWorld()->getComponent<Collision>(newEntity).value_or(nullptr);
    Transform* transform = getWorld()->getComponent<Transform>(newEntity).value_or(nullptr);

    if(!collision || !transform) return;

    gsl::Vector3D min = collision->scaledMinVector_;
    gsl::Vector3D max =  collision->scaledMaxVector_;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    vertices.reserve(8);
    Vertex vertex;
    vertex.set_rgb(1,0,0);

    vertex.set_xyz(min);                    // 0
    vertices.push_back(vertex);
    vertex.set_xyz(max.x, min.y, min.z);    // 1
    vertices.push_back(vertex);
    vertex.set_xyz(max.x, min.y, max.z);    // 2
    vertices.push_back(vertex);
    vertex.set_xyz(min.x, min.y, max.z);    // 3
    vertices.push_back(vertex);
    vertex.set_xyz(min.x, max.y, min.z);    // 4
    vertices.push_back(vertex);
    vertex.set_xyz(max.x, max.y, min.z);    // 5
    vertices.push_back(vertex);
    vertex.set_xyz(max);                    // 6
    vertices.push_back(vertex);
    vertex.set_xyz(min.x, max.y, max.z);    // 7
    vertices.push_back(vertex);

    indices = {
        0,1,
        1,2,
        2,3,
        3,0,
        0,4,
        1,5,
        2,6,
        3,7,
        4,5,
        5,6,
        6,7,
        7,4
    };

    Entity entity = getWorld()->createEntity();

    getWorld()->addComponent(entity, Transform(transform->position_));
    getWorld()->addComponent(entity, ResourceFactory::get()->createLines(vertices,indices));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->colorShader()));
    getWorld()->addComponent(entity, EntityData("Collision"));
    EntityData* data = getWorld()->getComponent<EntityData>(newEntity).value();

    data->children_.push_back(entity);

    lastEntityCollision = entity;

}


//    temp = new BillBoard();
//    temp->init();
//    temp->setShader(ShaderManager::instance()->textureShader());
//    temp->mMatrix.translate(4.f, 0.f, -3.5f);
//    temp->mName = "Billboard";
//    temp->mRenderWindow = this;
//    temp->mMaterial.mTextureUnit = 1;
//    temp->mMaterial.mColor = gsl::Vector3D(0.7f, 0.6f, 0.1f);
//    dynamic_cast<BillBoard*>(temp)->setConstantYUp(true);
//    mVisualObjects.push_back(temp);

// The stuff below this line should be somewhere else in the future.

//Simple way to turn on/off wireframe mode
//Not totally accurate, but draws the objects with
//lines instead of filled polygons
void RenderWindow::toggleWireframe()
{
    mWireframe = !mWireframe;
    if (mWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //turn on wireframe mode
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //turn off wireframe mode
        glEnable(GL_CULL_FACE);
    }
}

//The way this is set up is that we start the clock before doing the draw call,
//and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz


/// Uses QOpenGLDebugLogger if this is present
/// Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << message;
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            qDebug() << "glGetError returns " << err;
        }
    }
}

/// Tries to start the extended OpenGL debugger that comes with Qt
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            qDebug() << "This system can not use QOpenGLDebugLogger, so we revert to glGetError()";

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                qDebug() << "Started OpenGL debug logger!";
        }

        if(mOpenGLDebugLogger)
            mOpenGLDebugLogger->disableMessages(QOpenGLDebugMessage::APISource, QOpenGLDebugMessage::OtherType, QOpenGLDebugMessage::NotificationSeverity);
    }
}

//This function is called from Qt when window is exposed (shown)
//and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{

    if (!initialized_)
        init();

    //This is just to support modern screens with "double" pixels
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    emit updateCameraPerspectives(static_cast<float>(width()) / height());

    //    qDebug() << mCamera.mProjectionMatrix;
}

