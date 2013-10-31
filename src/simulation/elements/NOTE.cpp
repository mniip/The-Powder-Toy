#include "simulation/Elements.h"
#include "simulation/Sound.h"
//#TPT-Directive ElementClass Element_NOTE PT_NOTE 177
Element_NOTE::Element_NOTE()
{
	Identifier = "DEFAULT_PT_NOTE";
	Name = "NOTE";
	Colour = PIXPACK(0x33FFCC);
	MenuVisible = 1;
	MenuSection = SC_ELEC;
	Enabled = 1;
	
	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;
	
	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 2;
	
	Weight = 100;
	
	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 0;
	Description = ":^)";
	
	State = ST_SOLID;
	Properties = TYPE_SOLID;
	
	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
	
	Update = &Element_NOTE::update;
	Graphics = &Element_NOTE::graphics;
}

//#TPT-Directive ElementHeader Element_NOTE static int update(UPDATE_FUNC_ARGS)
int Element_NOTE::update(UPDATE_FUNC_ARGS)
{
	if(!parts[i].life)
		parts[i].life = 8;
	if(parts[i].tmp > 1000)
		parts[i].tmp = 1000;
	else if(!parts[i].tmp)
		parts[i].tmp = 100;
	if(parts[i].tmp2)
		parts[i].tmp2--;
	else
	{
		int r, rx, ry;
		int tone = (int)((parts[i].temp-73.15f)/100+1);
		for (rx=-1; rx<2; rx++)
			for (ry=-1; ry<2; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
						continue;
					if((r&0xFF) == PT_SPRK)
						if(parts[r>>8].life == 2+(r>>8 < i))
						{
							parts[i].tmp2 = 8;
							Sound::AddNote(parts[i].life, 440*pow(1.05946309436f, tone-30), parts[i].tmp*0.01f);
							return 0;
						}
				}
	}
	return 0;
}


//#TPT-Directive ElementHeader Element_NOTE static int graphics(GRAPHICS_FUNC_ARGS)
int Element_NOTE::graphics(GRAPHICS_FUNC_ARGS)

{
	float frequency = 0.0628;
	int q = (int)((cpart->temp-73.15f)*255/10000);
	*colr = 0x33;
	*colg = q;
	*colb = 0xFF-q;
	return 0;
}


Element_NOTE::~Element_NOTE() {}
