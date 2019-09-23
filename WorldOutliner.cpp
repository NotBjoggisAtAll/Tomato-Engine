#include "WorldOutliner.h"
#include "entitymanager.h"

WorldOutliner::WorldOutliner(QWidget *p) : QTreeWidget(p)
{

}

void WorldOutliner::init()
{
    for(auto& Entity : EntityManager::instance()->mEntities)
        addEntity(Entity);
}

void WorldOutliner::addEntity(std::pair<Entity, std::string> entity)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();

    item->setText(0, QString::fromStdString(entity.second));
    item->setText(1, QString::number(entity.first));
    addTopLevelItem(item);
}
