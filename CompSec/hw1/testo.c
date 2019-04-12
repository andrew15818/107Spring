#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
void dns_send(char *trgt_ip, int trgt_prt, char *dns_srv, int dns_p, unsigned char *dns_record);
int main(int argc, char *argv[]){
	//create the DNS header
	char *trgt_ip = argv[1];
	int trgt_p = atoi(argv[2]);
	int dns_prt = atoi(argv[4]);
	char *dns_srv = argv[3];
	dns_send(trgt_ip, trgt_p,dns_srv,trgt_p,"www.google.com"); 
	return 0;
}
