#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <queue>
#include "GameView.h"
#include "GameModel.h"
#include "interface/Point.h"
#include "simulation/Simulation.h"
#include "search/SearchController.h"
#include "render/RenderController.h"
#include "login/LoginController.h"
#include "ssave/SSaveController.h"
#include "tags/TagsController.h"
#include "console/ConsoleController.h"
#include "localbrowser/LocalBrowserController.h"
//#include "cat/TPTScriptInterface.h"
#include "cat/LuaScriptInterface.h"
#include "options/OptionsController.h"
#include "Menu.h"

using namespace std;

class GameModel;
class GameView;
class CommandInterface;
class ConsoleController;
class GameController
{
private:
	//Simulation * sim;
	GameView * gameView;
	GameModel * gameModel;
	SearchController * search;
	RenderController * renderOptions;
	LoginController * loginWindow;
	SSaveController * ssave;
	ConsoleController * console;
	TagsController * tagsWindow;
	LocalBrowserController * localBrowser;
	OptionsController * options;
	CommandInterface * commandInterface;
public:
	class LoginCallback;
	class SearchCallback;
	class RenderCallback;
	class SSaveCallback;
	class TagsCallback;
	class StampsCallback;
	class OptionsCallback;
	GameController();
	~GameController();
	GameView * GetView();

	bool MouseMove(int x, int y, int dx, int dy);
	bool MouseDown(int x, int y, unsigned button);
	bool MouseUp(int x, int y, unsigned button);
	bool MouseWheel(int x, int y, int d);
	bool KeyPress(int key, Uint16 character, bool shift, bool ctrl, bool alt);
	bool KeyRelease(int key, Uint16 character, bool shift, bool ctrl, bool alt);
	void Tick();

	void SetZoomEnabled(bool zoomEnable);
	void SetZoomPosition(ui::Point position);
	void AdjustBrushSize(int direction, bool logarithmic = false);
	void AdjustZoomSize(int direction, bool logarithmic = false);
	void ToolClick(int toolSelection, ui::Point point);
	void DrawPoints(int toolSelection, queue<ui::Point*> & pointQueue);
	void DrawRect(int toolSelection, ui::Point point1, ui::Point point2);
	void DrawLine(int toolSelection, ui::Point point1, ui::Point point2);
	void DrawFill(int toolSelection, ui::Point point);
	void StampRegion(ui::Point point1, ui::Point point2);
	void CopyRegion(ui::Point point1, ui::Point point2);
	void Update();
	void SetPaused(bool pauseState);
	void SetPaused();
	void SetDecoration(bool decorationState);
	void SetDecoration();
	void SetActiveMenu(Menu * menu);
	void SetActiveTool(int toolSelection, Tool * tool);
	void SetColour(ui::Colour colour);
	void OpenSearch();
	void OpenLogin();
	void OpenTags();
	void OpenOptions();
	void OpenRenderOptions();
	void OpenSaveWindow();
	void OpenStamps();
	void PlaceSave(ui::Point position);
	void ClearSim();
	void ReloadSim();
	void Vote(int direction);
	void ChangeBrush();
	void ShowConsole();
	void FrameStep();
	void TranslateSave(ui::Point point);
	void TransformSave(matrix2d transform);
	ui::Point PointTranslate(ui::Point point);
	ui::Point NormaliseBlockCoord(ui::Point point);
	std::string ElementResolve(int type);

	void LoadClipboard();
	void LoadStamp();
};

#endif // GAMECONTROLLER_H