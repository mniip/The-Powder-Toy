#if defined(RENDERER)

#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#include "Config.h"
#include "Format.h"
#include "interface/Engine.h"
#include "graphics/Graphics.h"
#include "graphics/Renderer.h"

#include "client/GameSave.h"
#include "simulation/Simulation.h"


void EngineProcess() {}
void ClipboardPush(char * text) {}
char * ClipboardPull() {}

void readFile(std::string filename, std::vector<char> & storage)
{
	std::ifstream fileStream;
	fileStream.open(std::string(filename).c_str(), std::ios::binary);
	if(fileStream.is_open())
	{
		fileStream.seekg(0, std::ios::end);
		size_t fileSize = fileStream.tellg();
		fileStream.seekg(0);

		unsigned char * tempData = new unsigned char[fileSize];
		fileStream.read((char *)tempData, fileSize);
		fileStream.close();

		std::vector<unsigned char> fileData;
		storage.clear();
		storage.insert(storage.end(), tempData, tempData+fileSize);
		delete[] tempData;
	}
}

void writeFile(std::string filename, std::vector<char> & fileData)
{
	std::ofstream fileStream;
	fileStream.open(std::string(filename).c_str(), std::ios::binary);
	if(fileStream.is_open())
	{
		fileStream.write(&fileData[0], fileData.size());
		fileStream.close();
	}
}

int main(int argc, char *argv[])
{	
	ui::Engine * engine;
	std::string outputPrefix, inputFilename;
	std::vector<char> inputFile;
	std::string ppmFilename, ptiFilename, ptiSmallFilename, pngFilename, pngSmallFilename;
	std::vector<char> ppmFile, ptiFile, ptiSmallFile, pngFile, pngSmallFile;

	inputFilename = std::string(argv[1]);
	outputPrefix = std::string(argv[2]);

	ppmFilename = outputPrefix+".ppm";
	ptiFilename = outputPrefix+".pti";
	ptiSmallFilename = outputPrefix+"-small.pti";
	pngFilename = outputPrefix+".png";
	pngSmallFilename = outputPrefix+"-small.png";

	readFile(inputFilename, inputFile);

	ui::Engine::Ref().g = new Graphics();
	
	engine = &ui::Engine::Ref();
	engine->Begin(XRES+BARSIZE, YRES+MENUSIZE);

	GameSave * gameSave = new GameSave(inputFile);

	Simulation * sim = new Simulation();
	Renderer * ren = new Renderer(ui::Engine::Ref().g, sim);

	sim->Load(gameSave);


	//Render save
	ren->decorations_enable = true;
	ren->blackDecorations = true;

	int frame = 15;
	while(frame)
	{
		frame--;
		ren->render_parts();
		ren->render_fire();
		ren->clearScreen(1.0f);
	}

	ren->RenderBegin();
	ren->RenderEnd();

	VideoBuffer buf = ren->DumpFrame();
	//ppmFile = format::VideoBufferToPPM(screenBuffer);
	ptiFile = format::VideoBufferToPTI(buf);
	pngFile = format::VideoBufferToPNG(buf);
#define W(X) (X).Width
#define H(X) (X).Height
#define A(B,X,Y) (B).Buffer[(Y)*W(B)+X]
#define M 6
#define DIS(A,X) abs(X-(A))+16
#define DM(A,X) (X)*(DIS(A,X))
	VideoBuffer small = VideoBuffer(W(buf)/M,H(buf)/M);
	int x,y,dx,dy;
	for(y=0;y<H(small);y++)
		for(x=0;x<W(small);x++)
		{
			int ar=0,ag=0,ab=0;
			int r=0,g=0,b=0;
			float nr=0.01f,ng=0.01f,nb=0.01f;
			for(dy=0;dy<M;dy++)
				for(dx=0;dx<M;dx++)
				{	
					ar+=PIXR(A(buf,x*M+dx,y*M+dy));
					ag+=PIXG(A(buf,x*M+dx,y*M+dy));
					ab+=PIXB(A(buf,x*M+dx,y*M+dy));
				}
			ar/=M*M;ag/=M*M;ab/=M*M;
			for(dy=0;dy<M;dy++)
				for(dx=0;dx<M;dx++)
				{
					r+=DM(ar,PIXR(A(buf,x*M+dx,y*M+dy)));
					nr+=DIS(ar,PIXR(A(buf,x*M+dx,y*M+dy)));
					g+=DM(ag,PIXG(A(buf,x*M+dx,y*M+dy)));
					ng+=DIS(ag,PIXG(A(buf,x*M+dx,y*M+dy)));
					b+=DM(ab,PIXB(A(buf,x*M+dx,y*M+dy)));
					nb+=DIS(ab,PIXB(A(buf,x*M+dx,y*M+dy)));
				}
			A(small,x,y)=PIXRGB((int)(r/nr),(int)(g/ng),(int)(b/nb));
		}
	ptiSmallFile = format::VideoBufferToPTI(small);
	pngSmallFile = format::VideoBufferToPNG(small);

	

	//writeFile(ppmFilename, ppmFile);
	writeFile(ptiFilename, ptiFile);
	writeFile(ptiSmallFilename, ptiSmallFile);
	writeFile(pngFilename, pngFile);
	writeFile(pngSmallFilename, pngSmallFile);
}

#endif
