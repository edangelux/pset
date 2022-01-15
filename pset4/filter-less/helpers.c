#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{   //hacer escalas grises, leer la documentacion para entenderle mejor
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            //reestablecer los colores, dividir con punto flotante y redonderar
            //necesito que los valores se conviertan a entero
            int valor_promedio = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = valor_promedio;

        }
    }
}
int maximo (int valor)
{
    return valor > 255 ? 255: valor;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{ //vamos a hacer la imagen marronsita osea sepia haremos casi lo mismo
  //con los for pero usaremos el formato sepa que sale en la documentacion
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            //valores originales de los colores y de formato sepia
            int originalRed = pixel.rgbtRed;
            int originalGreen = pixel.rgbtGreen;
            int originalBlue = pixel.rgbtBlue;
            //pasar los valores a flotantes y redondearlos
            //darle valor maximo 255 con la variable maximo
            image[i][j].rgbtRed = maximo(round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue));
            image[i][j].rgbtGreen = maximo(round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue));
            image[i][j].rgbtBlue = maximo(round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue));
        }
    }
}
//creamos variable reflex
void reflex(RGBTRIPLE * pixel1, RGBTRIPLE * pixel2)
{ //explicarlo y posible toma para clase de puntero
    RGBTRIPLE temp = *pixel1; //tomara el valor de todo esto
    *pixel1 = *pixel2; //pixel 2 tomara el valor de pixel 2 por que la funcion es hacer un reflex recuerden
    *pixel2 = temp; //y aca devolvemos todo que ya se hizo el reflex
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{ //darle un reflector a esto aunque sea innecesaario creo hay que hacerlo
  //tomaremos las direcciones
  for (int i = 0; i < height; i++)
  {
      for (int j = 0; j < width / 2; j++)
      {
          reflex(&image[i][j], &image[i][width - 1 - j]);
      }
  }
}
bool valido_pixel (int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE borroso (int i, int j, int height,int width, RGBTRIPLE image[height][width])
{ //Recorrer las celdas de 3x3 como la documentacion con funcion i y j
    int redValor, blueValor, greenValor; redValor = blueValor = greenValor = 0;
    // validacion de numero de pixeles
    int numeropixels = 0;
    for(int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int nueva_i = i + di;
            int nueva_j = j + dj;
            //crear validacion de pixel valido
            if (valido_pixel(nueva_i, nueva_j, height, width))
            { //acumular y validar los datos de los pixeles
                numeropixels++;
                redValor += image[nueva_i][nueva_j].rgbtRed;
                blueValor += image[nueva_i][nueva_j].rgbtBlue;
                greenValor += image[nueva_i][nueva_j].rgbtGreen;
            }
        }
    }
    //eliminar pixeles malos
    RGBTRIPLE blur_pixe;
    blur_pixe.rgbtRed = round((float) redValor / numeropixels);
    blur_pixe.rgbtGreen = round((float) greenValor / numeropixels);
    blur_pixe.rgbtBlue = round((float) blueValor / numeropixels);
    return blur_pixe;
}
// Blur image
// leer primero la documentacion de el desenfoque y entederle correctamente
void blur(int height, int width, RGBTRIPLE image[height][width])
{   //haremos una nueva imagen
    RGBTRIPLE nueva_imagen[height][width];
    for( int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   //creamos una variable que tomara los datos de entreparentesis
            nueva_imagen[i][j] = borroso(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = nueva_imagen[i][j];
}
