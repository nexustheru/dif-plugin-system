#include "container.h"
#include "ui_Container.h"
Game* new3game;

Container::Container(QWidget* parent) :QWidget(parent),ui(new Ui::Container)
{
    ui->setupUi(this);
    new3game = new Game();
    new3game->setParent(ui->dockWidgetContents);
}

Container::~Container()
{
    delete ui;
}
