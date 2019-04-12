#ifndef TESTO_H
#define TESTO_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/udp.h>
#include<arpa/inet.h>
#include<unistd.h>
//header structs
//we avoid having to rewrite the type for future calculation
//and conversions
typedef struct iphdr iph;
typedef struct udphdr udph;
//this will help us with udp header
typedef struct {
	u_int32_t saddr;	//source address
	u_int32_t daddr;	//destination address
	u_int8_t filler;
	u_int8_t protocol;
	u_int16_t len;		//length of header
}ps_hdr;
//DNS header
typedef struct{
	unsigned short id; 		//header ID
	unsigned short flags;	//special flags for DNS
	unsigned short qcount;	//question count
	unsigned short anscount;//answer count
	unsigned short auth;	//for authroization
	unsigned short add;		//addiitonals 
	
}dns_hdr;
// DNS query
typedef struct{
	unsigned short qtype;	//
	unsigned short qclass;	//
}query;

#endif
