#ifndef APP_H
#define APP_H

#include <memory>
#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

#include "types.h"
#include "mainwindow.h"

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
    void loadScene(QString JsonPath);
    void openSceneLoader();
    void saveScene(QString sceneName);
    void openSceneSaver();
    void newScene();
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

    void setupVisimOblig();
};

#endif // APP_H
