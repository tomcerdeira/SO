# Implementación de un cliente-servidor

Se provee una implementación de un juego tipo _"capture the flag"_

Para compilar:
* Ubicarse en el directorio raíz
* Ejecutar el comando "make all"

A continuación se crearán dos archivos: _server_ y _client_

Para jugar:
* Abrir dos consolas y ubicarlas en el directorio raíz
* Desde una consola ejecutar `./server`
* Desde la otra, ejecutar `./client`

De esta manera, el servidor empezará a escuchar los mensajes que envíe el cliente.

Se proveé también un archivo _"respuestas.txt"_ con las **respuestas** a los desafíos.

Para testear el correcto funcionamiento del servidor se puede ejecutar el siguiente script:
`./server & while read line; do echo "$line"; sleep 2; done <respuestas.txt | ./client`

##### Observaciones
* Para usar _strace_ y que el desafío 6 tenga el comportamiento esperado se debe ejecutar de la siguiente manera `strace -f -D ./server`, o ejecutarlo en base al pid `strace --pid`
* En el directorio **quineDir** se encuentra el _quine.c_ necesario para uno de los desafíos