#ifndef WORLDOUTLINER_H
#define WORLDOUTLINER_H

#include <QTreeWidget>
#include "Entity.h"

class WorldOutliner : public QTreeWidget
{
public:
    WorldOutliner(QWidget* p);

    void init();

    void addEntity(std::pair<Entity, std::string> entity);
};

#endif // WORLDOUTLINER_H
