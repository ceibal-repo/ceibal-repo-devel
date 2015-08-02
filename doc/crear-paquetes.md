Generar clave GPG:

    gpg --gen-key
    gpg ---export -a "User Name" > user_name.public.gpg

Enviar clave GPG publica al administrador del repositorio. Para copiar la clave privada a otro equipo:

    gpg --export-secret-key -a "User Name" > user_name.private.gpg
    gpg --allow-secret-key-import --import user_name.private.gpg

Instalar requerimientos:

    apt-get install dh-make devscripts build-essential dbhelper

Para crear paquetes nativos (e.j. solo scripts y configuración):

    dh_make --native --indep

Al construir paquetes, especificar el profile para lintian:

    debuild -uc -us --lintian-opts --profile=ceibal

(Averiguar porque no funcionan los exports de .profile)

Crear una nueva version:

    dch -i --vendor ceibal


Receta 1: crear un paquete para fix
=======

1) En el directorio de trabajo (supongamos /home/usuario/devel), creo un directorio con el nombre del nuevo paquete. Utilizo el prefijo fix, para indicar que el objetivo de este paqute es la correcion de un bug, y que va ser dependencia de ceibal-update

    /home/usuario/devel/fix-paquete/


2) Dentro del directorio fix-paquete, creo un dir, sources, donde iran todos losarchivos de codigo del paquete y los necesarios para generar el .deb.

   /home/usuario/devel/fix-paquete/
                                  sources/
   

3) Trabajo dentro de sources, genero los archivo de codigo.

   /sources/
          script1.sh
          configuracion-ej.cfg
          .
          .

3.a) Creo un repo en el servidor de git

3.b) Inicializo el repo local en el directorio sources. (git init)

3.c) Agrego el repo creado en el git server como remote.

3.d) Pusheo los cambios.

 
4) Parado en sources ejecuto el script, ceibal-paquete-setup. Este script generar una seria de directorios y archivos minimos necesarios para la generacion del .deb, que luego deberan ser editados.   

    /sources/
            debian/
            Makefile
            script1.sh
            configuracion-ej.cfg
            .
            .     

Los siguientes son pasos basicos, pueden ser necesarios, algunos otros adicionales.

5) Edito el Makefile para generar la reglas de armado del .deb

6) Edito debian/postinst, para generar las acciones que desee ejecutar luego de la instalacion.


7) Genero una nueva version de prueba , dch -i --vendor ceibal


8) Genero un .deb de prueba, debuild -uc -us --lintian-opts --profile=ceibal


9) Luego del paso 8) se crearan varios paquete en el direcotrio fix-paquete, al mismo nivel que sources.

/home/usuario/devel/fix-paquete/
                                sources/
                                fix-paquete_0.1+nmu1.tar.gz
                                fix-paquete_0.1+nmu1_all.deb
                                fix-paquete_0.1+nmu1.dsc
                                .
                                .
10) Instalo el paquete para probarlo, en el ambiente de prueba, que puede una magallanes, una maquina virtual, no se aconseja instalarlo en la propia maquina de de desarrollo. La instalacion puede ser mediante, subia al repo y luego descarga por apt-get, o simplement copiandolo e instalandolo con dpkg -i


11) Se prueba, y en caso de ser necesaria una modificacion se repite desde el paso 7. Se iran creando nuevos paquetes incrementando el sufijo +nmu1, +nmu2.

 
                        
