---
title: 'Reversing 101'
theme: night
highlightTheme: monokai
revealOptions:
    transition: 'slide'
---
## Reversing 101
#### Tony Palma
---


<!-- .slide: style="text-align: left;"> -->
### About Me

Me dedico a la consultoría de TI, casado, 31 años.

- Entusiasta de infosec
- CTF Player (Mayas)
- FLOSS
- HTB
- *Disfrutar una buena taza de café* **o una cerveza bien fria**.

---


<!-- .slide: style="text-align: left;"> -->
### Cual es el plan?

El plan es hablar un poco sobre reverse engineering, enfocado a binarios en formato ELF.

No planeo que hagamos reversing de un malware, la idea es mas como aprender los conceptos base.

---


<!-- .slide: style="text-align: left;"> -->
### Agenda

* Teoría necesaria (diapositivas hasta acá)
* Crear y compilar un hola mundo en C
* Reversear el programa conociendo el código
* Crear un programa en C que use funciones y reversearlo
* Resolver unos ejercicios basicos de IOLI

---


<!-- .slide: style="text-align: left;"> -->
### Arquitectura de computadoras

* Sistema binario y sistema hexadecimal
* bit(2¹), byte(8 bits), word(2 bytes), dword(4 bytes, 32bits), qword(8 bytes, 64bits)
* AL (byte), AX (word), EAX (dword), RAX (qword)


---


### Arquitectura de computadoras
![Diagrama de registros](/img/arq_x86.png)

---


<!-- .slide: style="text-align: left;"> -->
### Instrucciones de x86
* Sintaxis AT&T and Intel
* Registros de proposito general (GPR) 32bits
  - EAX, EBX, ECX y EDX
  - ESP y EBP
  - EDI y ESI
* Registros de segmento (16 bits)
* Registros de Flags (CF, PF, AF, ZF, SF, TF, IF, DF, OF, IOPL, NT)

---


<!-- .slide: style="text-align: left;"> -->
### Instrucciones de x86
* Instrucciones de operaciones arimeticas (sum, sub, mul, div)
* Instrucciones de operaciones no arimeticas (not, and, or, xor) 
* Instrucciones de movimiento (mov, pop, push, xchg)
* Instrucciones de flujo (jmp, je, jne, jg, jl, jge, jle, retn)

---


### Reverse Engineering
![Reverse Engineering](/img/Reverse_Engineering.gif)

---


<!-- .slide: style="text-align: left;"> -->
### Formatos de ejecución de archivos
* Windows: PE, PE32, PE32+, MZ, COM
* Unix: ELF, SOM, PEF, a.out
* COFF (Common Object File Format)

---


<!-- .slide: style="text-align: left;"> -->
### Conceptos interesantes
* Headers
* Linker
* Secciones
* Compilado vs interpretado
* Estatico vs dinamico

---


<!-- .slide: style="text-align: left;"> -->
### Sobre las secciones
* .data (Datos inicializados)
* .text (Instrucciones o codigo)
* .interp (linker)

---


<!-- .slide: style="text-align: left;"> -->
### Import Table
La tabla de importaciones (IT) contiene un array de estructuras Image
Import Descriptor (IID) donde cada una de estas contiene los siguientes
campos:

1. OriginalFirstThunk: Contiene un puntero hacia la dirección de memoria donde se encuentran los nombres de las funciones a cargar de la librerı́a, este array al que apunta nunca cambia, se mantiene original.
2. TimeDateStamp, ForwarderChain: Actualmente están obsoletos y no se suelen utilizar.

---


<!-- .slide: style="text-align: left;"> -->
### Import Table (2/2)

3. Name: Apunta a la dirección del string del nombre del fichero de la librerı́a (DLL).
4. FirstThunk: Contiene un puntero a la dirección de memoria que va a ser modificada por el sistema operativo cuando se cargue la aplicación y contendrá los punteros a las funciones de la librerı́a referida ya cargada en memoria (estas direcciones compondrán la IAT para una librerı́a).

