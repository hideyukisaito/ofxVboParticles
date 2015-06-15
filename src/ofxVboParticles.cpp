//
//  ofxVboParticles.cpp
//
//  Created by Atsushi Tadokoro on 8/14/14.
//  Forked by Hideyuki Saito on 6/15/15
//
//

#include "ofxVboParticles.h"

ofxVboParticles::ofxVboParticles(int _maxParticles, float _pointSize){
    pointSpriteShader.load("shaders/pointSprite");
    
    maxParticles = _maxParticles;
    pointSize = _pointSize;
    numParticles = 0;
    friction = 0.01;
    
    static GLfloat distance[] = { 0.0, 0.0, 1.0 };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
//    glPointSize(pointSize);
    
    billboards.setUsage(GL_DYNAMIC_DRAW);
    billboards.setMode(OF_PRIMITIVE_POINTS);
    billboards.disableTextures();
    
    billboards.getVertices().resize(maxParticles);
    billboards.getColors().resize(maxParticles);
    billboards.getNormals().resize(maxParticles, ofVec3f(0));
}

void ofxVboParticles::update(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec3f(0, 0, 0);
        forces[i] -= velocitys[i] * friction;
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
        normals[i].x -= normals[i].y;
        
        billboards.getVertices()[i].set(positions[i].x, positions[i].y, positions[i].z);
        billboards.getNormals()[i].set(normals[i]);
    }
    
}

void ofxVboParticles::draw(){
    ofPushStyle();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    ofEnablePointSprites();
    
    if (texture.isAllocated() && pointSpriteShader.isLoaded()) {
        pointSpriteShader.begin();
        GLint loc = pointSpriteShader.getAttributeLocation("size");
        pointSpriteShader.setAttribute1f(loc, pointSize);
        pointSpriteShader.setUniformTexture("tex", texture, 0);
        billboards.draw();
        pointSpriteShader.end();
    } else {
        billboards.draw();
    }
    
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    ofDisablePointSprites();
    ofPopStyle();
}

void ofxVboParticles::loadTexture(const string path)
{
    ofDisableArbTex();
    texture.loadImage(path);
    ofEnableArbTex();
}

// normals are used for the alpha.
//
// normal.x : initial value
// normal.y : dicreasing rate

void ofxVboParticles::addParticle(ofVec3f _position, ofVec3f _velocity, ofColor _color, ofVec3f _normal){
    positions.push_back(_position);
    velocitys.push_back(_velocity);
    colors.push_back(_color);
    normals.push_back(_normal);
    forces.push_back(ofVec3f(0, 0, 0));
    
    billboards.getVertices()[numParticles].set(positions[numParticles].x, positions[numParticles].y, positions[numParticles].z);
    billboards.getColors()[numParticles].set(colors[numParticles]);
    billboards.getNormals()[numParticles].set(_normal);
    
    numParticles++;
    
    if (positions.size() > maxParticles) {
        positions.pop_front();
        colors.pop_front();
        velocitys.pop_front();
        forces.pop_front();
        normals.pop_front();
        
        for (int i = 0; i < numParticles-1; i++) {
            //billboards.getVertices()[i] = billboards.getVertices()[i + 1];
            billboards.getColors()[i] = billboards.getColors()[i + 1];
        }
        
        numParticles--;
    }
}