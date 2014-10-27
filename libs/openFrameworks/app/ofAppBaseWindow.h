#pragma once

#include "ofPoint.h"
#include "ofTypes.h"
#include "ofEvents.h"
#include "ofWindowSettings.h"
#if defined(TARGET_LINUX) && !defined(TARGET_RASPBERRY_PI)
#include <X11/Xlib.h>
#endif

class ofBaseApp;
class ofBaseRenderer;

class ofAppBaseWindow{

public:

	ofAppBaseWindow(){};
	virtual ~ofAppBaseWindow(){};

	virtual void setup(const ofWindowSettings & settings)=0;
	virtual void update()=0;
	virtual void draw()=0;
	virtual void run(ofBaseApp * appPtr) {}
	virtual bool windowShouldClose(){
		return events().windowShouldClose();
	}
	virtual void close(){};
	virtual ofCoreEvents & events() = 0;
	virtual shared_ptr<ofBaseRenderer> & renderer() = 0;

	virtual void hideCursor() {}
	virtual void showCursor() {}

	virtual void	setWindowPosition(int x, int y) {}
	virtual void	setWindowShape(int w, int h) {}

	virtual ofPoint	getWindowPosition() {return ofPoint(); }
	virtual ofPoint	getWindowSize(){return ofPoint(); }
	virtual ofPoint	getScreenSize(){return ofPoint(); }

	virtual void			setOrientation(ofOrientation orientation){ }
	virtual ofOrientation	getOrientation(){ return OF_ORIENTATION_DEFAULT; }
	virtual bool	doesHWOrientation(){return false;}

	//this is used by ofGetWidth and now determines the window width based on orientation
	virtual int		getWidth(){ return 0; }
	virtual int		getHeight(){ return 0; }

	virtual void	setWindowTitle(string title){}

	virtual ofWindowMode	getWindowMode() {return OF_WINDOW ;}

	virtual void	setFullscreen(bool fullscreen){}
	virtual void	toggleFullscreen(){}

	virtual void	enableSetupScreen(){}
	virtual void	disableSetupScreen(){}
	
	virtual void	setVerticalSync(bool enabled){};
    virtual void    setClipboardString(const string& text) {}
    virtual string  getClipboardString() { return ""; }

#if defined(TARGET_LINUX) && !defined(TARGET_RASPBERRY_PI)
	virtual Display* getX11Display(){return NULL;}
	virtual Window  getX11Window() {return 0;}
#endif

#if defined(TARGET_LINUX) && !defined(TARGET_OPENGLES)
	virtual GLXContext getGLXContext(){return 0;}
#endif

#if defined(TARGET_LINUX) && defined(TARGET_OPENGLES)
	virtual EGLDisplay getEGLDisplay(){return 0;}
	virtual EGLContext getEGLContext(){return 0;}
	virtual EGLSurface getEGLSurface(){return 0;}
#endif

#if defined(TARGET_OSX)
	virtual void * getNSGLContext(){return NULL;}
	virtual void * getCocoaWindow(){return NULL;}
#endif

#if defined(TARGET_WIN32)
	virtual HGLRC getWGLContext(){return 0;}
	virtual HWND getWin32Window(){return 0;}
#endif
};

class ofAppBaseGLWindow: public ofAppBaseWindow{
public:
	virtual ~ofAppBaseGLWindow(){}
	virtual void setup(const ofGLWindowSettings & settings)=0;
	void setup(const ofWindowSettings & settings){
		const ofGLWindowSettings * glSettings = dynamic_cast<const ofGLWindowSettings*>(&settings);
		if(glSettings){
			setup(*glSettings);
		}else{
			setup(ofGLWindowSettings(settings));
		}
	}
};

class ofAppBaseGLESWindow: public ofAppBaseWindow{
public:
	virtual ~ofAppBaseGLESWindow(){}
	virtual void setup(const ofGLESWindowSettings & settings)=0;
	void setup(const ofWindowSettings & settings){
		const ofGLESWindowSettings * glSettings = dynamic_cast<const ofGLESWindowSettings*>(&settings);
		if(glSettings){
			setup(*glSettings);
		}else{
			setup(ofGLESWindowSettings(settings));
		}
	}
};
