#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_TIME PT_TIME 167
Element_TIME::Element_TIME()
{
    Identifier = "DEFAULT_PT_TIME";
    Name = "TIME";
    Colour = PIXPACK(0xFFCC33);
    MenuVisible = 1;
    MenuSection = SC_SPECIAL;
    Enabled = 1;

    Advection = 0.0f;
    AirDrag = 0.00f * CFDS;
    AirLoss = 0.00f;
    Loss = 0.00f;
    Collision = 0.0f;
    Gravity = 0.0f;
    Diffusion = 0.00f;
    HotAir = 0.000f	* CFDS;
    Falldown = 0;

    Flammable = 0;
    Explosive = 0;
    Meltable = 0;
    Hardness = 50;

    Weight = 100;

    Temperature = 273.15f;
    HeatConduct = 0;
    Description = "Can change how fast the time passes around it, hot = fast, cold = slow";

    State = ST_SOLID;
    Properties = TYPE_SOLID;

    LowPressure = IPL;
    LowPressureTransition = NT;
    HighPressure = IPH;
    HighPressureTransition = NT;
    LowTemperature = ITL;
    LowTemperatureTransition = NT;
    HighTemperature = NT;
    HighTemperatureTransition = ITH;

    Update = &Element_TIME::update;
    Graphics = &Element_PRTI::graphics;
}

//#TPT-Directive ElementHeader Element_TIME static int update(UPDATE_FUNC_ARGS)
int Element_TIME::update(UPDATE_FUNC_ARGS)
{
    parts[i].temp=fmax(-256.0f,fmin(256.0f,parts[i].temp-273.15f))+273.15f;
    sim->timefld->field[y/CELL][x/CELL]=(parts[i].temp-273.15f)/16;
	return 0;
}

//#TPT-Directive ElementHeader Element_TIME static int graphics(GRAPHICS_FUNC_ARGS)
int Element_TIME::graphics(GRAPHICS_FUNC_ARGS)

{
	return 0;
}

Element_TIME::~Element_TIME() {}
