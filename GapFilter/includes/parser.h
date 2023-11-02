typedef int32_t bpf_int32;
typedef u_int32_t bpf_u_int32;
typedef u_int16_t u_short;
typedef u_int32_t u_int32;
typedef u_int16_t u_int16;
typedef u_int8_t u_int8;

const bpf_u_int32 have_ether_hdr = 0x00000001;
const bpf_u_int32 no_ether_hdr = 0x00000065; 

struct pcap_file_header
{
	bpf_u_int32 magic;
	u_short version_major; 
	u_short version_minor; 
	bpf_int32 thiszone;
	bpf_u_int32 sigfigs; 
	bpf_u_int32 snaplen;
	bpf_u_int32 linktype; 
};

struct time_val
{
	int tv_sec;
	int tv_usec; 
};

struct pcap_pkthdr
{
	struct time_val ts;
	bpf_u_int32 caplen;
	bpf_u_int32 len;
};

typedef struct FramHeader_t
{
	u_int8 DstMAC[6];
	u_int8 SrcMAC[6]; 
	u_short FrameType;
} FramHeader_t;

typedef struct VirtualLAN_t
{ 
	u_int32 padding;
} VirtualLAN_t;

typedef struct IPHeader_t
{
	u_int8 Ver_HLen;       
	u_int8 TOS;  
	u_int16 TotalLen;
	u_int16 ID;
	u_int16 Flag_Segment;
	u_int8 TTL; 
	u_int8 Protocol;
	u_int16 Checksum; 
	u_int32 SrcIP;
	u_int32 DstIP;
} IPHeader_t;

typedef struct TCPHeader_t
{
	u_int16 SrcPort;
	u_int16 DstPort;
	u_int32 SeqNO;
	u_int32 AckNO;
	u_int8 HeaderLen;
	u_int8 Flags;
	u_int16 Window;
	u_int16 Checksum;
	u_int16 UrgentPointer;
}TCPHeader_t;

typedef struct UDPHeader_s
{
	u_int16_t SrcPort;
	u_int16_t DstPort;
	u_int16_t len;  
	u_int16_t checkSum;
}UDPHeader_t;

typedef struct Quintet
{
	double timestamp;
	u_int32_t SrcIP;
	u_int32_t DstIP;
	u_int32_t SeqNO;
	u_int32_t TCP_Length;
	u_int8_t TCP_Flags;
    u_int16_t IP_ID;
	u_int16_t SrcPort;
	u_int16_t DstPort; 
	u_int8_t Protocol;
}Quintet_t;