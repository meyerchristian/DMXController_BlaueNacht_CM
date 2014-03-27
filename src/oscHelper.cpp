//
//  File.cpp
//  DMXController_BlaueNacht_CM
//
//  Created by Christian Meyer on 26.03.14.
//
//

#include "oscHelper.h"
#include "testApp.h"

void oscHelper::setup()
{
    cout << "listening for osc messages on port " << 1100 << "\n";
    receiver.setup(1100);
    
    settings[0] = 0;
    settings[1] = 255;
    settings[2] = 255;
    settings[3] = 0;
    settings[4] = 255;
    settings[5] = 255;
    settings[6] = 0;
    settings[7] = 255;
    settings[8] = 255;
    settings[9] = 0;
    settings[10] = 255;
    settings[11] = 255;
}

void oscHelper::listen()
{
    while(receiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/color/col_01_h"){
            settings[0] = (m.getArgAsFloat(0));
        }

        if(m.getAddress() == "/color/col_01_s"){
            settings[1] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_01_b"){
            settings[2] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_02_h"){
            settings[3] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_02_s"){
            settings[4] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_02_b"){
            settings[5] = (m.getArgAsFloat(0));
        }

        if(m.getAddress() == "/color/col_03_h"){
            settings[6] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_03_s"){
            settings[7] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_03_b"){
            settings[8] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_04_h"){
            settings[9] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_04_s"){
            settings[10] = (m.getArgAsFloat(0));
        }
        
        if(m.getAddress() == "/color/col_04_b"){
            settings[11] = (m.getArgAsFloat(0));
        }
    }
}

float* oscHelper::getSettings()
{
    return settings;
}