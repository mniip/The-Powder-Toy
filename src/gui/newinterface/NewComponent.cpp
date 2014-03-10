#include "NewComponent.h"
#include "Point.h"
#include "NewPanel.h"
#include "../interface/ContextMenu.h"

using namespace ui;

NewComponent::NewComponent(NewPanel *parentpanel):
	parent(parentpanel),
	Position(Point(0, 0)),
	Size(Point(0, 0)),
	Visible(true),
	menu(NULL)
{
}

NewComponent::NewComponent(Point position, Point size):
	parent(NULL),
	Position(position),
	Size(size),
	Visible(true),
	menu(NULL)
{
}

NewComponent::NewComponent():
	parent(NULL),
	Position(Point(0, 0)),
	Size(Point(0, 0)),
	Visible(true),
	menu(NULL)
{
}

void NewComponent::SetParent(NewPanel *new_parent)
{
/*	if(parent)
		parent->RemoveComponent(this);
	if(new_parent)
		new_parent->AddComponent(this);
*/	parent = new_parent;
}

Point NewComponent::GetScreenPosition()
{
	Point position = Position;
	if(parent)
		position += parent->Position + parent->ViewportPosition;
	return position;
}

NewComponent::~NewComponent()
{
	if(menu)
		delete menu;
}
