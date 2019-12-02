#ifndef APP_H
#define APP_H

#include <memory>
#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

#include "types.h"
#include "mainwindow.h"
#include "GSL/vector3d.h"
#include "GSL/vector2d.h"

class RenderWindow;
class EventHandler;

class App : public QObject
{
    Q_OBJECT

public:
    App();
    ~App();

private slots:
    Entity createEntity();
    Entity spawnObject(std::string name, std::string path);
    void tick();
    void playGame();
    void stopGame();
    void updateCameraPerspectives(float aspectRatio);
    void loadScene();
    void saveScene();
    void newScene();
    void updateWorldOutliner();
    void raycastFromMouse();

    void postInit();
    void entitiesCollided(Entity entity1, Entity entity2);

private:

    std::unique_ptr<MainWindow> mainWindow_;
    std::shared_ptr<RenderWindow> renderWindow_;
    std::shared_ptr<EventHandler> eventHandler_;

    QTimer tickTimer_;

    float deltaTime_ = 0;
    float totalDeltaTime_ = 0;
    QElapsedTimer frameTimer_;
    QElapsedTimer deltaTimer_;
    int frameCounter = 0;

    void calculateFramerate();

    void spawnTower(gsl::Vector3D hitPosition);
    gsl::Vector2D map(gsl::Vector2D point, gsl::Vector2D oldMin, gsl::Vector2D oldMax, gsl::Vector2D newMin, gsl::Vector2D newMax);
};

#endif // APP_H
