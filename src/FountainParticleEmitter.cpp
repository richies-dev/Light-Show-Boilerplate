#include "FountainParticleEmitter.h"

void FountainParticleEmitter::setParticleToDefault(Particle& p) {
    p.speed = glm::vec3(
        hh::getRandomRange(-particleHorizontalSpread, particleHorizontalSpread),
        hh::getRandomRange(particleVerticalForce - 2, particleVerticalForce),
        hh::getRandomRange(-particleHorizontalSpread, particleHorizontalSpread));

    p.position = emmisionPosition;
    p.lifeTime = defaultLifeTime;
    p.weight   = defaultWeight;
    p.size     = defaultScale;
    p.color    = defaultColor;
}

void FountainParticleEmitter::performParticleCalculations(Particle& p) {
    p.speed += (currentWorldSettings->getWind() + currentWorldSettings->getGravity() + glm::vec3(0, -p.weight, 0)) * GameInfo::deltaTime * 0.5f;
    p.position += p.speed * GameInfo::deltaTime;
    p.speed.y -= GameInfo::deltaTime * fountainPull;
    p.color.a -= GameInfo::deltaTime / defaultLifeTime * defaultColor.a;
    p.size += GameInfo::deltaTime * endScale;
}