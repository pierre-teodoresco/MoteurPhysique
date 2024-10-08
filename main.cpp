#include "ofMain.h"
#include "ofApp.h"

#include "Vector3D/testVector3D.h"

//========================================================================
int main( ){
    
    // Unit Tests
    test::startVector3DTest();

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
