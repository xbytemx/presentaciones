---
title: 'Backdooring Linux'
theme: 'night.css'
highlightTheme: monokai
css: 'style.css'
template: 'template.html'
revealOptions:
    transition: 'slide'
    controls: false

---
<!-- .slide: data-background="./img/portada.png"; data-background-opacity="0.50";-->
## Backdooring Linux
#### Tony Palma
---


<!-- .slide: style="text-align: left;" -->
### About Me

Consultor de Ciberseguridad at ksquareinc, casado, 31 años

- Entusiasta de la ciberseguridad
- RE at Mayas National CTF Team
- FLOSS - Debian <3
- **HackTheBox**
- Cybersecurity For Fun
- *Disfrutar un buena taza de café*
---


### Objetivo

> Revisar algunos ejemplos practicos de como lucen los backdoors en linux
---


### Agenda
1. ¿Qué es un backdoor?
2. ¿Que tipos de backdoors podemos encontrar?
3. Maquina virtual de pruebas
4. Reptile Wins.
5. BONUS: Analisis forense de una maquina comprometida
---


<!-- .slide: data-background="./img/titles.png"; -->
### ¿Qué es un backdoor?
---


![Backdoor Open](./img/backdoor1.jpeg)
---


### Conceptos interesantes
* Puerta trasera; nueva o existente
* Post-comprometida
* Persistencia
* knock knock?
* proceso, módulo o estático
---


<!-- .slide: data-background="./img/titles.png"; -->                                             
### ¿Que tipos de backdoors podemos encontrar?
---  


### Backdooring
* `.ssh/authorized_keys`
* `.bashrc`, `.bash_aliases` and friends
* /var/www/html/$(generate-a-random-backdoor-name-here).php
* /var/spool/cron/crontabs/${USER}/hello-im-a-backdoor
* `systemctl --user enable im-a-user-backdoor.service`
* msfvenom blahblah >> `.local/bin/wget`
---


### Permisos
Si la máquina no ha sido comprometida a nivel de root, podemos aplicar permisos sobre archivos importantes de configuracion para que no se comprometa por completo.
---


### Monitoreo
Estar monitoreando de manera continua estos archivos nos permite enterarnos de los cambios en el sistema. Inclusive si un atacante deshabilita nuestro sistema de monitoreo, ganamos tiempo de respuesta ante un incidente.
---


### Se solicita de su colaboración!
---


### 
---


### 
---


<!-- .slide: data-background="./img/titles.png"; -->
### Playground!
---


## Muchas gracias por asistir
#### ¿Preguntas?
