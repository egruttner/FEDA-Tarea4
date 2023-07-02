#include "distance.h"
#include <iostream>
#include <vector>
#include <algorithm>

int clasica(string S, string T) 
{
  //Obtiene el largo de los strings
  int m = S.length();
  int n = T.length();

  //Matriz (vector 2D) para almacenar los cálculos de distancia
  vector< vector<int> > dp(m + 1, vector<int>(n + 1, 0));

  //Inicializa filas y columnas
  for (int i = 0; i <= m; ++i)
      dp[i][0] = i;
  for (int j = 0; j <= n; ++j)
      dp[0][j] = j;

  //Realiza el cálculo dinámico de distancias
  for (int i = 1; i <= m; ++i) 
  {
      for (int j = 1; j <= n; ++j) 
      {
          if (S[i - 1] == T[j - 1])
          {
              dp[i][j] = dp[i - 1][j - 1]; //queda igual, no suma costo
          }
          else
          {
              dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]); //costo 1 + DELETE o INSERT
          }
      }
  }

  //Retorna la distancia que queda "al final" de la matriz de cálculo
  return dp[m][n];
};


int verifica(string S, string T, int D) 
{  
  //Obtiene el largo de los strings
  int m = S.length();
  int n = T.length();
  
  //Si el valor absoluto de la diferencia de longitudes es mayor que D, retornar n+m+1
  if (abs(m - n) > D) 
  {
    return m + n + 1;
  }

  //Matriz (Vector 2D) para almacenar los cálculos de distancia
  vector<vector<int>> dp(m+1, vector<int>(n+1));

  //A diferencia del llenado de la matriz clásica, en este caso se completa
  //solamente lo que se va a utilizar, y se rellena con 0 si no
  for(int i = 0; i <= m; i++)
  {
    dp[i][max(0,i-D-1)] = i;
  } 
  
  for(int j=0; j <= n; j++)
  {
    dp[max(0,j-D-1)][j] = j;
  } 

  //Se opera con el pasillo central
  for (int i = 1; i <= m; i++) 
  {
      for (int j = max(1,i-D); j <=min(n,i+D); j++) 
      {
          if (S[i-1] == T[j-1]) 
          {
            dp[i][j] = dp[i-1][j-1]; //queda igual, no suma costo
          } 
          else 
          {
            dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]); //costo 1 + DELETE o INSERT
          }
        //Condición especial: si la distancia actual es superior a lo buscado, sale y entrega n+m+1
        if(dp[i][i]>D)
        {          
          return n+m+1;
        }
      }
  }

  //Si la distancia calculada es menor que la buscada, entonces entrega esa solución
  if(dp[m][n] <= D)
  {
    return dp[m][n];
  }

  //Si no ha salido antes, se va por el caso por defecto, entregando m+n+1
  return (m+n+1);
};


int adaptiva(string S, string T) 
{
  //Obtiene el largo de los strings
  int m = S.length();
  int n = T.length();

  //Variables e inicialización
  int calculo;
  int distancia_llamada=0;
  int aux=0;

  //Prospectando distancias
  while(distancia_llamada <= m+n)
  {

    calculo = verifica(S,T,distancia_llamada);

    if(calculo < m+n+1)
    {
      return calculo;
    }

    if(distancia_llamada * 2 > m+n)
    {
      distancia_llamada = m+n;
    }
    else
    {
      distancia_llamada=pow(2,aux);
      aux++;
    }
  }
  return m+n;
};




//////////ZONA DE PRUEBAS/////////////
int clasica_old_old(string S, string T) 
{
  //Obtiene el largo de los strings
  int m = S.length();
  int n = T.length();

  cout << "m: " << m << endl;
  cout << "n: " << n << endl;

  //Vector que almacenará la distanci
  vector<int> dp(n + 1);

  //Inicializa vector, de 0 a n. 
  //Esto representa la distancia de edición requerida para transformar
  //una cadena vacía en una subcadena de T del mismo tamaño.
  for (int i = 0; i <= n; ++i) {
      dp[i] = i;
  }

  int prev;
  //Se recorre el string S
  for (int i = 1; i <= m; ++i) 
  {
    //Se guarda el valor anterior de dp[0] en prev antes de ser actualizado.
    //Este valor representa la distancia de edición requerida para transformar
    //la subcadena vacía de S en una subcadena de T.
    prev = dp[0];

    //Se actualiza el valor de dp[0] en la posición 0 del vector dp para reflejar
    //la distancia de edición requerida para transformar la subcadena de S
    //desde el inicio hasta la posición actual en una subcadena vacía de T.
    dp[0] = i;

    //Se inicia un loop que itera desde 1 hasta n,
    //recorriendo cada posición en la cadena T.
    for (int j = 1; j <= n; ++j) 
    {
        //Se guarda el valor actual de dp[j] en la variable temp
        //antes de ser actualizado. Este valor representa la distancia
        //de edición requerida para transformar la subcadena de S
        //desde el inicio hasta la posición actual en una subcadena de T
        // desde el inicio hasta la posición anterior.
        int temp = dp[j];

        //Si son iguales, no se requiere ninguna operación y se asigna el valor de prev a dp[j].
        if (S[i - 1] == T[j - 1]) 
        {
            dp[j] = prev;
        } 
          else 
        {
        //Si los caracteres son diferentes, se elige el mínimo valor entre:
        //-prev (distancia para transformar la subcadena de S hasta
        // la posición actual en una subcadena de T hasta la posición anterior),
        //-dp[j] (distancia para transformar la subcadena de S hasta
        // la posición actual en una subcadena de T hasta la posición actual)
        //-dp[j-1] (distancia para transformar la subcadena de S hasta
        // la posición anterior en una subcadena de T hasta la posición actual).
        //Se le suma 1 al mínimo valor porque es una operación más.

      //insertion = d[i][j - 1];
      //deletion = d[i - 1][j];
      //replacement = d[i - 1][j - 1];

      //d[i][j] = 1 + findMin(insertion, deletion, replacement);



            dp[j] = 1 + min({ prev, dp[j], dp[j - 1] });
        }
        prev = temp;
    }
  }

  return dp[n];
};




int clasica_old(string S, string T)
{

  //Tamaño de string 1
  int m = S.length();

  //Tamaño de string 2
  int n = T.length();

  cout << "m: " << m << endl;
  cout << "n: " << n << endl;

  //Vector para calcular las distancias
  //vector< vector<int> > dp(m+1, vector<int>(n+1));
  vector< vector<int> > dp(m+1, vector<int>(n + 1, 0));

  //Limpia matriz dp
  for(int i = 0; i <= m; i++)
  {
    for(int j = 0; j <= n; j++)
    {
      dp[i][j]=0;
    }
  }

  //Inicializa primera fila/primera columna dp
  for(int i = 0; i <= m; i++) dp[i][0] = i;
  for(int j = 0; j <= n; j++) dp[0][j] = j;

  //Recorre palabra 1, comparando con palabra 2
  for(int i = 1; i <= m; i++)
  {
    for(int j = 1; j <= n; j++)
    {

      if(S[i-1] == T[j-1])
      {
        //Caracteres iguales, 
        dp[i][j] = dp[i-1][j-1];
      }
      else
      {
        //Menor valor del "triángulo" + 1 operación
        dp[i][j] = 1 + min( dp[i-1][j-1],
                            min(dp[i-1][j],
                            dp[i][j-1]));
      }

    }
  }

  //El resultado queda almacenado en el extremo de dp dp[m][n]
  return dp[m][n];

};
