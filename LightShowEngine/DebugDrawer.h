
#ifndef DEBUG_DRAWER_H
#define DEBUG_DRAWER_H

#include <Bullet/LinearMath/btIDebugDraw.h>
#include "ShaderBase.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "GameInfo.h"

class DebugDrawer : public btIDebugDraw
{
public:


	const unsigned int MAX_AMOUNT_DEBUG_LINES = 22500;

	void render(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

	void initialize();

	DebugDrawer(){}

	virtual void   drawLine(const btVector3& from, const btVector3& to, const btVector3&);

	virtual void   drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&){}

	virtual void   reportErrorWarning(const char* warningString);

	virtual void   draw3dText(const btVector3&, const char*){}

	virtual void   setDebugMode(int debugMode);

	virtual int    getDebugMode() const { return currentDebugMode; }
	
private:
	
	ShaderBase thisShader;


	std::vector<glm::vec3> lineVertices;

	int				currentDebugMode			= 0;
	unsigned int	currentMaxAmountOfVertices	= 0;
	unsigned int	currentAmountOfLines		= 0;

	GLuint VAO;
	GLuint vertID;

	GLint positionAttribute;
	GLint projectionLocation;
	GLint viewLocation;

};
#endif