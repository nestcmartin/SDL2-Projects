# PRACTICA 2

## Creación del nuevo proyecto Practica2

**1.** Añadimos el archivo _pacman.png_ al directorio _bin/resources/images_.

**2.** Duplicamos el directorio _prj/Practica1_ y lo renombramos a _prj/Practica2_.

**3.** Renombramos los tres archivos de _prj/Practica2_.

**4.** Abrimos  los tres archivos de _prj/Practica2_ en un editor de texto y cambiamos todas las referencias de _Practica1_ a _Practica2_ (en Sublime Text 3 _Alt + H_ y _Replace All_).

**5.** Duplicamos el directorio _src/Practica1_ y lo renombramos a _src/Practica2_.

**6.** Abrimos el archivo _Asteroids.sln_ en Visual Studio 2019. Agregamos el proyecto _Practica2_ a la solución _Asteroids_.

**7.** Accedemos a las propiedades del proyecto _Practica2_ y modificamos el valor del campo _General>Directorio Intermedio_ a $(SolutionDir)obj\$(ProjectName)\$(Platform)\$(Configuration)\ para todas las configuraciones, plataforma Win32.

**8.** Accedemos a las propiedades del proyecto _Practica1_ y modificamos el valor del campo _General>Directorio Intermedio_ a $(SolutionDir)obj\$(ProjectName)\$(Platform)\$(Configuration)\ para todas las configuraciones, plataforma Win32.

**9.** Establecemos _Practica2_ como proyecto de inicio.

**10.** Comprobamos que el proyecto _Practica2_ mantiene toda la funcionalidad de _Practica1_  compilando y ejecutando, en las configuraciones Debug y Release.


## Comparación de archivos existentes con la plantilla pacman_5

Como ya hemos comprobado que todo funciona, podemos borrar todos los archivos .cpp y .h del directorio _src/Practica2_; de igual modo, los elimianremos del proyecto _Practica2_ en Visual Studio. Es recomendable dejar el archivo _Main.cpp_ en una versión muy básica (por ejemplo, un "Hola Mundo") para que Visual Studio detecte _Practica2_ como un proyecto de C++ y mantenga la configuración establecida previamente.

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
	* ecs
	* Entity
	* Manager
	* mpl
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
	* SDL_Macros
	* Singleton
	* SRandBasedGenerator
	* Vector2D
* PacMan
* SDLGame
* Main

Se eliminan del proyecto y del directorio _src/Practica2_ los siguientes archivos por estar vacíos: _Transform.cpp_, _DefFactory.cpp_, _ObjectFactory.cpp_, _Objectpool.cpp_, _OFFactory.cpp_, _StarsPool.cpp_, _CollisionSystem.cpp_, _GameCtrlSystem.cpp_, _PacManSystem.cpp_, _RenderSystem.cpp_, _StarsSystem.cpp_, _System.cpp_ y _Singleton.cpp_.

Por último, realizamos una operción de comparación entre todos los archivos para decidir si nos quedamos con la versión de _Practica1_ o con la de _Practica2_. En algunos archivos la diferencia será únicamente de estilo (directivas de precompilación, nombres de variables o ficheros, etc.), pero en otros cambia por completo la funcionalidad; en estos casos nos quedaremos siempre con la versión de _Practica2_, y realizaremos los cambios estéticos oportunos sobre ella. En esta lista se muestran los archivos (_.cpp_ y _.h_) seguidos de la versión (1 para _Practica1_ y 2 para _Practica2_) que debemos conservar:

* Component					1
* ImageComponent			1
* LifeTime					1
* Rotation					1
* Score						1
* Transform					1
* DefFactory				1
* ecs						1
* Entity					1
* Manager					1
* mpl						1
* ObjectFactory				1
* ObjectPool				1
* OFFactory					1
* StarsPool					1
* CollisionSystem			1
* GameCtrlSystem			1
* PacManSystem				1
* RenderSystem				1
* StarSystem				1
* System					1
* AudioManager				1
* Font						1
* FontsManager				1
* Resources					1
* SDLAudioManager			1
* SDLFontsManager			1
* SDLTexturesManager		1
* Texture					1
* TexturesManager			1
* checkML					1
* Collisions				1
* InputHandler				1
* jute						1
* RandomNumberGenerator		1
* SDL_Macros				1
* Singleton					1
* SRandBasedGenerator		1
* Vector2D					1
* PacMan					1
* SDLGame					1
* Main						1

