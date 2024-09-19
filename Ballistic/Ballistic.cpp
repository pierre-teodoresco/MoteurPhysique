//
//  Ballistic.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 18/09/2024.
//

#include "Ballistic.hpp"
#include "ofMain.h"
#include "Vector3D/Vector3D.hpp"


void Ballistic::setup() {
    Vector3D pos(0.f, 700.f, 0.f);
    Vector3D velocity(70.f, -70.f, 0.f);
    p = new Particle(pos, velocity, 5);
}

float dtAvg = 1.f / 144.f; // Inital dt for 144 FPS

void Ballistic::update() {
    // Keep track of old position
    trajectory.push_back(p->position());
    
    // Gravity
    const Vector3D gravity(0.f, 9.81f, 0.f);
    p->applyForce(gravity);
    
    float dt = ofGetLastFrameTime();
    dtAvg = 0.9f * dtAvg + 0.1f * dt;   // moving average
    p->integrate(dtAvg);
}

void Ballistic::draw() {
    // Display frame time
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Frame time: " + ofToString(ofGetLastFrameTime()), 10, 20);
    
    // Draw trajectory
    ofSetColor(153, 204, 255);
    for (const auto& pos : trajectory) {
        ofDrawCircle(pos.v2(), 2);
    }
    
    // Draw particle p
    ofSetColor(51, 153, 255);
    p->draw(20);
}

void Ballistic::exit() {
    delete p;
}
