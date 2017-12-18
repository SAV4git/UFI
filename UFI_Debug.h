#ifndef UFI_DEBAG_H
#define UFI_DEBAG_H

class UFI_Debug
{
private:
	UFI_Debug(const UFI_Debug& rhs);
	UFI_Debug& operator=(const UFI_Debug& rhs);
	
	struct sysinfo {
		long uptime;             /* Seconds since boot */
		unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
		unsigned long totalram;  /* Total usable main memory size */
		unsigned long freeram;   /* Available memory size */
		unsigned long sharedram; /* Amount of shared memory */
		unsigned long bufferram; /* Memory used by buffers */
		unsigned long totalswap; /* Total swap space size */
		unsigned long freeswap;  /* Swap space still available */
		unsigned short procs;    /* Number of current processes */
		char _f[22];             /* Pads structure to 64 bytes */
	};
	
	sysinfo memInfo;
	
	//sysinfo (&memInfo);

	/*
	long long totalVirtualMem = memInfo.totalram;
	//Add other values in next statement to avoid int overflow on right hand side...
	totalVirtualMem += memInfo.totalswap;
	totalVirtualMem *= memInfo.mem_unit;
	
	long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
	//Add other values in next statement to avoid int overflow on right hand side...
	virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
	virtualMemUsed *= memInfo.mem_unit;s
	*/
	int parseLine(char*);
	
public:
	UFI_Debug();
	~UFI_Debug();
	int getMemSize_kB();
	void PrintRendObjParam(UFI_RenderObject_t*);
	void PrintAllRendObjParam();
};

#endif // UFI_DEBAG_H
