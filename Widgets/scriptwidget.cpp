#include "scriptwidget.h"
#include "ui_scriptwidget.h"
#include "constants.h"
#include "Components/script.h"
#include "Systems/scriptsystem.h"
#include "world.h"
#include <QTextStream>
#include <QDesktopServices>
#include <QFileInfo>
#include <QMenu>
#include <QUrl>

ScriptWidget::ScriptWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::ScriptWidget)
{
    ui->setupUi(this);

    component_ =  getWorld()->getComponent<Script>(entity_).value();
    ui->filePathText->setText(component_->file_);

}

ScriptWidget::~ScriptWidget()
{
    delete ui;
}

void ScriptWidget::on_moreButton_clicked()
{
    QMenu subMenu;

    // Add actions here with name and slot to execute when action is pressed
    subMenu.addAction("Remove", this, &ScriptWidget::remove);

    subMenu.exec(QCursor::pos());
}

void ScriptWidget::remove()
{
    getWorld()->removeComponent<Script>(entity_);
    hide();
}

void ScriptWidget::on_openFileButton_clicked()
{
    QFileInfo info(QString::fromStdString(gsl::scriptFilePath) + ui->filePathText->text());
    bool success = QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
    if(!success)
    {
        QFile file(QString::fromStdString(gsl::scriptFilePath) + ui->filePathText->text());
        file.open(QFile::WriteOnly);

        QTextStream stream(&file);
        // Base template for new files. Includes the functions beginPlay, tick, endPlay. keyPressed and onHit.
        stream << "// This will run when the game starts. If this is spawned during runtime it will run on creation.\n"
               << "function beginPlay()\n{\n\t//console.log(\"Begin play called on entity \" + id);\n}\n\n"
               << "// This will run each frame\n"
               << "function tick()\n{\n\n}\n\n"
               << "// This will run when the game stops.\n"
               << "function endPlay()\n{\n\n}\n";
        file.close();

        QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));
        component_->file_ = ui->filePathText->text();
    }
}

void ScriptWidget::on_filePathText_editingFinished()
{
    component_->file_ = ui->filePathText->text();
}
