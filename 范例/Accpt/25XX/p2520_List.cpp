#include <stdio.h>
int a[23]={0,220,1184,2620,5020,6232,10744,12285,17296,63020,66928,67095,69615,79750,100485,122265,122368,141664,142310,171856,176272,185368,196724};
int b[23]={0,284,1210,2924,5564,6368,10856,14595,18416,76084,66992,71145,87633,88730,124155,139815,123152,153176,168730,176336,180848,203432,202444}; 
main ()
{
     int N;
     while ( scanf ( "%d" , &N ) != EOF )
           printf ( "%d %d\n" , a [N] , b [N] );
}
