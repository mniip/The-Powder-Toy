#include "SDL.h"
#include "SDL_main.h"
#include <android/log.h>
#include <jni.h>

#define JNI(x) Java_com_mniip_thepowdertoy_SDLActivity_##x

extern "C" void SDL_Android_Init(JNIEnv*e,jclass c);
extern int main(int argc,char**argv);

extern "C" void Java_org_libsdl_app_SDLActivity_onNativeResize(JNIEnv*e,jclass c,jint a,jint b,jint d);
extern "C" void JNI(onNativeResize)(JNIEnv*e,jclass c,jint a,jint b,jint d){Java_org_libsdl_app_SDLActivity_onNativeResize(e,c,a,b,d);}
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyDown(JNIEnv*e,jclass c,jint a);
extern "C" void JNI(onNativeKeyDown)(JNIEnv*e,jclass c,jint a){Java_org_libsdl_app_SDLActivity_onNativeKeyDown(e,c,a);}
extern "C" void Java_org_libsdl_app_SDLActivity_onNativeKeyUp(JNIEnv*e,jclass c,jint a);
extern "C" void JNI(onNativeKeyUp)(JNIEnv*e,jclass c,jint a){Java_org_libsdl_app_SDLActivity_onNativeKeyUp(e,c,a);}
extern "C" void Java_org_libsdl_app_SDLActivity_nativePause(JNIEnv*e,jclass c);
extern "C" void JNI(nativePause)(JNIEnv*e,jclass c,jint a){Java_org_libsdl_app_SDLActivity_nativePause(e,c);}

extern "C" void JNI(nativeQuit)(JNIEnv*e,jclass c,jint a){}
extern "C" void JNI(onNativeAccel)(JNIEnv*e,jclass c,jint x,jint y,jint z){}

extern "C" void Android_JNI_CreateContext(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k);

extern "C" void JNI(nativeInit)(JNIEnv*env,jclass cls,jobject obj)
{
    SDL_Android_Init(env,cls);
    //Android_JNI_CreateContext(1,0,8,8,8,0,1,24,0,1,0);
    int status;
    char*argv[2];
    argv[0]=strdup("SDL_app");
    argv[1]=NULL;
    SDL_SetMainReady();
    status=main(1,argv);
    exit(0);
}
