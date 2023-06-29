#include "distance.h"


#include <iostream>
#include <vector>
#include <algorithm>

int clasica(string S, string T) {
    int m = S.length();
    int n = T.length();

    // Create a 2D matrix to store the edit distances
    vector< vector<int> > dp(m + 1, vector<int>(n + 1, 0));

    // Initialize the first row and column of the matrix
    for (int i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (int j = 0; j <= n; ++j)
        dp[0][j] = j;

    // Calculate edit distances
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (S[i - 1] == T[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + std::min(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m][n];
};




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



int verifica(string S, string T, int D) {
  
  int m = S.length();
  int n = T.length();
  
  // Caso base: si la diferencia de longitudes es mayor que D, retornar n+m+1
  if (abs(m - n) > D) {
    return m + n + 1;
  }

  // en caso de que la segunda cadena se mayor a la primera se intercambian para trabajar 
  // siempre con la misma forma de matriz
  if (m > n) {
        swap(S, T);
        swap(m, n);
    }

  // Se crea un vector inicial que guaradará las distancias entre los distintos largos de las
  // cadenas de texto.
  vector<vector<int>> dp(m+1, vector<int>(n+1));

  // Se completa la primera fila y columna con las distancias, correspondientes a uno de los 
  // textos vacios y a otro con i o j caracteres.
  for(int i = 0; i <= m; i++){
    dp[i][max(0,i-D-1)] = i;
  } 
  
  for(int i=0; i <= n; i++){
    dp[max(0,i-D-1)][i] = i;
  } 


  // Se continua con elementos del corredor central
  for (int i = 1; i <= m; i++) {
      // Calcular las columnas restantes de la matriz de distancias actual
      for (int j = max(1,i-D); j <=min(n,i+D); j++) {
          if (S[i-1] == T[j-1]) {
            dp[i][j] = dp[i-1][j-1]; // En caso de que sean iguales
          } else {
            dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);// en caso de que sean distintas se ve 
                                                       // cual tiene la menor distancia.
          }
      }
  }

//prueba de impresión de matriz
//
// for(int k=0;k<m;k++){
//  for(int g =0;g<n;g++){
//
//    cout<<dp[k][g]<<"   ";
//  }
//  cout<<endl;
// }

  //Finalmente retorna 
    if(dp[m][n] <= D)
    {
      return dp[m][n];
    }
    return (m + n + 1);
};


int adaptiva(string S, string T) 
{

  int m = S.length();
  int n = T.length();
  int jump=1;
  int result;

  while(jump<=m+n){

    result = verifica(S,T,jump);
    //cout<<"Para jump "<<jump<<" verifica retorna "<<result<<endl;
    if(result < m+n+1){
      return result;
    }
    if(jump*2>m+n){
      jump = m+n;
    }else{
      jump=jump*2;
    }
  }
  return n+m;
}