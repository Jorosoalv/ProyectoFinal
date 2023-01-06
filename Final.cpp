/*---------------------------------------------------------*/
/* ----------------  Proyecto Final -----------*/
/*Integrantes: -Gonzalez Castro Juan Fernando
				-Lopez Cruz Luis Enrique
				-Osorio Alvarado Jorge Adalberto*/
				/*-----------------    2023-1   ---------------------------*/


#include <glad/glad.h>//es la biblioteca que carga los modelos 
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture


#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor* monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(35.0f, 15.0f, -80.0f));
float MovementSpeed = 10.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 0.0f, 0.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);  //coomo es que se dirije la luz al esenario 

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = -140.0f,
movAuto_z = -130.0f,
movAuto_y = -2.5f,
rotCarro = 0.0f,
movimiento = 0.0f,
rotacion = 0.0f,
llanta = 0.0f,
orienta = 0.0f,
movTortuga_x = 0.0f,
movTortuga_y = 0.0f,
orientacionTortuga = -90.0f,
orientacionTortuga2 = 0.0f,
movTortuga_z = 0.0f,
movHuevo = 0.0f,
movHuevo2 = 0.0f,
movPinguino_z = 0.0f,
movPinguino_y = 0.0f,
movPinguino_x = 0.0f,
rotacionPinguino = 0.0f,
movPataIzquierda = 0.0f,
movPataDerecha = 0.0f,
AletaTibuDer = 0.0f,
AletaSup = 0.0f,
ColaTiburon1 = 0.0f,
ParteTraseraTibu = 0.0f,
CuerpoTiburonX = 0.0f,
CuerpoTiburonY = 0.0f,
CuerpoTiburonZ = 0.0f,
GiroTiburon = 0.0f,
GiroTiburon2 = 0.0f,
pataDerechaX = 0.0f,
pataIzquierdaX = 0.0f,
tortuga_x = 0.0f,
tortuga_y = 0.0f,
tortuga_z = 0.0f,
movPez1_x = 0.0f,
movPez2_x = 0.0f,
movPez3_x = 0.0f,
rotacionPez1 = 0.0f,
rotacionPez2 = 0.0f,
rotacionPez4 = 0.0f,
rotacionPez5 = 0.0f,
rotacionPez6 = 0.0f,
rotacionPez7 = 0.0f,
rotacionPez3 = 0.0f;
bool	animacion = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;
//banderas animacion Tortuga compleja
bool	animacionTortuga = false,
estadoTortuga1 = true,
estadoTortuga2 = false,
estadoTortuga3 = false,
estadoTortuga4 = false,
estadoAleta1 = true,
estadoAleta2 = false;
//banderas animacion Huevo tortuga
bool	animacionHuevo = false,
estadoHuevo1 = true,
estadoHuevo2 = false,
estadoHuevo3 = false,
estadoHuevo4 = false,
estadoHuevo5 = false;
//banderas animacion Pinguino
bool	animacionPinguino = false,
estadoPinguino1 = true,
estadoPinguino2 = false,
estadoPinguino3 = false,
estadoPinguino4 = false,
estadoPinguino5 = false,
estadoPinguino6 = false,
estadoPinguino7 = false,
estadoPinguino8 = false,
estadoPinguino9 = false,
estadoCabezaPinguino1 = true,
estadoCabezaPinguino2 = false;
//banderas luz que cambia de color
bool	animacionLuces = false,
RGB1 = true,
RGB2 = false,
RGB3 = false,
RGB4 = false,
RGB5 = false;
//banderas Huevo tortuga 2
bool	animacionTortuga2 = false,
estadoAnim1 = true,
estadoAnim2 = false,
estadoAnim3 = false,
estadoAnim4 = false,
estadoAnim5 = false,
estadoAleta3 = true,
estadoAleta4 = false;
//animacion de peces
bool	animacionPeces = true,
estadoPeces1 = true,
estadoPeces2 = false,
estadoPeces3 = true,
estadoPeces4 = false;
float tiempo = 0.0f;
float cambio = 0.0f;
bool luz = true;
float	myValue = 0.0f,
rojo = 0.0f,
verde = 0.0f,
apagar = 1.0f,
azul = 0.0f;

//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
posY = 0.0f,
posZ = 0.0f,
posXP = 0.0f,
posYP = 0.0f,
posZP = 0.0f,
rotRodIzq = 0.0f,
giroMonito = 0.0f,
rotAletaUno = 0.0f,
rotAletaDos = 0.0f,
giroAletaDer = 0.0f,
giroAletaIzq = 0.0f,
rotacionHuevo = 0.0f,
rotacionCabezaPinguino = 0.0f,
giroPingu = 0.0f,
rotAletaIzq = 0.0f,
rotAletaDer = 0.0f,
MovBracitoIzq = 0.0f,
MovBracitoDer = 0.0f;
float	incX = 0.0f,
incY = 0.0f,
incZ = 0.0f,
rotInc = 0.0f,
giroMonitoInc = 0.0f,
incXP = 0.0f,
incYP = 0.0f,
incZP = 0.0f,
giroPinguINC = 0.0f,
rotAletaIzqINC = 0.0f,
rotAletaDerINC = 0.0f,
MovBracitoIzqINC = 0.0f,
MovBracitoDerINC = 0.0f;
//banderas tiburon
bool animacionTiburon = false;
int animacionTibu = 0,
aleteo = 0;
#define MAX_FRAMES 30
int i_max_steps = 45;
int i_curr_steps = 0;
int contador = 1;
int contador2 = 1;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;

	float posXP;
	float posYP;
	float posZP;
	float giroPingu;
	float rotAletaIzq;
	float rotAletaDer;
	float MovBracitoIzq;
	float MovBracitoDer;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 24;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posXP = posXP;
	KeyFrame[FrameIndex].posYP = posYP;
	KeyFrame[FrameIndex].posZP = posZP;
	KeyFrame[FrameIndex].giroPingu = giroPingu;
	KeyFrame[FrameIndex].rotAletaIzq = rotAletaIzq;
	KeyFrame[FrameIndex].rotAletaDer = rotAletaDer;
	KeyFrame[FrameIndex].MovBracitoIzq = MovBracitoIzq;
	KeyFrame[FrameIndex].MovBracitoDer = MovBracitoDer;
	FrameIndex++;
}

void resetElements(void)
{

	posXP = KeyFrame[0].posXP;
	posYP = KeyFrame[0].posYP;
	posZP = KeyFrame[0].posZP;
	giroPingu = KeyFrame[0].giroPingu;
	rotAletaIzq = KeyFrame[0].rotAletaIzq;
	rotAletaDer = KeyFrame[0].rotAletaDer;
	MovBracitoIzq = KeyFrame[0].MovBracitoIzq;
	MovBracitoDer = KeyFrame[0].MovBracitoDer;


}

void interpolation(void)
{



	incXP = (KeyFrame[playIndex + 1].posXP - KeyFrame[playIndex].posXP) / i_max_steps;
	incYP = (KeyFrame[playIndex + 1].posYP - KeyFrame[playIndex].posYP) / i_max_steps;
	incZP = (KeyFrame[playIndex + 1].posZP - KeyFrame[playIndex].posZP) / i_max_steps;

	giroPinguINC = (KeyFrame[playIndex + 1].giroPingu - KeyFrame[playIndex].giroPingu) / i_max_steps;
	rotAletaIzqINC = (KeyFrame[playIndex + 1].rotAletaIzq - KeyFrame[playIndex].rotAletaIzq) / i_max_steps;
	rotAletaDerINC = (KeyFrame[playIndex + 1].rotAletaDer - KeyFrame[playIndex].rotAletaDer) / i_max_steps;
	MovBracitoIzqINC = (KeyFrame[playIndex + 1].MovBracitoIzq - KeyFrame[playIndex].MovBracitoIzq) / i_max_steps;
	MovBracitoDerINC = (KeyFrame[playIndex + 1].MovBracitoDer - KeyFrame[playIndex].MovBracitoDer) / i_max_steps;
}

void animate(void)//anima a nuestros objetos realiza que tengan algun movimento 
{
	//lightPosition.x = -800.0f * cos(tiempo); //lo largo de la circunferencia que queramos 
	//lightPosition.y = 800.0f * sin(tiempo);

	tiempo += 0.01f;
	//animacion de Luz posicional que cambia de color para el modelo tortuga
	if (animacionLuces) {
		if (RGB1) {
			rojo += 0.1f;
			verde = 0.0f;
			azul = 0.0f;
			if (rojo > 1.0f) {
				RGB1 = false;
				RGB2 = true;
			}
		}
		if (RGB2) {
			rojo -= 0.1f;
			verde += 0.1f;
			azul = 0.0f;
			if (verde > 1.0f) {
				RGB2 = false;
				RGB3 = true;
			}
		}
		if (RGB3) {
			rojo += 0.1f;
			verde -= 0.1f;
			azul += 0.1f;
			if (azul > 1.0f) {
				RGB3 = false;
				RGB4 = true;
			}
		}
		if (RGB4) {
			rojo -= 0.1f;
			verde += 0.1f;
			azul = 1.0f;
			if (verde > 1.0f) {
				RGB4 = false;
				RGB5 = true;
			}
		}
		if (RGB5) {
			rojo += 0.1f;
			verde = 1.0f;
			azul = 1.0f;
			if (rojo > 1.0f) {
				rojo = 0.0f;
				RGB5 = false;
				RGB1 = true;
			}
		}
	}
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posXP += incXP;
			posYP += incYP;
			posZP += incZP;

			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;
			giroPingu += giroPinguINC;
			rotAletaIzq += rotAletaIzqINC;
			rotAletaDer += rotAletaDerINC;
			MovBracitoIzq += MovBracitoIzqINC;
			MovBracitoDer += MovBracitoDerINC;
			i_curr_steps++;
		}
	}
	llanta -= 3.5f;

	//Vehículo
	if (animacion) {
		if (movimiento == 0)
			movAuto_x += 1.5f;
		if (movAuto_x > 190.0f) {
			rotCarro = -90.0f;
			movimiento = 1;
		}

		if (movimiento == 1) {
			movAuto_z += 1.5f;
			if (movAuto_z > 260.0f) {
				rotCarro = -180.0f;
				movimiento = 2;
			}
		}
		if (movimiento == 2) {
			movAuto_x -= 1.5f;
			if (movAuto_x < -200.5f) {
				rotCarro = -270.0f;
				movimiento = 3;
			}
		}
		if (movimiento == 3) {
			movAuto_z -= 1.5f;
			if (movAuto_z < -140.0f) {
				rotCarro = -360.0f;
				movimiento = 4;
			}
		}
		if (movimiento == 4) {
			movimiento = 0;
		}
	}
	//Animacion Tortuga que recorre estanque
	if (animacionTortuga) {
		if (estadoTortuga1) {
			movTortuga_z += 0.30f;
			movTortuga_y += 0.30f * 0.24f;
			orientacionTortuga = -90.0f;
			if (movTortuga_z >= 75.0 && movTortuga_y >= 18.0f) {
				estadoTortuga1 = false;
				estadoTortuga2 = true;
			}
		}
		if (estadoTortuga2) {
			movTortuga_z -= 0.20f;
			movTortuga_x += 0.20f * .222f;
			orientacionTortuga = 77.48f;
			if (movTortuga_x > 16.0f && movTortuga_z < 3.0f) {
				estadoTortuga2 = false;
				estadoTortuga3 = true;
			}
		}
		if (estadoTortuga3) {
			movTortuga_y -= 0.30f * 0.2647f;
			movTortuga_z += 0.30f;
			orientacionTortuga = -90.0f;
			if (movTortuga_z > 70.0f && movTortuga_y < 0.0f) {
				estadoTortuga3 = false;
				estadoTortuga4 = true;
			}
		}
		if (estadoTortuga4) {
			movTortuga_x -= 0.20f * 0.2285f;
			movTortuga_z -= 0.20f;
			orientacionTortuga = 102.87f;
			if (movTortuga_x < 0.0f) {
				orientacionTortuga = 0.0f;
				estadoTortuga4 = false;
				estadoTortuga1 = true;
			}
		}

	}
	//animacion de aletas de la tortuga que recorre estanque
	if (animacionTortuga) {
		if (estadoAleta1) {
			rotAletaDos -= 0.5f;
			rotAletaUno += 0.5f;
			if (rotAletaUno >= 12.0f) {
				estadoAleta1 = false;
				estadoAleta2 = true;
			}
		}
		if (estadoAleta2) {
			rotAletaDos += 0.5f;
			rotAletaUno -= 0.5f;
			if (rotAletaUno <= -7.0f) {
				estadoAleta1 = true;
				estadoAleta2 = false;
			}
		}
	}

	if (animacionHuevo) {
		if (estadoHuevo1) {
			movHuevo += 0.01f;
			rotacionHuevo = 0.0f;
			if (movHuevo > 0.50f) {
				estadoHuevo1 = false;
				estadoHuevo2 = true;
			}
		}
		if (estadoHuevo2) {
			//movHuevo += 0.1f;
			rotacionHuevo += 0.5f;
			if (rotacionHuevo > 40.0f) {
				estadoHuevo2 = false;
				estadoHuevo3 = true;
			}
		}
		if (estadoHuevo3) {
			//movHuevo += 0.1f;
			rotacionHuevo -= 0.5f;
			if (rotacionHuevo < -20.0f) {
				estadoHuevo3 = false;
				estadoHuevo4 = true;
			}
		}
		if (estadoHuevo4) {
			//movHuevo += 0.1f;
			rotacionHuevo += 0.2f;
			if (rotacionHuevo >= 0.0f) {
				estadoHuevo4 = false;
				estadoHuevo5 = true;
			}
		}
		if (estadoHuevo5) {
			movHuevo -= 0.01f;
			rotacionHuevo = 0.0f;
			if (movHuevo <= 0.0f) {
				estadoHuevo5 = false;
				estadoHuevo1 = true;
			}
		}
	}
	//animacion de pinguino que camina en escenario de hielo
	if (animacionPinguino) {

		if (estadoPinguino1) {
			if (movPinguino_z >= 54.0f) {
				movPinguino_z = 54.0f;
				pataDerechaX = 0.55f;
				pataIzquierdaX = -0.15f;
				contador = 90;
				estadoPinguino3 = true;
				estadoPinguino1 = false;
				rotacionPinguino = -90.0f;
			}
			else {
				movPinguino_z += 0.1f;
				movPataDerecha += 0.2f;
				if ((movPinguino_z / (contador * 0.60)) >= 1.0f) {
					estadoPinguino1 = false;
					estadoPinguino2 = true;
					contador += 1;
				}
			}
		}
		if (estadoPinguino2) {
			movPinguino_z += 0.1f;
			movPataIzquierda += 0.2;
			if ((movPinguino_z / (contador * 0.60)) >= 1.0f) {
				estadoPinguino2 = false;
				estadoPinguino1 = true;
				contador += 1;
			}
		}
		if (estadoPinguino3) {
			if (movPinguino_x <= -14.0f) {
				movPinguino_x = -14.3f;
				pataDerechaX = -13.85f;
				pataIzquierdaX = -14.55f;
				contador2 = 24;
				estadoPinguino3 = false;
				estadoPinguino5 = true;
				rotacionPinguino = 90.0f;
			}
			else {
				movPinguino_x -= 0.1f;
				movPinguino_y += 0.1 * 0.402;
				pataDerechaX -= 0.2;
				if (-(movPinguino_x / (contador2 * 0.60)) >= 1.0f) {
					estadoPinguino3 = false;
					estadoPinguino4 = true;
					contador2 += 1;
				}
			}
		}
		if (estadoPinguino4) {
			movPinguino_x -= 0.1f;
			movPinguino_y += 0.1f * 0.402f;
			pataIzquierdaX -= 0.2;
			if (-(movPinguino_x / (contador2 * 0.60)) >= 1.0f) {
				estadoPinguino4 = false;
				estadoPinguino3 = true;
				contador2 += 1;
			}
		}
		if (estadoPinguino5) {
			if (movPinguino_x >= 0.0f) {
				movPinguino_x = 0.0f;
				movPinguino_z = 54.0f;
				movPinguino_y = 0.0f;
				pataDerechaX = 0.0f;
				pataIzquierdaX = 0.0f;
				movPataDerecha = 54.55f;
				movPataIzquierda = 53.85f;
				rotacionPinguino = 180.0f;
				contador2 = 1;
				estadoPinguino5 = false;
				estadoPinguino7 = true;
			}
			else {
				movPinguino_x += 0.1f;
				movPinguino_y -= 0.1 * 0.402;
				pataDerechaX += 0.2;
				if (-(movPinguino_x / (contador2 * 0.60)) <= 1.0f) {
					estadoPinguino5 = false;
					estadoPinguino6 = true;
					contador2 -= 1;
				}
			}
		}
		if (estadoPinguino6) {
			movPinguino_x += 0.1f;
			movPinguino_y -= 0.1f * 0.402f;
			pataIzquierdaX += 0.2;
			if (-(movPinguino_x / (contador2 * 0.60)) <= 1.0f) {
				estadoPinguino6 = false;
				estadoPinguino5 = true;
				contador2 -= 1;
			}
		}
		if (estadoPinguino7) {
			if (movPinguino_z <= 0.0f) {
				movPinguino_z = 0.0f;
				movPataDerecha = 0.0f;
				movPataIzquierda = 0.0f;
				estadoPinguino1 = true;
				estadoPinguino7 = false;
				contador = 1;
				rotacionPinguino = 0.0f;
			}
			else {
				movPinguino_z -= 0.1f;
				movPataDerecha -= 0.2f;
				if ((movPinguino_z / (contador * 0.60)) <= 1.0f) {
					estadoPinguino7 = false;
					estadoPinguino8 = true;
					contador -= 1;
				}
			}
		}
		if (estadoPinguino8) {
			movPinguino_z -= 0.1f;
			movPataIzquierda -= 0.2;
			if ((movPinguino_z / (contador * 0.60)) <= 1.0f) {
				estadoPinguino8 = false;
				estadoPinguino7 = true;
				contador -= 1;
			}
		}
	}
	//animacion de cabeza de pinguino que camina en escenario de hielo
	if (animacionPinguino) {
		if (estadoCabezaPinguino1) {
			rotacionCabezaPinguino += 0.3f;
			if (rotacionCabezaPinguino > 15.0f) {
				estadoCabezaPinguino1 = false;
				estadoCabezaPinguino2 = true;
			}
		}
		if (estadoCabezaPinguino2) {
			rotacionCabezaPinguino -= 0.3f;
			if (rotacionCabezaPinguino < -15.0f) {
				estadoCabezaPinguino2 = false;
				estadoCabezaPinguino1 = true;
			}
		}
	}
	//animacion Huevo tortuga 2
	if (animacionTortuga2) {
		if (estadoAnim1) {
			movHuevo2 += 0.021f;
			tortuga_y += 0.01f;
			if (tortuga_y > 2.0f) {
				estadoAnim1 = false;
				estadoAnim2 = true;
			}
		}
		if (estadoAnim2) {
			tortuga_y += 0.1f * 0.5f;
			tortuga_z += 0.1f;
			movHuevo2 -= 0.042f;
			if (tortuga_z >= 10.0f) {
				estadoAnim2 = false;
				estadoAnim3 = true;
			}
		}
		if (estadoAnim3) {
			tortuga_z -= 0.1f;
			orientacionTortuga2 = 180.0f;
			if (tortuga_z <= 0.0f) {
				estadoAnim3 = false;
				estadoAnim4 = true;
			}
		}
		if (estadoAnim4) {
			tortuga_z += 0.1f;
			tortuga_y -= 0.1f * 0.88f;
			orientacionTortuga2 = 0.0f;
			if (tortuga_z >= 10.0f) {
				estadoAnim4 = false;
				estadoAnim5 = true;
			}
		}
		if (estadoAnim5) {
			tortuga_z -= 0.1f;
			orientacionTortuga2 = 180.0f;
			if (tortuga_z <= 4.0f) {
				estadoAnim5 = false;
				animacionTortuga2 = false;
				giroAletaDer = 0.0f;
				giroAletaIzq = 0.0f;
			}
		}
	}
	if (animacionTortuga2) {
		if (estadoAleta3) {
			giroAletaIzq -= 0.5f;
			giroAletaDer += 0.5f;
			if (giroAletaDer >= 12.0f) {
				estadoAleta3 = false;
				estadoAleta4 = true;
			}
		}
		if (estadoAleta4) {
			giroAletaIzq += 0.5f;
			giroAletaDer -= 0.5f;
			if (giroAletaDer <= -7.0f) {
				estadoAleta3 = true;
				estadoAleta4 = false;
			}
		}
	}
	if (animacionPeces) {
		if (estadoPeces1) {
			movPez1_x -= 0.2f;
			movPez2_x += 0.2f;
			rotacionPez1 = 0.0f;
			rotacionPez2 = 180.0f;
			if (movPez1_x <= -134.5f) {
				estadoPeces1 = false;
				estadoPeces2 = true;
			}

		}
		if (estadoPeces2) {
			movPez1_x += 0.2f;
			movPez2_x -= 0.2f;
			rotacionPez1 = 180.0f;
			rotacionPez2 = 0.0f;
			if (movPez1_x >= 0.0f) {
				estadoPeces1 = true;
				estadoPeces2 = false;
			}
		}
		if (estadoPeces3) {
			movPez3_x -= 0.08f;
			rotacionPez7 = 180.0f;
			if (movPez3_x <= -50.5f) {
				estadoPeces3 = false;
				estadoPeces4 = true;
			}

		}
		if (estadoPeces4) {
			movPez3_x += 0.08f;
			rotacionPez7 = 0.0f;
			if (movPez3_x >= 0.0f) {
				estadoPeces3 = true;
				estadoPeces4 = false;
			}
		}
	}

	if (animacionTiburon) {

		if (animacionTibu == 0) {
			//std::cout << "Entre a la animación tiburon" << std::endl;
			if (CuerpoTiburonY <= 10.0f) {
				CuerpoTiburonY += 0.8f;
				if (CuerpoTiburonX <= 40) {
					CuerpoTiburonX += 0.8f;
				}//if (CuerpoTiburonZ <= 50) {
					//CuerpoTiburonZ += 3.0f;

			//	}
				if (GiroTiburon2 >= -28) {
					GiroTiburon2 -= 1.0f;
				}
				if (aleteo == 0) {
					AletaTibuDer += 0.3f;
					AletaSup += 0.3f;
					ColaTiburon1 += 0.3f;
					ParteTraseraTibu += 0.3;
					if (AletaTibuDer >= 6.0f) {
						aleteo = 1;
					}
				}
				else if (aleteo == 1) {
					AletaTibuDer -= 0.3f;
					AletaSup -= 0.3f;
					ColaTiburon1 -= 0.2f;
					ParteTraseraTibu -= 0.3;
					if (AletaTibuDer <= -6.0f) {
						aleteo = 0;
					}
				}
			}
			else {
				animacionTibu = 1;
			}
		}
		else if (animacionTibu == 1) {
			if (CuerpoTiburonY >= 1.0f) {
				CuerpoTiburonY -= 0.4f;
				if (CuerpoTiburonX <= 80) {
					CuerpoTiburonX += 1.0f;
				}if (CuerpoTiburonZ >= -10) {
					CuerpoTiburonZ -= 3.0f;

				}//if (GiroTiburon >= -180) {
					//GiroTiburon -= 8.0f;
			//	}
				if (GiroTiburon2 <= 28) {
					GiroTiburon2 += 1.0f;
				}
				if (aleteo == 0) {
					AletaTibuDer += 0.3f;
					AletaSup += 0.3f;
					ColaTiburon1 += 0.3f;
					ParteTraseraTibu += 0.3;
					if (AletaTibuDer >= 6.0f) {
						aleteo = 1;
					}
				}
				else if (aleteo == 1) {
					AletaTibuDer -= 0.3f;
					AletaSup -= 0.3f;
					ColaTiburon1 -= 0.2f;
					ParteTraseraTibu -= 0.3;
					if (AletaTibuDer <= -6.0f) {
						aleteo = 0;
					}
				}


			}
			else {
				animacionTibu = 2;
			}
		}
		else if (animacionTibu == 2) {
			if (CuerpoTiburonY <= 8.0f) {
				CuerpoTiburonY += 0.5f;
				if (CuerpoTiburonX <= 100) {
					CuerpoTiburonX += 1.0f;
				}if (CuerpoTiburonZ <= 0) {
					CuerpoTiburonZ += 1.0f;
				}
				if (GiroTiburon2 >= 0) {
					GiroTiburon2 -= 1.0f;
				}
				if (aleteo == 0) {
					AletaTibuDer += 0.3f;
					AletaSup += 0.3f;
					ColaTiburon1 += 0.3f;
					ParteTraseraTibu += 0.3;
					if (AletaTibuDer >= 6.0f) {
						aleteo = 1;
					}
				}
				else if (aleteo == 1) {
					AletaTibuDer -= 0.3f;
					AletaSup -= 0.3f;
					ColaTiburon1 -= 0.2f;
					ParteTraseraTibu -= 0.3;
					if (AletaTibuDer <= -6.0f) {
						aleteo = 0;
					}
				}
			}

			else {
				animacionTibu = 3;
			}
		}




		else if (animacionTibu == 3) {
			if (GiroTiburon >= -180) {
				GiroTiburon -= 9.0f;
			}
			else {
				animacionTibu = 4;
			}
			if (aleteo == 0) {
				AletaTibuDer += 0.3f;
				AletaSup += 0.3f;
				ColaTiburon1 += 0.3f;
				ParteTraseraTibu += 0.3;
				if (AletaTibuDer >= 6.0f) {
					aleteo = 1;
				}
			}
			else if (aleteo == 1) {
				AletaTibuDer -= 0.3f;
				AletaSup -= 0.3f;
				ColaTiburon1 -= 0.2f;
				ParteTraseraTibu -= 0.3;
				if (AletaTibuDer <= -6.0f) {
					aleteo = 0;
				}
			}
		}
		else if (animacionTibu == 4) {
			if (CuerpoTiburonX >= -0) {
				CuerpoTiburonX -= 2.0f;
				if (aleteo == 0) {
					AletaTibuDer += 0.3f;
					AletaSup += 0.3f;
					ColaTiburon1 += 0.8f;
					ParteTraseraTibu += 0.3;
					if (AletaTibuDer >= 6.0f) {
						aleteo = 1;
					}
				}
				else if (aleteo == 1) {
					AletaTibuDer -= 0.3f;
					AletaSup -= 0.3f;
					ColaTiburon1 -= 0.8f;
					ParteTraseraTibu -= 0.3;
					if (AletaTibuDer <= -6.0f) {
						aleteo = 0;
					}
				}
			}
			else {
				animacionTibu = 5;
			}

		}
		else if (animacionTibu == 5) {
			if (GiroTiburon <= 0) {
				GiroTiburon += 9.0f;

				if (aleteo == 0) {
					AletaTibuDer += 0.3f;
					AletaSup += 0.3f;
					ColaTiburon1 += 0.8f;
					ParteTraseraTibu += 0.3;
					if (AletaTibuDer >= 6.0f) {
						aleteo = 1;
					}
				}
				else if (aleteo == 1) {
					AletaTibuDer -= 0.3f;
					AletaSup -= 0.3f;
					ColaTiburon1 -= 0.8f;
					ParteTraseraTibu -= 0.3;
					if (AletaTibuDer <= -6.0f) {
						aleteo = 0;
					}
				}

			}
			if (aleteo == 0) {
				AletaTibuDer += 0.3f;
				AletaSup += 0.3f;
				ColaTiburon1 += 0.8f;
				ParteTraseraTibu += 0.3;
				if (AletaTibuDer >= 6.0f) {
					aleteo = 1;
				}
			}
			else if (aleteo == 1) {
				AletaTibuDer -= 0.3f;
				AletaSup -= 0.3f;
				ColaTiburon1 -= 0.8f;
				ParteTraseraTibu -= 0.3;
				if (AletaTibuDer <= -6.0f) {
					aleteo = 0;
				}
			}

		}

	}


	//Movimiento de peces.
	rotacionPez3 += 2.0f;
	rotacionPez4 -= 1.0f;
	rotacionPez5 -= 1.5f;
	rotacionPez6 -= 0.5f;
}



void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//Gitano app

	float my_points[10000];
	int count = 0;

	string nombreArchivo = "Valores.txt";
	ifstream archivo(nombreArchivo.c_str());
	string linea;
	// Obtener línea de archivo, y almacenar contenido en "linea"
	while (getline(archivo, linea)) {
		my_points[count] = std::stof(linea);
		cout << my_points[count] << " ";
		count++;
	}




	int j = 0;

	for (int i = 0; i < FrameIndex; i++)
	{

		KeyFrame[i].posXP = my_points[j++];
		KeyFrame[i].posYP = my_points[j++];
		KeyFrame[i].posZP = my_points[j++];
		KeyFrame[i].giroPingu = my_points[j++];
		KeyFrame[i].rotAletaIzq = my_points[j++];
		KeyFrame[i].rotAletaDer = my_points[j++];
		KeyFrame[i].MovBracitoIzq = my_points[j++];
		KeyFrame[i].MovBracitoDer = my_points[j++];
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces//donde se carga la textura del fondo
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models modelo estatico, formato obj que es la que mejor le da el soporte
	// -----------
	//Animales
	Model FishUno("resources/objects/FishUno/FishUno.obj");
	Model Cangrejo("resources/objects/crab/crabs.obj");
	Model Pecesito("resources/objects/Pecesito/Pecesito.obj");
	Model PezNaranja("resources/objects/PezNaranja/PezNaranja.obj");
	Model PezCinco("resources/objects/PezCinco/PezCinco.obj");
	Model TresPeces("resources/objects/TresPeces/TresPeces.obj");
	Model PezGlobo("resources/objects/PezGlobo/PezGlobo.obj");
	Model PezGlobo2("resources/objects/PezGlobo2/PezGlobo2.obj");
	Model Naranja("resources/objects/Naranja/Naranja.obj");
	Model leonMarino("resources/objects/leonMarino/leonMarino.obj");
	//Objetos
	//escenario
	Model acuario("resources/objects/Acuario/acuario.obj"); // este es el piso del escenario
	Model Acceso("resources/objects/Acceso/Accesoo.obj"); //bardas, arco y arboles con base
	Model EstanqueTiburon("resources/objects/EstanqueT/EstanqueTiburon.obj"); //2 estanques cilindricos en medio
	Model Pecera1("resources/objects/Pecera1.1/PeceraUno.obj"); //pecera en forma de C
	Model Pecera234("resources/objects/Pecera234/PeceraPrueba.obj"); //demas peceras incluido la del pinguino
	Model letreros("resources/objects/letreros/letreros.obj"); // letreros de animaciones

	//modelos
	Model cuerpoTortuga("resources/objects/Tortuga/cuerpoTortuga.obj"); //modelo tortuga parte 1
	Model aletaUno("resources/objects/Tortuga/aletaUno.obj"); //modelo tortuga parte 2
	Model aletaDos("resources/objects/Tortuga/aletaDos.obj"); //modelo tortuga parte 3

	//tortuga Huevo
	Model huevo("resources/objects/Huevo/huevo.obj"); //cascaron de huevo
	Model huevoRoto("resources/objects/Huevo/huevoRoto.obj"); //cascara del huevo pequeña que se mueve
	Model tortugaHuevo("resources/objects/Huevo/tortugaHuevo.obj"); //tortuga dentro del huevo

	//pinguino 
	Model cuerpoPinguino("resources/objects/pinguino/cuerpoPinguino.obj"); // modelo pinguino animado para pecera 234
	Model pataIzquierda("resources/objects/pinguino/pataIzquieda.obj"); // modelo pinguino animado para pecera 234
	Model pataDerecha("resources/objects/pinguino/pataDerecha.obj"); // modelo pinguino animado para pecera 234
	Model cabezaPinguino("resources/objects/pinguino/cabezaPinguino.obj"); // modelo pinguino animado para pecera 234
	Model rampa("resources/objects/rampaPinguino/rampa.obj"); // rampa de pinguino

	//tortuga Huevo 2
	Model aletaIzquierda("resources/objects/Huevo2/aletaIzquierda.obj"); //aleta tortuga huevo 2
	Model aletaDerecha("resources/objects/Huevo2/aletaDerecha.obj"); //aleta tortuga huevo 2
	Model huevo2("resources/objects/Huevo2/huevo.obj"); //cascaron de huevo 2
	Model huevoRoto2("resources/objects/Huevo2/huevoRoto.obj"); //cascara del huevo pequeña que se mueve 2
	Model tortugaHuevo2("resources/objects/Huevo2/Tortuga.obj"); //tortuga dentro del huevo 2

	//ModeloTiburon
	Model AletaDerTiburon("resources/objects/Tiburon2/AletaDer.obj");
	Model AletaIzqTiburon("resources/objects/Tiburon2/AletaIzq.obj");
	Model AletaSupTiburon("resources/objects/Tiburon2/AletaSup.obj");
	Model ColaTiburon("resources/objects/Tiburon2/ColaTiburon.obj");
	Model CuerpoTiburon("resources/objects/Tiburon2/CuerpoTiburon.obj");
	Model CuerpoTraseroTiburon("resources/objects/Tiburon2/ParteTraseraTiburon.obj");

	//pinguino modelado por KeyFrames
	Model AletaDer("resources/objects/Pingu/AletaDerecha.obj");
	Model AletaIzq("resources/objects/Pingu/AletaIzquierda.obj");
	Model piernaDer("resources/objects/Pingu/pieDer.obj");
	Model piernaIzq("resources/objects/Pingu/pieIzq.obj");
	Model torso("resources/objects/Pingu/Torso.obj");
	//modelo de coche animado
	Model Carro("resources/objects/Carro/Carro.obj"); // este es el coche animado
	Model Llanta("resources/objects/LlantaTI/LlantaTI.obj"); // esta es la llanta del coche

	//decoracion
	//Model Starbucks("resources/objects/StarB/Starbucks.obj"); //fachada starbucks
	//Model SilasAndTable("resources/objects/Sillas/SillasAndTable.obj"); //conjunto de sillas
	//Model Juegos("resources/objects/Juegos/Juegos.obj"); //area de juegos
	//Model InteriorStarbucks("resources/objects/InteriorStarbucks/InteriorStarbucks.obj"); //interior starbucks

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights// ilumincion 
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));//las no iluminadas tienen al color negro 
		staticShader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));//cara iluminadas 
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));//reflejos de las superficies 


		staticShader.setVec3("pointLight[0].position", lightPosition);//funte de luz posicional lamparas 
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.09f);//controlas la distancia con la que van a poder viajar los rayos 
		staticShader.setFloat("pointLight[0].linear", 0.09f);//controlas la distancia con la que van a poder viajar los rayos 
		staticShader.setFloat("pointLight[0].quadratic", 0.01f);//potencia de los rayos luminosos 

		staticShader.setVec3("pointLight[1].position", glm::vec3(movTortuga_x, movTortuga_y, movTortuga_z)); //LUZ FIJA AZUL
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(rojo, verde, azul));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(rojo, verde, azul));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(20.0f, 20.0f, 10.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0005f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		glm::mat4 tortuga = glm::mat4(1.0f);
		glm::mat4 tortuga2 = glm::mat4(1.0f);
		glm::mat4 huevotemp = glm::mat4(1.0f);
		glm::mat4 huevotemp2 = glm::mat4(1.0f);
		glm::mat4 origen = glm::mat4(1.0f);
		glm::mat4 pinguino = glm::mat4(1.0f);
		glm::mat4 tmp2 = glm::mat4(1.0f);
		glm::mat4 tmp3 = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);
		//-------------------------------------------------------------------------------------------------------
		//Peces básicos
		//-------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPez1_x + 20.5f, 12.5f, 170.0f));
		model = glm::rotate(model, glm::radians(rotacionPez1), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		FishUno.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPez2_x - 114.0f, 7.0f, 192.0f));
		model = glm::rotate(model, glm::radians(rotacionPez2), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		FishUno.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f, 5.0f, 40.0f));
		model = glm::rotate(model, glm::radians(rotacionPez3), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		Pecesito.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-47.0f, 10.0f, 40.0f));
		model = glm::rotate(model, glm::radians(rotacionPez4), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		PezNaranja.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-47.0f, 13.0f, 40.0f));
		model = glm::rotate(model, glm::radians(rotacionPez5), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		PezCinco.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-47.0f, 7.5f, 40.0f));
		model = glm::rotate(model, glm::radians(rotacionPez6), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		PezCinco.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-47.0f, 3.0f, 40.0f));
		model = glm::rotate(model, glm::radians(rotacionPez5), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		TresPeces.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-47.0f, 3.0f, 105.0f));
		model = glm::rotate(model, glm::radians(rotacionPez3), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.4f));
		staticShader.setMat4("model", model);
		PezGlobo.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-47.0f, 10.0f, 105.0f));
		model = glm::rotate(model, glm::radians(rotacionPez5), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.82f));
		staticShader.setMat4("model", model);
		PezGlobo2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPez3_x - 65.0f, 16.0f, -54.0f));
		model = glm::rotate(model, glm::radians(rotacionPez7), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.7f));
		staticShader.setMat4("model", model);
		Naranja.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPez3_x - 65.0f, 9.0f, -28.0f));
		model = glm::rotate(model, glm::radians(rotacionPez7), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.7f));
		staticShader.setMat4("model", model);
		Naranja.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 10.0f, -10.0f));
		model = glm::rotate(model, glm::radians(rotacionPez5), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		PezGlobo2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 15.0f, -15.0f));
		model = glm::rotate(model, glm::radians(rotacionPez4), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f));
		staticShader.setMat4("model", model);
		PezGlobo2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 19.0f, -15.0f));
		model = glm::rotate(model, glm::radians(rotacionPez5), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		PezGlobo2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		leonMarino.Draw(staticShader);
		//-----------------------------------------------------------------------------------------------------
		//Tiburon
		//-----------------------------------------------------------------------------------------------------
		//Cuerpo
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-70.0f, 0.0f, 180.0f));
		model = glm::translate(model, glm::vec3(CuerpoTiburonX, CuerpoTiburonY, CuerpoTiburonZ));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(GiroTiburon), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(GiroTiburon2), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		tmp2 = model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		CuerpoTiburon.Draw(staticShader);

		//AletaDerechaTiburon
		model = glm::translate(tmp2, glm::vec3(-0.0f, 0.0f, -0.0f));
		model = glm::translate(model, glm::vec3(-5.2f, 15.4f, 3.5f));
		model = glm::rotate(model, glm::radians(AletaTibuDer), glm::vec3(0.0f, 0.0f, 1.0));
		//model = glm::rotate(model, glm::radians(-rotAletaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		AletaDerTiburon.Draw(staticShader);

		//AletaIzquierdaTiburon
		model = glm::translate(tmp2, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(6.0f, 15.0f, 2.4f));
		model = glm::rotate(model, glm::radians(-AletaTibuDer), glm::vec3(0.0f, 0.0f, 1.0));
		//model = glm::rotate(model, glm::radians(-rotAletaDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		AletaIzqTiburon.Draw(staticShader);

		//AletaSupTiburon
		model = glm::translate(tmp2, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 23.9f, 0));
		model = glm::rotate(model, glm::radians(AletaSup), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		AletaSupTiburon.Draw(staticShader);

		//CuerpoTraseroTiburon
		model = glm::translate(tmp2, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 18.2f, -11.6f));
		tmp3 = model = glm::rotate(model, glm::radians(ParteTraseraTibu), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		CuerpoTraseroTiburon.Draw(staticShader);

		//ColaTiburon
		model = glm::translate(tmp3, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(7.2f, -4.5f, -14.0f));
		model = glm::rotate(model, glm::radians(ColaTiburon1), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		ColaTiburon.Draw(staticShader);

		//-------------------------------------------------------------------------------------------------------
		//Tortuga
		//-------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0., 0, 0));
		model = glm::translate(model, glm::vec3(movTortuga_x, movTortuga_y, movTortuga_z));
		tortuga = model = glm::rotate(model, glm::radians(orientacionTortuga), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		cuerpoTortuga.Draw(staticShader);

		model = glm::translate(tortuga, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotAletaUno), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		aletaUno.Draw(staticShader);

		model = glm::translate(tortuga, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotAletaDos), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		aletaDos.Draw(staticShader);
		//-------------------------------------------------------------------------------------------------------
		//Huevo
		//-------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0, 55.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		huevotemp = model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		huevo.Draw(staticShader);

		model = glm::translate(huevotemp, glm::vec3(0.0f, movHuevo, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotacionHuevo), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		huevoRoto.Draw(staticShader);

		model = glm::translate(huevotemp, glm::vec3(0.0f, movHuevo, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotacionHuevo), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		tortugaHuevo.Draw(staticShader);
		//-------------------------------------------------------------------------------------------------------
		//Huevo 2
		//-------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0, 35.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		huevotemp2 = model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		huevo2.Draw(staticShader);

		model = glm::translate(huevotemp2, glm::vec3(0.0f, movHuevo2, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		huevoRoto2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0, 35.0f));
		model = glm::translate(model, glm::vec3(tortuga_x, tortuga_y, tortuga_z));
		tortuga2 = model = glm::rotate(model, glm::radians(orientacionTortuga2), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		tortugaHuevo2.Draw(staticShader);

		model = glm::translate(tortuga2, glm::vec3(0.077f, 0.0f, -0.071f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-giroAletaDer), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		aletaDerecha.Draw(staticShader);

		model = glm::translate(tortuga2, glm::vec3(-0.077f, 0.0f, -0.071f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-giroAletaIzq), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		aletaIzquierda.Draw(staticShader);
		//-------------------------------------------------------------------------------------------------------
		//Pinguino
		//-------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movPinguino_x - 96.0f, movPinguino_y, movPinguino_z + 33.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		pinguino = model = glm::rotate(model, glm::radians(rotacionPinguino), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		cuerpoPinguino.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(pataDerechaX - 96.0f, movPinguino_y, 32.45f + movPataDerecha));
		model = glm::rotate(model, glm::radians(rotacionPinguino), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		pataDerecha.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(pataIzquierdaX - 96.0f, movPinguino_y, 33.15f + movPataIzquierda));
		model = glm::rotate(model, glm::radians(rotacionPinguino), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		pataIzquierda.Draw(staticShader);

		model = glm::translate(pinguino, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotacionCabezaPinguino), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		cabezaPinguino.Draw(staticShader);

		//-------------------------------------------------------------------------------------------------------
		//pinguino Linux
		//-------------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0, -80.0f));
		model = glm::translate(model, glm::vec3(posXP, posYP, posZP));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		tmp = model = glm::rotate(model, glm::radians(giroPingu), glm::vec3(0.0f, 1.0f, 0.0));
		staticShader.setMat4("model", model);
		torso.Draw(staticShader);

		//Pierna Der
		model = glm::translate(tmp, glm::vec3(-0.0f, 0.0f, -0.0f));
		model = glm::translate(model, glm::vec3(1.9f, 2.0f, 0.0f));

		//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotAletaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaDer.Draw(staticShader);

		//Pierna Izq
		model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-1.9f, 2.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotAletaDer), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		piernaIzq.Draw(staticShader);

		//Brazo derecho
		model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-2.6f, 7.5f, 0));
		model = glm::rotate(model, glm::radians(MovBracitoDer), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		AletaDer.Draw(staticShader);

		//Brazo izquierdo
		model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.6f, 7.5f, 0));
		model = glm::rotate(model, glm::radians(MovBracitoIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		staticShader.setMat4("model", model);
		AletaIzq.Draw(staticShader);
		//-----------------------------------------------------------------------------------------------------
		//Carro
		//-----------------------------------------------------------------------------------------------------
		model = glm::rotate(glm::mat4(1.0f), glm::radians(rotacion), glm::vec3(0.0f, 1.0f, 0.0f)); //direccion del carro como se haran la ruta
		model = glm::translate(model, glm::vec3(movAuto_x, movAuto_y, movAuto_z));//Pone al carro en su posicion inicial 
		tmp = model = glm::rotate(model, glm::radians(rotCarro), glm::vec3(0.0f, 5.0f, 0.0f));//la rotacion de como el carro va andar 
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setMat4("model", model);
		Carro.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(18.0f, 3.0f, -11.5f));
		model = glm::rotate(model, glm::radians(llanta), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.7f, 6.7f, 6.7f));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-18.0f, 3.0f, -11.5));
		model = glm::scale(model, glm::vec3(6.7f, 6.7f, 6.7f));
		model = glm::rotate(model, glm::radians(llanta), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//izq tras

		model = glm::translate(tmp, glm::vec3(-18.0f, 3.0f, 11.0f));
		model = glm::scale(model, glm::vec3(6.7f, 6.7f, 6.7f));
		model = glm::rotate(model, glm::radians(llanta), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(18.0f, 3.0f, 11.0f));
		model = glm::rotate(model, glm::radians(llanta), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.7f, 6.7f, 6.7f));
		staticShader.setMat4("model", model);
		Llanta.Draw(staticShader);	//Del Derecha
		//-----------------------------------------------------------------------------------------------------
		//Escenario
		//-----------------------------------------------------------------------------------------------------
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		acuario.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		Acceso.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		letreros.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		EstanqueTiburon.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		Pecera1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		origen = model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		Pecera234.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		origen = model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		rampa.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		origen = model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		Cangrejo.Draw(staticShader);
		//----------------------------------------------------------------------------------------------------------------
		//Decoracion
		//----------------------------------------------------------------------------------------------------------------
		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f));
		//staticShader.setMat4("model", model);
		//Starbucks.Draw(staticShader);

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(-15.0f, 0.0f, -80.0f));
		//model = glm::scale(model, glm::vec3(1.0f));
		//staticShader.setMat4("model", model);
		//SilasAndTable.Draw(staticShader);

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f));
		//staticShader.setMat4("model", model);
		//Juegos.Draw(staticShader);

		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f));
		//staticShader.setMat4("model", model);
		//InteriorStarbucks.Draw(staticShader);

		// -------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPosition.x++;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPosition.x--;

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) //Prende y apaga una luz en especifco como si funcionara como un foco 
	{
		if (luz == true)
		{
			cambio = 1.0f;
			luz = false;
		}
		else {
			cambio = 0.0f;
			luz = true;
		}
	}
	//pinguino que camina
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		animacionPinguino ^= true;
	}
	//Luz de color que prende y apaga
	//Tortuga que recorre estanque
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		animacionTortuga ^= true;
		animacionLuces ^= true;
	}
	//Tortuga que sale de su huevo y se esconde
	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
		animacionHuevo ^= true;
	//Animacion Carro 
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		animacion ^= true;
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		animacionTiburon ^= true;


	//Tortuga que sale de su huevo y se esconde
	if (key == GLFW_KEY_5 && action == GLFW_PRESS)
		animacionTortuga2 ^= true;
	//Boton que resetea las animaciones
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		//Reset Tortuga
		movTortuga_x = 0.0f;
		movTortuga_y = 0.0f;
		movTortuga_z = 0.0f;
		orientacionTortuga = -90.0f;
		rotAletaDos = 0.0f;
		rotAletaUno = 0.0f;
		animacionTortuga = false;
		estadoTortuga1 = true;
		estadoTortuga2 = false;
		estadoTortuga3 = false;
		estadoTortuga4 = false;
		//Reset HuevoTortuga
		estadoHuevo1 = true;
		estadoHuevo2 = false;
		estadoHuevo3 = false;
		estadoHuevo4 = false;
		estadoHuevo5 = false;
		movHuevo = 0.0f;
		rotacionHuevo = 0.0f;
		animacionHuevo = false;

		//Reset Tiburon
		animacionTiburon = false;
		AletaTibuDer = 0.0f;
		AletaSup = 0.0f;
		ColaTiburon1 = 0.0f;
		ParteTraseraTibu = 0.0f;
		CuerpoTiburonX = 0.0f;
		CuerpoTiburonY = 0.0f;
		CuerpoTiburonZ = 0.0f;
		GiroTiburon = 0.0f;
		GiroTiburon2 = 0.0f;
		animacionTibu = 0;
		//Reset Luces
		animacionLuces = false;
		RGB1 = true;
		RGB2 = false;
		RGB3 = false;
		RGB4 = false;
		RGB5 = false;
		rojo = 0.0f;
		verde = 0.0f;
		azul = 0.0f;
		//Reset pinguino
		animacionPinguino = false;
		estadoPinguino1 = true;
		estadoPinguino2 = false;
		estadoPinguino3 = false;
		estadoPinguino4 = false;
		estadoPinguino5 = false;
		estadoPinguino6 = false;
		estadoPinguino7 = false;
		estadoPinguino8 = false;
		contador = 1;
		contador2 = 1;
		movPataDerecha = 0.0f;
		movPataIzquierda = 0.0f;
		movPinguino_z = 0.0f;
		movPinguino_x = 0.0f;
		movPinguino_y = 0.0f;
		pataDerechaX = 0.0f;
		pataIzquierdaX = 0.0f;
		rotacionPinguino = 0.0f;
		estadoCabezaPinguino1 = true;
		estadoCabezaPinguino2 = false;
		rotacionCabezaPinguino = 0.0f;
		//Reset Huevo 2
		animacionTortuga2 = false;
		estadoAnim1 = true;
		estadoAnim2 = false;
		estadoAnim3 = false;
		estadoAnim4 = false;
		estadoAnim5 = false;
		tortuga_x = 0.0f;
		tortuga_y = 0.0f;
		tortuga_z = 0.0f;
		giroAletaDer = 0.0f;
		giroAletaIzq = 0.0f;
		movHuevo2 = 0.0f;
		orientacionTortuga2 = 0.0f;
		estadoAleta3 = true;
		estadoAleta4 = false;
		//Se pausa coche
		animacion = false;
	}
	//To play KeyFrame animation 
	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
