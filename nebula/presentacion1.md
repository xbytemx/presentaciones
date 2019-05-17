---
title: 'Nebula @ Exploit.Education'
theme: night
highlightTheme: monokai
revealOptions:
    transition: 'fade'
---
## Nebula from Exploit.Education
#### Tony Palma
---


### About Me

Me dedico a la consultoria de TI, casado, 30 años.

> Me gusta/apasiona: 
> - Aprender de seguridad
> - Resolver retos (CTF)
> - FLOSS
> - **HackTheBox**
> - *Tomar un buena taza de café*

---


### Objetivo

> Resolver todos los niveles de Nebula (Exploit.Education)

---


### Pasos generales

0. Leer la documentacion de Nebula en Exploit.Education
1. Descargar el iso de Nebula
2. Crear una VM
3. Resolver cada reto

---


### Exploit.Education

- vulnerability analysis
- exploit development
- software debugging
- binary analysis
- general cyber security issues

---


### Nebula
Nebula es en si una imagen ISO de un sistema operativo con vulnerabilidades simples e intermedias que tienen enfoque en:

- Escalacion de privilegios en Linux
- Problemas comunes sobre scripts
- Condiciones de ejecución en el *file system*
- y más.

En general, es una muy buena maquina para comenzar a explorar vulnerabilidades de Linux.

---


### ISO? Live?

Como mencione anteriormente, Nebula es una imagen ISO por lo que es necesario utilizar un hipervisor para poder ejecutarla. Al iniciar la Maquina Virtual, debemos considerar lo siguiente:

- Memoria: 1G
- vCores: 1 (x86\_64)
- No requiere Hard Drive

---


### Notas (1/2)

Antes de pasar al tema del hipervisor, tengo algunas notas que compartir:

- El usuario por defecto es **nebula:nebula**, usuario y password.
- El usuario `nebula` puede ser root en cualquier momento via `sudo -s`

----


### Notas (2/2)

- Todos los usuarios donde nos enfocaremos tienen el nombre del nivel; level00, level01, etc.
- El objetivo de cada nivel es escalar de levelXX a flagXX; level00 hacia flag00
- Para cada usuario levelXX, su contraseña respectiva es levelXX
- Una vez que seamos flagXX debemos ejecutar con exito getflag (nos indicara con un mensaje si hemos tenido exito)

---


### QEMU and KVM

En mi caso particular y como tambien ejercicio de aprendizaje, he utilizado `qemu` como hipervisor, ya que encontre estas rapidas ventajas:

- Un solo comando crea y cuando termina destruye la VM
- Asocio el proceso de la VM con un puerto en el host, que hace NAT hacia el puerto SSH de la VM (Vault)

---


### Download and run

```
$ wget https://github.com/ExploitEducation/Nebula/\
releases/download/v5.0.0/exploit-exercises-nebula-5.iso
$ sha1sum exploit-exercises-nebula-5.iso | grep \
e82f807be06100bf3e048f82e899fb1fecc24e3a
$ qemu-system-x86_64 -m 1024 -boot d -cdrom \
exploit-exercises-nebula-5.iso -vga std \
-enable-kvm -net nic -net user,hostfwd=tcp::10022-:22
$ ssh nebula@localhost -p10022 
```

---


## Level00
----


Como este es el nivel inicial, el usuario / contraseña es **level00** / **level00**. El hit que tenemos para el nivel 1 es:
----


> This level requires you to find a Set User ID program that will run as the “flag00” account. You could also find this by carefully looking in top level directories in / for suspicious looking directories.

> Alternatively, look at the find man page.

----


## Solution
----


<pre class="stretch"><code data-trim>
$ find / -perm -4000 -user flag00 2>/dev/null 
# getflag
</code></pre>

La descripción del reto ya nos decia un poco acerca de donde seguir la pista, debiamos usar el comando `man` y buscar como usar `find` para que para encontrar el ejecutable con SUID de flag00 desde el directorio root hasta lo mas profundo que podamos. En mi caso mando todos los mensajes de error a */dev/null*

---


## Level01
----


Ingresamos como user/pass, **level01/level01**, y nos movemos a la carpeta de /home/flag01, aqui debemos encontrar un binario generado con el siguiente codigo:
----


```c
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
  gid_t gid;
  uid_t uid;
  gid = getegid();
  uid = geteuid();

  setresgid(gid, gid, gid);
  setresuid(uid, uid, uid);

  system("/usr/bin/env echo and now what?");
}
```
<!-- .element: class="stretch" -->

----


## Solution
----


Como pudimos ver, el binario env ejecuta confiando de las variables, el comando `echo` y le pasa a `echo` los parametros del string que mostrará en pantalla. Abusamos de la variable $PATH que hereda de quien ejecuta el binario (geteuid, getegid) y cambiamos donde encontrara a `echo`. Para ello, `echo` sera un script de `bash` que ejecute bash interactivo (`bash -i`)

```
$ printf '#!/bin/bash\nbash -i' > /tmp/echo
$ PATH="/tmp/:$PATH" flag01
# getflag
```
<!-- .element: class="stretch" -->

---


## Level02
----


El level02, es muy parecido a level01; accedemos con **level02/level02** y todo lo que necesitamos se encuentra en la carpeta `/home/flag02/`. Aqui encontraremos el binario del siguiente codigo fuente:

----


```c
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
  char *buffer;

  gid_t gid;
  uid_t uid;

  gid = getegid();
  uid = geteuid();

  setresgid(gid, gid, gid);
  setresuid(uid, uid, uid);

  buffer = NULL;

  asprintf(&buffer, "/bin/echo %s is cool", getenv("USER"));
  printf("about to call system(\"%s\")\n", buffer);
  
  system(buffer);
}
```
<!-- .element: class="stretch" style="font-size: 0.49em !important;" -->

----


## Solution
----



---


## Level03

----

Para el level03, tenemos que ir al directorio de */home/flag03* y ahi encontraremos todo lo que necesitamos. Hemos de saber también que existe un cronjob trabajando en esta carpeta, por lo que hay que entender la mecanica de lo que sucede.

----


## Solution

---


## Level04

----


Para este nivel, necesitamos leer un archivo **token**, el cual se encuentra en */home/flag04* bajo la propiedad de flag04. Existe un programa que podemos ejecutar en dicha carpeta, del cual tenemos afortunadamente su codigo fuente:

----


```c
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
  char buf[1024];
  int fd, rc;

  if(argc == 1) {
      printf("%s [file to read]\n", argv[0]);
      exit(EXIT_FAILURE);
  }

  if(strstr(argv[1], "token") != NULL) {
      printf("You may not access '%s'\n", argv[1]);
      exit(EXIT_FAILURE);
  }

  fd = open(argv[1], O_RDONLY);
  if(fd == -1) {
      err(EXIT_FAILURE, "Unable to open %s", argv[1]);
  }

  rc = read(fd, buf, sizeof(buf));
  
  if(rc == -1) {
      err(EXIT_FAILURE, "Unable to read fd %d", fd);
  }

  write(1, buf, rc);
}
```
<!-- .element: class="stretch" style="font-size: 0.35em !important;" -->

----


## Solution

---


## Level05

----


Para el level05, debemos buscar una mala asignacion de permisos a los archivos y carpetas que estan dentro de */home/flag05*.

----

 
## Solution

---


## Level06

----


Parece que las credenciales de **flag06** se encuentran en un formato legacy de unix. Hay que buscar como explotar este formato desde level06 hacia flag06.

----


## Solution

---


## Level07

----


En el level07, tenemos que el usuario flag07 ha escribio una aplicacion web para hacer ping y probar si un host es alcanzable. Afortunadamente nos hemos hecho con una copia de el programa que se ejecuta desde **flag07**.

----


```perl
#!/usr/bin/perl

use CGI qw{param};

print "Content-type: text/html\n\n";

sub ping {
  $host = $_[0];

  print("<html><head><title>Ping results</title></head><body><pre>");

  @output = `ping -c 3 $host 2>&1`;
  foreach $line (@output) { print "$line"; }

  print("</pre></body></html>");
  
}

# check if Host set. if not, display normal page, etc

ping(param("Host"));
```
<!-- .element: class="stretch" style="font-size: 0.56em !important;" -->

----


## Solution

---


## Level08

----


Para level08, debemos buscar en la carpeta */home/flag08* por archivos que nos permitan hacernos de la cuenta de flag08. Como recomendación, nos dicen que busquemos por archivos que cualquier usuario puede leer.

----


## Solution

---


## Level09

----


En el level09, encontraremos un programa escrito en C, que tiene la labor de ser el wrapper del siguiente codigo en php. Nuestro objetivo es usar todo lo que se encuentre disponible en */home/flag09* para escalar.

----


```php
<?php

function spam($email)
{
  $email = preg_replace("/\./", " dot ", $email);
  $email = preg_replace("/@/", " AT ", $email);
  
  return $email;
}

function markup($filename, $use_me)
{
  $contents = file_get_contents($filename);

  $contents = preg_replace("/(\[email (.*)\])/e", "spam(\"\\2\")", $contents);
  $contents = preg_replace("/\[/", "<", $contents);
  $contents = preg_replace("/\]/", ">", $contents);

  return $contents;
}

$output = markup($argv[1], $argv[2]);

print $output;

?>
```
<!-- .element: class="stretch" style="font-size: 0.49em !important;" -->

----


## Solution

---


## Level10

----


## Solution

---


## Level11

----


## Solution

---


## Level12

----


## Solution

---


## Level13

----


## Solution

---


## Level14

----


## Solution

---


## Level15

----


## Solution

---


## Level16

----


## Solution

---


## Level17

----


## Solution

---


## Level18

----


## Solution

---


## Level19

----


## Solution

---


# Muchas gracias por asistir
## ¿Preguntas?
