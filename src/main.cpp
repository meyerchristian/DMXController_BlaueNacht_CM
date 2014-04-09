#include "testApp.h"
#include "ofAppGlutWindow.h"


int main() {
	ofAppGlutWindow window;
	//ofSetupOpenGL(&window, 512, 256, OF_WINDOW);
    ofSetupOpenGL(450,750,OF_WINDOW);
	ofRunApp(new testApp());
}
