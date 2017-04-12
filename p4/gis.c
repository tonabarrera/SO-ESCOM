#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
	pid_t pid, ppid;
	int proc;
	for (int i=0; i<10; i++){
		proc=fork();// crea proceso por copia exacta de codigo
		pid=getpid();//Obtiene pid del proceso actual
		ppid=getppid();//Obtiene pid del padre del proceso actual
		if(i==0 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);		
			for (int j=0; j<5; j++){//v1
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI0 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(j==4){
						for(int k=0;k<5;k++){//h1
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT0 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int K=0;K<5;K++){//h1
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int J=0; J<5; J++){//v1				
				wait(0);
			}
			exit(0);
		}
		else if(i==1 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int l=0; l<4; l++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI1 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(l==3){
						for(int m=0;m<4;m++){//h2
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT1 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int M=0;M<4;M++){//h2
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int L=0; L<4; L++){//v2
				wait(0);
			}	
			exit(0);
		}
		else if(i==2 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int n=0; n<3; n++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI2 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(n==2){
						for(int o=0;o<3;o++){//h2
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT2 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int O=0;O<3;O++){//h2
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int N=0; N<3; N++){//v2
				wait(0);
			}	
			exit(0);
		}
		else if(i==3 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int p=0; p<2; p++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI3 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(p==1){
						for(int q=0;q<2;q++){//h2
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT3 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int Q=0;Q<2;Q++){//h2
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int P=0; P<2; P++){//v2
				wait(0);
			}	
			exit(0);
		}
		else if(i==4 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int r=0; r<2; r++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					if(r==1){
						pid=getpid();
						ppid=getppid();
						printf ("\nT4 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
						exit(0);  
					}
					else{
						printf ("\nI4 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					}
				}
				else{
					break;
				}
			}
			for (int R=0; R<2; R++){//v2
				wait(0);
			}	
			exit(0);		
		}
		else if(i==5 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int r=0; r<2; r++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					if(r==1){
						pid=getpid();
						ppid=getppid();
						printf ("\nT5 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
						exit(0);  
					}
					else{
						printf ("\nI5 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					}
				}
				else{
					break;
				}
			}
			for (int R=0; R<2; R++){//v2
				wait(0);
			}	
			exit(0);
		}
		else if(i==6 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int p=0; p<2; p++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI6 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(p==1){
						for(int q=0;q<2;q++){//h2
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT6 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int Q=0;Q<2;Q++){//h2
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int P=0; P<2; P++){//v2
				wait(0);
			}	
			exit(0);
		}
		else if(i==7 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int n=0; n<3; n++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI7 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(n==2){
						for(int o=0;o<3;o++){//h2
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT7 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int O=0;O<3;O++){//h2
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int N=0; N<3; N++){//v2
				wait(0);
			}	
			exit(0);
		}
		else if(i==8 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
			for (int l=0; l<4; l++){//v2
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI8 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(l==3){
						for(int m=0;m<4;m++){//h2
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT8 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int M=0;M<4;M++){//h2
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int L=0; L<4; L++){//v2
				wait(0);
			}	
			exit(0);
		}
		else if(i==9 && proc==0){
			printf ("\nM Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);		
			for (int j=0; j<5; j++){//v1
				proc=fork();
				if(proc==0){
					pid=getpid();
					ppid=getppid();
					printf ("\nI9 Proceso Hijo con pid= %i del Proceso Padre con pid= %i\n", pid, ppid);
					if(j==4){
						for(int k=0;k<5;k++){//h1
							proc=fork();
							pid=getpid();
							ppid=getppid();
							if(proc==0){
								printf ("\nT9 Proceso Terminal Hijo con pid= %i, Proceso Padre con pid= %i\n", pid, ppid);
								exit(0);
							}
						}
						for(int K=0;K<5;K++){//h1
							wait(0);
						}
					}
				}
				else{
						break;
				}
			}
			for (int J=0; J<5; J++){//v1				
				wait(0);
			}
			exit(0);	
		}	
	}//for de 10
	for(int I=0;I<10;I++){
		wait(0);//espera al proceso padre principal (main)
	}		
}