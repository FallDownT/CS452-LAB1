///////////////////////////////////////////////////////////////////////
// Chris Schwarz
// 1/28/14
// Lab 1
///////////////////////////////////////////////////////////////////////

// -----------------------
// --- I N C L U D E S ---
// -----------------------
#include "initShaders.h"
#include "vec.h"

using namespace std;

int currentObject;

// Vertex IDs
GLuint vaoID, vboID;
// Vertices
GLfloat trianglevertexarray[]={
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
	-0.5f,-0.5f,0.0f
};
GLfloat squarevertexarray[]={
	-0.5f,0.5f,0.0f,
	-0.5f,-0.5f,0.0f,
	0.5f,0.5f,0.0f,
	0.5f,-0.5f,0.0f
};
GLfloat pentagonvertexarray[]={
	-0.2939f,-0.4045f,0.0f,
	-0.4755f,0.1545f,0.0f,
	0.0f,0.5f,0.0f,
	0.4755f,0.1545f,0.0f,
	0.2939f,-0.4045f,0.0f
};
// Indices of triangle
GLubyte indices[3]={0,1,2};

// -----------------------------------------
// --- O B J E C T   G E N E R A T I O N ---
// -----------------------------------------
void triangle(){
	glClear(GL_COLOR_BUFFER_BIT);	// Clears the screen
  
	glGenVertexArrays(1, &vaoID);	// Generates object name for Vertex Array Objects
	glBindVertexArray(vaoID);	// Bind the object to the array

	glGenBuffers(1, &vboID);	// Generates object name for the Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, vboID);	// Bind the object to the array
	glBufferData(GL_ARRAY_BUFFER, sizeof(trianglevertexarray), trianglevertexarray, GL_STATIC_DRAW);	// Allocates the memory of the vertices

	ShaderInfo shaders[]={	// Create the shader specified by my initshaders 
		{ GL_VERTEX_SHADER , "vertexshader.glsl"} ,
		{ GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
		{ GL_NONE , NULL} 
	};

	initShaders(shaders);	// Creates shaders
  
	glEnableVertexAttribArray(0);	// Enables the vertex attribute index 
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);	// Specified the start the vertice array used to the draw

	glDrawArrays(GL_TRIANGLES, 0, 3);	// Draws array
	glFlush();	// Makes sure the processes finish
}

void square(){
	glClear(GL_COLOR_BUFFER_BIT);	// Clears the screen
  
	glGenVertexArrays(1, &vaoID);	// Generates object name for Vertex Array Objects
	glBindVertexArray(vaoID);	// Bind the object to the array

	glGenBuffers(1, &vboID);	// Generates object name for the Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, vboID);	// Bind the object to the array
	glBufferData(GL_ARRAY_BUFFER, sizeof(squarevertexarray), squarevertexarray, GL_STATIC_DRAW);	// Allocates the memory of the vertices

	ShaderInfo shaders[]={	// Create the shader specified by my initshaders 
		{ GL_VERTEX_SHADER , "vertexshader.glsl"} ,
		{ GL_FRAGMENT_SHADER , "fragmentshader2.glsl"},
		{ GL_NONE , NULL} 
	};

	initShaders(shaders);	// Creates shaders
  
	glEnableVertexAttribArray(0);	// Enables the vertex attribute index 
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);	// Specified the start the vertice array used to the draw

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	// Draws array
	glFlush();	// Makes sure the processes finish
}

void pentagon(){
	glClear(GL_COLOR_BUFFER_BIT);	// Clears the screen
  
	glGenVertexArrays(1, &vaoID);	// Generates object name for Vertex Array Objects
	glBindVertexArray(vaoID);	// Bind the object to the array

	glGenBuffers(1, &vboID);	// Generates object name for the Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, vboID);	// Bind the object to the array
	glBufferData(GL_ARRAY_BUFFER, sizeof(pentagonvertexarray), pentagonvertexarray, GL_STATIC_DRAW);	// Allocates the memory of the vertices

	ShaderInfo shaders[]={	// Create the shader specified by my initshaders 
		{ GL_VERTEX_SHADER , "vertexshader.glsl"} ,
		{ GL_FRAGMENT_SHADER , "fragmentshader3.glsl"},
		{ GL_NONE , NULL} 
	};

	initShaders(shaders);	// Creates shaders
  
	glEnableVertexAttribArray(0);	// Enables the vertex attribute index 
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);	// Specified the start the vertice array used to the draw

	glDrawArrays(GL_TRIANGLE_FAN, 0, 5);	// Draws array
	glFlush();	// Makes sure the processes finish
}

// -----------------------------------
// --- D R A W   F U N C T I O N S ---
// -----------------------------------
void drawscene(){
	// Display corresponding object
	switch(currentObject){
		case 0:
			glutDisplayFunc(triangle);
			glutPostRedisplay();	// Redraw the display
			break;
		case 1:
			glutDisplayFunc(square);
			glutPostRedisplay();	// Redraw the display
			break;
		case 2:
			glutDisplayFunc(pentagon);
			glutPostRedisplay();	// Redraw the display
			break;
	}
}

void idle(void){
  glutPostRedisplay();
}

// -------------------------------
// --- M O U S E   E V E N T S ---
// -------------------------------
void mousepress(int button, int state, int x, int y){
	// Right click closes the screen
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		exit(0);
	}
	// Left click changes the object displayed
	else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		currentObject = (currentObject+1) % 3;
		drawscene();
	}
}

// -----------------------------
// --- M A I N   M E T H O D ---
// -----------------------------
int main(int argc, char **argv){
	// Initialize to display first object
	currentObject = 0;
	
	// Freeglut window and context management	
	glutInit(&argc, argv);
	glutCreateWindow("Chris Schwarz - Lab 1");	// Creates the window with the specified name
  
	// Initializes glew
	glewExperimental = GL_TRUE;
	if(glewInit()){
		fprintf(stderr, "Unable to initalize GLEW");
		exit(EXIT_FAILURE);
	}

	glutDisplayFunc(drawscene);	// Displays callback draws the shapes
	glutMouseFunc(mousepress);		// Control callback specifies the mouse controls
	glutMainLoop();					// Sets opengl state in a neverending loop
	return 0;
}

