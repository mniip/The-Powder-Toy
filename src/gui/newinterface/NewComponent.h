#ifndef NEWCOMPONENT_H
#define NEWCOMPONENT_H
#include "Point.h"

namespace ui
{
	class ContextMenu;
	class NewPanel;

	class NewComponent
	{
	private:
		NewPanel *parent;
	protected:
		ContextMenu *menu;
	public:
		NewComponent(NewPanel *parent);
		NewComponent(Point position, Point size);
		NewComponent();
		~NewComponent();

		Point Position;
		Point Size;
		bool Visible;

		Point GetScreenPosition();

		void SetParent(NewPanel *parent);
		NewPanel *GetParent() { return parent; }
		
		virtual void Tick(float dt) { }
		virtual void Draw(Point screenPos) { }
		virtual void OnMouseHover(int localx, int localy) { }
		virtual void OnMouseMoved(int localx, int localy, int dx, int dy) { }
		virtual void OnMouseMovedInside(int localx, int localy, int dx, int dy) { }
		virtual void OnMouseEnter(int localx, int localy) { }
		virtual void OnMouseLeave(int localx, int localy) { }
		virtual void OnMouseDown(int x, int y, unsigned int button) { }
		virtual void OnMouseUp(int x, int y, unsigned int button) { }
		virtual void OnMouseClick(int localx, int localy, unsigned int button) { }
		virtual void OnMouseUnClick(int localx, int localy, unsigned int button) { }
		virtual void OnMouseWheel(int localx, int localy, int d) { }
		virtual void OnMouseWheelInside(int localx, int localy, int d) { }
		virtual void OnKeyPress(int key, Uint16 character, bool shift, bool ctrl, bool alt) { }
		virtual void OnKeyRelease(int key, Uint16 character, bool shift, bool ctrl, bool alt) { }
		virtual void OnContextMenuAction(int item) { }
 	};
}
#endif
