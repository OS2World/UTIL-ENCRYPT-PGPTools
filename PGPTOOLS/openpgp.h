/*																				*
 * openpgp.h -- OpenPGP SDK								 			*
 *																				*
 * Part of the E-Secure OpenPGP Toolkit							*
 *																				*
 * William H. Geiger III												*
 * Geiger Consulting														*
 * whgiii@openpgp.net													*
 *																				*
 * 00 -- Pre-Alpha Limited Release					15 Aug 1998	*
 *																				*
 * openpgp.h contains the #define's									*
 * 																			*
 */



/* OpenPGP Definitions */

/* File I/O Definitions */

#define MAX_BUFFER  102400  /* Max internal file read buffer     */
#define MAX_PATH    256     /* Maximum file path                 */

/* Memory Definitions */

#define PK_MPI_MAX    4      /* Max number of MPI's in Public Key */
#define SIG_MPI_MAX   2      /* Max number of MPI's in Signature  */
#define SK_MPI_MAX    4      /* Max number of MPI's in Secret Key */

/* Ascii-Armor Definfitions */

#define CRC24_INIT 0xb704ce
#define CRC24_POLY 0x1864cfb

/* Public Key Algorithms */

#define P_RSA         1
#define P_RSA_ENC     2
#define P_RSA_SIGN    3
#define P_EL         16
#define P_DSA        17
#define P_EC         18      /* Reserved */
#define P_ECDSA      19      /* Reserved */
#define P_EL_BOTH    20      /* Reserved */
#define P_DH         21      /* Reserved */

/* Hash Algorithms */

#define H_MD5        1
#define H_SHA1       2
#define H_RIPMED     3
#define H_HAVAL      4
#define H_MD2        5
#define H_TIGER      6

/* Semetric Key Algorithms */

#define S_TEXT       0
#define S_IDEA       1
#define S_CAST       3
#define S_3DES       2
#define S_BLOW       4
#define S_SAFER      5
#define S_DES_SK     6


/* PGP Packet Versions */

#define V_2          2
#define V_3          3
#define V_4          4

/* PGP Compresion Algorithms */

#define Z_NONE       0
#define Z_ZIP        1
#define Z_ZLIB       2

	struct hash_asn1{
		unsigned char *algo;
		unsigned char *odi;
		unsigned char *prefix;
	};


#define OP_MD2    { "\x2a\x86\x48\x86\xf7\x0d\x02\x02","1.2.840.113549.2.2","\x30\x20\x30\x0c\x06\x08\x2a\x86\x48\x86\xf7\x0d\x02\x02\x05\x00\x04\x10"}
#define OP_MD5    {"\x2a\x86\x48\x86\xf7\x0d\x02\x05","1.2.840.113549.2.5","\x30\x20\x30\x0c\x06\x08\x2a\x86\x48\x86\xf7\x0d\x02\x05\x05\x00\x04\x10"}
#define OP_RIPEMD {"\x2b\x24\x03\x02\x01","1.3.36.3.2.1","\x30\x21\x30\x09\x06\x05\x2b\x0e\x03\x02\x02\x1a\x05\x00\x04\x14"}
#define OP_SHA1   {"\x2b\x0e\03\02\1a","1.3.14.3.2.26","\x30\x21\x30\x09\x06\x05\x2b\x0e\x03\x02\x1a\x05\x00\x04\x14"}

#define PTEXT00 "Reserved"
#define PTEXT01 "Pubkey Encrypted Session Key"
#define PTEXT02 "Signature"
#define PTEXT03 "Symetric Encrypted Session Key"
#define PTEXT04 "OnePass Signature"
#define PTEXT05 "Secret Key"
#define PTEXT06 "Public Key"
#define PTEXT07 "Secret Sub-Key"
#define PTEXT08 "Compression Packet"
#define PTEXT09 "Symetric Encrypted Packet"
#define PTEXT10 "Marker Packet"
#define PTEXT11 "Literal Packet"
#define PTEXT12 "Trust Packet"
#define PTEXT13 "UserID Packet"
#define PTEXT14 "Public Sub-Key"
#define PTEXT15 "Reserved"

	static struct hash_asn1  hash[4] ={ OP_MD2, OP_MD5, OP_RIPEMD, OP_SHA1};

	static char *ptext[16] = {PTEXT00,PTEXT01,PTEXT02,PTEXT03,PTEXT04,PTEXT05, \
										PTEXT06,PTEXT07,PTEXT08,PTEXT09,PTEXT10,PTEXT11, \
										PTEXT12,PTEXT13,PTEXT14,PTEXT15};

	typedef struct mpi_packet{
		int packet;					 /* packet # for mem functions */
		unsigned long int size;	 /* size of MPI data */
		unsigned long int max;	 /* allocated size of data */
		unsigned char *data;		 /* raw MPI data */
	}OP_MPI;

	typedef struct sig_sub{
		int packet;		/* packet # for mem functions */
		int type;		/* type of sub signature */
		int size;		/* size of sub sig in data */
		int max;			/* allocated size of data */
		char *data;		/* raw sub_sig data */
	}OP_SIGSUB;

	typedef struct pgp_buffer{
		int	packet;	/* packet # for mem functions */
		int	size;		/* size of data */
		int	pnt;		
		int	fpnt;
		unsigned char *input; /* raw data */
	}OP_BUFFER;

	typedef struct pgp_packet{
		int packet;		/* packet # for mem functions */
		int type;      /* packet type */
		int size;      /* packet size */
		int pnt;       /* start pointer */
		int pnt2;      /* start pointer + size of ctb */
		int flags;     /* flags 0=None, 1=unknown size */
	}OP_PACKET;

/* Tag 1 */
	typedef struct p_enc_ses_packet{
		int packet;							/* packet # for mem functions */
		int version;
		unsigned char id[9];
		int algo;
		OP_MPI **mpi;
	}OP_PES;

/* Tag 2 */
	typedef struct sig_packet{
		int packet;							/* packet # for mem functions */
		int link;
		int version;
		int len;
		int type;
		unsigned char time[5];        /* Version 3 Sigs only */
		unsigned char id[9];          /* Version 3 Sigs only */
		int algo;
		int hash;
		unsigned char check[3];
		int first;
		int mpi_cnt;
		int mpi_aloc;
		OP_MPI **mpi;
		int sig_hsub_sz;              /* Version 4 Sigs only */
		int sig_hsub_cnt;             /* Version 4 Sigs only */
		OP_SIGSUB **sig_hsub;         /* Version 4 Sigs only */
		int sig_usub_sz;              /* Version 4 Sigs only */
		int sig_usub_cnt;             /* Version 4 Sigs only */
		OP_SIGSUB **sig_usub;         /* Version 4 Sigs only */
	}OP_SIG;

/* Tag 3 */
	typedef struct s_enc_ses_packet{
   	int packet;
   	int version;
   	int algo;
   	int s2k;
   	int size;
   	unsigned char *data;
  	}OP_SES;

/* Tag 4 */
	typedef struct onepass_packet{
		int packet;
		int version;
		int type;
		int hash;
		int algo;
		unsigned char id[9];
		int flag;
	}OP_ONEPASS;

/* Tag 6 & 14 */
	typedef struct pub_packet{
		int packet;
		int version;
		unsigned char time[5];
		unsigned char id[9];
		int finger_len;
		unsigned char finger[21];
		int valid;
		int algo;
		int mpi_cnt;
		int mpi_aloc;
		OP_MPI **mpi;
	}OP_PUB;

/* Tag 5 & 7 */
	typedef struct sec_packet{
		int packet;
		struct pub_packet *pub;
		int s2k;
		int algo;
		unsigned char *s2k_spec;
		int iv_len;
		unsigned char *iv;
		OP_MPI **mpi;
		int check;
	}OP_SEC;

/* Tag 8 */
	typedef struct comp_packet{
		int packet;
		int algo;
		int size;
		unsigned char *data;
	}OP_COMP;

/* Tag 9 */
	typedef struct s_crypt_packet{
		int packet;
		int size;
		unsigned *data;
	}OP_SCRYPT;

/* Tag 10 */
	typedef struct marker_packet{
		int packet;
		unsigned char data[4];
	}OP_MARKER;

/* Tag 11 */
	typedef struct literal_packet{
		int packet;
		int format;
		int f_len;
		unsigned char *filename;
		unsigned char time[5];
		int size;
		unsigned char *data;
	}OP_LIT;

/* Tag 12 */
	typedef struct trust_packet{
		int packet;
		int type;
		int link;
		int trust;
	}OP_TRUST;

/* Tag 13 */
	typedef struct userid_packet{
		int packet;
		int link;
		int max;
		int size;
		unsigned char *data;
	}OP_UID;
	
	/* UserID with Signatures */
	typedef struct s_userid{
		int packet;		 /* packet # for mem functions */
		char keyid[9];	 /* Public KeyID that UID belongs to */
		int s_count;	 /* # of Signatures */
		int s_max;		 /* # of OP_SIG's Allocated */
		OP_UID *uid;	 /* UserID structure */
		OP_SIG *sig;	 /* Array of OP_SIG's */
	}OP_SUID;

	/* Public Key with Self Signature(s) */
	typedef struct s_pubkey{
		int packet;					/* packet # for mem functions */
		int sig_cnt;				/* # of OP_SIG structs */
		int sig_max;				/*	# of allocated OP_SIG structs */
		OP_PUB pub;					/* OP_PUB struct */
		OP_SIG sig;					/* Array of OP_SIG structs */
	}OP_SPUB;

	typedef struct pubkey{
		int packet;					/* packet # for mem functions */
		int pub_cnt;				/* # of OP_PUB structs */
		int pub_max;				/* # of allocated OP_PUB structs */
		int sig_cnt;				/* # of OP_SIG structs */
		int sig_max;				/* # of allocated OP_SIG structs */
		int uid_cnt;				/* # of OP_UID structs */
		int uid_max;				/* # of allocated OP_UID structs */
		int trust_cnt;				/* # of OP_TRUST structs */
		int trust_max;				/* # of allocated OP_Trust structs */
		OP_SPUB *spub;				/* Array of OP_SPUB structs */
		OP_SUID *suid;				/* Array of OP_SUID structs */
		OP_TRUST *trust;			/* Array of OP_TRUST structs */
	}OP_PUBKEY;

	typedef struct pubkey_raw{
		int packet;					/* packet # for mem functions */
		int size;					/* size of data */
		int max;						/* allocated size of data */
		int trust;					/* flag */
		int strip;					/* flag */
		int point;					
		int htype;					/* hash type */
		int hsize;					/* size of hash */
		unsigned char hash[21]; /* Hash of data */
		OP_PUB *pub;				/* OP_PUB struct */
		char *data;					/* raw public key data */
		}OP_PUBRAW;

int ctb(OP_BUFFER *, OP_PACKET *);
int mpi(OP_BUFFER *, unsigned char *, OP_MPI *, int);
int ps_crypt(void);
int sig(OP_BUFFER *, OP_PACKET *, OP_SIG *,int);
int sig_sub(OP_BUFFER *, unsigned char *, int , OP_SIG *, OP_SIGSUB **, int);
int ss_crypt(void);
int onepass(void);
int seckey(void);
int pubkey(OP_BUFFER *, OP_PACKET *, OP_PUB *,int);
int s_subkey(void);
int compress(void);
int s_crypt(void);
int marker(void);
int literal(void);
int trust(OP_BUFFER *, OP_PACKET *, OP_TRUST *);
int userid(OP_BUFFER *, OP_PACKET *, OP_UID *);
int op_init(void **, int);
int op_wipe(void **);
int op_free(void **);
int op_dearmor(int, unsigned char *, unsigned char *);
int op_armor(unsigned char *, unsigned char *);
int op_crc24(int, unsigned char *, int);
/*1st int: trust flag, 2nd int: strip sigs */
int pubraw(OP_BUFFER *, OP_PACKET *, OP_PUBRAW *, OP_SIG *, int, int);
int op_pubkey(OP_BUFFER *, OP_PACKET *, OP_PUBKEY *);