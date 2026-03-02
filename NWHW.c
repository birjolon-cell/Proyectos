**FREE
ctl-opt dftactgrp(*no) actgrp(*caller) option(*nodebugio);

// Programa RPGLE que muestra "Hola mundo" en un display

dcl-s mensaje varchar(50) inz('Hola mundo');

// dsply es la forma más sencilla de enviar un mensaje al display
// en un programa interactivo.
dsply mensaje;

*inlr = *on;
return;