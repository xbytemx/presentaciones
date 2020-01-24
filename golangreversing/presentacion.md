---
title: 'Reverse Engineering GO binaries'
theme: night
highlightTheme: monokai
css: 'style.css'
template: 'template.html'
revealOptions:
    transition: 'slide'
    controls: false

---
<!-- .slide: data-background="./img/portada.png"; data-background-opacity="0.50";-->
## (RE)Go binaries
#### Tony Palma
---


<!-- .slide: style="text-align: left;" -->
### About Me

Consultor de TI, casado, 31 años

- Entusiasta de la ciberseguridad
- RE at Mayas National CTF Team
- FLOSS - Debian <3
- **HackTheBox**
- Cybersecurity For Fun
- *Disfrutar un buena taza de café*
---


### Objetivo

> Presentar algunos ejemplos practicos de cómo un reverse engineer hace aproximaciones al código fuente que genero un binario.
---


### Agenda
1. ¿Qué es Reverse Engineering?
2. ¿Cómo se generan los programas en go?
3. Mi primer 'Hola mundo'
4. Herramientas de RE
5. BONUS: Facebook CTF 2019: go\_get\_the\_flag
---


<!-- .slide: data-background="./img/titles.png"; -->
### ¿Qué es Reverse Engineering?
---


### Reverse Engineering
![Reverse Engineering](/img/Reverse_Engineering.gif)
---


### Conceptos interesantes
* Headers
* Linker
* Secciones
* Compilado vs interpretado
* Estatico vs dinamico
---


### Sobre las secciones
* .data (Datos inicializados)
* .text (Instrucciones o codigo)
* .interp (linker)
---


### Import Table
La tabla de importaciones (IT) contiene un array de estructuras Image Import Descriptor (IID) donde cada una de estas contiene los siguientes campos:
- OriginalFirstThunk: Contiene un puntero hacia la dirección de memoria donde se encuentran los nombres de las funciones a cargar de la librerı́a, este array al que apunta nunca cambia, se mantiene original.
---


<!-- .slide: data-background="./img/titles.png"; --> 
### ¿Cómo se generan los programas en go?
---


### Se solicita de su colaboración!
---


### Características de GOLANG
- defer. Las llamadas a las funciones pueden ser puestas en espera y apiladas
- goroutines. Concurrencia al estilo CSP (comunicación y sincronización)
- reflection. Permite la evaluación del tipo de dato sobre la ejecución
---


### goroutines
- Segmented Stacks
- runtime\_morestack en cada función
- Threads mucho más pesados, porque se reserva más memoria por la multiplezación del stack.
---


<!-- .slide: data-background="./img/titles.png"; -->
### Hola mundo!
---


### Hello world
```golang
package main
import "fmt"

func main() {
    fmt.Println("Hola, Mundo!")
}
```
---


### Build time
```bash
$ go build -o hola-stripped -ldflags "-s" hola.go
$ go build -o hola-normal hola.go
```
---


<!-- .slide: data-background="./img/titles.png"; -->
### Herramientas de RE
---


### A simple crackme
```go
package main;

import (
    "fmt";
    "os";
    "bufio";
)

func main() {
    fmt.Print("Enter Password: ");
    user_input,_,err := bufio.NewReader(os.Stdin).ReadLine();
    if err != nil {
            fmt.Println("Something is wrong with your computer, ",err);
    }
    if string(user_input) == "golangmid" {
        fmt.Println("Win!");
    } else {
        fmt.Println("Try harder");
    }
}
```
<!-- .element: class="stretch" style="font-size: 0.50em !important;" -->
---


### IDA Pro

La mejor herramienta comercial del mercado.

Tiene una versión FREE pero limitada a analizar estáticamente con algunas funciones de debugging, eliminando la función de decompilado.

---


### Radare2

Mi herramienta favorita, tiene todo lo que se necesita para reversear aplicaciones de cualquier tipo. Su punto más débil es su curva de aprendizaje, inclusive XKCD tiene un comic sobre eso. También su debugger en windows no es muy bueno.

---


### Ghidra

El nuevo chico en la cuadra. Fue la herramienta que por muchos años uso y desarrollo la NSA para protegerse del malware. Escrita en Java (sad) tiene uno de los decompiladores más poderosos de manera gratuita. IDA se esta poniendo pilas!

---


### Tiempo de reversear
Probaremos estas tres herramientas con los tres binarios que hemos generado para ver que tanto podemos obtener sin el código fuente.

---


## Muchas gracias por asistir
#### ¿Preguntas?
