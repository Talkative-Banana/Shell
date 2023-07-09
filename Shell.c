#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<pthread.h>

char* path = "/home/lucky/Directory/Assignments/Assignment2/External/";

int method(char parameters[10]){
	char k[3] = {'&','t','\0'}; 
	if(strcmp(parameters,k) == 0){
		return 1;
	}
	return 0;
}

void *threaded_function(void *arg){
	//pthread_detach(pthread_self());
	system(arg);
	pthread_exit(NULL);
}

int main() {
	char cwd[300];
	while(1){
	char String[100];
	char *parameters[10];
	printf("prompt> ");
	fgets(String, sizeof(String),stdin);
	int len = strlen(String);
	if(String[len-1] == '\n'){
		String[len-1] = 0;
	}
	char *command = strtok(String," ");
	char *token = command;
	char * parameter = "NULL";
	int i = 0;
	while(token != NULL){
		token = strtok(NULL," ");
		parameters[i] = "NULL";
		if(token != NULL && token != "\n"){
			parameters[i] = token;
			parameter = token;
			i++;
		}
	}
	int th = method(parameter);
	if(strcmp(command,"exit") == 0 && strcmp(parameters[0], "NULL") == 0){
		break;
	} else if (strcmp(command, "cd") == 0){
		if(strcmp(parameters[0],"..") == 0){
			chdir("..");
		} else if (strcmp(parameters[0],"/") == 0) {
			chdir("/");
		} else {
			chdir(parameters[0]);
		}
	} else if(strcmp(command,"echo") == 0){
		char k[100] = "";
		for(int j=0;j<i;j++){
			strcat(k,parameters[j]);
			strcat(k," ");
		}
		printf("%s\n",k);
	} else if (strcmp(command, "pwd") == 0) {
		if(strcmp(parameters[0],"-L") == 0) {
			printf("%s\n",getcwd(cwd,sizeof(cwd)));
		} else if(strcmp(parameters[0],"-P") == 0) {
			printf("%s\n",getcwd(cwd,sizeof(cwd)));
		} else if (strcmp(parameters[0],"NULL") == 0){
			printf("%s\n",getcwd(cwd,sizeof(cwd)));
		} else{
			printf("Command not Supported\n");
		}
	} else if((strcmp(command,"ls") == 0 || strcmp(command,"cat") == 0 || strcmp(command,"date") == 0 || 
		strcmp(command,"rm") == 0 || strcmp(command,"mkdir") == 0)  && th){
			pthread_t id;
			if(strcmp(command,"ls") == 0) {
				char arg_v[50] = "./External/my_ls_file.out ";
				if(strcmp(parameters[0], "-a") == 0){
					strcat(arg_v,"\".\"");	
				} else if(strcmp(parameters[0], "/") == 0){
					strcat(arg_v,"\"/\"");
				} else if(strcmp(parameters[0],"&t") == 0){
					strcat(arg_v,"\".\"");
				} else{
					printf("Command not supported\n");
				}
				pthread_create(&id,NULL,&threaded_function,arg_v);
			} else if(strcmp(command,"cat") == 0) {
				char arg_v[50] = "./External/my_cat_file.out ";
				if(strcmp(parameters[0], ">") == 0){
					strcat(arg_v,"\">\" \"");
					strcat(parameters[1],"\"");
					strcat(arg_v,parameters[1]);	
				} else if(strcmp(parameters[0], "-n") == 0){
					strcat(arg_v ,"\"-n\" \"");
					strcat(parameters[1],"\"");
					strcat(arg_v ,parameters[1]);
				} else {
					printf("Command not supported\n");
				}
				printf("%s\n",arg_v);
				pthread_create(&id,NULL,&threaded_function,arg_v);
			} else if(strcmp(command,"date") == 0) {
				char arg_v[50] = "./External/my_date_file.out ";
				if(strcmp(parameters[0], "-u") == 0){
					strcat(arg_v, "\"-u\"");
				} else if(strcmp(parameters[0], "&t") == 0){
					strcat(arg_v,"\"NULL\"");
				} else {
					printf("Command not supported\n");
				}

				pthread_create(&id,NULL,&threaded_function,arg_v);
			} else if(strcmp(command,"rm") == 0) {
				char arg_v[50] = "./External/my_rm_file.out ";
				if(strcmp(parameters[0], "-i") == 0){
					strcat(arg_v ,"\"-i\" \"");
					strcat(parameters[1],"\"");
					strcat(arg_v ,parameters[1]);
				} else if(strcmp(parameters[0], "-v") == 0){
					strcat(arg_v , "\"-v\" \"");
					strcat(parameters[1],"\"");
					strcat(arg_v ,parameters[1]);
					if(strcmp(parameters[2], "NULL") !=0){
						strcat(arg_v," \"");
						strcat(parameters[2],"\"");	
						strcat(arg_v, parameters[2]);		
					}
				} else {
					printf("Command not supported\n");
				}
		
				pthread_create(&id,NULL,&threaded_function,arg_v);
			} else {
				char arg_v[100] = "./External/my_mkdir_file.out ";
				if(strcmp(parameters[0], "-m777") == 0){
					strcat(arg_v,"\"-m777\" \"");
					strcat(parameters[1],"\"");
					strcat(arg_v,parameters[1]);
				} else if(strcmp(parameters[0], "-v") == 0){
					strcat(arg_v,"\"-v\" \"");
					strcat(parameters[1],"\"");
					strcat(arg_v ,parameters[1]);
					if(strcmp(parameters[2], "NULL") != 0){
						strcat(arg_v, " \"");
						strcat(parameters[2],"\"");	
						strcat(arg_v, parameters[2]);		
					}

				} else {
					printf("Command not supported\n");
				}
	
				pthread_create(&id,NULL,&threaded_function,arg_v);
			}
		       pthread_join(id,NULL);
		      // pthread_exit(NULL);
		} else if(th == 0 && (strcmp(command,"ls") == 0) || (strcmp(command,"cat") == 0) || 
		(strcmp(command,"date") == 0) || (strcmp(command,"rm") == 0) || (strcmp(command,"mkdir") == 0)){
			pid_t pid;
			pid = fork();
			if (pid == -1){
				printf("fork failed");
			} else if(pid > 0){
				wait(NULL);
			} else if (pid == 0 ){

				if(strcmp(command,"ls") == 0) {
					char* arg_v[] = {"./External/my_ls_file.out","temp",NULL};
					if(strcmp(parameters[0], "-a") == 0){
						arg_v[1] = ".";	
						execvp("./External/my_ls_file.out",arg_v);
					} else if(strcmp(parameters[0], "/") == 0){
						arg_v[1] = "/";
						execvp("./External/my_ls_file.out",arg_v);
					} else if(strcmp(parameters[0],"NULL") == 0){
						arg_v[1] = ".";
						execvp("./External/my_ls_file.out",arg_v);
					} else{
						printf("Command not supported\n");
					}
				} else if(strcmp(command,"cat") == 0) {
					char* arg_v[] = {"./External/my_cat_file.out","temp","temp",NULL};
					if(strcmp(parameters[0], ">") == 0){
						arg_v[1] = parameters[0];
						arg_v[2] = parameters[1];	
						execvp("./External/my_cat_file.out",arg_v);
					} else if(strcmp(parameters[0], "-n") == 0){
						arg_v[1] = parameters[0];
						arg_v[2] = parameters[1];
						execvp("./External/my_cat_file.out",arg_v);
					} else {
						printf("Command not supported\n");
					}	
				} else if(strcmp(command,"date") == 0) {
					char* arg_v[] = {"./External/my_date_file.out","temp",NULL};
					if(strcmp(parameters[0], "-u") == 0){
						arg_v[1] = "-u";	
						execvp("./External/my_date_file.out",arg_v);
					} else if(strcmp(parameters[0], "NULL") == 0){
						arg_v[1] = "NULL";
						execvp("./External/my_date_file.out",arg_v);
					} else {
						printf("Command not supported\n");
					}
				} else if(strcmp(command,"rm") == 0) {
					char* arg_v[] = {"./External/my_rm_file.out","temp",parameters[1],parameters[2],NULL};
					if(strcmp(parameters[0], "-i") == 0){
						arg_v[1] = "-i";	
						execvp("./External/my_rm_file.out",arg_v);
					} else if(strcmp(parameters[0], "-v") == 0){
						arg_v[1] = "-v";
						execvp("./External/my_rm_file.out",arg_v);
					} else {
						printf("Command not supported\n");
					}
				} else {
					char* arg_v[] = {"./External/my_mkdir_file.out","temp","temp","temp",NULL};
					if(strcmp(parameters[0], "-m777") == 0){
						arg_v[1] = "-m777";
						arg_v[2] = parameters[1];	
						execvp("./External/my_mkdir_file.out",arg_v);
					} else if(strcmp(parameters[0], "-v") == 0){
						arg_v[1] = "-v";
						arg_v[2] = parameters[1];
						arg_v[3] = parameters[2];
						execvp("./External/my_mkdir_file.out",arg_v);
					} else {
						printf("Command not supported\n");
					}
				}
			}
				
	} else {
		printf("Command Failed\n");
		}
	}
	return 0;
}
