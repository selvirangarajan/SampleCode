#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static unsigned char* hMemPool = NULL;
static unsigned int freechunks = 0;
static unsigned char* memnext = NULL;
static unsigned char* memstart = NULL;
static unsigned int chunk_size = 0;
static unsigned int numberofblocks = 0;

void createPool(size_t chunksize, unsigned int numberofchunks)
{
    hMemPool = (unsigned char*)malloc(chunksize*numberofchunks);
    
    if(hMemPool != NULL)
    {    
    	memstart = hMemPool;
    	freechunks = numberofchunks;
    	memnext = hMemPool;
    	chunk_size = chunksize;
    	numberofblocks = numberofchunks;

    	//Initialize memnext for all available chunks
    	for(int i=1;i<numberofblocks;i++)
    	{

           *(unsigned int*)memnext = i;
	   memnext = memnext+chunksize;
   	 }

    	memnext = hMemPool;
     }


}

unsigned char* AddrFromIndex(unsigned int id)
{

       return(memstart+(id*chunk_size));
}


void* allocate()
{

     void* buf = NULL;
     if(freechunks > 0 )
     {
         buf = (void*)memnext;
	 freechunks--;
         if(freechunks > 0)
	 {
         
		 memnext = AddrFromIndex(*(unsigned int*)memnext);
           
	 }
	 else{

            memnext = NULL;
	
	 }
       

     }

     return buf;


}

void* release(unsigned char* buf)
{
    if(memnext == NULL)
    {

        memnext = buf;
	*(unsigned int*)buf = 0;

    }
    else{

	 unsigned int id = *(unsigned int*)memnext;
         memnext = buf;
	 *(unsigned int*)memnext = id;
    }


     freechunks++;


}

void destroyPool()
{
	free((void*)hMemPool);
	hMemPool = NULL;
	freechunks = 0;
	memnext = NULL;
	memstart = NULL;
	chunk_size = 0;
	numberofblocks = 0;

}

main()
{
     createPool(1024,5);
     
     void* buf1 = allocate();
     if(buf1 == NULL)
     printf("buf NULL");
     printf("%x\n",buf1);

     void* buf2 = allocate();
     if(buf2 == NULL)
     printf("buf NULL");
     printf("%x\n",buf2);

     void* buf3 = allocate();
     if(buf3 == NULL)
     printf("buf NULL");
     printf("%x\n",buf3);
     
     void* buf4 = allocate();
     if(buf4 == NULL)
     printf("buf NULL");
     printf("%x\n",buf4);

     void* buf5 = allocate();
     printf("%x\n",buf5);
     
     release(buf5);

     void* buf6 = allocate();
     if(buf6 == NULL)
     printf("buf NULL");
     printf("%x\n",buf6);

     void* buf7 = allocate();
     if(buf7 == NULL)
     printf("buf NULL");
     printf("%x\n",buf7);




     destroyPool();

}
