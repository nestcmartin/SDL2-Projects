# PRACTICA 2

## Creando el nuevo proyecto Practica2

**1.** Añadimos el archivo _pacman.png_ al directorio _bin/resources/images_.

**2.** Duplicamos el directorio _prj/Practica1_ y lo renombramos a _prj/Practica2_.

**3.** Renombramos los tres archivos de _prj/Practica2_.

**4.** Abrimos  los tres archivos de _prj/Practica2_ en un editor de texto y cambiamos todas las referencias de _Practica1_ a _Practica2_ (en Sublime Text 3 _Alt + H_ y _Replace All_).

**5.** Duplicamos el directorio _src/Practica1_ y lo renombramos a _src/Practica2_.

**6.** Abrimos el archivo _Asteroids.sln_ en Visual Studio 2019. Agregamos el proyecto _Practica2_ a la solución _Asteroids_.

**7.** Accedemos a las propiedades del proyecto _Practica2_ y modificamos el valor del campo _General>Directorio Intermedio_ a _$(SolutionDir)obj\\$(ProjectName)\\$(Platform)\\$(Configuration)\\_ para todas las configuraciones, plataforma Win32 (x86).

**8.** Accedemos a las propiedades del proyecto _Practica1_ y modificamos el valor del campo _General>Directorio Intermedio_ a _$(SolutionDir)obj\\$(ProjectName)\\$(Platform)\\$(Configuration)\\_ para todas las configuraciones, plataforma Win32 (x86).

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
	* mpl
* ecs
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

Antes de hacer nada, deberíamos cambiarle el nombre a la clase principal del juego: pasará de llamarse _PacMan_ a llamarse _Asteroids_; recuerda también cambiarle el nombre (y el tamaño, si lo deseas) a la ventana de SDL en esta misma clase. En la plantilla existen dos sistemas que podemos reutilizar y que nos servirán de base para dar los primeros pasos. Por una parte, _StarsSystem_ se asimila bastante a lo que podría ser nuestro _AsteroidsSystem_ o _BulletsSystem_, mientras que por otra, _PacManSystem_ podría interpretarse como _FighterSystem_.

### Factorías y Sistemas

El primer paso es crear las factorías de asteroides y de balas. Ambas clases, _AsteroidsPool_ y _BulletsPool_, se implementan como _Singleton_, y cuentan con un _ObjectPool_ de entidades como atributo; la diferenciación se produce en la constructora privada de ambas clases: en función de los componentes que se añadan aquí, estaremos creando un _pool_ de asteroides o de balas. La función _construct()_ de estas clases devuelve una entidad del _pool_ activada, estableciendo los parámetros iniciales de los componentes correspondientes. La función _destroy()_, por contra, devuelve una entidad al _pool_.
Una buena forma de hacer estas dos clases fácilmente es sobrescribir la clase _StarsPool_, que comparte la misma funcionalidad; recuerda cambiar las directivas de inclusión y otras posibles apariciones de la clase _StarsPool_ a lo largo del proyecto, incluyendo la inicialización del correspondiente _pool_ en la clase principal del juego.

Los componentes _Transform_, _ImageComponent_ y _Rotation_ ya vienen incluiddos en la plantilla, por lo que sólo tendremos que crear el componente _AsteroidLifeTime_ (se puede utilizar el archivo _LifeTime.h_ sobrescribiendo su funcionalidad), que mantiene el número de generaciones de un asteroide. Para añadir nuevos componentes al juego, debemos dirigirnos al archivo _ECS.h_, donde veremos varias listas y predeclaraciones. En el apartado de componentes, deberemos incluir _AsteroidLifeTime_ (o sustituir _LifeTime_). En el apartado de grupos, deberemos definir dos nuevos identificadores: _\_grp_Bullet_ y _\_grp_Asteroid_. En el apartado de sistemas, debemos incluir _AsteroidsSystem_ y _BulletsSystem_, que implementaremos a continuación.

Las clases _AsteroidsSystem_ y _BulletsSystem_ recogen la funcionalidad de las clases _AsteroidsPool_ y _BulletsPool_ del proyecto _Practica1_, con ciertas diferencias que radican en el manejo de la gestión de las entidades. Para comprender cómo funciona el gestor de entidades y cómo se implementan estos sistemas, se recomienda sobrescribir la clase _StarsSystem_. Una vez creados los sistemas, debemos añadirlos a la clase principal del juego y recordar inicializarlos y actualizarlos en el bucle principal.

### Manejadores y Renderizado

El segundo paso es recrear la funcionalidad del caza. Si bien el código de _PacManSystem_ es muy similar al que debería tener _FighterSystem_, existen ciertas particularidades que no debemos pasar por alto, como la no limitación de velocidad de _PacMan_. Es buena idea tomar como base _PacManSystem_ para crear _FighterSystem_, pero utilizando el código de _FighterCtrl_ y _FighterMotion_ del proyecto _Practica1_. Fíjate en que el manejador que se utiliza en _PacManSystem_ no es el mismo que deberías utilizar tú, así que ve al archivo _ECS.h_ y en el apartado de manejadores, cambia _\_hdlr_PacMan_ por _\_hdlr_Fighter_; recuerda cambiar el nombre en todos los archivos del proyecto. Podemos utilizar este manejador en _FighterGunSystem_ para acceder a los componentes del caza necesrios para la correcta implementación del sistema de disparo. Del mismo modo, necesitaremos acceso al método _shoot()_ de _BulletsSystem_.

Los componentes _Transform_ e _ImageComponent_ necesarios para el caza ya vienen incluidos en la plantilla, por lo que sólo tendremos que crear el componente _Health_, que mantiene el número de vidas del caza, así como la imagen (_Texture*_) que utilizamos para representarlas. Recuerda registrar el componente en el archivo _ECS.h_, así como incluir, inicializar y actualizar los sistemas del caza en la clase principal del juego. Es importante que _FighterGunSystem_ se inicialice después de _FighterSystem_, puesto que presenta una dependencia directa.

Si queremos empezar a ver avances en pantalla, tendremos que modificar _RenderSystem_. Este sistema se encarga de renderizar todos los elementos de nuestro juego en la ventana de SDL. En primer lugar, pinta todos los asteroides y las balas: debemos iterar los grupos de asteroides y balas llamando al método _draw()_ con cada una de las entidades como parámetro. Después debemos pintar el caza, al que podremos acceder a través del correspondiente manejador. En el método _draw()_ debemos distinguir entre el caza y el resto de entidades, dado que el caza necesitará, por un lado, un rectángulo fuente concreto, y por otro, renderizar las vidas que le queden; podemos utilizar el componente _Health_ como señalizador en este caso (_if (entity->getComponent<Health>() != nullptr) { ... }_). Después, se renderizan la puntuación y los mensajes.

### Comunicación entre Sistemas

La coordinación entre todos los sistemas de juego corre a cargo de _GameCtrlSystem_. Este sistema gestiona una sola entidad con los componentes _Score_ (para la puntuación) y _GameState_ (para el estado del juego: _running_, _game_over_, _win_). Registra ambos componentes en el archivo _ECS.h_, así como un nuevo manejador llamado _\_hdlr_GameState_ que utilizaremos para acceder al controlador del juego. 

Normalmente, las llamadas a los métodos de _GameCtrlSystem_ se realizarán desde _CollisionSystem_. El sistema de detección de colisiones también se encarga de llamar a los métodos correspondientes de _AsteroidsSystem_, _BulletsSystem_ y _FighterSystem_. Sigue el esquema propuesto en el enunciado para no cometer errores.

Recuerda realizar los ajustes necesarios en _RenderSystem_ para que se visualicen adecuadamente tanto la puntuación como los mensajes. Además, revisa el enunciado para saber si es necesario modificar el resto de sistemas (por ejemplo, permitir el movimiento del caza si el estado de juego no es _running_). Aprovecha esta revisión para incluir el audio del juego (música y efectos de sonido). Si todos los sistemas están incluidos, inicializados y actualizados correctamente en la clase _Asteroids_, el juego debería funcionar. ¡Bien!

### Gestión eficiente de la Memoria

Una de las clases que no hemos utilizado en todo el proyecto es _ObjectFactory_. Esta clase, como su propio nombre indica, es una factoría que, al igual que _AsteroidsPool_ o _BulletsPool_, utiliza un _pool_ para crear sus objetos. Sin embargo, no nos encontramos ante un _ObjectPool_ corriente, ya que esta factoría utiliza un _MemoryPool_, un _pool_ que permite la gestión eficiente de la memoria y evita la fragmentación.

Si queremos utilizar esta factoría, debemos especificarlo en la llamada al método correspondiente (generalmente, _addEntity()_ o _addComponent()_). Hasta ahora, la factoría por defecto para todos los componentes era _DefaultFactory_, pero si la cambiamos por _ObjectFactory_ podemos reducir drásticamente las llamadas a _new_ y _delete_. Tendremos que tener en cuenta, eso sí, que debemos inicializar todos y cada uno de los _pools_ de memoria, al igual que hacíamos con _AsteroidsPool_ o _BulletsPool_. 

### Revisión de inclusiones

No olvides peinar las inclusiones para agilizar el trabajo del compilador de Visual Studio. El esquema seguido en la plantilla, bastante intuitivo, es el siguiente:

* Librerías de C++
* Librerías de SDL
* Entidades
* Componentes
* Sistemas
* Recursos
* Utilidades
* Otros