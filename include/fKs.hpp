/*
 * Mathieu Gravey
 * Copyright (C) 2017 Mathieu Gravey
 * 
 * This program is protected software: you can not redistribute, use, and/or modify it
 * without the explicit accord from the author : Mathieu Gravey, gravey.mathieu@gmail.com
 *
 */
#ifndef fKS_HPP
#define fKS_HPP

#include <iostream>
#include <cmath>
#include <immintrin.h>
#include <limits>
#include <chrono>
#include <algorithm>
#include <numeric>

#define restrict
namespace fKst {

template<typename T>
inline void findKsmallest(const T* data,const unsigned int N,const unsigned short k, T* restrict output){

	std::fill(output,output+k,INFINITY);

	for (int i = 0; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					position--;
			}
			output[position+1]=data[i];
		}
	}

}

template<typename T>
inline void findKsmallest(const T* data,const unsigned int N,const unsigned short k, T* restrict output, unsigned int* restrict positionValue){

	std::fill(output,output+k,INFINITY);
	std::fill(positionValue,positionValue+k,UINT_MAX);

	for (int i = 0; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position]; 
					positionValue[position+1]=positionValue[position]; 
					position--;
			}
			output[position+1]=data[i];
			positionValue[position+1]=i;
		}
	}

}

#if __SSE4_1__
inline void findKsmallest128(const float* data,const unsigned int N,const unsigned short k, float* restrict output){


	std::fill(output,output+k,INFINITY);

    unsigned char ratio=sizeof(__m128)/sizeof(float);

    __m128 bigest=_mm_set1_ps(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m128 dataVector=_mm_loadu_ps(data+i);

		if(!_mm_testc_si128(_mm_set1_epi8(0),_mm_castps_si128(_mm_cmplt_ps(dataVector,bigest))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							position--;
					}
					output[position+1]=data[j];
				}
			}
			bigest=_mm_set1_ps(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					position--;
			}
			output[position+1]=data[i];
		}
	}
}

inline void findKsmallest128(const float* data,const unsigned int N,const unsigned short k, float* restrict output, unsigned int* restrict positionValue){


	std::fill(output,output+k,INFINITY);
	std::fill(positionValue,positionValue+k,UINT_MAX);

    unsigned char ratio=sizeof(__m128)/sizeof(float);

    __m128 bigest=_mm_set1_ps(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m128 dataVector=_mm_loadu_ps(data+i);

		if(!_mm_testc_si128(_mm_set1_epi8(0),_mm_castps_si128(_mm_cmplt_ps(dataVector,bigest))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							positionValue[position+1]=positionValue[position]; 
							position--;
					}
					output[position+1]=data[j];
					positionValue[position+1]=j;
				}
			}
			bigest=_mm_set1_ps(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					positionValue[position+1]=positionValue[position]; 
					position--;
			}
			output[position+1]=data[i];
			positionValue[position+1]=i;
		}
	}
}

inline void findKsmallest128(const double* data,const unsigned int N,const unsigned short k, double* restrict output){


	std::fill(output,output+k,INFINITY);

    unsigned char ratio=sizeof(__m128)/sizeof(double);

    __m128d bigest=_mm_set1_pd(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m128d dataVector=_mm_loadu_pd(data+i);

		if(!_mm_testc_si128(_mm_set1_epi8(0),_mm_castpd_si128(_mm_cmplt_pd(dataVector,bigest))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							position--;
					}
					output[position+1]=data[j];
				}
			}
			bigest=_mm_set1_pd(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					position--;
			}
			output[position+1]=data[i];
		}
	}
}

inline void findKsmallest128(const double* data,const unsigned int N,const unsigned short k, double* restrict output, unsigned int* restrict positionValue){


	std::fill(output,output+k,INFINITY);
	std::fill(positionValue,positionValue+k,UINT_MAX);

    unsigned char ratio=sizeof(__m128)/sizeof(double);

    __m128d bigest=_mm_set1_pd(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m128d dataVector=_mm_loadu_pd(data+i);

		if(!_mm_testc_si128(_mm_set1_epi8(0),_mm_castpd_si128(_mm_cmplt_pd(dataVector,bigest))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							positionValue[position+1]=positionValue[position]; 
							position--;
					}
					output[position+1]=data[j];
					positionValue[position+1]=j;
				}
			}
			bigest=_mm_set1_pd(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					positionValue[position+1]=positionValue[position]; 
					position--;
			}
			output[position+1]=data[i];
			positionValue[position+1]=i;
		}
	}
}


#endif

#if __AVX__

inline void findKsmallest256(const float* data,const unsigned int N,const unsigned short k, float* restrict output){


	std::fill(output,output+k,INFINITY);

    unsigned char ratio=sizeof(__m256)/sizeof(float);

    __m256 bigest=_mm256_set1_ps(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m256 dataVector=_mm256_loadu_ps(data+i);
		if(!_mm256_testc_si256(_mm256_set1_epi8(0),_mm256_castps_si256(_mm256_cmp_ps(dataVector,bigest,_CMP_LT_OQ))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							position--;
					}
					output[position+1]=data[j];
				}
			}
			bigest=_mm256_set1_ps(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					position--;
			}
			output[position+1]=data[i];
		}
	}
}

inline void findKsmallest256(const float* data,const unsigned int N,const unsigned short k, float* restrict output, unsigned int* restrict positionValue){


	std::fill(output,output+k,INFINITY);
	std::fill(positionValue,positionValue+k,UINT_MAX);

    unsigned char ratio=sizeof(__m256)/sizeof(float);

    __m256 bigest=_mm256_set1_ps(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m256 dataVector=_mm256_loadu_ps(data+i);
		if(!_mm256_testc_si256(_mm256_set1_epi8(0),_mm256_castps_si256(_mm256_cmp_ps(dataVector,bigest,_CMP_LT_OQ))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							positionValue[position+1]=positionValue[position]; 
							position--;
					}
					output[position+1]=data[j];
					positionValue[position+1]=j;
				}
			}
			bigest=_mm256_set1_ps(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					positionValue[position+1]=positionValue[position]; 
					position--;
			}
			output[position+1]=data[i];
			positionValue[position+1]=i;
		}
	}
}


inline void findKsmallest256(const double* data,const unsigned int N,const unsigned short k, double* restrict output){


	std::fill(output,output+k,INFINITY);

    unsigned char ratio=sizeof(__m256)/sizeof(double);

    __m256d bigest=_mm256_set1_pd(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m256d dataVector=_mm256_loadu_pd(data+i);
		if(!_mm256_testc_si256(_mm256_set1_epi8(0),_mm256_castpd_si256(_mm256_cmp_pd(dataVector,bigest,_CMP_LT_OQ))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							position--;
					}
					output[position+1]=data[j];
				}
			}
			bigest=_mm256_set1_pd(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					position--;
			}
			output[position+1]=data[i];
		}
	}
}

inline void findKsmallest256(const double* data,const unsigned int N,const unsigned short k, double* restrict output, unsigned int* restrict positionValue){


	std::fill(output,output+k,INFINITY);
	std::fill(positionValue,positionValue+k,UINT_MAX);

    unsigned char ratio=sizeof(__m256)/sizeof(double);

    __m256d bigest=_mm256_set1_pd(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m256d dataVector=_mm256_loadu_pd(data+i);
		if(!_mm256_testc_si256(_mm256_set1_epi8(0),_mm256_castpd_si256(_mm256_cmp_pd(dataVector,bigest,_CMP_LT_OQ))))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							positionValue[position+1]=positionValue[position]; 
							position--;
					}
					output[position+1]=data[j];
					positionValue[position+1]=j;
				}
			}
			bigest=_mm256_set1_pd(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					positionValue[position+1]=positionValue[position]; 
					position--;
			}
			output[position+1]=data[i];
			positionValue[position+1]=i;
		}
	}
}




#endif

#if __AVX512F__

inline void findKsmallest512(const float* data,const unsigned int N,const unsigned short k, float* restrict output){



	std::fill(output,output+k,INFINITY);

    unsigned char ratio=sizeof(__m512)/sizeof(float);

    __m512 bigest=_mm512_set1_ps(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m512 dataVector=_mm512_loadu_ps(data+i);	
		if(!_mm512_kortestz(_mm512_int2mask(0),_mm512_cmp_ps_mask(dataVector,bigest,_CMP_LT_OQ)))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							position--;
					}
					output[position+1]=data[j];
				}
			}
			bigest=_mm512_set1_ps(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					position--;
			}
			output[position+1]=data[i];
		}
	}
}

inline void findKsmallest512(const float* data,const unsigned int N,const unsigned short k, float* restrict output, unsigned int* restrict positionValue){

	std::fill(output,output+k,INFINITY);
	std::fill(positionValue,positionValue+k,UINT_MAX);

    unsigned char ratio=sizeof(__m512)/sizeof(float);

    __m512 bigest=_mm512_set1_ps(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m512 dataVector=_mm512_loadu_ps(data+i);	
		if(!_mm512_kortestz(_mm512_int2mask(0),_mm512_cmp_ps_mask(dataVector,bigest,_CMP_LT_OQ)))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							positionValue[position+1]=positionValue[position]; 
							position--;
					}
					output[position+1]=data[j];
					positionValue[position+1]=j;
				}
			}
			bigest=_mm512_set1_ps(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					positionValue[position+1]=positionValue[position]; 
					position--;
			}
			output[position+1]=data[i];
			positionValue[position+1]=i;
		}
	}
}

inline void findKsmallest512(const double* data,const unsigned int N,const unsigned short k, double* restrict output){

	std::fill(output,output+k,INFINITY);

    unsigned char ratio=sizeof(__m512)/sizeof(double);

    __m512d bigest=_mm512_set1_pd(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m512d dataVector=_mm512_loadu_pd(data+i);	
		if(!_mm512_kortestz(_mm512_int2mask(0),_mm512_cmp_pd_mask(dataVector,bigest,_CMP_LT_OQ)))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							position--;
					}
					output[position+1]=data[j];
				}
			}
			bigest=_mm512_set1_pd(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					position--;
			}
			output[position+1]=data[i];
		}
	}
}

inline void findKsmallest512(const double* data,const unsigned int N,const unsigned short k, double* restrict output, unsigned int* restrict positionValue){

	std::fill(output,output+k,INFINITY);
	std::fill(positionValue,positionValue+k,UINT_MAX);

    unsigned char ratio=sizeof(__m512)/sizeof(double);

    __m512d bigest=_mm512_set1_pd(output[k-1]);
	for (int i = 0; i < ( (N-1)/ratio)*ratio; i+=ratio)
	{
		__m512d dataVector=_mm512_loadu_pd(data+i);	
		if(!_mm512_kortestz(_mm512_int2mask(0),_mm512_cmp_pd_mask(dataVector,bigest,_CMP_LT_OQ)))
		{
			for (int j = i; j < i+ratio; ++j)
			{
				if(data[j]<output[k-1]) //then change
				{
					short position=k-2;
					while ((data[j]<output[position]) && (position>-1) ){
							output[position+1]=output[position];
							positionValue[position+1]=positionValue[position]; 
							position--;
					}
					output[position+1]=data[j];
					positionValue[position+1]=j;
				}
			}
			bigest=_mm512_set1_pd(output[k-1]);
		}
		
	}

	for (int i = ( N/ratio)*ratio; i < N; ++i)
	{
		if(data[i]<output[k-1]) //then change
		{
			short position=k-2;
			while ((data[i]<output[position]) && (position>-1) ){
					output[position+1]=output[position];
					positionValue[position+1]=positionValue[position]; 
					position--;
			}
			output[position+1]=data[i];
			positionValue[position+1]=i;
		}
	}
}

#endif


template<typename T>
inline void findKSmallest(const T* data,const unsigned int N,const unsigned short k, T* restrict output){
#if __AVX512F__
	#if __INTEL_COMPILER
	if(_may_i_use_cpu_feature(_FEATURE_AVX512F))
	#endif
	{
		findKsmallest512(data, N, k, output);
		return;
	}
#endif

#if __AVX__
	#if __INTEL_COMPILER
	if(_may_i_use_cpu_feature(_FEATURE_AVX))
	#endif
	{
		findKsmallest256(data, N, k, output);
		return;
	}
#endif

#if __SSE4_1__
	#if __INTEL_COMPILER
	if(_may_i_use_cpu_feature(_FEATURE_SSE4_1))
	#endif
	{
		findKsmallest128(data, N, k, output);
		return;
	}
#endif

	findKsmallest<T>(data, N, k, output);
	return;

}
template<typename T>
inline void findKSmallest(const T* data,const unsigned int N,const unsigned short k, T* restrict output, unsigned int* restrict positionValue){
#if __AVX512F__
	#if __INTEL_COMPILER
	if(_may_i_use_cpu_feature(_FEATURE_AVX512F))
	#endif
	{
		findKsmallest512(data, N, k, output, positionValue);
		return;
	}
#endif

#if __AVX__
	#if __INTEL_COMPILER
	if(_may_i_use_cpu_feature(_FEATURE_AVX))
	#endif
	{
		findKsmallest256(data, N, k, output, positionValue);
		return;
	}
#endif

#if __SSE4_1__
	#if __INTEL_COMPILER
	if(_may_i_use_cpu_feature(_FEATURE_SSE4_1))
	#endif
	{
		findKsmallest128(data, N, k, output, positionValue);
		return;
	}
#endif

	findKsmallest<T>(data, N, k, output, positionValue);
	return;

}

}
#endif
