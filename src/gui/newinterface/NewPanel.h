#ifndef PANEL_H
#define PANEL_H

#include "Point.h"
#include "Engine.h"
#include "NewComponent.h"
#ifdef OGLI
#include "graphics/OpenGLHeaders.h"
#endif

class Graphics;
namespace ui
{
	class NewPanel: public NewComponent
	{
	protected:
		std::vector<NewComponent *> children;
		bool mouseInside;
	public:
		friend class NewComponent;
#ifdef OGLI
		GLuint myVid, myVifTex;
#else
		pixel *myVid;
#endif
		Point InnerSize;
		Point ViewportPosition;

		NewPanel(Point position, Point size);
		virtual ~NewPanel();
		
		void AddChild(NewComponent *c);
		void RemoveChild(NewComponent *c, bool freeMem = true);
		void RemoveChild(unsigned int idx, bool freeMem = true);
		unsigned int GetChildCount();
		NewComponent *GetChild(unsigned int idx);
		void Tick(float dt);
		void Draw(Point screenPos);

		void OnMouseHover(int localx, int localy);
		void OnMouseMoved(int localx, int localy, int dx, int dy);
		void OnMouseMovedInside(int localx, int localy, int dx, int dy);
		void OnMouseDown(int x, int y, unsigned button);
		void OnMouseUp(int x, int y, unsigned button);
		void OnMouseClick(int localx, int localy, unsigned button);
		void OnMouseUnClick(int localx, int localy, unsigned button);
		void OnMouseWheel(int localx, int localy, int d);
		void OnMouseWheelInside(int localx, int localy, int d);
	};
}

#endif
