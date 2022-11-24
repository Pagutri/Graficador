/**********************************
*     GRAFICADOR DE FUNCIONES     *
*                                 *
* Salma Patricia Gutiérrez Rivera *
* Maestría en Computación         *
* salma.gutierrez@cimat.mx        *
* agosto 2022                     *
**********************************/

#include <iostream>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include "fparser.hh"
using namespace std;

int main()
{
char funcion[20];
int i;
int width = 500;
int height = 500;
int divisiones = 10;
int puntos = 50;
float a, b, avancex, avancey, minf, maxf;
/* Variables utilizadas para dibujar la cuadrícula
   sobre la que se graficará la función */
float ejex = width - (width / 8);
float ejey = height / 8;
float origenx = width / 8;
float origeny = height - (height / 8);
float metrica_ejex = (ejex - origenx) / divisiones;
float metrica_ejey = (origeny - ejey) / divisiones;
float metricax[divisiones + 1];
/**********************************************/
float fdex[puntos];
float misxs[puntos];
double variable[1];
std::string s[divisiones + 1];
FunctionParser fp;

printf("Escribe la función, inicio y final del dominio a graficar:\n");
scanf("%s %f %f", funcion, &a, &b);

fp.Parse(funcion, "x");
avancex = abs(b - a) / puntos;

// Evaluar la función
for(i = 0; i < puntos; i++)
  {
  misxs[i] = a + (avancex * i);
  variable[0] = {misxs[i]};
  fdex[i] = fp.Eval(variable);
  }

/* Encontrar los valores máximos y mínimos de la función
 en el rango dado para etiquetar el eje 'y' de la gráfica*/
minf = maxf = fdex[0];
for(i = 1; i < puntos; i++)
  {
  if(fdex[i] < minf)
    {
    minf = fdex[i];
    }
  if(fdex[i] > maxf)
    {
    maxf = fdex[i];
    }
  }

// Inicialización de la superficie de pintado y el lienzo.
cairo_surface_t *surface;
cairo_t *cr;
surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
cr = cairo_create(surface);

// Dibujar fondo con degradado
cairo_pattern_t *pat;
pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.9, 0.9, 0.9);
cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.6, 0.6, 0.6);
cairo_rectangle(cr, 0, 0, width, height);
cairo_set_source(cr, pat);
cairo_fill(cr);

// Dibujar los ejes
cairo_set_source_rgba(cr, 1, 0.2, 0.2, 0.6);
cairo_set_line_width(cr, 3.0);
cairo_move_to(cr, origenx, origeny); cairo_line_to(cr, ejex, origeny);
cairo_move_to(cr, origenx, origeny); cairo_line_to(cr, origenx, ejey);
cairo_stroke_preserve(cr);
cairo_set_source_rgba(cr, 0.9, 0.0, 0.0, 0.3);
cairo_fill(cr);

// Dibujar la cuadrícula
for(i = 1; i <= divisiones; i++)
  {
  cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
  cairo_set_line_width(cr, 0.5);
  // Líneas verticales
  cairo_move_to(cr, origenx + (metrica_ejex * i), origeny);
  cairo_line_to(cr, origenx + (metrica_ejex * i), ejey);
  // Líneas horizontales
  cairo_move_to(cr, origenx, ejey + (metrica_ejey * (i - 1)));
  cairo_line_to(cr, ejex, ejey + (metrica_ejey * (i - 1)));
  cairo_stroke(cr);
  }

// Etiquetar el eje x
avancex = abs(b - a) / divisiones;

for(i = 0; i <= divisiones; i++)
  {
  metricax[i] = a + avancex * i;
  // Convertir las etiquetas de los ejes a strings
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << metricax[i];
  s[i] = stream.str();

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, 10.0);
  cairo_move_to(cr, origenx + (metrica_ejex * i), origeny + 10);
  cairo_save(cr);
  cairo_show_text(cr, s[i].c_str());
  }

// Etiquetar el eje y
avancey = abs(maxf - minf) / divisiones;

for(i = 0; i <= divisiones; i++)
  {
  metricax[i] = minf + avancey * i;
  // Convertir las etiquetas de los ejes a strings
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << metricax[i];
  s[i] = stream.str();

  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, 10.0);
  cairo_move_to(cr, origenx - 30, origeny - (metrica_ejex * i));
  cairo_save(cr);
  cairo_show_text(cr, s[i].c_str());
  }

// Graficar
avancex = abs(ejex - origenx) / abs(b - a);
avancey = abs(origeny - ejey) / abs(maxf - minf);

for(i = 0; i < puntos - 1; i++)
  {
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_set_line_width(cr, 1);
  cairo_move_to(cr, origenx + avancex * (misxs[i] + abs(a)), origeny - avancey * (fdex[i] + abs(minf)));
  cairo_line_to(cr, origenx + avancex * (misxs[i + 1] + abs(a)), origeny - avancey * (fdex[i + 1] + abs(minf)));
  cairo_stroke(cr);
  }

// Escritura de objeto gráfico y liberación de memoria
cairo_surface_write_to_png(surface, "grafica.png");
cairo_destroy(cr);
cairo_surface_destroy(surface);

return 0;
}
