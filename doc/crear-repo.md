# Creacion y configuracion del repositorio de paquetes

Este documento describe el proceso que se siguió para generar el repositorio de APT Ceibal. En caso de que sea necesario crear el repositorio desde cero, es posible usar este proceso para replicarlo, pero para agregar nuevos mirrors del repositorio o equipos de build se recomienda usar las imagenes Docker directamente.

## Configurar el repositorio

El proceso asume que el paquete ceibal-repo-devel esta instalado o accesible, ya que hace referencia a archivos de ejemplo incluidos en este paquete.

0. Esta disponible el script ceibal-setup-reposerver que realiza basicamente este procedmiento.

1. Crear estructura de directorios para el repositorio:

    $ sudo mkdir -p /srv/reprepro/ubuntu/{conf,dists,incoming,indices,logs,pool,project,tmpl}
    $ cd /srv/reprepro/ubuntu

*Copiar los archivos de configuracion* de ejemplo incluidos en ceibal-repo-devel a `/src/reprepro/ubuntu/conf/`:

    $ cp /usr/share/doc/ceibal-repo-devel/examples/reprepro.distributions /srv/reprepro/ubuntu/conf/distributions
    $ cp /usr/share/doc/ceibal-repo-devel/examples/reprepro.options /srv/reprepro/ubuntu/conf/options

Editarlos y modificar los campos que se considere necesario (nombre del repositorio, etc.).

2. Generar la clave GPG que se va a utilizar para firmar los paquetes del repositorio. Esta clave debería ser provista y administrada por Ceibal, y todos los repositorios deberían utilizar la misma.

En caso de poseer una clave privada provista por ceibal, se debe registrar la misma para `root`.

Para *crear una nueva clave* se debe tener `gpg` instalado y ejecutar (como `root`):

    $ gpg --gen-key

Luego seguir las instrucciones. Una vez completado el proceso, la clave sera guardada en el keyring de `root`. La clave puede verse ejecutando: 

    $ gpg --list-keys
    pub   4096R/BCACEF2D 2014-08-22
    uid                  Proyecto Ceibal (Repositorio APT Ceibal) <apt@plan.ceibal.edu.uy>
    sub   4096R/716EBEE6 2014-08-22

En el caso anterior, la clave esta asociada al email `apt@plan.ceibal.edu.uy` y tiene como ID `BCACEF2D`.

Para *exportar la clave publica*, ejecutar el siguiente comando usando la direccion de email asociada:

    $ gpg --armor --export apt@plan.ceibal.edu.uy --output ceibal.gpg.key > /srv/reprepro/ceibal.gpg.key

La clave exportada es la que deben importar los equipos para poder usar el repositorio.

Editar `/srv/reprepro/ubuntu/conf/distributions`, *configurar el ID de la clave GPG* usada para firmar los paquetes (en el ejemplo `BCACEF2D`) en el campo `SignWith`.

## Operaciones sobre paquetes

Una vez que se disponga de paquetes creados correctamente, se pueden *agregar paquetes al repositorio*:

    $ reprepro --basedir /srv/reprepro/ubuntu/ include tatu /home/saguiar/dev/hello/hello_world_0.1_amd64.changes

Donde `.changes` es creada via `debuild` o un comando similar, como se explica en [crear-paquetes.md]. `tatu` es el `Codename` del repositorio, tal como se configura en `/srv/reprepro/ubuntu/conf/distributions`.

Para agregar paquetes firmados por un desarrollador, es necesario *importar la clave publica del desarrollador* (generada al igual que la clave GPG para el repositorio):

     gpg --import developer1.public.gpg

Tambien se puede *eliminar un paquete*:

    reprepro --basedir /srv/reprepro/ubuntu/ remove tatu hello_world

Los paquetes pueden copiarse al repositorio manualmente, o utilizar los scripts de ceibal-repo-devel para publicarlos y construirlos automaticamente a partir de un repositorio, como se explica en [crear-paquetes.md].

## Configuraciones adicionales

Si se quiere conectarse al servidor del repositorio por SSH e importar paquetes y el servidor tiene instalado `gnupg2`, incluir en el archivo `~/.profile` del usuario que se este conectando la siguiente linea, para evitar errores al pedir el passphrase de la clave:

     export GPG_TTY=$(tty)

