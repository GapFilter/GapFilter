#pragma pack(1)
#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <netinet/in.h>
#include <string>
#include "Realtime/includes/parser.h"
using namespace std;

double ftime = -1;
int main(int argc, char* argv[])
{
	struct pcap_file_header *file_header = NULL;
	struct pcap_pkthdr *pkt_header = NULL;
	FramHeader_t *eth_header = NULL;
	IPHeader_t *ip_header = NULL;
	TCPHeader_t *tcp_header = NULL;
	UDPHeader_t *udp_header = NULL;
	Quintet_t *quintet = NULL;

	file_header =  (struct pcap_file_header *)malloc(sizeof(struct pcap_file_header));
	pkt_header  = (struct pcap_pkthdr *)malloc(sizeof(struct pcap_pkthdr));
	eth_header = (FramHeader_t *)malloc(sizeof(FramHeader_t));
	ip_header = (IPHeader_t *)malloc(sizeof(IPHeader_t));
	tcp_header = (TCPHeader_t *)malloc(sizeof(TCPHeader_t));
	udp_header = (UDPHeader_t *)malloc(sizeof(UDPHeader_t));
	quintet = (Quintet_t *)malloc(sizeof(Quintet_t));

	double tv_usec_s = 0, tv_usec_rs = 0;
	bool have_ether_hdr_flag = true;
	bool haveVirtualLAN = false;
	bool haveTimeFile = false;
	string path, outpath, timepath;

	if(argc == 4){
		path = argv[1], outpath = argv[2], timepath = argv[3];
		haveTimeFile = true;
	}
	else if(argc == 3){
		path = argv[1], outpath = argv[2];
	}
	else{
		printf("parser.cpp need 2or3 parameters: pcap source file, target output file, (times source file)\n");
		return 0;
	}

	FILE* pFile = fopen(path.c_str(), "rb");
	if( pFile == 0){
		printf( "parser: pcap source file error\n");
		return 0;
	}
	FILE *output = fopen(outpath.c_str(),"wb");
	if(output == 0){
		printf( "parser.cpp: output file error\n");
		return 0;
	}

	FILE* tFile;
	int timestmap_cnt;
	if(haveTimeFile){
		tFile = fopen(timepath.c_str(), "rb");
		if(tFile == 0){
			printf("parser.cpp: times file error\n");;
			return 0;
		}
		timestmap_cnt = 0;
	}

	printf("begin reading\n");
	long long int pkt_offset = 0;

	memset(file_header, 0, sizeof(struct pcap_file_header));
	if(fread(file_header, 24, 1, pFile) != 1)
	{
		printf("can not read file_header\n");
		return 0;
	}

	if(file_header->linktype == have_ether_hdr){
		have_ether_hdr_flag = true;
		printf("file_header->linktype=%u\n",file_header->linktype);
	}
	else 
		have_ether_hdr_flag = false;
	if(file_header->magic == 0xA1B2C3D4u){
		tv_usec_s = 1e-6;
		tv_usec_rs = 1e6;
	}
	else{
		tv_usec_s = 1e-9;
		tv_usec_s = 1e9;
	}

	pkt_offset += 24;
	int i = 0;
	int j =0;
	int k = 0;
	int l = 0;
	u_short ftype = 0;
	u_int8 ip_ver =0;
	long tcp_cnt = 0, udp_cnt = 0;

	while(fseek(pFile, pkt_offset, SEEK_SET) == 0)
	{
		i++;
		memset(pkt_header, 0, sizeof(struct pcap_pkthdr));
		memset(quintet,0,sizeof(struct Quintet));
		if(fread(pkt_header, 16, 1, pFile) != 1)
		{
			printf("%d: can not read pkt_header\n", i);
			break;
		}
		pkt_offset += 16 + pkt_header->caplen;

		if(have_ether_hdr_flag){
			memset(eth_header, 0, sizeof(FramHeader_t));
			if(fread(eth_header, sizeof(FramHeader_t), 1, pFile) != 1){
				printf("%d: can not read eth_header\n", i);
				break;
			}
			if(haveVirtualLAN){
				if(fread(eth_header, 4, 1, pFile) != 1){
					printf("%d: can not read eth_header\n", i);
					break;
				}
			}
		}

		memset(ip_header, 0, sizeof(IPHeader_t));
		if(fread(ip_header, sizeof(IPHeader_t), 1, pFile) != 1)
		{
			printf("%d: can not read ip_header\n", i);
			break;
		}
		
		ip_ver = (ip_header->Ver_HLen>>4)&(0b00001111);
		if (ip_ver == 4)
		{
			j++;
			double timestamp = 0;

			if(haveTimeFile){
				while(timestmap_cnt < i){
					if(fscanf(tFile, "%lf\n", &timestamp) == EOF){
						printf("something wrong with the times file\n");
						exit(1);
					}
					timestmap_cnt++;
				}
			}
			else{
				timestamp = *((uint32_t*)(&((pkt_header->ts).tv_sec))) 
					+ (*((uint32_t*)(&((pkt_header->ts).tv_usec)))) * tv_usec_s;
			}

			quintet->timestamp = timestamp;
			quintet->SrcIP = ntohl(ip_header->SrcIP);
			quintet->DstIP = ntohl(ip_header->DstIP);
			quintet->IP_ID = ntohs(ip_header->ID);

			if(ip_header->Protocol == 0x06){ //TCP
				memset(tcp_header, 0, sizeof(TCPHeader_t));
				if(fread(tcp_header, sizeof(TCPHeader_t), 1, pFile) == 1)
				{
					tcp_cnt++;
					quintet->SrcPort = ntohs(tcp_header->SrcPort);
					quintet->DstPort = ntohs(tcp_header->DstPort);
					quintet->SeqNO = ntohl(tcp_header->SeqNO);
					quintet->TCP_Flags = tcp_header->Flags;
					quintet->Protocol = 0x06;
					quintet->TCP_Length = ntohs(ip_header->TotalLen) - sizeof(IPHeader_t) - sizeof(TCPHeader_t);
					
					if (ftime < 0)
						ftime = quintet->timestamp;
					fprintf(output, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
					((uint8_t*)&quintet->SrcIP)[0],
					((uint8_t*)&quintet->SrcIP)[1],
					((uint8_t*)&quintet->SrcIP)[2],
					((uint8_t*)&quintet->SrcIP)[3],
					((uint8_t*)&quintet->DstIP)[0],
					((uint8_t*)&quintet->DstIP)[1],
					((uint8_t*)&quintet->DstIP)[2],
					((uint8_t*)&quintet->DstIP)[3],
					((uint8_t*)&quintet->SrcPort)[0],
					((uint8_t*)&quintet->SrcPort)[1],
					((uint8_t*)&quintet->DstPort)[0],
					((uint8_t*)&quintet->DstPort)[1],
					((uint8_t*)&quintet->Protocol)[0],
					quintet->IP_ID,
					uint32_t((quintet->timestamp - ftime) * tv_usec_rs)
					);
				}
			}
			else if(ip_header->Protocol == 0x11){ //UDP
				memset(udp_header, 0, sizeof(UDPHeader_t));
				if(fread(udp_header, sizeof(UDPHeader_t), 1, pFile) == 1){
					udp_cnt++;
					quintet->SrcPort = udp_header->SrcPort;
					quintet->DstPort = udp_header->DstPort;
					quintet->Protocol = 0x11;

					if (ftime < 0)
						ftime = quintet->timestamp;
					fprintf(output, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
					((uint8_t*)&quintet->SrcIP)[0],
					((uint8_t*)&quintet->SrcIP)[1],
					((uint8_t*)&quintet->SrcIP)[2],
					((uint8_t*)&quintet->SrcIP)[3],
					((uint8_t*)&quintet->DstIP)[0],
					((uint8_t*)&quintet->DstIP)[1],
					((uint8_t*)&quintet->DstIP)[2],
					((uint8_t*)&quintet->DstIP)[3],
					((uint8_t*)&quintet->SrcPort)[0],
					((uint8_t*)&quintet->SrcPort)[1],
					((uint8_t*)&quintet->DstPort)[0],
					((uint8_t*)&quintet->DstPort)[1],
					((uint8_t*)&quintet->Protocol)[0],
					quintet->IP_ID,
					uint32_t((quintet->timestamp - ftime) * tv_usec_rs)
					);
				}
			}
		}
		else if (ip_ver == 6) k++;
		else l++;
	}
	fclose(pFile);
	printf("Finish!\n");
	printf("ipv4 pkts: %d\n""ipv6 pkts: %d\n",j,k);
	printf("non-IP pkts: %d\n",l);
	printf("IPv4-TCP pkts: %ld\n", tcp_cnt);
	printf("IPv4-UDP pkts: %ld\n", udp_cnt);
	printf("The output file should be %ld bytes\n", tcp_cnt * 30);
	fclose(output);
	return 0;
}
