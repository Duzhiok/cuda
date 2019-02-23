#include <stdio.h>
#include <iostream>
#include <cuda_runtime.h> // For the CUDA runtime routines (prefixed with "cuda_")
#include <device_launch_parameters.h>
#include <time.h> 


#define DATA_SIZE 9  
#define THREAD_NUM 5  
using namespace std;
int anData[DATA_SIZE];

//Generate random data
void GenerateNumber(int *pnNumber, int nSize)
{

	for (int i = 0; i < nSize; i++)  pnNumber[i] = rand() % 10;
}

//Global function to calculate square kernel: call on a host computer, performed on the equipment
__global__ static void sumofSquares(int *pnNum, int* pnResult, clock_t *pclock_ttime)
{
	int tid = threadIdx.x;
	int nSum = 0;
	int i;

	int nSize = 0;


	if (DATA_SIZE % THREAD_NUM) nSize = DATA_SIZE / THREAD_NUM + 1;
	else nSize = DATA_SIZE / THREAD_NUM; //nSize, One thread to calculate the amount of data



										 //start counting
	clock_t clock_tstart;
	if (tid == 0)  clock_tstart = clock(); 

	for (i = nSize * tid; i < (tid + 1) *nSize; i++)
	{
		nSum += (pnNum[i] * pnNum[i]);

	}
	pnResult[tid] = nSum;
	//end
	if (tid == 0) *pclock_ttime = clock() - clock_tstart; //Time with a thread
}

int main(void)
{
	GenerateNumber(anData, DATA_SIZE); //Generate random data
	int *pnGpuData, *pnResult;
	clock_t *pclock_ttime;//time storage
	int *nSummat;
	cudaMallocHost((void**)&nSummat, sizeof(int) * THREAD_NUM);
	cudaMalloc((void**)&pnGpuData, sizeof(int) * DATA_SIZE);
	cudaMalloc((void**)&pnResult, sizeof(int) * THREAD_NUM);
	cudaMalloc((void**)&pclock_ttime, sizeof(clock_t));

	cudaMemcpy(pnGpuData, anData, sizeof(int)*DATA_SIZE, cudaMemcpyHostToDevice);



	sumofSquares <<< 1, THREAD_NUM, 0 >>>(pnGpuData, pnResult, pclock_ttime);

	cudaMemcpy(nSummat, pnResult, sizeof(int) * THREAD_NUM, cudaMemcpyDeviceToHost);
	clock_t pclocksum;
	cudaMemcpy(&pclocksum, pclock_ttime, sizeof(clock_t), cudaMemcpyDeviceToHost);

	//operation of the CPU
	int finishsum = 0;
	for (size_t i = 0; i < THREAD_NUM; i++)
	{
		finishsum = finishsum + nSummat[i];

	}

	printf("SuM = %d    Time = %d\n", finishsum, pclocksum);
	cudaFree(pnGpuData);
	cudaFree(pnResult);
	cudaFree(pclock_ttime);
	system("pause");
	//return 0;

}