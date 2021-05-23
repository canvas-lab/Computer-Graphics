/**
 * This code is created based on learnopengl.com by Joey de Vries 
 **/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>

#include <iostream>
#include <string>

#define PI 3.14159265

// Box coordinate with 36 vertices.
// Every 3 coordinates will form 1 triangle.
// The last 2 columns represent texture coordinate for mapping.
float box[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_input(GLFWwindow *window);
unsigned int loadTexture(const char *path);


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
glm::vec3 camera_pos   = glm::vec3(0.0f, 0.9f,  3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;




// timing
float delta_time = 0.0f;	// time between current frame and last frame
float last_frame = 0.0f;

//Toggle Logo and Button (Animation or states)
bool BUTTON_PRESSED = false;
int BUTTON_DELAY = 0;
bool BUTTON_CLOSE_ENOUGH = false;

bool SHOW_COORDINATE = false;
int SHOW_DELAY = 0;

//Animation Variables
float curtin_rotate_y = 0.0;
float curtin_translate_y = 0.0;

//sheep Animate
float sheep_translate_y = 0.0;
float sheep_rotate_y = 0.0;

//Sven
bool SVEN_PRESSED = false;
int SVEN_DELAY = 0;
bool SVEN_CLOSE_ENOUGH = false;

bool SHOW_SVEN_COORDINATE = false;
int SHOW_SVEN_DELAY = 0;

//Toggle TORCH (Animation or states)
bool TORCH_PRESSED = false;
int TORCH_DELAY = 0;
bool TORCH_CLOSE_ENOUGH = false;

bool SHOW_TORCH_COORDINATE = false;
int SHOW_TORCH_DELAY = 0;


//Toggle INCREASE light RADIUS (Animation or states)
bool INC_RADIUS_PRESSED = false;
int INC_RADIUS_DELAY = 0;

bool SHOW_INC_RADIUS_COORDINATE = false;
int SHOW_INC_RADIUS_DELAY = 0;


//Toggle DECREASE light RADIUS (Animation or states)
bool DECR_RADIUS_PRESSED = false;
int DECR_RADIUS_DELAY = 0;

bool SHOW_DECR_RADIUS_COORDINATE = false;
int SHOW_DECR_RADIUS_DELAY = 0;

//Toggle SCENE RADIUS (Animation or states)
bool SCENE_PRESSED = false;
int SCENE_DELAY = 0;

bool SHOW_SCENE_COORDINATE = false;
int SHOW_SCENE_DELAY = 0;




// Countdown until the button trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_delay()
{
	if(BUTTON_DELAY > 0) BUTTON_DELAY -= 1;
	if(SHOW_DELAY > 0) SHOW_DELAY -= 1;
}

// Toggle button pressing only if the camera is close enough.
void toggle_button_distance(glm::vec3 button_pos)
{
	if(glm::length(camera_pos - button_pos) <= 1.6f)
		BUTTON_CLOSE_ENOUGH = true;
	else
		BUTTON_CLOSE_ENOUGH = false;
}


// Toggle TORCH pressing only if the camera is close enough.
void toggle_torch_distance(glm::vec3 torch_pos)
{
	if(glm::length(camera_pos - torch_pos) <= 1.6f)
		TORCH_CLOSE_ENOUGH = true;
	else
		TORCH_CLOSE_ENOUGH = false;
}

// Countdown until the torch trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_torch_delay()
{
	if(TORCH_DELAY > 0) TORCH_DELAY -= 1;
	if(SHOW_TORCH_DELAY > 0) SHOW_TORCH_DELAY -= 1;
}


// Countdown until the INC RADIUS trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_inc_radius_delay()
{
	if(INC_RADIUS_DELAY > 0) INC_RADIUS_DELAY -= 1;
	if(SHOW_INC_RADIUS_DELAY > 0) SHOW_INC_RADIUS_DELAY -= 1;
}

// Countdown until the DECR RADIUS trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_decr_radius_delay()
{
	if(DECR_RADIUS_DELAY > 0) DECR_RADIUS_DELAY -= 1;
	if(SHOW_DECR_RADIUS_DELAY > 0) SHOW_DECR_RADIUS_DELAY -= 1;
}

// Countdown until the scene trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_scene_delay()
{
	if(SCENE_DELAY > 0) SCENE_DELAY -= 1;
	if(SHOW_SCENE_DELAY > 0) SHOW_SCENE_DELAY -= 1;
}


// Countdown until the Sven trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_sven_delay()
{
	if(SCENE_DELAY > 0) SCENE_DELAY -= 1;
	if(SHOW_SCENE_DELAY > 0) SHOW_SCENE_DELAY -= 1;
}

// Toggle button pressing only if the camera is close enough.
void toggle_sven_distance(glm::vec3 sven_pos)
{
	if(glm::length(camera_pos - sven_pos) <= 1.6f)
		SVEN_CLOSE_ENOUGH = true;
	else
		SVEN_CLOSE_ENOUGH = false;
}





int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement for OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Tutorial", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShader("sample1.vs", "sample1.fs");
    Shader lampShader("lamp.vs", "lamp.fs");


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	unsigned int VBO_box, VAO_box;

	glGenVertexArrays(1, &VAO_box);
	glGenBuffers(1, &VBO_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);

	glBindVertexArray(VAO_box);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);



	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


	// load and create a texture 
	// -------------------------
	unsigned int tex_street = loadTexture(FileSystem::getPath("resources/textures/street.png").c_str());   
	unsigned int tex_sven = loadTexture(FileSystem::getPath("resources/textures/sven.jpg").c_str());
    unsigned int tex_grass = loadTexture(FileSystem::getPath("resources/textures/grass.jpg").c_str());   
	unsigned int tex_marble = loadTexture(FileSystem::getPath("resources/textures/marble.jpg").c_str());
    unsigned int tex_curtin = loadTexture(FileSystem::getPath("resources/textures/curtin.jpg").c_str());   
	unsigned int tex_sky = loadTexture(FileSystem::getPath("resources/textures/night_sky.jpg").c_str());
    unsigned int tex_grass_specular = loadTexture(FileSystem::getPath("resources/textures/grass_specular.jpg").c_str());   
	unsigned int tex_wood = loadTexture(FileSystem::getPath("resources/textures/wood.jpg").c_str());
	unsigned int tex_toy_box_diffuse = loadTexture(FileSystem::getPath("resources/textures/toy_box_diffuse.png").c_str());
    unsigned int tex_red_dark = loadTexture(FileSystem::getPath("resources/textures/red_dark.jpg").c_str());   
	unsigned int tex_red_bright = loadTexture(FileSystem::getPath("resources/textures/red_bright.jpg").c_str());
    unsigned int tex_red = loadTexture(FileSystem::getPath("resources/textures/red.jpg").c_str());   
	unsigned int tex_green = loadTexture(FileSystem::getPath("resources/textures/green.jpg").c_str());
	unsigned int tex_blue = loadTexture(FileSystem::getPath("resources/textures/blue.jpg").c_str());
   
    unsigned int tex_flower_petal = loadTexture(FileSystem::getPath("resources/textures/flower_petal.jpg").c_str());   
	unsigned int tex_flower_stem = loadTexture(FileSystem::getPath("resources/textures/flower_stem.jpg").c_str());
    unsigned int tex_tree_leaves = loadTexture(FileSystem::getPath("resources/textures/tree_leaves.jpg").c_str());   
	unsigned int tex_tree_trunk = loadTexture(FileSystem::getPath("resources/textures/tree_trunk.jpg").c_str());
	unsigned int tex_chair = loadTexture(FileSystem::getPath("resources/textures/chair.jpg").c_str());
    unsigned int tex_table_top = loadTexture(FileSystem::getPath("resources/textures/table_top.jpg").c_str());   
	unsigned int tex_water_sheep = loadTexture(FileSystem::getPath("resources/textures/water_sheep.jpg").c_str());
	unsigned int tex_water_sheep_face = loadTexture(FileSystem::getPath("resources/textures/awesomeface.jpg").c_str());



	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
    // shader configuration
    // --------------------
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		//update delay countdown
		update_delay();
		update_torch_delay();
		update_inc_radius_delay();
		update_decr_radius_delay();
		update_scene_delay();
		update_sven_delay();


		// input
		// -----
		process_input(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


		// activate shader
		// be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("light.position", camera_pos);
        lightingShader.setVec3("light.direction", camera_front);
        lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(0.0f)));
        lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(0.0f)));
        lightingShader.setVec3("viewPos", camera_pos);
        // light properties
        lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);


//scene dark/bright
	if (SCENE_PRESSED == true)
	{
        lightingShader.setVec3("light.ambient", 1.5f, 1.5f, 1.5f);
		lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(0.0f)));
    	lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(0.0f)));
	}

	//torch pressed
	if (TORCH_PRESSED == true)
	{
        lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		
			//light decrease radius
			if (DECR_RADIUS_PRESSED == true)
			{
				lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(7.5f)));
				lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(12.5f)));
			}
			//light increase radius
			if (INC_RADIUS_PRESSED == true)
			{
				lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(22.5f)));
				lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(27.5f)));
			}
		
	}


        // we configure the diffuse intensity slightly higher; the right lighting conditions differ with each lighting method and environment.
        // each environment and lighting type requires some tweaking to get the best out of your environment.
        lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("light.constant", 1.0f);
        lightingShader.setFloat("light.linear", 0.09f);
        lightingShader.setFloat("light.quadratic", 0.032f);

        // material properties
        lightingShader.setFloat("material.shininess", 32.0f);




		// camera/view transformation
		glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
		lightingShader.setMat4("view", view);

 // view/projection transformations
 // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------------------------------------------------------------------------------------------------------
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
        lightingShader.setMat4("projection", projection);


		//declare transformation matrix
		glm::mat4 model = glm::mat4();
        lightingShader.setMat4("model", model);
		/*
		//example (remember, it is in column matrix position, so the order is reversed.)
		model = glm::translate(model, glm::vec3(1.0f, 2.0f, 3.0f)); 			// translate by (1.0, 2.0, 3.0)
		model = glm::scale(model, glm::vec3(2.0f, 5.0f, 3.0f)); 			// scale by (2.0, 5.0, 3.0) on X, Y, and Z respectively.
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));	// rotate 45 degree about Y-axis (0,1,0)
		*/


		//Draw objects
		//------------------------------------------------------------------------------------------
		
		//Sky
		glBindVertexArray(VAO_box);//This does not have to binded every time after first call, but just for consistency.

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_sky);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(200.0f, 200.0f, 200.0f));

		lightingShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Coordinate System
		if(SHOW_COORDINATE == true)
		{
			
			glm::vec3 coord_scales[] = {
				glm::vec3( 100.0f,  0.02f,  0.02f),	//X
				glm::vec3( 0.02f,  100.0f,  0.02f),	//Y
				glm::vec3( 0.02f,  0.02f,  100.0f),	//Z
			};

			glBindVertexArray(VAO_box);

			glActiveTexture(GL_TEXTURE0);

			for(int tab = 0; tab < 3; tab++)
			{	
				if(tab == 0) glBindTexture(GL_TEXTURE_2D, tex_red); 	//X
				if(tab == 1) glBindTexture(GL_TEXTURE_2D, tex_green);	//Y
				if(tab == 2) glBindTexture(GL_TEXTURE_2D, tex_blue);	//Z

				model = glm::mat4();
				model = glm::scale(model, coord_scales[tab]);

				lightingShader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}


		//Street
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_street);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(3.0f, 0.0f, 7.0f));

		lightingShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//Grass
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_grass);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 0.0f, 7.0f));

		lightingShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);





//Sven (4 tall boxes for legs & 1 thick long box as body and a long thin box tail, 2 small boxes as ears and a nose)
		glm::vec3 sven_scales[] = {
			glm::vec3( 0.5f,  0.25f,  0.4f),	//top
			glm::vec3( -0.1f,  0.3f,  -0.1f),//near left
			glm::vec3( -0.1f,  0.3f,  -0.1f),	//near right
			glm::vec3( -0.1f,  0.3f,  -0.1f),//far left
			glm::vec3( -0.1f,  0.3f,  -0.1f),	//far right
			glm::vec3( 0.25f,  0.25f,  -0.4f),	//head
			glm::vec3( 0.40f,  -0.10f,  -0.1f),	//tail
			glm::vec3( 0.1f,  -0.10f,  -0.1f),	//ear far
			glm::vec3( 0.1f,  -0.10f,  -0.1f),	//ear near
			glm::vec3( 0.1f,  -0.10f,  -0.15f),	//nose
		};
		

		glm::vec3 sven_positions[] = {
			glm::vec3( 0.0f,  0.25f, 0.0f),		//top
			glm::vec3(-0.20f, 0.0f,  0.15f),	//near left
			glm::vec3( 0.20f, 0.0f,  0.15f),	//near right
			glm::vec3(-0.20f, 0.0f, -0.15f),	//far left
			glm::vec3( 0.20f, 0.0f, -0.15f),	//far right
			glm::vec3( -0.35f, 0.40f, 0.0f),	//head
			glm::vec3( 0.30f, 0.5f,  0.0f),	//tail
			glm::vec3( -0.43f, 0.75f,  -0.15f),	//ear far
			glm::vec3( -0.43f, 0.75f,  0.15f),	//ear near
			glm::vec3( -0.52f, 0.49f,  0.0f),	//nose
		};

		//sven picked up by pressing "E"
			if (SVEN_PRESSED == true)
			{
				//.............
			}

		glm::vec3 sven_final_location = glm::vec3(0.0f, 0.56f, 0.25f);
		toggle_sven_distance(sven_final_location); 

		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_sven);

		
		for(int tab = 0; tab < 11; tab++)
		{	
			model = glm::mat4();
			model = glm::translate(model, sven_positions[tab]);
			model = glm::scale(model, sven_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
			
			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		


		

		//Water sheep (4 tall boxes for legs & 1 thick long box as body thin box and a face)
		glm::vec3 sheep_scales[] = {
			glm::vec3( 0.0f,  0.25f,  -0.4f),	//face
			glm::vec3( 0.25f,  0.25f,  -0.4f),	//head
			glm::vec3( 0.5f,  0.25f,  0.4f),	//top
			glm::vec3( -0.1f,  0.3f,  -0.1f),//near left
			glm::vec3( -0.1f,  0.3f,  -0.1f),	//near right
			glm::vec3( -0.1f,  0.3f,  -0.1f),//far left
			glm::vec3( -0.1f,  0.3f,  -0.1f),	//far right


		};
		glm::vec3 sheep_positions[] = {
			glm::vec3( -2.88f, 0.40f, -2.0f),	//face
			glm::vec3( -2.75f, 0.40f, -2.0f),	//head
			glm::vec3( -2.40f,  0.25f,  -2.0f),		//top
			glm::vec3(-2.60f, 0.0f,  -1.85f),	//near left
			glm::vec3( -2.20f, 0.0f,  -1.85f),	//near right
			glm::vec3(-2.60f, 0.0f, -2.15f),	//far left
			glm::vec3( -2.20f, 0.0f, -2.15f),	//far right
		};

		glBindVertexArray(VAO_box);

		for(int tab = 0; tab < 8; tab++)
		{	
			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_water_sheep_face);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, tex_water_sheep);
			}

			model = glm::mat4();
			model = glm::translate(model, sheep_positions[tab]);
			model = glm::scale(model, sheep_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			//sven picked up by pressing "E"
			if (SVEN_PRESSED == true)
			{
			sheep_translate_y += 0.1f;
			sheep_rotate_y += 0.3f;
			
			
			model = glm::mat4();
			model = glm::translate(model, glm::vec3(0.0f, 0.8f + (0.4f * sin(sheep_translate_y * PI / 180.f)), -3.2f));
			model = glm::rotate(model, glm::radians(sheep_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));

		
			}

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}





		//Left Tree
		glm::vec3 leftTree_scales[] = {
			glm::vec3( -0.1f,  1.7f,  0.1f),	//trunk
			glm::vec3( 0.55f,  0.6f,  -0.4f),	//top leaves
			glm::vec3( 0.55f,  0.6f,  -0.4f),	//left leaves
			glm::vec3( 0.55,  0.6f,  -0.4f),	//right leaves
		};
		glm::vec3 leftTree_positions[] = {
			glm::vec3( -2.0f, 0.0f, -1.20f),	//trunk
			glm::vec3( -2.0f, 1.75f, -1.20f),	//top leaves
			glm::vec3( -2.25f,  1.2f,  -1.20f),	//left leaves
			glm::vec3( -1.75f, 1.2f,  -1.20f),	//right leaves
		};

		glBindVertexArray(VAO_box);


		for(int tab = 0; tab < 4; tab++)
		{	
			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_tree_trunk);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, tex_tree_leaves);
			}

		
			model = glm::mat4();
			model = glm::translate(model, leftTree_positions[tab]);
			model = glm::scale(model, leftTree_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		//Right Tree
		glm::vec3 rightTree_scales[] = {
			glm::vec3( -0.1f,  1.7f,  0.1f),	//trunk
			glm::vec3( 0.55f,  0.6f,  -0.4f),	//top leaves
			glm::vec3( 0.55f,  0.6f,  -0.4f),	//left leaves
			glm::vec3( 0.55,  0.6f,  -0.4f),	//right leaves
		};
		glm::vec3 rightTree_positions[] = {
			glm::vec3( 2.0f, 0.0f, -1.20f),	//trunk
			glm::vec3( 2.0f, 1.75f, -1.20f),	//top leaves
			glm::vec3( 2.25f,  1.2f,  -1.20f),	//left leaves
			glm::vec3( 1.75f, 1.2f,  -1.20f),	//right leaves
		};

		glBindVertexArray(VAO_box);

		for(int tab = 0; tab < 4; tab++)
		{	
			
			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_tree_trunk);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, tex_tree_leaves);
			}

			model = glm::mat4();
			model = glm::translate(model, rightTree_positions[tab]);
			model = glm::scale(model, rightTree_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}




//Table top w/ chairs (1 tall boxe for legs & 1 thin long box as table top)
		glm::vec3 tableTop_scales[] = {
			glm::vec3( 0.35f,  0.10f,  -0.8f),	//table top
			glm::vec3( -0.1f,  0.50f,  0.1f),	//table leg

		};
		glm::vec3 tableTop_positions[] = {
			glm::vec3( 2.8f,  0.50f,  1.0f),	//table top
			glm::vec3( 2.8f, 0.0f, 1.0f),	//table leg
		};

		glBindVertexArray(VAO_box);

		for(int tab = 0; tab < 3; tab++)
		{	

			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_table_top);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}


			model = glm::mat4();
			model = glm::translate(model, tableTop_positions[tab]);
			model = glm::scale(model, tableTop_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}





		//Right Chair
		glm::vec3 rightChair_scales[] = {
			glm::vec3( 0.35f,  0.10f,  -0.8f),	//Chair top
			glm::vec3( -0.1f,  0.30f,  0.08f),	//Chair leg near
			glm::vec3( -0.1f,  0.30f,  0.08f),	//Chair leg far

		};
		glm::vec3 rightChair_positions[] = {
			glm::vec3( 3.2f,  0.25f,  1.0f),	//Chair top
			glm::vec3( 3.2f, 0.0f, 1.40f),	//Chair leg near
			glm::vec3( 3.2f, 0.0f, 0.6f),	//Chair leg far
		};

		glBindVertexArray(VAO_box);

		for(int tab = 0; tab < 3; tab++)
		{	

			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_chair);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}

			model = glm::mat4();
			model = glm::translate(model, rightChair_positions[tab]);
			model = glm::scale(model, rightChair_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//Left Chair
		glm::vec3 leftChair_scales[] = {
			glm::vec3( 0.35f,  0.10f,  -0.8f),	//Chair top
			glm::vec3( -0.1f,  0.30f,  0.08f),	//Chair leg near
			glm::vec3( -0.1f,  0.30f,  0.08f),	//Chair leg far

		};
		glm::vec3 leftChair_positions[] = {
			glm::vec3( 2.44f,  0.25f,  1.0f),	//Chair top
			glm::vec3( 2.44f, 0.0f, 1.40f),	//Chair leg near
			glm::vec3( 2.44f, 0.0f, 0.6f),	//Chair leg far
		};

		glBindVertexArray(VAO_box);

		for(int tab = 0; tab < 3; tab++)
		{	

			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_chair);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}


			model = glm::mat4();
			model = glm::translate(model, leftChair_positions[tab]);
			model = glm::scale(model, leftChair_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}





		//Flower
		glm::vec3 flower_scales[] = {
			glm::vec3( -0.05f,  0.20f,  -0.1f),	//stem
			glm::vec3( 0.1f,  -0.10f,  -0.1f),	//top petal
			glm::vec3( 0.1f,  -0.10f,  -0.1f),	//right petal
			glm::vec3( 0.1f,  -0.10f,  -0.1f),	//left petal


		};
		glm::vec3 flower_positions[] = {
			glm::vec3( -2.48, 0.0f,  0.15f),	//stem
			glm::vec3( -2.48f, 0.40f,  0.15f),	//top petal
			glm::vec3( -2.43f, 0.30f,  0.15f),	//right petal
			glm::vec3( -2.53f, 0.30f,  0.15f),	//left petal
		};

		glBindVertexArray(VAO_box);

		for(int tab = 0; tab < 4; tab++)
		{	
			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_flower_stem);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, tex_flower_petal);
			}

			model = glm::mat4();
			model = glm::translate(model, flower_positions[tab]);
			model = glm::scale(model, flower_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}




		//Table (4 tall boxes for legs & 1 thin box as table top)
		glm::vec3 table_scales[] = {
			glm::vec3( 1.0f,  0.1f,  1.0f),	//top
			glm::vec3( 0.1f,  0.5f,  0.1f),//near left
			glm::vec3( 0.1f,  0.5f,  0.1f),	//near right
			glm::vec3( 0.1f,  0.5f,  0.1f),//far left
			glm::vec3( 0.1f,  0.5f,  0.1f),	//far right
		};
		glm::vec3 table_positions[] = {
			glm::vec3( 0.0f,  0.5f,  -2.0f),		//top
			glm::vec3(-0.45f, 0.0f,  -1.55f),	//near left
			glm::vec3( 0.45f, 0.0f,  -1.55f),	//near right
			glm::vec3(-0.45f, 0.0f, -2.45f),	//far left
			glm::vec3( 0.45f, 0.0f, -2.45f),	//far right
		};

		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_wood);

		for(int tab = 0; tab < 5; tab++)
		{	
			model = glm::mat4();
			model = glm::translate(model, table_positions[tab]);
			model = glm::scale(model, table_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		//Button on table (1 big box & 1 small box as button)
		glm::vec3 button_scales[] = {
			glm::vec3( 0.2f,  0.12f,  0.2f),		//case
			glm::vec3( 0.12f,  0.12f,  0.12f),		//button
		};

		float red_button_height = 0.05f;
		if(BUTTON_PRESSED == true) 
		{
			red_button_height -= 0.02f;
		}

		glm::vec3 button_positions[] = {
			glm::vec3( 0.0f,  0.0f,  -2.3f),			//case
			glm::vec3( 0.0f,  red_button_height,  -2.3f),	//button
		};

		glm::vec3 button_final_location = glm::vec3(0.0f, 0.56f, 0.25f);
		toggle_button_distance(button_final_location); 

		glBindVertexArray(VAO_box);
		
		for(int tab = 0; tab < 2; tab++)
		{	
			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_marble);
			}
			else
			{
				if(BUTTON_PRESSED == false)
				{
					glBindTexture(GL_TEXTURE_2D, tex_red_dark); 	// Not pressed
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, tex_red_bright);	// Pressed
				}
			}

			model = glm::mat4();
			model = glm::translate(model, button_final_location);
			model = glm::translate(model, button_positions[tab]);
			model = glm::scale(model, button_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}



		//logo
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_curtin);

		//transformation for animation
		if(BUTTON_PRESSED == true)
		{
			curtin_translate_y += 0.3f;
			curtin_rotate_y += 0.3f;
			if(abs(curtin_translate_y - 360.0f) <= 0.1f) curtin_translate_y = 0.0f;
			if(abs(curtin_rotate_y - 360.0f) <= 0.1f) curtin_rotate_y = 0.0f;
		}

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 0.8f + (0.4f * sin(curtin_translate_y * PI / 180.f)), -3.2f));
		model = glm::rotate(model, glm::radians(curtin_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.0f));

		lightingShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);




		
		//Torch 
		glm::vec3 torch_scales[] = 
		{
			glm::vec3( 0.05f,  0.04f,  0.2f),		//torch
			glm::vec3( 0.02f,  0.01f,  -0.1f),		//button
		};

		float torch_move = 1.0;
		float torch_height = -0.5;

		float button_height = -0.46;
		if(TORCH_PRESSED == true)
		{
			torch_move += 0.05;
			torch_height += 0.1;

			button_height += 0.1;
		}

		glm::vec3 torch_positions[] = 
		{
			glm::vec3( 1.0f,  torch_height,  1.0f),			//torch
			glm::vec3( 1.0f,  button_height,  torch_move),	//button
		};

		glm::vec3 torch_final_location = glm::vec3(0.0f, 0.56f, 0.25f);
		toggle_torch_distance(torch_final_location); 

		
		glBindVertexArray(VAO_box);
		
		for(int tab = 0; tab < 2; tab++)
		{	
			glActiveTexture(GL_TEXTURE0);
			if(tab == 0)
			{	
				glBindTexture(GL_TEXTURE_2D, tex_toy_box_diffuse);
			}
			else
			{
				if(TORCH_PRESSED == false)
				{
					glBindTexture(GL_TEXTURE_2D, tex_red_dark); 	// Not pressed
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, tex_red_bright);	// Pressed
				}
			}

			model = glm::mat4();
			model = glm::translate(model, torch_final_location);
			model = glm::translate(model, torch_positions[tab]);
			model = glm::scale(model, torch_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));


			lightingShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		

   
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();



	}

	   
	

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_box);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO_box);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{
    	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);

	float cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		cameraSpeed = 2.5 * delta_time; 
	else
		cameraSpeed = 2.5 * delta_time * 2;	// double speed with "Shift" pressed


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_pos += cameraSpeed * camera_front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_pos -= cameraSpeed * camera_front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;

	//move away
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera_pos += (glm::normalize(camera_pos + camera_up)) * cameraSpeed;
		//if(abs(camera_pos - 360.0f) <= 0.1f) camera_pos= 0.0f;	
	}
		 

	//toggle red button
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && BUTTON_DELAY == 0 && BUTTON_CLOSE_ENOUGH == true)
	{
		BUTTON_DELAY = 10;
		if(BUTTON_PRESSED == false) 		
			BUTTON_PRESSED = true;
		else
			BUTTON_PRESSED = false;
	}

	//toggle SVEN
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && SVEN_DELAY == 0 && SVEN_CLOSE_ENOUGH == true)
	{
		SVEN_DELAY = 10;
		if(SVEN_PRESSED == false) 		
			SVEN_PRESSED = true;
		else
			SVEN_PRESSED = false;
	}

	//toggle coordinate visibility
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && SHOW_DELAY == 0)
	{
		SHOW_DELAY = 10;
		if(SHOW_COORDINATE == false) 		
			SHOW_COORDINATE = true;
		else
			SHOW_COORDINATE = false;
	}



//light INCincrease radius
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		{
			INC_RADIUS_DELAY = 10;
			if(INC_RADIUS_PRESSED == false) 		
				INC_RADIUS_PRESSED = true;
			else
				INC_RADIUS_PRESSED = false;		
		}
		
//light DECdecrease radius
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
			DECR_RADIUS_DELAY = 10;
			if(DECR_RADIUS_PRESSED == false) 		
				DECR_RADIUS_PRESSED = true;
			else
				DECR_RADIUS_PRESSED = false;	
	}


	//toggle TORCH
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && TORCH_DELAY == 0 && TORCH_CLOSE_ENOUGH == true)
	{
		TORCH_DELAY = 10;
		if(TORCH_PRESSED == false) 		
			TORCH_PRESSED = true;
		else
			TORCH_PRESSED = false;
	}


			
//scene light/dark
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
			SCENE_DELAY = 10;
			if(SCENE_PRESSED == false) 		
				SCENE_PRESSED = true;
			else
				SCENE_PRESSED = false;	
	}

}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}



//registering a new texture. You can modify this function to allow for more configuration options.
void register_texture(unsigned int * tex, std::string path)
{
	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, *tex);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor [] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(FileSystem::getPath(path).c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
