#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    // OSC
    osc.setup();
    
    // UI setup
    ofSetVerticalSync(true);
    ofSetWindowTitle("DMX Color Settings");
    setGui1();
    setGui2();
    setGui3();
    setGui4();
    
    // Device Management
    hasDevice = false;
    dmx = new ofxDmx;
    hasDevice = dmx->connect(DEVICE);
    
    // Color presetting
    col_01.setHsb(0, 0, 0);   // left wall
    col_02.setHsb(0, 0, 0);   // heart
    col_03.setHsb(0, 0, 0);   // right wall
    col_04.setHsb(0, 0, 0);   // trees
    
    /*
    col_01.getHue()/255;
    col_01.getSaturation()/255;
    col_01.getBrightness()/255;
    */
     
    // Terminal control
    updateConsole();
    
    // DMX control
    updateDMX();
    
    

}


//--------------------------------------------------------------
void testApp::update(){
    
    if (touchosc == true) {
    osc.listen();

    col_01.setHue(osc.settings[0]);
    col_01.setSaturation(osc.settings[1]);
    col_01.setBrightness(osc.settings[2]);
    
    col_02.setHue(osc.settings[3]);
    col_02.setSaturation(osc.settings[4]);
    col_02.setBrightness(osc.settings[5]);
    
    col_03.setHue(osc.settings[6]);
    col_03.setSaturation(osc.settings[7]);
    col_03.setBrightness(osc.settings[8]);
    
    col_04.setHue(osc.settings[9]);
    col_04.setSaturation(osc.settings[10]);
    col_04.setBrightness(osc.settings[11]);
    }
}

//--------------------------------------------------------------
void testApp::setGui1(){
    
    gui1 = new ofxUISuperCanvas("col_01 - left wall");
    gui1->addSpacer();
    
    gui1->addSlider("Hue", 0, 1, col_01.getHue()/255);
    gui1->addSlider("Saturation", 0, 1, col_01.getSaturation()/255);
    gui1->addSlider("Brightness", 0, 1, col_01.getBrightness()/255);
    
    gui1->setPosition(10,10);
    gui1->autoSizeToFitWidgets();
    ofAddListener(gui1->newGUIEvent,this,&testApp::gui1Event);
    
}   // Slider left wall
void testApp::setGui2(){
    
    gui2 = new ofxUISuperCanvas("col_02 - heart");
    gui2->addSpacer();
    
    gui2->addSlider("Hue", 0, 1, col_02.getHue()/255);
    gui2->addSlider("Saturation", 0, 1, col_02.getSaturation()/255);
    gui2->addSlider("Brightness", 0, 1, col_02.getBrightness()/255);
    
    gui2->setPosition(10,150);
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent,this,&testApp::gui2Event);
    
}   // Slider heart
void testApp::setGui3(){
    
    gui3 = new ofxUISuperCanvas("col_03 - right wall");
    gui3->addSpacer();
    
    gui3->addSlider("Hue", 0, 1, col_03.getHue()/255);
    gui3->addSlider("Saturation", 0, 1, col_03.getSaturation()/255);
    gui3->addSlider("Brightness", 0, 1, col_03.getBrightness()/255);
    
    gui3->setPosition(10,290);
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent,this,&testApp::gui3Event);
    
}   // Slider right wall
void testApp::setGui4(){
    
    gui4 = new ofxUISuperCanvas("col_04 - trees");
    gui4->addSpacer();
    
    gui4->addSlider("Hue", 0, 1, col_04.getHue()/255);
    gui4->addSlider("Saturation", 0, 1, col_04.getSaturation()/255);
    gui4->addSlider("Brightness", 0, 1, col_04.getBrightness()/255);
    
    gui4->setPosition(10,430);
    gui4->autoSizeToFitWidgets();
    ofAddListener(gui4->newGUIEvent,this,&testApp::gui4Event);
    
}   // Slider trees

void testApp::gui1Event(ofxUIEventArgs &e){
    
    string name = e.getName();
    int kind = e.getKind();
    
    if (kind == OFX_UI_WIDGET_SLIDER_H) {
        
        ofxUISlider *slider = (ofxUISlider*) e.widget;
        
        if(name == "Hue"){
            col_01.setHue(slider->getValue()*255);
        }
        
        if(name == "Saturation"){
            col_01.setSaturation(slider->getValue()*255);
        }
        
        if(name == "Brightness"){
            col_01.setBrightness(slider->getValue()*255);
        }
        updateConsole();
        updateDMX();
    }
}   // Control left wall
void testApp::gui2Event(ofxUIEventArgs &e){
    
    string name = e.getName();
    int kind = e.getKind();
    
    if (kind == OFX_UI_WIDGET_SLIDER_H) {
        
        ofxUISlider *slider = (ofxUISlider*) e.widget;
        
        if(name == "Hue"){
            col_02.setHue(slider->getValue()*255);
        }
        
        if(name == "Saturation"){
            col_02.setSaturation(slider->getValue()*255);
        }
        
        if(name == "Brightness"){
            col_02.setBrightness(slider->getValue()*255);
        }
        
        updateConsole();
        updateDMX();
    }
}   // Control heart

void testApp::gui4Event(ofxUIEventArgs &e){
    
    string name = e.getName();
    int kind = e.getKind();
    
    if (kind == OFX_UI_WIDGET_SLIDER_H) {
        
        ofxUISlider *slider = (ofxUISlider*) e.widget;
        
        if(name == "Hue"){
            col_04.setHue(slider->getValue()*255);
        }
        
        if(name == "Saturation"){
            col_04.setSaturation(slider->getValue()*255);
        }
        
        if(name == "Brightness"){
            col_04.setBrightness(slider->getValue()*255);
        }
        
        updateConsole();
        updateDMX();
    }
}   // Control trees
void testApp::gui3Event(ofxUIEventArgs &e){
    
    string name = e.getName();
    int kind = e.getKind();
    
    if (kind == OFX_UI_WIDGET_SLIDER_H) {
        
        ofxUISlider *slider = (ofxUISlider*) e.widget;
        
        if(name == "Hue"){
            col_03.setHue(slider->getValue()*255);
        }
        
        if(name == "Saturation"){
            col_03.setSaturation(slider->getValue()*255);
        }
        
        if(name == "Brightness"){
            col_03.setBrightness(slider->getValue()*255);
        }
        
        updateConsole();
        updateDMX();
    }
}   // Control right wall


//--------------------------------------------------------------
void testApp::draw(){
    
    if (touchosc == false){
        ofSetColor(255,255,255);
        ofDrawBitmapString("1,2: TouchOSC deactivated " /*+ ofToString(bool(touchosc))*/,15, 590);
    }
    else if (touchosc == true)
    {ofSetColor(255,255,255);
        ofDrawBitmapString("1,2: TouchOSC activated " /*+ ofToString(bool(touchosc))*/,15, 590);
    };

    
    // ColorControl left wall
    ofFill();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(col_01);
	ofRect(240, 10, 140, 128);
    
    ofSetColor(255,255,255);
    ofDrawBitmapString("HSB: " +ofToString(int(col_01.getHue()))+ " " +ofToString(int(col_01.getSaturation()))+ " " +ofToString(int(col_01.getBrightness())), 245, 30 );
    ofDrawBitmapString("RGB: "+ofToString(int(col_01.r))+ " " +ofToString(int(col_01.g))+ " " +ofToString(int(col_01.b)), 245, 45 );
    
    // ColorControl heart
    ofFill();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(col_02);
	ofRect(240, 150, 140,128);
    
	ofSetColor(255,255,255);
    ofDrawBitmapString("HSB: " +ofToString(int(col_02.getHue()))+ " " +ofToString(int(col_02.getSaturation()))+ " " +ofToString(int(col_02.getBrightness())), 245, 170 );
    ofDrawBitmapString("RGB: "+ofToString(int(col_02.r))+ " " +ofToString(int(col_02.g))+ " " +ofToString(int(col_02.b)), 245, 185 );
    
    // ColorControl right wall
    ofFill();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(col_03);
	ofRect(240, 290, 140,128);
    
	ofSetColor(255,255,255);
    ofDrawBitmapString("HSB: " +ofToString(int(col_03.getHue()))+ " " +ofToString(int(col_03.getSaturation()))+ " " +ofToString(int(col_03.getBrightness())), 245, 310 );
    ofDrawBitmapString("RGB: "+ofToString(int(col_03.r))+ " " +ofToString(int(col_03.g))+ " " +ofToString(int(col_03.b)), 245, 325 );
    
    // ColorControl trees
    ofFill();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(col_04);
	ofRect(240, 430, 140,128);
	
    ofSetColor(255,255,255);
    ofDrawBitmapString("HSB: " +ofToString(int(col_04.getHue()))+ " " +ofToString(int(col_04.getSaturation()))+ " " +ofToString(int(col_04.getBrightness())), 245, 450 );
    ofDrawBitmapString("RGB: "+ofToString(int(col_04.r))+ " " +ofToString(int(col_04.g))+ " " +ofToString(int(col_04.b)), 245, 465 );
    
    ofDrawBitmapString("Elapsed time [sec] : " + ofToString(int(ofGetElapsedTimef())), 15,573);
    
    
}   // ColorControl

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key == '1') {
        touchosc = true;
    }
    if (key == '2') {
        touchosc = false;
    }
    /*
    if (key == 'a') {
        kb = true;
    }
    
    if (kb == true) {
        ////#########################################################################################
        //#################################   FARBEN   ############################################
        //#########################################################################################
        
        if (key == 'q'){
            col_01.setHue(0.1*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'w'){
            col_01.setHue(0.2*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'e'){
            col_01.setHue(0.3*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'r'){
            col_01.setHue(0.4*255);
            updateDMX();
            updateConsole();
        }
        if (key == 't'){
            col_01.setHue(0.5*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'z'){
            col_01.setHue(0.6*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'u'){
            col_01.setHue(0.7*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'i'){
            col_01.setHue(0.8*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'o'){
            col_01.setHue(0.9*255);
            updateDMX();
            updateConsole();
        }
        if (key == 'p'){
            col_01.setHue(1.0*255);
            updateDMX();
            updateConsole();
        }
        
        
        
        //#########################################################################################
        //#################################   SŠttigung   #########################################
        //#########################################################################################
        
        if (key == 'a'){
            col_01.setSaturation(0.1*255);
            dmx->update();
            updateConsole();
        }
        if (key == 's'){
            col_01.setSaturation(0.2*255);
            dmx->update();
            updateConsole();
        }
        if (key == 'd'){
            col_01.setSaturation(0.3*255);
            dmx->update();
            updateConsole();
        }
        if (key == 'f'){
            col_01.setSaturation(0.4*255);
            dmx->update();
            updateConsole();
        }
        if (key == 'g'){
            col_01.setSaturation(0.5*255);
            dmx->update();
            updateConsole();
        }
        if (key == 'h'){
            col_01.setSaturation(0.6*255);
            dmx->update();
            updateConsole();
        }
        if (key == 'j'){
            col_01.setSaturation(0.7*255);
            dmx->update();
            updateConsole();
        }
        if (key == 'k'){
            col_01.setSaturation(0.8*255);
            dmx->update();
            updateConsole();
        }
        if (key == 'l'){
            col_01.setSaturation(0.9*255);
            dmx->update();
            updateConsole();
        }
        if (key == '#'){
            col_01.setSaturation(1.0*255);
            dmx->update();
            updateConsole();
        }
        
        //#########################################################################################
        //#################################   Helligkeit   ########################################
        //#########################################################################################
        
        if (key == '1'){
            col_01.setBrightness(0.1*255);
            dmx->update();
            updateConsole();
        }
        if (key == '2'){
            col_01.setBrightness(0.2*255);
            dmx->update();
            updateConsole();
        }
        if (key == '3'){
            col_01.setBrightness(0.3*255);
            dmx->update();
            updateConsole();
        }
        if (key == '4'){
            col_01.setBrightness(0.4*255);
            dmx->update();
            updateConsole();
        }
        if (key == '5'){
            col_01.setBrightness(0.5*255);
            dmx->update();
            updateConsole();
        }
        if (key == '6'){
            col_01.setBrightness(0.6*255);
            dmx->update();
            updateConsole();
        }
        if (key == '7'){
            col_01.setBrightness(0.7*255);
            dmx->update();
            updateConsole();
        }
        if (key == '8'){
            col_01.setBrightness(0.8*255);
            dmx->update();
            updateConsole();
        }
        if (key == '9'){
            col_01.setBrightness(0.9*255);
            dmx->update();
            updateConsole();
        }
        if (key == '0'){
            col_01.setBrightness(1.0*255);
            dmx->update();
            updateConsole();
        }
    }
    
     //ColorControlviaKeyboard */ }

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void testApp::exit(){
    
    //turn off
    col_01.set(0, 0, 0);
    col_02.set(0, 0, 0);
    col_03.set(0, 0, 0);
    col_04.set(0, 0, 0);
    updateDMX();
    updateConsole();
    
    delete gui1;
    delete gui2;
    delete gui3;
    delete gui4;
    
    //disconnect Interface
    if(hasDevice){
        dmx->disconnect();
        delete dmx;
    }
}   // Close program

//--------------------------------------------------------------
void testApp::updateDMX(){
    
    if (hasDevice) {
        dmx->setLevel(group_01.address + group_01.red, col_01.r);       // left wall
        dmx->setLevel(group_01.address + group_01.green, col_01.g);
        dmx->setLevel(group_01.address + group_01.blue, col_01.b );
        dmx->setLevel(group_01.address + group_01.master, 255);
        
        
        
        dmx->setLevel(group_02.address + group_02.red, col_02.r);       // heart
        dmx->setLevel(group_02.address + group_02.green, col_02.g);
        dmx->setLevel(group_02.address + group_02.blue, col_02.b );
        dmx->setLevel(group_02.address + group_02.master, 255);
        
        dmx->setLevel(group_03.address + group_03.red, col_03.r);       // right wall
        dmx->setLevel(group_03.address + group_03.green, col_03.g);
        dmx->setLevel(group_03.address + group_03.blue, col_03.b );
        dmx->setLevel(group_03.address + group_03.master, 255);
        
        dmx->setLevel(group_04.address + group_04.red, col_04.r);       // trees
        dmx->setLevel(group_04.address + group_04.green, col_04.g);
        dmx->setLevel(group_04.address + group_04.blue, col_04.b );
        dmx->setLevel(group_04.address + group_04.master, 255);
        
        dmx->update();
    }
}   // DMX control

void testApp::updateConsole(){
    
    cout << " " << endl;
    cout << "col_01 - right wall" << endl;
    cout << "H:" << ofToString(int(col_01.getHue())) << "  S:" << ofToString(int(col_01.getSaturation())) << "  B:" << ofToString(int(col_01.getBrightness())) << endl;
    cout << "R:" << ofToString(int(col_01.r)) << "  G:" << ofToString(int(col_01.g)) << "  B:" << ofToString(int(col_01.b)) << endl;
    
    cout << " " << endl;
    cout << "col_02 - heart" << endl;
    cout << "H:" << ofToString(int(col_02.getHue())) << "  S:" << ofToString(int(col_02.getSaturation())) << "  B:" << ofToString(int(col_02.getBrightness())) << endl;
    cout << "R:" << ofToString(int(col_02.r)) << "  G:" << ofToString(int(col_02.g)) << "  B:" << ofToString(int(col_02.b)) << endl;
    
    cout << " " << endl;
    cout << "col_03 - left wall" << endl;
    cout << "H:" << ofToString(int(col_03.getHue())) << "  S:" << ofToString(int(col_03.getSaturation())) << "  B:" << ofToString(int(col_03.getBrightness())) << endl;
    cout << "R:" << ofToString(int(col_03.r)) << "  G:" << ofToString(int(col_03.g)) << "  B:" << ofToString(int(col_03.b)) << endl;
    
    cout << " " << endl;
    cout << "col_04 - trees" << endl;
    cout << "H:" << ofToString(int(col_04.getHue())) << "  S:" << ofToString(int(col_04.getSaturation())) << "  B:" << ofToString(int(col_04.getBrightness())) << endl;
    cout << "R:" << ofToString(int(col_04.r)) << "  G:" << ofToString(int(col_04.g)) << "  B:" << ofToString(int(col_04.b)) << endl;
    
    cout << "__________________" << endl;
}   // Terminal control

