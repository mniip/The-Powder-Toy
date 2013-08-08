#include "Utf8.h"

#define INVALID_CODEPOINT 0xFFFD

int Utf8::step(const char* s)
{
	if(s[0]&0x80)
		if(s[0]&0x40)
			if(s[0]&0x20)
				if(s[0]&0x10)
					if(s[0]&0x08)
						return 1; // invalid: codepoints after U+10FFFF are deprecated
					else
						if((s[1]&0xC0)==0x80 && (s[2]&0xC0)==0x80 && (s[3]&0xC0)==0x80)
							if(s[0]<0xF4 || s[1]<0x8F)
								return 4;
							else
								return 1; // invalid: codepoints after U+10FFFF are deprecated
						else
							return 1; // invalid: 11110xxx not followed by 10xxxxxx 10xxxxxx 10xxxxxx
				else
					if((s[1]&0xC0)==0x80 && (s[2]&0xC0)==0x80)
						return 3;
					else
						return 1; // invalid: 1110xxxx not followed by 10xxxxxx 10xxxxxx
			else
				if((s[1]&0xC0)==0x80)
					return 2;
				else
					return 1; // invalid: 110xxxxx not followed by 10xxxxxx
		else
			return 1; // invalid: 10xxxxxx without an initializer
	else
		return 1;
}

int Utf8::len(const char* s)
{
	int i=0;
	while(*s)
	{
		s+=step(s);
		i++;
	}
	return i;
}

int Utf8::ord(const char* s)
{
	if(s[0]&0x80)
		if(s[0]&0x40)
			if(s[0]&0x20)
				if(s[0]&0x10)
					if(s[0]&0x08)
						return INVALID_CODEPOINT; // invalid: codepoints after U+10FFFF are deprecated
					else
						if((s[1]&0xC0)==0x80 && (s[2]&0xC0)==0x80 && (s[3]&0xC0)==0x80)
							if(s[0]<0xF4 || s[1]<0x8F)
								return (s[0]&0x0F)<<18 | (s[1]&0x3F)<<12 | (s[2]&0x3F)<<6 | (s[3]&0x3F);
							else
								return INVALID_CODEPOINT; // invalid: codepoints after U+10FFFF are deprecated
						else
							return INVALID_CODEPOINT; // invalid: 11110xxx not followed by 10xxxxxx 10xxxxxx 10xxxxxx
				else
					if((s[1]&0xC0)==0x80 && (s[2]&0xC0)==0x80)
						return (s[0]&0x1F)<<12 | (s[1]&0x3F)<<6 | (s[2]&0x3F);
					else
						return INVALID_CODEPOINT; // invalid: 1110xxxx not followed by 10xxxxxx 10xxxxxx
			else
				if((s[1]&0xC0)==0x80)
					return (s[0]&0x3F)<<6 | (s[1]&0x3F);
				else
					return INVALID_CODEPOINT; // invalid: 110xxxxx not followed by 10xxxxxx
		else
			return INVALID_CODEPOINT; // invalid: 10xxxxxx without an initializer
	else
		return s[0];
}

void Utf8::chr(char* s,int k)
{
	if(k>0x7F)
		if(k>0x07FF)
			if(k>0xFFFF)
				if(k>0x10FFFF)
					chr(s,INVALID_CODEPOINT);
				else
				{
					s[0]=0xF0|k>>18;
					s[1]=0x80|(k>>12&0x3F);
					s[2]=0x80|(k>>6&0x3F);
					s[3]=0x80|(k&0x3F);
					s[4]=0;
				}
			else
			{
				s[0]=0xE0|k>>12;
				s[1]=0x80|(k>>6&0x3F);
				s[2]=0x80|(k&0x3F);
				s[3]=0;
			}
		else
		{
			s[0]=0xC0|k>>6;
			s[1]=0x80|(k&0x3F);
			s[2]=0;
		}
	else
	{
		s[0]=k;
		s[1]=0;
	}
}
std::string Utf8::chr(int k)
{
	char r[5];
	chr(r,k);
	return std::string(r);
}
