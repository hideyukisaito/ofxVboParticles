//
//  ofxVboParticles.h
//
//  Created by Atsushi Tadokoro on 8/14/14.
//  Forked by Hideyuki Saito on 6/15/15
//
//

#pragma once
#include "ofMain.h"

class ofxVboParticles {
public:
    ofxVboParticles(int maxParticles = 10000, float pointSize = 0.1);
    void update();
    void draw();
    void loadTexture(const string path);
    void clear();
    void addParticle(ofVec3f position = ofVec3f(0, 0, 0),
                     ofVec3f velocity = ofVec3f(0, 0, 0),
                     ofColor color = 0xffffff,
                     ofVec3f normal = ofVec3f(1, 0, 0));
    
    int maxParticles;
    float pointSize;
    
    int numParticles;
    deque<ofVec3f> positions;
    deque<ofVec3f> velocitys;
    deque<ofVec3f> forces;
    deque<ofColor> colors;
    deque<ofVec3f> normals;
    float friction;
    
    ofShader billboardShader;
    ofShader pointSpriteShader;
    ofImage texture;
    ofVboMesh billboards;
};


