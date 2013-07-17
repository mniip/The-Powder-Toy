#include "SDL.h"
#include "SDL_main.h"
#include <android/log.h>
#include <jni.h>
#include <sstream>
#include "cat/LuaScriptInterface.h"
#include "cat/LuaScriptHelper.h"

#define JNI(x) Java_com_mniip_thepowdertoy_SDLActivity_##x

extern "C" void SDL_Android_Init(JNIEnv*e,jclass c);
extern int main(int argc,char**argv);

extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyDown(JNIEnv*e,jclass c,jint a);
extern "C" void JNI(onNativeKeyDown)(JNIEnv*e,jclass c,jint a){Java_org_libsdl_app_SDLActivity_onNativeKeyDown(e,c,a);}
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyUp(JNIEnv*e,jclass c,jint a);
extern "C" void JNI(onNativeKeyUp)(JNIEnv*e,jclass c,jint a){Java_org_libsdl_app_SDLActivity_onNativeKeyUp(e,c,a);}
extern "C" void Java_org_libsdl_app_SDLActivity_nativePause(JNIEnv*e,jclass c);
extern "C" void JNI(nativePause)(JNIEnv*e,jclass c,jint a){Java_org_libsdl_app_SDLActivity_nativePause(e,c);}
extern "C" void Java_org_libsdl_app_SDLActivity_nativeResume(JNIEnv*e,jclass c);
extern "C" void JNI(nativeResume)(JNIEnv*e,jclass c,jint a){Java_org_libsdl_app_SDLActivity_nativeResume(e,c);}

extern "C" void JNI(nativeQuit)(JNIEnv*e,jclass c,jint a){}

extern "C" void JNI(nativeInit)(JNIEnv*env,jclass cls,jobject obj)
{
    SDL_Android_Init(env,cls);
    int status;
    char*argv[2];
    argv[0]=strdup("SDL_app");
    argv[1]=NULL;
    SDL_SetMainReady();
    status=main(1,argv);
    exit(0);
}

int screen_width=1;
int screen_height=1;

extern "C" void Java_org_libsdl_app_SDLActivity_onNativeResize(JNIEnv*e,jclass c,jint a,jint b,jint d);
extern "C" void JNI(onNativeResize)(JNIEnv*env,jclass cls,jint w,jint h,jint o)
{
	Java_org_libsdl_app_SDLActivity_onNativeResize(env,cls,w,h,o);
	screen_width=w;
	screen_height=h;
}

int last_x=0;
int last_y=0;

extern "C" void Java_org_libsdl_app_SDLActivity_onNativeTouch(JNIEnv*e,jclass c,jint a,jint b,jint d,jfloat f,jfloat g,jfloat i);
extern "C" void JNI(onNativeTouch)(JNIEnv*env,jclass cls,jint devid,jint fingerid,jint action,jfloat x,jfloat y,jfloat p)
{
	Java_org_libsdl_app_SDLActivity_onNativeTouch(env,cls,devid,fingerid,action,x,y,p);
	// TODO: add stuff here
}

extern "C" void Java_org_libsdl_app_SDLActivity_onNativeAccel(JNIEnv*e,jclass c,jint x,jint y,jint z);
extern "C" void JNI(onNativeAccel)(JNIEnv*env,jclass cls,jint x,jint y,jint z)
{
	Java_org_libsdl_app_SDLActivity_onNativeAccel(env,cls,x,y,z);
	// TODO: add stuff here
}
