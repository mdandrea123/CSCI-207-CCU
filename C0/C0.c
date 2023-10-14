/* FIGURE 2.14  Batch Version of Miles-to-Kilometers Conversion Program */
/* Converts distances from miles to kilometers.        */

#include <stdio.h> /* printf, scanf definitions 	   */
#include <stdlib.h> // atof() and maybe others



int main(int argc, char** argv) {
  double toKMS = 1.609;
  double toNM = 1.151;
  double toPar = 1.917 *pow(10, 13);
  double toLS = 186300;

  //check if user passed number of miles
  if(argc != 2){
    printf("Error! Usage: %s <number of miles> \n", argv[0]);
    exit(1);
  }

  double miles = atof(argv[1]);
  double kms = miles * toKMS;
  double nautical = miles * toNM;
  double parsec = miles * toPar;
  double ls = miles * toLS;

  printf("The number of miles is %f \n", miles);
  printf("The number of kilometers is %f \n", kms);
  printf("The number of Nautical Miles is %f \n", nautical);
  printf("The number of Parsecs is %f \n", parsec);
  printf("The number of Light Seconds is %f \n", ls);
  return 0;
}