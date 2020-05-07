Para ejecutar un programa desde la consola en Windows:


* Compilar el programa en Visual Studio

* Abrir una consola (Pulsar Window+R, teclar "cmd" y hacer clic sobre OK --- si no funciona busca en google "open command prompt windows")

* Entrar en el directorio de proyecto:        

       cd C:\dir1\dir2\TPV2 
       donde C:\dir1\dir2\TPV2 es la ruta del proyecto

* Ejecutar el programa (donde TPV2Debug.exe es el programa (esto depende del nombre del proyecto  en Visual Studio):

       bin\TPV2Debug.exe server 2000
       bin\TPV2Debug.exe client localhost 2000

   

Otra posibilidad es crear en archivo BAT y ejecutarlo como cualquier otro programa (es decir con doble clic sobre el nombre en el *File Explorer*). Crear un archivo de texto con el nombre CLIENT.BAT (CLIENT puede ser cualquier nombre, el  importante es la extensión BAT) con el siguiente contenido
    
       cd C:\dir1\dir2\TPV2 
       bin\TPV2Debug.exe client localhost 2000
    
Hacer lo mismo con SERVER.BAT pero ejecutando la linea del servidor. Ahora  se puede ejecutar con doble clic sobre el CLIENT.BAT y SERVER.BAT en el *File Explorer*. Mejor poner los archivos BAT dentro la carpeta del proyecto, pero no es necesario.

**IMPORTANTE**: antes de compilar, hay que parar el programa que está ejecutando desde la consola, si no Visual Studio quejaría de que el programa está en uso.