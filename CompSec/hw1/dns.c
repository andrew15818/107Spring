//here we implement the functions that connect
//and send packages to corresponding DNS server
#include"testo.h"
//print error
void error(char	*str){
	printf("%s\n", str);
}
//calculate the checksum over the header
unsigned short csum(unsigned short *ptr, int nbytes){
	unsigned long sum;
	unsigned short odd; //for odd bytes
	unsigned short chksum;

	sum=0;
	while(nbytes>1){
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes==1){
		odd=0;	
		*((unsigned char *)&odd)=*(unsigned char *)ptr;
		sum+=odd;
	}
	sum= (sum>>16)+(sum& 0xffff);
	sum+=(sum>>16);
	chksum = (short)~sum;
	return chksum;	
}
//basically converting the host name to appropriate format
//for request
void dns_format(unsigned char *dns, unsigned char *host){
	int lock=0;
	strcat((char*)host, ".");
	for(int i=0;i<strlen((char*)host); i++){
		if(host[i]=='.'){
			*dns++ = i-lock;	
			for(;lock;lock++){
				*dns++=host[lock];	
			}
			lock++;
		}	
	}
	*dns++='\0';	//c way of terminating a string
}
void dns_hdr_create(dns_hdr *dns){
	dns->id=(unsigned short) htons(getpid());	//id of the current process
	dns->flags=htons(0x0100);
	dns->qcount=htons(1);						//question count
	dns->anscount=0;									//answer count
	dns->auth=0;
	dns->add=0;
}
void dns_send( char *trgt_ip, int trgt_p,char *dns_srv, int dns_p, unsigned char *dns_record, int argc, char *argv[]){
	//this array will contain all the info for the packet, including headers and DNS query
	unsigned char dns_data[128];
	dns_hdr *dns=(dns_hdr *)&dns_data;		//putting the DNS header first into packet
	dns_hdr_create(dns);

	unsigned char *dns_name, dns_rcrd[32];
	dns_name=(unsigned char*)&dns_data[sizeof(dns_hdr)]; //the name of the dns will go after the header
	strcpy(dns_rcrd, dns_record);

	query *q;
	q=(query *)&dns_data[sizeof(dns_hdr)+(strlen(dns_name)+1)];// the query will follow the name and header
	q->qtype=htons(0x00ff);		//code for general type of query 
	q->qclass = htons(0x1);
	//here we create sockets and headers
	char datagram[4096], *data, *psgram;
	memset(datagram,0,4096);	//making space for the datagram in memory
	data = datagram+ sizeof( iph) + sizeof(udph);
	memcpy(data, &dns_data, sizeof(dns_hdr)+(strlen(dns_name)+1)+sizeof(query)+1); //copying all the previous info to data

	/*creating sockets*/
	struct sockaddr_in sin, din;
	sin.sin_family=AF_INET;
	din.sin_family=AF_INET;

	//these are the addresses of the ports we will use
	sin.sin_port=htons(atoi(argv[2]));
	din.sin_port=htons(atoi(argv[4]));
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	din.sin_addr.s_addr = inet_addr(argv[3]);

	/*declaring the IP header info*/
	iph *ip = (iph *)datagram;	//because we already have a pointer to the datagram array
	ip->version=4;
	ip->ihl=5;
	ip->tos=0;
	ip->tot_len = sizeof(iph) + sizeof(udph)+sizeof(dns_hdr)+(strlen(dns_name)+1)+sizeof(query); //our total size
	ip->id = htonl(getpid()); //have to be running as root to get the process id 
	ip->frag_off =0;
	ip->ttl =64;
	ip->protocol = IPPROTO_UDP;
	ip->check=0;
	ip->saddr = inet_addr(argv[1]);
	ip->daddr = inet_addr(argv[3]);
	ip->check = csum((unsigned short *)datagram, ip->tot_len);
	/* declaring the UDP header info*/
	udph *udp = (udph * )(datagram + sizeof(iph));
	udp->source = htons(trgt_p);
	udp->dest = htons(dns_p);
	udp->len = htons(8+sizeof(dns_hdr)+(strlen(dns_name)+1)+sizeof(query));
	udp->check=0;	
	
	/*performing the checksum calculations on pseudo object for ease*/
	ps_hdr pshdr;
	pshdr.daddr=sin.sin_addr.s_addr;
	pshdr.filler =0;
	pshdr.protocol = IPPROTO_UDP;
	pshdr.len = htons(sizeof(udph)+ sizeof(dns_hdr)+ (strlen(dns_name)+1)+ sizeof(query));

	//total packet size in bytes
	int pssize = sizeof(ps_hdr)+ sizeof(udph)+sizeof(dns_hdr) + (strlen(dns_name)+1)+ sizeof(query);
	psgram = malloc(pssize);
	memcpy(psgram, (char* )&pshdr, sizeof(ps_hdr));
	memcpy(psgram+ sizeof(ps_hdr), udp, pssize- sizeof(ps_hdr));

	udp->check = csum((unsigned short * )psgram, pssize);
	
	/*Actually finally sending the data*/
	//socket
	int sd =socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

	if(sd<0){
		perror("Could not create socket");
		exit(-1);
	}

	for(int count=0;count<100;count++){
		sendto(sd, datagram, ip->tot_len, 0, (struct sockaddr *)&sin, sizeof(sin));	
		printf("Count #%d was sent successfully.\n", count);	
		sleep(1);
	}
	free(psgram);
	close(sd);
}
	
