#include "renderwindow.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include "Components/allcomponents.h"
#include "Systems/rendersystem.h"
#include "Systems/rendersystem2d.h"
#include "Factories/resourcefactory.h"
#include "world.h"
#include "Managers/shadermanager.h"

RenderWindow::RenderWindow()
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

void RenderWindow::tick(float deltaTime)
{
    context_->makeCurrent(this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    getWorld()->getSystem<RenderSystem>()->tick(deltaTime);
    getWorld()->getSystem<RenderSystem2D>()->tick(deltaTime);
    context_->swapBuffers(this);
}

void RenderWindow::exposeEvent(QExposeEvent *)
{
    if (!initialized_)
        init();
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));
    getWorld()->getSystem<RenderSystem2D>()->setWidthAndHeight(width(),height());
    emit updateCameraPerspectives(static_cast<float>(width() * retinaScale / height() * retinaScale));
}

void RenderWindow::init()
{
    if (!context_->makeCurrent(this))
    {
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

    emit initDone();
}

void RenderWindow::callExposeEvent()
{
    exposeEvent(nullptr);
}

void RenderWindow::makeCollisionBorder(Entity newEntity){

    if(lastCollisionEntity != -1)
    {
        getWorld()->destroyEntityLater(lastCollisionEntity);

        if(newEntity == -1){
            lastCollisionEntity = -1;
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
    vertex.normal_ = {1,0,0};

    vertex.xyz_ = min;                      // 0
    vertices.push_back(vertex);
    vertex.xyz_ = {max.x, min.y, min.z};    // 1
    vertices.push_back(vertex);
    vertex.xyz_ = {max.x, min.y, max.z};    // 2
    vertices.push_back(vertex);
    vertex.xyz_ = {min.x, min.y, max.z};    // 3
    vertices.push_back(vertex);
    vertex.xyz_ = {min.x, max.y, min.z};    // 4
    vertices.push_back(vertex);
    vertex.xyz_ = {max.x, max.y, min.z};    // 5
    vertices.push_back(vertex);
    vertex.xyz_ = max;                      // 6
    vertices.push_back(vertex);
    vertex.xyz_ = {min.x, max.y, max.z};    // 7
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
    getWorld()->addComponent(entity, Material(ShaderManager::get()->plainShader()));
    getWorld()->addComponent(entity, EntityData("__collision"));
    EntityData* data = getWorld()->getComponent<EntityData>(newEntity).value_or(nullptr);

    if(!data) return;
    data->children_.push_back(entity);

    lastCollisionEntity = entity;

}

void RenderWindow::toggleWireframe()
{
    wireframe_ = !wireframe_;
    if (wireframe_)
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

/// Uses QOpenGLDebugLogger if this is present
/// Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(openGLDebugLogger_)
    {
        const QList<QOpenGLDebugMessage> messages = openGLDebugLogger_->loggedMessages();
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
    QOpenGLContext * temp = context_;
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            qDebug() << "This system can not use QOpenGLDebugLogger, so we revert to glGetError()";

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            openGLDebugLogger_ = new QOpenGLDebugLogger(this);
            if (openGLDebugLogger_->initialize()) // initializes in the current context
                qDebug() << "Started OpenGL debug logger!";
        }
        if(openGLDebugLogger_)
            openGLDebugLogger_->disableMessages(QOpenGLDebugMessage::APISource, QOpenGLDebugMessage::OtherType, QOpenGLDebugMessage::NotificationSeverity);
    }
}
