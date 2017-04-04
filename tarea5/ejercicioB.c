#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(void) { //0
  int proc;
    if(proc = fork())==0){ // 1
      if(proc = fork())==0){ // 2
        if(proc = fork())==0){ // 3
          int x;
          for (x = 0; x < 3; x++) {
            proc = fork();
            if(proc == 0 && x == 0) {
              // Rama izquierda
              int x_izq;
              for (x_izq = 0; x_izq < 2; x_izq++){
                proc = fork();
                if (x_izq == 0 && proc = 0) {
                  // Rama izq. 0
                  proc = fork(); // Rama izq. 0.1
                  if (proc == 0) {
                    int x_izq_final;
                    for (x_izq_final = 0; x_izq_final < 3; x_izq_final++) {
                      // Rama izq. 0.1 tres hijos
                      if((proc=fork())==0){
                        exit(0);
                      } else {
wait(NULL)}
                    }
                  } else {wait(NULL);}
                  exit(0);
                } else if(x_izq == 1 && proc = 0){
                  // Rama izq. 1
                    proc = fork(); // Rama izq 1.1
                    if (proc == 0) {
                      int x_izq_final2;
                      for (x_izq_final2 = 0; x_izq_final2 < 2; x_izq_final2++) {
                        // Rama izq. 1.1 dos hijos
                        if((proc=fork())==0){
                          exit();
                        } else {wait(NULL);}
                      }
                    } else {wait(NULL);}
                    exit(0);
                } else {wait(NULL);}
              }
            } else if(proc == 0 && x == 1) {
              // Esta es la rama del centro
                proc = fork(); // Rama centro 0
                if(proc == 0){
                  int x_cen;
                  for(x_cen = 0; x_cen < 2; x_cen++){
                    if((proc = fork()) == 0){// Rama centro 0 dos hijos
                      exit(0);
                    } else {wait(NULL);}
                  }
                } else {wait(NULL);}
                exit(0);
            } else if(proc == 0 && x == 2) {
              // Rama de la derecha
              int x_der;
              for (x_der = 0; x_der < 2; x_der++){
                proc = fork();
                if (x_der == 0 && proc = 0) {
                  // Rama der 0
                  proc = fork(); // Rama der 0.1
                  if (proc == 0) {
                    int x_der_final;
                    for (x_der_final = 0; x_der_final < 3; x_der_final++) {
                      // Rama der 0.1 con tres hijos
                      if((proc = fork()) == 0){
                        exit(0)
                      }else {wait(NULL);}
                    }
                  } else {wait(NULL);}
                  exit(0);
                } else if(x_der == 1 && proc = 0){
                  // Rama der 1
                  proc = fork(); // Rama der 1.1
                  if (proc == 0) {
                    int x_der_final2;
                    for (x_der_final2 = 0; x_der_final2 < 2; x_der_final2++) {
                      // Rama der 1.1 con dos hijos
                      if ((proc=fork())==0) {
                        exit(0);
                      } else {wait(NULL);}
                    }
                    exit(0);
                  } else{wait(NULL);}
                  exit(0);
                } else {wait(NULL);}
              }
            } else {wait(NULL);}
          }
        } else {wait(NULL);}
      } else {wait(NULL);}
    } else {wait(NULL);}
  return 0;
}
