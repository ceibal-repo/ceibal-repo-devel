1) Si llega a fallar la publicacion, ejecutando ceibal-publish, en algun punto del final del proceso,  por ej, al ingresar la passphrase de la clave PGP, el paquete queda en un estado, no espereado y si intentamos republicarlo va a fallar tambien. Tenemos que deregistrarlo. 

reprepro --basedir /srv/reprepro/ubuntu/ deleteunreferenced

O alternativamente, se puede exportar el repositorio:

reprepro --basedir /srv/reprepro/ubuntu/ export

2) Se aconseja siempre en lo posible, publicar para ambas arquitecturas, sin pasar el siwtch -a a ceibal-publish

Por ej:

    ceibal-publish -n tatu-hello -v 0.21

3) Para evitar ingresar la passphrase de gpg demasiadas veces al hacer export, se puede utilizar el gpg-agent.
