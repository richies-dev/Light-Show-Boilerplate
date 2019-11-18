#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include "DebuggingController.h"
#include "DirectionalLightShadowMap.h"
#include "FountainParticleEmitter.h"
#include "GuiButton.h"
#include "GuiSprite.h"
#include "GuiString.h"
#include "LitShader.h"
#include "Model.h"
#include "PointLightShadowMap.h"
#include "Scene.h"
#include "SystemBase.h"
#include "ThirdPersonCamera.h"

using _3DM::AnimatedModel;
using _3DM::Model;

class RenderingSystem : public SystemBase {

public:
    void initialize(Scene& scene, Settings& settings, PhysicsWorld& world, SubSystems& systems) override;
    void render(PointLightShadowMap& pointLightDepthMap, DirectionalLightShadowMap& directionalLightDepthMap, Time& currentTime);

private:
    //This function searches for any particle systems that may exist.
    //As of 4/17/2016, there is only one particle system implemented, so it will only return either a nullptr,
    //or a fountain particle system pointer
    ParticleEmitter* getParticleEmitter(int32_t entity);

    void renderParticles(Particles& particles, Camera& currentCamera, Time& currentTime);

    void initializeLights(LitShader& litShader);
    void initializeModels(ShaderBase& shader, const int32_t& entity);

    //Prepares and retrieves the first shader found in scene that is associated with entity.
    //**Does use program.
    ShaderBase* prepareShader(const int32_t& entity, PointLightShadowMap& pointLightDepthMap, DirectionalLightShadowMap& directionalLightDepthMap, Camera& currentCamera, Time& currentTime);

    void supplyLitShaderUniforms(ShaderBase& shader, PointLightShadowMap& pointLightDepthMap, DirectionalLightShadowMap& directionalLightDepthMap, Camera& currentCamera, Time& currentTime);

    void supplyDefaultShaderUniforms(ShaderBase& shader, Camera& currentCamera, Time& currentTime);

    void supplyParticleShaderUniforms(ShaderBase& particleShader, Camera& currentCamera, Time& currentTime);
};
#endif
