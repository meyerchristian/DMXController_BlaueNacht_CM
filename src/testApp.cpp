#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(20);
    
    
    // OSC Emfänger
    osc.setup();
    sender.setup(HOST, PORT);
   	cout << "Listening fo OSC messages on PORT: " << PORT << "\n";
	receiver.setup(PORT);
	current_msg_string = 0;
    
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
    dmx->setChannels(29);
    // Color presetting
    col_01.setHsb(0, 0, 0);   // left wall
    col_02.setHsb(0, 0, 0);   // heart
    col_03.setHsb(0, 0, 0);   // right wall
    col_04.setHsb(0, 0, 0);   // trees
    
    // Terminal control
    //updateConsole();
    
    // DMX control
    updateDMX();
    
    // Brightness col_03
    //zeit = ofGetElapsedTimeMillis();

}

//--------------------------------------------------------------
void testApp::update(){
    


    updateTouchOSC();
    
    if (touchosc == true) {
    osc.listen();

    col_01.setHue(osc.settings[0]);
        updateDMX();
    col_01.setSaturation(osc.settings[1]);
        updateDMX();
    col_01.setBrightness(osc.settings[2]);
        updateDMX();
        
    col_02.setHue(osc.settings[3]);
        updateDMX();
    col_02.setSaturation(osc.settings[4]);
        updateDMX();
    col_02.setBrightness(osc.settings[5]);
        updateDMX();
    
    col_03.setHue(osc.settings[6]);
        updateDMX();
    col_03.setSaturation(osc.settings[7]);
        updateDMX();
    col_03.setBrightness(osc.settings[8]);
        updateDMX();
        
    col_04.setHue(osc.settings[9]);
        updateDMX();
    col_04.setSaturation(osc.settings[10]);
        updateDMX();
    col_04.setBrightness(osc.settings[11]);
        updateDMX();
    speedspektrum = osc.settings[12];
        updateDMX();
    valuespektrum = osc.settings[13];
        updateDMX();
    }
    
    
    // Spektrum
    if(ofGetElapsedTimeMillis()-timespektrum > speedspektrum){
        
        osc.settings[9] += valuespektrum;
        col_04.setHue(osc.settings[9]);
        timespektrum = ofGetElapsedTimeMillis();
        updateDMX();
        // cout << "       Spektrum: " << ofToString(osc.settings[9]) << endl;
        if(osc.settings[9] >= 255) {
            osc.settings[9] = 1;
            col_04.setHue(osc.settings[9]);
        }
    }

    // OSC Empfänger
    // hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        // unrecognized message: display on the bottom of the screen
        string msg_string;
        msg_string = m.getAddress();
        msg_string += ": ";
       
        for(int i = 0; i < m.getNumArgs(); i++){
            // get the argument type
            msg_string += m.getArgTypeName(i);
            msg_string += ":";
     
            if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                msg_string += ofToString(m.getArgAsFloat(i));
                oscIncoming = m.getArgAsFloat(i);
                cout <<"                                 oscIncoming " << oscIncoming << endl;
                
                // Brightness col_03
                anton = oscIncoming;

               /* for (int i; i <= 200; i++){
                    osc.settings[8] += 1;
                    col_03.setBrightness(osc.settings[8]);
                    updateDMX();
                    cout << "osc8 :" << osc.settings[8] << endl;
                        if (osc.settings[8]>200){break;}
                }
            */
                //cout << "osc8 :" << osc.settings[8] << endl;
                col_03.setBrightness(osc.settings[8]);
               // cout << "Brightness :" <<col_03.getBrightness() << endl;
                updateDMX();
                
                /*
                
                if (ofGetElapsedTimeMillis()-timezwei > (anton/320)){
                    osc.settings[8] += 1;
                    col_03.setBrightness(osc.settings[8]);
                    timezwei = ofGetElapsedTimeMillis();
                    updateDMX();
                    //cout << "Col_04 Spektrum: " << ofToString(osc.settings[9]) << endl;
                    if(osc.settings[8] >= 255) {
                        osc.settings[8] = 255;
                        col_03.setBrightness(osc.settings[8]);
                    }
                    updateDMX();
                }
                
                
                zeit = ofGetElapsedTimeMillis();
                cout <<"Anton " << anton << endl;
                if (ofGetElapsedTimeMillis()-zeit <= (anton/2)){
                    brightnessplus();
                    cout << "test" << endl;
                }
                
                
                if ((ofGetElapsedTimeMillis()-zeit > (anton/2)) && (ofGetElapsedTimeMillis()-zeit <= anton)){
                    brightnessminus();
                }
                
                if (ofGetElapsedTimeMillis()-zeit > anton){
                    anton = oscIncoming;
                }*/
            }
        }
        /*
        // add to the list of strings to display
        msg_strings[current_msg_string] = msg_string;
        timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
        current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
        // clear the next line
        msg_strings[current_msg_string] = "";
        */
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
    
}
void testApp::setGui2(){
    
    
    gui2 = new ofxUISuperCanvas("col_02 - heart");
    gui2->addSpacer();
    
    gui2->addSlider("Hue", 0, 1, col_02.getHue()/255);
    gui2->addSlider("Saturation", 0, 1, col_02.getSaturation()/255);
    gui2->addSlider("Brightness", 0, 1, col_02.getBrightness()/255);
    
    gui2->setPosition(10,150);
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent,this,&testApp::gui2Event);
    
}
void testApp::setGui3(){
    
    
    gui3 = new ofxUISuperCanvas("col_03 - right wall");
    gui3->addSpacer();
    
    gui3->addSlider("Hue", 0, 1, col_03.getHue()/255);
    gui3->addSlider("Saturation", 0, 1, col_03.getSaturation()/255);
    gui3->addSlider("Brightness", 0, 1, col_03.getBrightness()/255);
    
    gui3->setPosition(10,290);
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent,this,&testApp::gui3Event);
    
}
void testApp::setGui4(){
    
    
    gui4 = new ofxUISuperCanvas("col_04 - trees");
    gui4->addSpacer();
    
    gui4->addSlider("Hue", 0, 1, col_04.getHue()/255);
    gui4->addSlider("Saturation", 0, 1, col_04.getSaturation()/255);
    gui4->addSlider("Brightness", 0, 1, col_04.getBrightness()/255);
    gui4->addSlider("Speed", 0, 200, speedspektrum);
    gui4->addSlider("Value", 0 , 10, valuespektrum);
    
    gui4->setPosition(10,430);
    gui4->autoSizeToFitWidgets();
    ofAddListener(gui4->newGUIEvent,this,&testApp::gui4Event);
    
}


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
       // updateConsole();
        updateDMX();
    }
}
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
        
       // updateConsole();
        updateDMX();
    }
}
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
        
        if(name == "Speed"){
            speedspektrum = int(slider->getValue());
        }
        
        if(name == "Value"){
            valuespektrum = int(slider->getValue());
        }
       // updateConsole();
        updateDMX();
    }
}
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
        
       // updateConsole();
        updateDMX();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    /*
    int spacing = 50;
	ofBeginShape();
    
	for(int x=0; x<ofGetWidth(); x+= spacing) {
		ofCurveVertex(x, ofGetHeight()/2 + ofGetHeight() * 0.3f * sin(x*0.01f + ofGetFrameNum() * 0.02f));
            test = sin(x*0.01f + ofGetFrameNum() * 0.02f);
        cout << test << endl;
	}
    ofEndShape(false);
    */
    
    ofBeginShape();
    float x = 5;
		ofCurveVertex(x, ofGetHeight()/2 + ofGetHeight() * 0.3f * sin(x*0.01f + ofGetFrameNum() * 0.02f));
        test = sin(x*0.01f + ofGetFrameNum() * 0.03f);
        cout <<"sin: " << test << endl;
    
        col_04.setBrightness(50+(abs(test*200)));
    c3test = 100+(abs(test)*200)*(oscIncoming/10);
    cout << "                                            c3test: " << c3test << endl;
        col_03.setBrightness(c3test);
    cout <<"                 sinus col_03: " << col_03.getBrightness() << endl;
        updateDMX();
    
   	ofEndShape(false);
    
    
    ofFill();
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetColor(col_04);
	ofRect(380, 525, 8,test*95);
    
    
    
    if (touchosc == false){
        ofSetColor(255,255,255);
        ofDrawBitmapString("TouchOSC deactivated [1/2]", 15, 660);
    }
    else if (touchosc == true) {
        ofSetColor(255,255,255);
        ofDrawBitmapString("TouchOSC activated [1/2]", 15, 660);
    };
    
    ofSetColor(255,255,255);
    ofDrawBitmapString("Framerate: " + ofToString(int(ofGetFrameRate())), 240, 670);
    
    ofSetColor(255,255,255);
        ofDrawBitmapString("Elapsed time [sec] : " + ofToString(int(ofGetElapsedTimef())), 15,680);
    
        drawRects();
    }

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key == 'a'){
        brightness = true;
    }
    
    if (key == 'b'){
        brightness = false;
    }
    
    if (key == '1') {
        touchosc = true;
        
        osc.settings[0] = col_01.getHue();
        osc.settings[1] = col_01.getSaturation();
        osc.settings[2] = col_01.getBrightness();
        
        osc.settings[3] = col_02.getHue();
        osc.settings[4] = col_02.getSaturation();
        osc.settings[5] = col_02.getBrightness();
        
        osc.settings[6] = col_03.getHue();
        osc.settings[7] = col_03.getSaturation();
        osc.settings[8] = col_03.getBrightness();
        
        osc.settings[9] = col_04.getHue();
        osc.settings[10] = col_04.getSaturation();
        osc.settings[11] = col_04.getBrightness();
        osc.settings[12] = speedspektrum;
        osc.settings[13] = valuespektrum;
        
    }
    
    if (key == '2') {
        touchosc = false;
    }
    
    if (key == '3') {
        setGui1();
        setGui2();
        setGui3();
        setGui4();
    }
    
}

//--------------------------------------------------------------
void testApp::exit(){
    
    
    //turn off
    col_01.set(0, 0, 0);
    col_02.set(0, 0, 0);
    col_03.set(0, 0, 0);
    col_04.set(0, 0, 0);
    updateDMX();
    //updateConsole();
    
    delete gui1;
    delete gui2;
    delete gui3;
    delete gui4;
    
    //disconnect Interface
    if(hasDevice){
        dmx->disconnect();
        delete dmx;
    }
}

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
}

//--------------------------------------------------------------
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
}

//--------------------------------------------------------------
void testApp::brightnessplus(){

    if (ofGetElapsedTimeMillis()-timezwei > (anton/320)){
        osc.settings[8] += 1;
        col_03.setBrightness(osc.settings[8]);
        timezwei = ofGetElapsedTimeMillis();
        updateDMX();
        //cout << "Col_04 Spektrum: " << ofToString(osc.settings[9]) << endl;
        if(osc.settings[8] >= 255) {
            osc.settings[8] = 255;
            col_03.setBrightness(osc.settings[8]);
        }
        updateDMX();
    }
}

//--------------------------------------------------------------
void testApp::brightnessminus(){

     if(ofGetElapsedTimeMillis()-timezwei > (anton/320)){
        osc.settings[8] -= 1;
        col_03.setBrightness(osc.settings[8]);
        timezwei = ofGetElapsedTimeMillis();
        updateDMX();
        //cout << "Col_04 Spektrum: " << ofToString(osc.settings[9]) << endl;
        if(osc.settings[8] <= 0) {
            osc.settings[8] = 0;
            col_03.setBrightness(osc.settings[8]);
        }
        updateDMX();
    }
}

//--------------------------------------------------------------
void testApp::drawRects(){
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
	ofRect(240, 430, 140,190);
	
    ofSetColor(255,255,255);
    ofDrawBitmapString("HSB: " +ofToString(int(col_04.getHue()))+ " " +ofToString(int(col_04.getSaturation()))+ " " +ofToString(int(col_04.getBrightness())), 245, 450 );
    ofDrawBitmapString("RGB: "+ofToString(int(col_04.r))+ " " +ofToString(int(col_04.g))+ " " +ofToString(int(col_04.b)), 245, 465 );
    ofDrawBitmapString("Time: " + ofToString(int(speedspektrum)), 245, 485);
    ofDrawBitmapString("Value: " + ofToString(int(valuespektrum)), 245, 500);
    

}

//--------------------------------------------------------------
void testApp::updateTouchOSC(){
    
    
        // Col_01 Update Touch OSC
        ofxOscMessage a;
        //a.clear();
        a.addFloatArg(col_01.getHue()/255);
        a.setAddress("/color/col_01_h");sender.sendMessage(a);
        
        ofxOscMessage b;
        //b.clear();
        b.addFloatArg(col_01.getSaturation()/255);
        b.setAddress("/color/col_01_s");sender.sendMessage(b);
        
        ofxOscMessage c;
        //c.clear();
        c.addFloatArg(col_01.getBrightness()/255);
        c.setAddress("/color/col_01_b");sender.sendMessage(c);
        
        // Col_02 Update Touch OSC
        ofxOscMessage d;
        //d.clear();
        d.addFloatArg(col_02.getHue()/255);
        d.setAddress("/color/col_02_h");sender.sendMessage(d);
        
        ofxOscMessage e;
        //e.clear();
        e.addFloatArg(col_02.getSaturation()/255);
        e.setAddress("/color/col_02_s");sender.sendMessage(e);
        
        ofxOscMessage f;
        //f.clear();
        f.addFloatArg(col_02.getBrightness()/255);
        f.setAddress("/color/col_02_b");sender.sendMessage(f);
        
        // Col_03 Update Touch OSC
        ofxOscMessage g;
        //g.clear();
        g.addFloatArg(col_03.getHue()/255);
        g.setAddress("/color/col_03_h");sender.sendMessage(g);
        
        ofxOscMessage h;
        //h.clear();
        h.addFloatArg(col_03.getSaturation()/255);
        h.setAddress("/color/col_03_s");sender.sendMessage(h);
        
        ofxOscMessage m;
        //m.clear();
        m.addFloatArg(col_03.getBrightness()/255);
        m.setAddress("/color/col_03_b");sender.sendMessage(m);
        
        // Col_04 Update Touch OSC
        ofxOscMessage j;
        //j.clear();
        j.addFloatArg(col_04.getHue()/255);
        j.setAddress("/color/col_04_h");sender.sendMessage(j);
        
        ofxOscMessage k;
        //k.clear();
        k.addFloatArg(col_04.getSaturation()/255);
        k.setAddress("/color/col_04_s");sender.sendMessage(k);
        
        ofxOscMessage l;
        //l.clear();
        l.addFloatArg(col_04.getBrightness()/255);
        l.setAddress("/color/col_04_b");sender.sendMessage(l);
    
    
        ofxOscMessage n;
        //m.clear();
        n.addFloatArg(speedspektrum/200);
        n.setAddress("/color/col_04_speedspektrum");sender.sendMessage(n);
    
        ofxOscMessage p;
        //m.clear();
        p.addFloatArg(valuespektrum/10);
        p.setAddress("/color/col_04_valuespektrum");sender.sendMessage(p);
}

