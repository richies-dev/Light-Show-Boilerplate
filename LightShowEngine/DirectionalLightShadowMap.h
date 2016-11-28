#ifndef DIRECTIONAL_LIGHT_SHADOW_MAP_H
#define DIRECTIONAL_LIGHT_SHADOW_MAP_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "HelpingHand.h"
#include "ShaderBase.h"

class DirectionalLightShadowMap
{

public:

	const glm::mat4 * const getLightSpaceMatrix()	{ return &lightSpaceMatrix; }
	GLint getDepthMapShader	()	{ return depthMapShader.getProgramID(); }
	GLint getDepthMap		()	{ return depthMap; }
	GLuint getFBO			()	{ return depthMapFBO; }

	unsigned int getDepthMapWidth	() const { return DEPTH_MAP_WIDTH; }
	unsigned int getDepthMapHeight	() const { return DEPTH_MAP_HEIGHT; }
	void setDepthMapResolution(const unsigned int & width, const unsigned int & height)
	{
		DEPTH_MAP_WIDTH = width;
		DEPTH_MAP_HEIGHT = height;
		updateDepthMapResolution();
	}


	void setShadowActive(bool t)	{ lightSupplied = t; }
	bool isActive		()			{ return lightSupplied; }

	glm::vec3 getCurrentLightDirection() { return lightDirection; }
	void setCurrentLightDirection(const glm::vec3& lightDir) 
	{ lightDirection = glm::vec3(lightDir.x + securityAdditiveForDirection, lightDir.y + securityAdditiveForDirection, lightDir.z ); }



	void updateDepthMap(const glm::vec3& camerPosition);
	void initialize();


private:

	//4096 is amazing quality.
	unsigned int DEPTH_MAP_WIDTH	= 2048;
	unsigned int DEPTH_MAP_HEIGHT	= 2048;


	//This floating point value will be added to two of the light direction vector's axes. 
	//If 2/3 of the direction vector's axes is equal to 0, the shadows will not work.
	const float securityAdditiveForDirection = .0001f;

	struct OrthographicBounds
	{
		float left;
		float right;
		float bottom;
		float top;
		float zNear;
		float zFar;
	};

	void updateDepthMapResolution();

	OrthographicBounds bounds{ -25, 25, -25, 25, -50, 50};

	glm::vec3 lightDirection = glm::vec3(0.0001f, -1.f, 0);
	
	bool lightSupplied = false;

	glm::mat4	lightSpaceMatrix;
	GLuint		depthMapFBO;
	ShaderBase	depthMapShader;
	GLuint		depthMap;



};

#endif
