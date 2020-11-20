#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include "mcfunctions.h"

#define SUCCESS 0
#define ERROR -1

void display_help(){
	fprintf(stdout, "%s \n", "Usage:");
	fprintf(stdout, "   %s \n", "common -h");
	fprintf(stdout, "   %s \n", "common -V");
	fprintf(stdout, "   %s \n", "common [options] M N");
	fprintf(stdout, "%s \n", "Options:");
	fprintf(stdout, "   %s \n", "-h, --help      Prints usage information.");
	fprintf(stdout, "   %s \n", "-V, --version   Prints version information.");
	fprintf(stdout, "   %s \n", "-o, --output    Path to output file.");
	fprintf(stdout, "   %s \n", "-d, --divisor   Just the divisor.");
	fprintf(stdout, "   %s \n", "-m, --multiple  Just the multiple.");
	fprintf(stdout, "%s\n \n","Examples:");
	fprintf(stdout, "   %s\n", "     common -o - 256 192");
}

int main(int argc, char **argv){ 
	if (argc > 6){
		fprintf(stderr,"%s \n","Invalid command");
		return ERROR;
	}
	static struct option long_options[] = {
        {"divisor", no_argument, 0, 'd' },
        {"output", required_argument, 0, 'o' },
        {"multiple", no_argument, 0, 'm' },
        {"help", no_argument, 0,'h'},
        {"version", no_argument, 0, 'V'},
    };
	FILE* output_file;
	int option_index = 0;
	bool multiple = false;
    bool divisor = false;
    int offset = 1;
	int option;
	while ((option = getopt_long(argc, argv, "hV:dm:o", long_options, &option_index)) != -1) {
    	switch (option) {
    		case 'm':
    			multiple = true;
                offset++;
    			break;
    		case 'o':
                if (strcmp(optarg, "-") == 0) output_file = stdout; //verificar si pasaba algo dsp al cerrarste output o si ta todo piola
    			else output_file = fopen(optarg, "wt");
                offset += 2;
    			break;
    		case 'h':
    			display_help();
    			return SUCCESS;
    		case 'V':
    			fprintf(stdout,"%s \n", "Version 1.3");
    			return SUCCESS;
            case 'd':
                //hago algo más??
                divisor = true;
                offset++;
                break;
            default:
            	fprintf(stderr, "%s \n", "Invalid command");
				return ERROR;
        }
    }

    // int prueba = 9999999999;
    // printf("tamaño en int %d \n", sizeof(prueba));
    // char casteado = (char) prueba;
    // printf("tamaño en char %d \n", sizeof(casteado));

    int n1 = atoll(argv[offset]);
    int n2 = atoll(argv[offset + 1]);
    if (n1 > INT_MAX || n1 < 2 || n2 > INT_MAX || n2 < 2){  //DUDA en el tp dice MAX_INT pero solo encontre que existe INT_MAX
		fprintf(stderr, "%s \n", "Invalid numbers");
		return ERROR;
    }
    int result;
    if (!multiple && !divisor){
        result = mcd(n1, n2);
        int result2 = mcm(n1, n2);
        //char* result_to_string = malloc(result_size);
		//char result_to_string[result_size];
        //snprintf(result_to_string, sizeof(char) + sizeof(int), "%c\n", result);
        //sprintf(result_to_string, '\n');
        //snprintf(result_to_string, sizeof(char) + sizeof(int), "%c\n", result2);
        //sprintf(result_to_string, '\n');
        // char* result_to_string = (char)result + '\n' + (char)result2 + '\n';
		//fputs(result_to_string, output_file);
        fprintf(output_file, "%d\n%d\n", result, result2);
        //fputs(output_file, (char*)result);
        //fputs(output_file, (char*)result2);
        return SUCCESS;
    }
    else if (divisor) result = mcd(n1, n2);
	else result = mcm(n1, n2);  //verificar si puede haber error acá
    fprintf(output_file, "%d\n", result);
    //fputs((char)result, output_file);
	return SUCCESS;
}
