# PRACTICA 2

## Creando el nuevo proyecto Practica2

**1.** Añadimos el archivo _pacman.png_ al directorio _bin/resources/images_.

**2.** Duplicamos el directorio _prj/Practica1_ y lo renombramos a _prj/Practica2_.

**3.** Renombramos los tres archivos de _prj/Practica2_.

**4.** Abrimos  los tres archivos de _prj/Practica2_ en un editor de texto y cambiamos todas las referencias de _Practica1_ a _Practica2_ (en Sublime Text 3 _Alt + H_ y _Replace All_).

**5.** Duplicamos el directorio _src/Practica1_ y lo renombramos a _src/Practica2_.

**6.** Abrimos el archivo _Asteroids.sln_ en Visual Studio 2019. Agregamos el proyecto _Practica2_ a la solución _Asteroids_.

**7.** Accedemos a las propiedades del proyecto _Practica2_ y modificamos el valor del campo _General>Directorio Intermedio_ a _$(SolutionDir)obj\\$(ProjectName)\\$(Platform)\\$(Configuration)\\_ para todas las configuraciones, plataforma Win32.

**8.** Accedemos a las propiedades del proyecto _Practica1_ y modificamos el valor del campo _General>Directorio Intermedio_ a _$(SolutionDir)obj\\$(ProjectName)\\$(Platform)\\$(Configuration)\\_ para todas las configuraciones, plataforma Win32.

**9.** Establecemos _Practica2_ como proyecto de inicio en el explorador de soluciones de Visual Studio.

**10.** Comprobamos que el proyecto _Practica2_ mantiene toda la funcionalidad de _Practica1_  compilando y ejecutando, en las configuraciones Debug y Release.


## De la plantilla pacman_5 a Practica2

Como ya hemos comprobado que todo funciona, podemos borrar todos los archivos .cpp y .h del directorio _src/Practica2_; de igual modo, los eliminaremos del proyecto _Practica2_ en Visual Studio. Es recomendable dejar el archivo _Main.cpp_ en una versión muy básica (por ejemplo, un "Hola Mundo") para que Visual Studio detecte _Practica2_ como un proyecto de C++ y mantenga la configuración establecida previamente, o copiar el código de _main.cpp_ de la plantilla _pacman_5_.

A continuación, añadimos todos los archivos de la plantilla _pacman_5_ al proyecto _Practica2_; es recomendable copiar previamente todos los archivos al directorio _src/Practica2_. Distribuimos los archivos agregados entre los distintos filtros, de modo que el proyecto _Practica2_ quedará con esta distribución en el explorador de soluciones de Visual Studio:

* Components
	* Component
	* ImageComponent
	* LifeTime
	* Rotation
	* Score
	* Transform
* Entities
	* DefFactory
	* Entity
	* Manager
	* ObjectFactory
	* ObjectPool
	* OFFactory
	* StarsPool
* Systems
	* CollisionSystem
	* GameCtrlSystem
	* PacManSystem
	* RenderSystem
	* StarSystem
	* System
* Resources
	* AudioManager
	* Font
	* FontsManager
	* Resources
	* SDLAudioManager
	* SDLFontsManager
	* SDLTexturesManager
	* Texture
	* TexturesManager
* Utils
	* checkML
	* Collisions
	* InputHandler
	* jute
	* RandomNumberGenerator
	* SDL_macros
	* Singleton
	* SRandBasedGenerator
	* Vector2D
* ecs
* mpl
* PacMan
* SDLGame
* Main

Se eliminan del proyecto y del directorio _src/Practica2_ los siguientes archivos por estar vacíos: _Transform.cpp_, _DefFactory.cpp_, _ObjectFactory.cpp_, _Objectpool.cpp_, _OFFactory.cpp_, _StarsPool.cpp_, _CollisionSystem.cpp_, _GameCtrlSystem.cpp_, _PacManSystem.cpp_, _RenderSystem.cpp_, _StarsSystem.cpp_, _System.cpp_ y _Singleton.cpp_.

Ahora realizamos una operción de comparación entre todos los archivos para decidir si nos quedamos con la versión de _Practica1_ o con la de _Practica2_. En algunos archivos la diferencia será únicamente de estilo (directivas de precompilación, nombres de variables o ficheros, etc.), pero en otros cambia por completo la funcionalidad; en estos casos nos quedaremos siempre con la versión de _Practica2_, y realizaremos los cambios estéticos oportunos sobre ella. Los únicos archivos que podemos conservar son los que se encuentran en el filtro _Resources_, aunque con algunas modificaciones: todos los métodos heredados ahora se declaran como _override_. Además, en todos los métodos en los que _Font_ se pasaba por referencia ahora se pasa como puntero (_Font*_). No olvide añadir la nueva imagen _pacman.png_ a los recursos.

Renombramos algunos archivos para clarificar su funcionalidad. Estos cambios de nombre afectan no solo al nombre del fichero, sino también a las directivas de inclusión (en caso de tratarse de un .h) y a los nombres de las clases o espacios de nombres y sus respectivas directivas de precompilación (los nombres de los _#ifndef_). Los archivos renombrados son:

* DefFactory -> DefaultFactory
* ecs -> ECS
* Manager -> EntityManager
* OFFactory -> MemoryPool
* mpl -> MPL
* sdl_macros -> SDL_Macros

Ahora podemos aplicar los cambios estéticos que consideremos necesarios. Una vez hayamos acabado, compilamos el proyecto _Practica2_ y lo ejecutamos; si el juego _Stars_ funciona correctamente, podemos concluir con esta sección. Como producto obtendremos la plantilla base sobre la que realizar toda la práctica: _TPV2_Template_2_. La plantilla _pacman_5_ se conservará en el directorio _src_ para futuras referencias.


## Asteroids 2.0

