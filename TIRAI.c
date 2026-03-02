**FREE
ctl‑opt dftactgrp(*no) actgrp(*caller) option(*nodebugio);

/* arreglo de flujos, primera posición = periodo 0 */
dcl‑s flows     dim(10) packed(15:5) inz;
dcl‑s input     varchar(20);
dcl‑s msg       varchar(80);

dcl‑s irr       packed(7:5);
dcl‑s npv       packed(31:15);
dcl‑s diff      packed(31:15);

dcl‑s i         int(10);

/* calcula el VAN para una tasa dada */
dcl‑proc calcnpv export;
  dcl‑pi *n packed(31:15) rate packed(7:5); end‑pi;
  dcl‑s sum packed(31:15) inz(0);
  dcl‑s j int(10);

  for j = 1 to %elem(flows);
     /* j‑1 porque el primer flujo es t=0 */
     sum += flows(j) / %power( (1 + rate) : (j - 1) );
  endfor;

  return sum;
end‑proc;

/* lectura de los 10 flujos */
for i = 1 to 10;
   msg = 'Ingrese flujo #' + %char(i) + ' :';
   dsply msg input;           // dsply con segundo parámetro lee la entrada
   flows(i) = %dec(input:15:5);
endfor;

/* método de Newton simple para encontrar la raíz npv(rate)=0 */
irr = 0.10;                    // suposición inicial 10%
dow 1;
   npv = calcnpv(irr);
   if %abs(npv) < 0.0000001;   // tolerancia
      leave;
   endif;
   /* derivada aproximada */
   diff = (calcnpv(irr + 0.0000001) - npv) / 0.0000001;
   irr = irr - npv / diff;
enddo;

/* muestra la TIR */
msg = 'TIR = ' + %char(%editc(irr:'X':'0':'*'));
dsply msg;

*inlr = *on;
return;