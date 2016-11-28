#ifndef PLAYER_CONTROLLER_SYSTEM
#define PLAYER_CONTROLLER_SYSTEM

#include "CollisionMesh.h"
#include "Component.h"
#include "RayCaster.h"
#include "PlayerController.h"
#include "PhysicsWorld.h"
#include "ThirdPersonCamera.h"
#include "UserControls.h"
#include "ControllerRayCollision.h"


namespace PLR_CTRLR_NS
{
	const unsigned int	AMOUNT_OF_RAYS = 4;
	const float			CLAMPING_VELOCITY = -5;
	const float			RAY_DISTANCE_CORRECTOR = -0.1f;
}


class PlayerControllerSystem
{

public:

	PlayerControllerSystem() 
	{
		assert(PLR_CTRLR_NS::AMOUNT_OF_RAYS == 4);
	}

	void update(Input& input, Transform& modelsTransform, CollisionMesh& mesh, PhysicsWorld& world, PlayerController& playerController, Camera& camera, const UserControls& userControls);
	

private:
	
	RayCaster rayCast[PLR_CTRLR_NS::AMOUNT_OF_RAYS];

	void performJump		(CollisionMesh & collisionMesh, float jumpVelocity);

	void getPlayerInput		(Input& input, CollisionMesh& collisionMesh, PlayerController& playerController, Camera& camera, const UserControls& userControls);

	void handleRayHit		(PlayerController & playerController, CollisionMesh & collisionMesh, float closest);

	int getLowestRayHitIndex(const RayCaster & rayResults, PlayerController& playerController);

	ControllerRayCollision getLowestRayHitForAllRays(PlayerController & playerController);

	void executeRayTesting(PlayerController & playerController, CollisionMesh & collisionMesh, const Transform & meshTransform, PhysicsWorld & world);

	glm::vec3 getSlopeSpeed	(float sensitivity, const glm::vec3& rayNormal) { return rayNormal * sensitivity * GameInfo::deltaTime; }

	int getCurrentSlopeSpeedIndex(const glm::vec3& rayNormal, const PlayerController& playerController);
	
	void performCommands(CollisionMesh & collisionMesh, PlayerController & playerController);

	void applyForces(CollisionMesh & collisionMesh, PlayerController & playerController);

	void applyNewTransform(CollisionMesh & mesh, const glm::vec3& cameraForward, const PlayerController & playerController, Transform& oldTransform);


};

#endif