# Configuracion de entorno de build

Las siguientes instrucciones son aplicables para crear un entorno de creacion de paquetes para cada desarrollador, asi como para configurar un servidor de build independiente que se utilice en el proceso de publicacion de paquetes, como se describe en [crear-paquetes.md].

Normalmente, para construir un paquete debian alcanza con utilizar el comando [`dpkg-buildpackage`](http://man7.org/linux/man-pages/man1/dpkg-buildpackage.1.html), sobre una estructura adecuada de archivos, como se descibe en el [manual de mantenimiento de Debian](https://www.debian.org/doc/manuals/maint-guide/build.en.html). Alternativamente, se puede utilizar [`debuild`](http://manpages.ubuntu.com/manpages/lucid/man1/debuild.1.html) que ejecuta validaciones sobre el paquete para verificar que se apegue a los estandares de Debian/Ubuntu. Sin embargo, ambas opciones construyen el paquete basados en la configuracion actual del equipo donde se ejecutan. Por lo tanto si, por ejemplo, el equipo tiene versiones viejas de una dependencia, o es un Ubuntu 14 cuando se quiere crear el paquete para Ubuntu 12, el paquete generado no sera el deseado.

Para evitar problema con la configuracion actual del equipo, se utiliza `pbuilder` que construye un entorno aislado donde instala todas las dependencias de la plataforma de destino para la que se genera el paquete (por ejemplo, una distribucion minima de Ubuntu 12, si esta es la plataforma destino).

## Instalar y configurar `pbuilder`

Instalar `ceibal-repo-devel`. El paquete depende de `pbuilder` e instala en `/etc/pbuilder*` los archivos de configuracion necesarios. Tambien configura el nombre y email usado al crear paquetes (`/etc/profile.d/ceibalrepo.sh`).

Crear entornos `i386` y `amd64` para `pbuilder`:

    sudo pbuilder create --configfile /etc/pbuilderrc.i386.ceibal
    sudo pbuilder create --configfile /etc/pbuilderrc.amd64.ceibal

Para paquetes que no son dependientes de la arquitectura, cualquiera de las dos opciones es valida, pero los paquetes seran generados con sufijo `amd64` de todos modos.

`ceibal-repo-devel` configura cron para actualizar automaticamente los entornos de pbuilder diariamente, pero el proceso se puede ejecutar manualmente via `ceibal-update-builder`. La actualizacion se asegura de que el entorno aislado este actualizado con los ultimos paquetes de la distribucion que utiliza.

## Probar construir paquetes

Dado un directorio con una estructura de paquetes valida, construir un paquete usando `pdebuild`:

    pdebuild --configfile /etc/pbuilderrc.i386.ceibal # para i386
    pdebuild --configfile /etc/pbuilderrc.amd64.ceibal # para amd64

Para ver los paquetes resultantes:

    ls /var/cache/pbuilder/precise-i386/result/*
    ls /var/cache/pbuilder/precise-amd64/result/*

Asumiendo que la distrubucion base es Ubuntu precise.
