#include <vector>

#include "NewPanel.h"
#include "Point.h"
#include "graphics/Graphics.h"

using namespace ui;

NewPanel::NewPanel(Point position, Point size):
	NewComponent(position, size),
	InnerSize(size),
	ViewportPosition(0, 0),
	mouseInside(false)
{
#ifdef OGLI
	GLint lastVid;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &lastVid);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &myVidTex);
	glBindTexture(GL_TEXTURE_2D, myVidTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WINDOWW, WINDOWH, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	//FBO
	glGenFramebuffers(1, &myVid);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, myVid);
	glEnable(GL_BLEND);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, myVidTex, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Reset framebuffer binding
	glDisable(GL_TEXTURE_2D);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, lastVid);
#else
	myVid = new pixel[WINDOWW*WINDOWH];
#endif
}

NewPanel::~NewPanel()
{
	for(std::vector<NewComponent *>::iterator i = children.begin(), end = children.end(); i != end; i++)
		if(*i)
			delete *i;
#ifdef OGLI
	glDeleteTextures(1, &myVIdTex);
	glDeleteFramebuffers(1, &myVid);
#else
	delete[] myVid;
#endif
}

void NewPanel::AddChild(NewComponent *c)
{
	c->SetParent(this);
	children.push_back(c);
}

void NewPanel::RemoveChild(NewComponent *c, bool freeMem)
{
	for(std::vector<NewComponent *>::iterator i = children.begin(), end = children.end(); i != end; i++)
		if(*i == c)
		{
			if(freeMem)
				delete *i;
			children.erase(i);
			// XXX: focus
			break;
		}
}

void NewPanel::RemoveChild(unsigned int idx, bool freeMem)
{
	if(freeMem)
		delete children[idx];
	children.erase(children.begin() + idx);
}

void NewPanel::Draw(Point screenPos)
{
#ifdef OGLI
	GLint lastVid;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &lastVid);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, myVid);
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
#else
	pixel * lastVid = ui::Engine::Ref().g->vid;
	ui::Engine::Ref().g->vid = myVid;
	std::fill(myVid, myVid+(WINDOWW*WINDOWH), 0);
#endif
	Point vp = ViewportPosition;
	Point vs = Point(Engine::Ref().GetWidth(), Engine::Ref().GetHeight());//XXX: size
	for(std::vector<NewComponent *>::iterator i = children.begin(), end = children.end(); i != end; i++)
	{
		Point cp = (*i)->Position;
		Point cs = (*i)->Size;
		if(cp.X + vp.X + cs.X >= 0 && cp.Y + vp.Y + cs.Y >= 0 &&
			cp.X + vp.X < vs.X && cp.Y + vp.Y < vs.Y)
		{
			(*i)->Draw(cp + vp);
		}
	}
	// XXX: I have no idea what's going on here
#ifdef OGLI
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, lastVid);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myVidTex);

	int x = screenPos.X, y = screenPos.Y;
	int h = Size.Y, w = Size.X;

	double texX = double(Size.X)/WINDOWW, texY = 1, texYB = 1-(double(Size.Y)/WINDOWH);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
    glTexCoord2d(0, texYB);
    glVertex2f(x, y+h);
    glTexCoord2d(texX, texYB);
    glVertex2f(x+w, y+h);
    glTexCoord2d(texX, texY);
    glVertex2f(x+w, y);
    glTexCoord2d(0, texY);
    glVertex2f(x, y);
    glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
#else
	ui::Engine::Ref().g->vid = lastVid;

	//dst=(pixel *)sdl_scrn->pixels+y*sdl_scrn->pitch/PIXELSIZE+x;
	for (int row = 0; row < Size.Y; row++)
	{
		std::copy(myVid+(row*WINDOWW), myVid+(row*WINDOWW)+Size.X, lastVid+((screenPos.Y+row)*WINDOWW)+screenPos.X);
	}
#endif	
}

void NewPanel::Tick(float dt)
{
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
		(*i)->Tick(dt);
}

void NewPanel::OnMouseClick(int localx, int localy, unsigned int button)
{
	bool clicked = false;
	Point vp = ViewportPosition;
	for(std::vector<NewComponent *>::const_reverse_iterator i = children.rbegin(), end = children.rend(); i != end; i++)
	{
		Point cp = (*i)->Position;
		Point cs = (*i)->Size;
		if(localx >= cp.X + vp.X && localy >= cp.Y + vp.Y &&
			localx < cp.X + vp.X + cs.X && localy < cp.Y + vp.Y + cs.Y)
		{
			clicked = true;
			//XXX:Focus
			(*i)->OnMouseClick(localx - cp.X - vp.X, localy - cp.Y - vp.Y, button);
			break;
		}
	}
	if(!clicked)
	{
		//XXX:self
	}
}

void NewPanel::OnMouseUnClick(int localx, int localy, unsigned int button)
{
	bool clicked = false;
	Point vp = ViewportPosition;
	for(std::vector<NewComponent *>::const_reverse_iterator i = children.rbegin(), end = children.rend(); i != end; i++)
	{
		Point cp = (*i)->Position;
		Point cs = (*i)->Size;
		if(localx >= cp.X + vp.X && localy >= cp.Y + vp.Y &&
			localx < cp.X + vp.X + cs.X && localy < cp.Y + vp.Y + cs.Y)
		{
			clicked = true;
			//XXX:Focus
			(*i)->OnMouseUnClick(localx - cp.X - vp.X, localy - cp.Y - vp.Y, button);
			break;
		}
	}
	if(!clicked)
	{
		//XXX:self
	}
}

void NewPanel::OnMouseDown(int x, int y, unsigned int button)
{
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
		(*i)->OnMouseDown(x, y, button);
}

void NewPanel::OnMouseHover(int localx, int localy)
{
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
	{
		Point cp = (*i)->Position;
		Point cs = (*i)->Size;
		if(localx >= cp.X && localy >= cp.Y &&
			localx < cp.X + cs.X && localy < cp.Y + cs.Y)
		{
			(*i)->OnMouseHover(localx - cp.X, localy - cp.Y);
			break;
		}
	}
}

void NewPanel::OnMouseMoved(int localx, int localy, int dx, int dy)
{
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
		(*i)->OnMouseMoved(localx - (*i)->Position.X - ViewportPosition.X, localy - (*i)->Position.Y - ViewportPosition.Y, dx, dy);
}

void NewPanel::OnMouseMovedInside(int localx, int localy, int dx, int dy)
{
	mouseInside = true;
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
		//if(!(*i)->Locked)
		{
			Point local	(localx - (*i)->Position.X - ViewportPosition.X, localy - (*i)->Position.Y - ViewportPosition.Y)
			, prevlocal (local.X - dx, local.Y - dy);
			
			// mouse currently inside?
			if( local.X >= 0 &&
				local.Y >= 0 &&
				local.X < (*i)->Size.X &&
				local.Y < (*i)->Size.Y )
			{
				(*i)->OnMouseMovedInside(localx - (*i)->Position.X - ViewportPosition.X, localy - (*i)->Position.Y - ViewportPosition.Y, dx, dy);
				
				// was the mouse outside?
				if(!(prevlocal.X >= 0 &&
					 prevlocal.Y >= 0 &&
					 prevlocal.X < (*i)->Size.X &&
					 prevlocal.Y < (*i)->Size.Y ) )
					(*i)->OnMouseEnter(local.X, local.Y);
			}
			// if not currently inside
			else
				// was the mouse inside?
				if(	prevlocal.X >= 0 &&
					prevlocal.Y >= 0 &&
					prevlocal.X < (*i)->Size.X &&
					prevlocal.Y < (*i)->Size.Y )
					(*i)->OnMouseLeave(local.X, local.Y);
		}
}

void NewPanel::OnMouseUp(int x, int y, unsigned int button)
{
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
		(*i)->OnMouseUp(x, y, button);
}

void NewPanel::OnMouseWheel(int x, int y, int d)
{
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
		(*i)->OnMouseWheel(x, y, d);
}

void NewPanel::OnMouseWheelInside(int localx, int localy, int d)
{
	for(std::vector<NewComponent *>::const_iterator i = children.begin(), end = children.end(); i != end; i++)
	{
		Point cp = (*i)->Position + ViewportPosition;
		Point cs = (*i)->Size;
		if(localx >= cp.X && localy >= cp.Y &&
			localx < cp.X + cs.X && localy < cp.Y + cs.Y)
		{
			(*i)->OnMouseWheelInside(localx - cp.X, localy - cp.Y, d);
			break;
		}
	}
}
