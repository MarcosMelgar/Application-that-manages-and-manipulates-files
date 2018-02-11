/*******************************************************************

  Fichero     senhal.h

  Resumen     MÃ³dulo para el manejo de seÃ±ales

  DescripciÃ³n MÃ³dulo para el manejo de senhales. Incluye la funciÃ³n que 
              inicializa las seÃ±ales y los distintos manejadores de seÃ±ales.

  Ver tambiÃ©n 

  Autor       Iria EstÃ©vez Ayres

  Copyright   [Copyright (c) 2016 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningÃºn tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentaciÃ³n para cualquier propÃ³sito siempre y cuando esta advertencia
  y los siguientes dos pÃ¡rrafos aparezcan en las copias.

  EN NINGÃšN CASO SE RECONOCERÃ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÃ‘OS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÃ“N, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÃ‘OS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÃFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÃAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÃCITAS
  DE LA COMERCIALIZACIÃ“N Y ADECUACIÃ“N PARA CUALQUIER PROPÃ“SITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÃ“N ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#ifndef SENHAL_H
#define SENHAL_H

/*****************************************************************************

  Resumen      Inicializa el mÃ³dulo.
  DescripciÃ³n  Vincula las seÃ±ales que se van a capturar por el programa
               con su correspondiente manejador de seÃ±ales.
  Ver tambiÃ©n  signal_handlers

******************************************************************************/
void inicialize_signal_handlers();




#endif
